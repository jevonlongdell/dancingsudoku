#ifndef node_hpp
#define node_hpp
#include <string>
#include "rowdat.hpp"

class Node
{
public:
  Node(int rowNum, int lbl, Rowdat* rd);
  Node(){};
  void setLeft(Node*); 
  Node* getLeft();
  void setRight(Node*);
  Node* getRight();
  void setUp(Node*);
  Node* getUp();
  void setDown(Node*);
  Node* getDown();
  void setColumn(Node* node);
  Node* getColumn();
  int getRowNumber();
  void setRowNumber(int);
  Rowdat* getRowdat();
  int getLabel();
  void setLabel(int);
  
private:
  Node* left;
  Node* right;
  Node* up;
  Node* down;
  Node* col;
  Rowdat *rowdat;
  // ColumnNode* column;
  int rowNumber;
  int label;

};

#endif //node_hpp
