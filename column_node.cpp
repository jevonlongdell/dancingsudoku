#include "column_node.hpp"
//#include <iostream>

ColumnNode::ColumnNode(int row, int lbl):Node(row,lbl,NULL)
{
  setColumn(NULL);
};
ColumnNode::ColumnNode():Node(0,0,NULL)
{
  setColumn(NULL);
};
  

void ColumnNode::setSize(int s){
  size=s;
}

int ColumnNode::getSize(){
  return(size);
}

void ColumnNode::incSize(){
  // std::cout<<"ere"<<std::endl;
  size++;
}

void ColumnNode::decSize(){
  size--;
}

