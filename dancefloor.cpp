#include "dancefloor.hpp"
#include <cassert>
#include <iostream>


using namespace std;

struct MaxSolnsExceeded {};

DanceFloor::DanceFloor(std::vector<int> labels){

  unsigned int i;

  maxSolns=1000;
  rowCount=0;
  givenCount=0;
  columns.resize(labels.size());
  givenCols.resize(0);
  print_explain=1; //do print explainations

  for(i=0;i<labels.size();i++){
    columns[i].setLabel(i);
    columns[i].setSize(0);
    columns[i].setUp((Node*)&columns[i]);
    columns[i].setDown((Node*)&columns[i]);
    columns[(i+1)%labels.size()].setLeft((Node*)&columns[i]);
    columns[i].setRight((Node*)&columns[(i+1)%labels.size()]);
    //    cout<<"i = "<<i<<" up: "<<(int)columns[i].getUp()<<" "<<columns[i].setLabels()<<endl;
  }

  root.setLeft ((Node*)&columns[labels.size()-1]);
  root.setRight((Node*)&columns[0]);
  columns[labels.size()-1].setRight(&root);
  columns[0].setLeft(&root);

  root.setLabel(-1);

}


void DanceFloor::addGivenSudokuRow(int *rowData,int row, int col, int digit){
  int k;
  //  cout<<"in addSudokuRowgiven"<<endl;

  assert(givenCount==rowCount);
  givenCount++;
  addSudokuRow(rowData,row,col,digit);

  for(k=0;k<4;k++){
        givenCols.push_back(rowData[k]);
  }

}


void DanceFloor::addSudokuRow(int *rowData, int row, int col, int digit){
  int k;
  Node *n[4];
  Rowdat* rdat;
  //  cout<<"in addSudokuRow"<<endl;
  rdat = new Rowdat(rowCount,row,col,digit);

  for(k=0;k<4;k++)
    n[k] = new Node(rowCount,rowData[k],rdat);

  
  for(k=0;k<4;k++){
    n[k]->setColumn(&columns[rowData[k]]);
    
    //    cout<<(int)(n[k]->getColumn())<<endl;
    
    n[k]->setDown(&columns[rowData[k]]);
    n[k]->setUp(columns[rowData[k]].getUp());
      
    columns[rowData[k]].setUp(n[k]);
    n[k]->getUp()->setDown(n[k]);
          
	  //	  cout<<"here"<<endl;
    columns[rowData[k]].incSize();

    n[(k+1)%4]-> setLeft(n[k]);
    n[k]      -> setRight(n[(k+1)%4]);

  }
  rowCount++;
  
}



void DanceFloor::addRow(std::vector<int> rowData){
  int k;
  int count;

  assert(rowData.size()==columns.size());
  std::vector<Node*> n;

  count=0;
  for(k=0;k<(int)rowData.size();k++){
    if(rowData[k]!=0){
      n.push_back(new Node(rowCount,k,NULL));
      count++;
	}
  }

  count=0;
  for(k=0;k<(int)rowData.size();k++){
    if(rowData[k]!=0){
      //      cout<<"Node: "<<count<<" " <<n[count]<<" "<<rowCount<< " "<<k<<endl;
      n[count]->setColumn(&columns[k]);
      n[count]->setDown(&columns[k]);
      n[count]->setUp(columns[k].getUp());
      
      columns[k].setUp(n[count]);
      n[count]->getUp()->setDown(n[count]);
      
      //	  cout<<"here"<<endl;
      columns[k].incSize();
      
      n[(count+1)%n.size()]-> setLeft(n[count]);
      n[count]      -> setRight(n[(count+1)%n.size()]);
      
      count++;
    }
  }
  for(k=0;k<count;k++){
    cout<<"Node: "<<" " <<n[k]<<" "<<rowCount<< " "<<n[k]->getLabel()
	  <<" "<<n[k]->getLeft()<<" "<<n[k]->getRight()<<endl;

  }

  rowCount++;
  
}



void DanceFloor::test(){
//   ColumnNode* colScan;
//    for(colScan=(ColumnNode*)root.getRight();//.getRight();
//        colScan!=&root;
//        colScan=(ColumnNode*)colScan->getRight()){
//      //     cout<<colScan->getSize()<<" ";
//      assert( colScan->getSize()>0);
      
//    }
//     cout<<endl;

}

void DanceFloor::solve(int max_sols){
  int k;
  maxSolns=max_sols;
  Node *nd;


  assert((int)givenCols.size()==4*givenCount);
  
  for(k=0;k<(int)givenCols.size();k++){
//     cout<<"givenCol "<<givenCols[k] <<endl;
//     cout<<"col addr" <<(int)&columns[givenCols[k]]<<endl;
//     cout<<"node addr" <<(int)columns[givenCols[k]].getDown()<<endl;
    nd = columns[givenCols[k]].getDown();
    givens.push_back(nd);
    //    givens.push_back(columns[givenCols[k]].getDown());
 //  cout<<"first node "<< columns[givenCols[k]].getDown()->getRowNumber()<<endl;
//     cout<<"sec node "<< columns[givenCols[k]].getDown()->getDown()->getRowNumber()<<endl;
//     cout<<"given count "<<givenCount<<endl;
    //    assert(columns[givenCols[k]].getDown()->getDown()->getRowNumber() >= givenCount);
    hideColumn(&columns[givenCols[k]]);
  }
  
  try {
    solution.resize(0);
    search();
    cout<<"There were "<<solutions.size()<<" solutions found"<<endl;

  }
  catch(MaxSolnsExceeded){
    std::cout<<"That's too many solutions I'm giving up looking for more"<<endl;
  }
  
  
}





void DanceFloor::search(){
  
  ColumnNode* colScan;
  ColumnNode* c;
  Node* r;
  Node* j;
  int min;


  if(root.getRight()==&root){
    //solution found
    solutions.push_back(vector<Node*>(solution));
    cout<<"Found a solution -- "<<solutions.size()<<" found so far."<<endl;
    if(maxSolns==(int)solutions.size()){
      throw MaxSolnsExceeded();
    }

  }else{
    //choose a column to hide
    min = -1;
    for(colScan=(ColumnNode*)root.getRight();//.getRight();
	colScan!=&root;
	colScan=(ColumnNode*)colScan->getRight()){
      if(colScan->getSize()<=min||min<0){
	min=colScan->getSize();
	c = colScan;       
      }
    }


    //printout explaination
    //        cout<<"Rank: "<<min<<endl;

    if(print_explain){
      if (min>1)
	cout<<"A bit stuck guessing that:"<<endl<<"\t";
if(min>0){
    //print description
    Node* nd = c->getDown();
    if(c->getLabel()<81)
      cout<<"A "<<nd->getRowdat()->getDigit()<<" is the only option for the square ("<<nd->getRowdat()->getRow()<<","<<nd->getRowdat()->getCol()<<")"<<endl;
    else if(c->getLabel()<2*81 )
      cout<<"The only way to get a "<<nd->getRowdat()->getDigit()<<" in row "<<nd->getRowdat()->getRow()<<" is in col "<<nd->getRowdat()->getCol()<<"."<<endl;
    else if(c->getLabel()<3*81 )
      cout<<"The only way to get a "<<nd->getRowdat()->getDigit()<<" in col "<<nd->getRowdat()->getCol()<<" is in row "<<nd->getRowdat()->getRow()<<"."<<endl;
    else 
      cout<<"A "<<nd->getRowdat()->getDigit()<<" is needed at ("<<nd->getRowdat()->getRow()<<","<<nd->getRowdat()->getCol()<<") because that box must have a "<<nd->getRowdat()->getDigit()<<endl;
    }
    }

    hideColumn(c);
     
    for(r=c->getDown();r!=c;r=r->getDown()){
      solution.push_back(r);
      for(j=r->getRight();j!=r;j=j->getRight()){
	hideColumn((ColumnNode*)j->getColumn());
      }
      search();
      solution.pop_back();
      for(j=r->getLeft();j!=r;j=j->getLeft()){
	unhideColumn((ColumnNode*)j->getColumn());
      }
    }
      if(print_explain && min>1)
	cout<<"Nowhere more to go, forgetting that last guess."<<endl;
    unhideColumn(c);
  }
}


void DanceFloor::hideColumn(ColumnNode* col)
{
  Node *i;
  Node *j;

  //  cout<<"Hiding column "<<col->getLabel()<<" "<<col<<endl;
  col->getRight()->setLeft(col->getLeft());
  col->getLeft()->setRight(col->getRight());
  

  for(i=col->getDown();i!=col;i=i->getDown()){
    //    cout<<"i="<<i<<endl;
    for(j=i->getRight();j!=i;j=j->getRight()){
      //      cout<<"j="<<j<<endl;
      j->getDown()->setUp(j->getUp());
      j->getUp()->setDown(j->getDown());
      ((ColumnNode*)j->getColumn())->decSize();
    }
  }
};

void DanceFloor::unhideColumn(ColumnNode* col)
{
  Node *i;
  Node *j;
  
  //  cout<<"unHiding column "<<col->getLabel()<<endl;

  for(i=col->getUp();i!=col;i=i->getUp()){
    for(j=i->getLeft();j!=i;j=j->getLeft()){
      ((ColumnNode*)j->getColumn())->incSize();
      j->getDown()->setUp(j);
      j->getUp()->setDown(j);
    }
  }

  col->getRight()->setLeft(col);
  col->getLeft()->setRight(col);

};







int DanceFloor::printSudokuSolution(  vector<vector<int> > puzzle)
{
  int i,j,l,m;
  Node *nd;
  int row,col,digit;


  for(i=0;i<(int)solutions.size();i++){
    for(j=0;j<(int)solutions[i].size();j++){
      for(nd=solutions[i][j];(nd->getColumn()->getLabel()>=81);nd=nd->getLeft());
      col=nd->getColumn()->getLabel() / 9;
      row=nd->getColumn()->getLabel() % 9;
      digit=nd->getLeft()->getColumn()->getLabel()%9+1;
      //assert(puzzle[row][col]==0);
      puzzle[row][col]=digit;
    }
    for(l=0;l<9;l++){
      for(m=0;m<9;m++){
	cout<<puzzle[l][m]<<" ";
      }
      cout<<endl;
    }
    cout<<endl;
  }
  return solutions.size();
}
