#ifndef YAFTL_H
#define YAFTL_H

#include "VFLBase.h"

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
//
//
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
/*
YAFTL_CXT = Struct("YAFTL_CXT",
    String("version", 4),
    ULInt32("unknCalculatedValue0"),
    ULInt32("totalPages"),
    ULInt32("latestUserBlock"),
    ULInt32("cxt_unkn0_usn"),
    ULInt32("latestIndexBlock"),
    ULInt32("maxIndexUsn"),
    ULInt32("blockStatsField4"),
    ULInt32("blockStatsField10"),
    ULInt32("numAllocatedBlocks"),
    ULInt32("numIAllocatedBlocks"),
    ULInt32("unk184_0xA"),
    Array(10, ULInt32("cxt_unkn1")),
    ULInt32("field_58"),
    ULInt16("tocArrayLength"),
    ULInt16("tocPagesPerBlock"),
    ULInt16("tocEntriesPerPage"),
 
    ULInt16("unkn_0x2A"),
    ULInt16("userPagesPerBlock"),
    ULInt16("unk64"),
    Array(11, ULInt32("cxt_unkn2")),
    ULInt8("unk188_0x63"),
)
*/

// 
// TODO REMARK 
// Check the difference between python code and original C code
//
struct YAFTLContext
{
    char     version[4];
    uint32_t unknCalculatedValue0;
    uint32_t totalPages;
    uint32_t latestUserBlock;
    uint32_t cxt_unkn0_usn;
    uint32_t latestIndexBlock;
    uint32_t maxIndexUsn;
    uint32_t blockStatsField4;
    uint32_t blockStatsField10;
    uint32_t numAllocatedBlocks;
    uint32_t numIAllocatedBlocks;
    uint32_t unk184_0xA;
    uint32_t cxt_unkn1[10];
    uint32_t field_58;
    uint16_t tocArrayLength;
    uint16_t tocPagesPerBlock;
    uint16_t tocEntriesPerPage;
    uint16_t unkn_0x2A;
    uint16_t userPagesPerBlock;
    uint16_t unk64;
    uint32_t cxt_unkn2[11];
    uint8_t  unk188_0x63;
};

struct TOCStruct
{
    uint32_t indexPage;
    uint16_t cacheNum;
    uint16_t TOCUnkMember2;
};

struct BlockStates
{
    uint32_t numAllocated;   // 00
    uint32_t numAvailable;   // 04
    uint32_t numValidDPages; // 08
    uint32_t numIAllocated;  // 0C
    uint32_t numIAvailable;  // 10
    uint32_t numValidIPages; // 14
    uint32_t numFree;        // 18
    uint32_t field_1C;       // 1C
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
//
//
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
class YAFTL
{
public:
    YAFTL(VFLBase* vsvfl);

private:
    map<uint32_t, uint32_t> _lpn2vpn;

    VFLBase* _vfl;
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
//
//
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
#endif
