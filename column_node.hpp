#ifndef column_node_hpp
#define column_node_hpp
#include "node.hpp"

class ColumnNode : public Node {

public:
  ColumnNode(int row,int label);
  ColumnNode();

  void setSize(int);
  int getSize();
  void incSize();
  void decSize();
  int size;

  

};

#endif 
