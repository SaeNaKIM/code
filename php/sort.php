#!/usr/local/php4/bin/php -q
<?
   $b = array("��â��", "�ڱ��", "�����", "��â��");
   $a = array("bbb", "cccc", "aaa");
   sort($a);
   sort($b);
   for($i=0; $i<4; $i++) print $a[$i];
   for($i=0; $i<4; $i++) print $b[$i];
?>
