#ifndef BTREE_H_TT9U7QXW
#define BTREE_H_TT9U7QXW

#include "hfs.h"
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class HFSFile;

class BTree
{
public:
  BTree(HFSFile* file);

public:
  bool node_in_use(uint32_t no);

protected:
  BTHeaderRec m_header_record;

  HFSFile*    m_file;

  uint32_t    m_blocks_per_node;
  uint32_t    m_node_size;
};

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#endif