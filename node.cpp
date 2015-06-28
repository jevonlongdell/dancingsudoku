#include "node.hpp"


Node::Node(int row, int lbl, Rowdat *rd){
  label=lbl;
  rowNumber=row;
  left=this;
  right=this;
  up=this;
  down=this;
  rowdat=rd;

}

Rowdat* Node::getRowdat(){
  return rowdat;
}

void Node::setLeft(Node* l ){left=l;}
Node* Node::getLeft(){return left;};

void Node::setRight(Node* l ){right=l;}
Node* Node::getRight(){return right;};

void Node::setUp(Node* l ){up=l;}
Node* Node::getUp(){return up;};

void Node::setDown(Node* l ){down=l;}
Node* Node::getDown(){return down;};

void Node::setColumn(Node* l ){col=l;}
Node* Node::getColumn(){return col;};

void Node::setLabel(int i) {label=i;};
int Node::getLabel(){return label;};

int Node::getRowNumber(){return rowNumber;};
void Node::setRowNumber(int r){rowNumber=r;};
