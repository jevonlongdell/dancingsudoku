#include <iostream>
#include <fstream>
#include <vector>
#include "node.hpp"
#include "column_node.hpp"
#include "dancefloor.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/time.h>

using namespace std;

class Rowidx{
public:
  Rowidx(int ii){i=ii;sortnum=rand();};
  int i;
  int sortnum;
}; 

bool operator<(const Rowidx& a,const Rowidx&b) {
    return a.sortnum<b.sortnum;
  };


struct ReadInError {};

int main(int argc,char **argv){
  int ch,i,j,row,col,digit;
  int puzzle_size=3;
  vector<int> labels;
  int rowData[4];
  vector<vector<int> > puzzle;
  int ncols;
  timeval tv;
  gettimeofday(&tv,NULL);
  srand(tv.tv_sec+tv.tv_usec);

  /*  ncols=4;
  
  labels.resize(ncols);
  for(i=0;i<ncols;i++)
    labels[i]=i;
  
  DanceFloor df(labels);
  
  vector<int> rowdat1;
  rowdat1.push_back(1);
  rowdat1.push_back(1);
  rowdat1.push_back(0);
  rowdat1.push_back(0);
  
  vector<int> rowdat2;
  rowdat2.push_back(0);
  rowdat2.push_back(0);
  rowdat2.push_back(1);
  rowdat2.push_back(1);

    df.addRow(rowdat1);
    df.addRow(rowdat2);
    df.addRow(rowdat1);
    df.addRow(rowdat1);
    df.addRow(rowdat1);


  df.solveRand(10);

  return 0;*/


  //set up dancefloor
  ncols = 4*puzzle_size*
            puzzle_size*
            puzzle_size*
            puzzle_size;


  labels.resize(ncols);
  for(i=0;i<ncols;i++)
    labels[i]=i;

  DanceFloor df(labels);



  //read in the puzzle
  ifstream puzin(argv[1]);
  puzzle.resize(9);
  for(i=0;i<9;i++){
    puzzle[i].resize(9);
    for(j=0;j<9;j++){
      for(;;){
	ch=puzin.get();
	if(ch==-1)
	  throw ReadInError();
	if (ch==(int)'.'||(ch>=(int)'1'&&ch<=(int)'9'))
	  break;
      }
      if(ch==(int)'.')
	puzzle[i][j]=0;
      else
	puzzle[i][j]=ch-(int)'1'+1;
    }
  }



  // fill out the dance floor wrowth the givens
  for(row=0;row<9;row++){//row
    for(col=0;col<9;col++){//cols
      for(digit=0;digit<9;digit++){//digit
	if(puzzle[row][col]==digit+1){
	  //this row is a given so add it to the danceloor
	  rowData[0]=0*81 + row   + col*9;
	  rowData[1]=1*81 + row*9  + digit;
	  rowData[2]=2*81 + col*9 + digit;
	  rowData[3]=3*81 + (row/3 + 3*(col/3))*9 + digit;
	  //	  cout<<df.rowCount<<" "<<row<<" "<<col<<" "<<
	    //	  digit<<" "<<rowData[0]<<" "<<rowData[1]<<" "<<rowData[2]<<" "<<rowData[3]<<endl;
	  
	  df.addGivenSudokuRow(rowData,row+1,col+1,digit+1);
	  //	  printf("hello_outside\n");
	}
      }
    }
  }


  // fill out the dance floor with the unknowns
  for(row=0;row<9;row++){//row
    for(col=0;col<9;col++){//cols
      for(digit=0;digit<9;digit++){//digit
	if(puzzle[row][col]!=digit+1){
	  //this row is a given so add it to the dancefloor
	  rowData[0]=0*81 + row   + col*9;
	  rowData[1]=1*81 + row*9  + digit;
	  rowData[2]=2*81 + col*9 + digit;
	  rowData[3]=3*81 + (row/3 + 3*(col/3))*9 + digit;
	  df.addSudokuRow(rowData,row+1,col+1,digit+1);
	}
      }
    }
  }
	  
  df.test();
  df.solve(10);

  
  df.printSudokuSolution(puzzle);


//   DanceFloor df2(labels);
//   vector<Rowidx> rows;

//   for(i=0;i<9*9*9;i++)
//     rows.push_back(Rowidx(i));

//   sort(rows.begin(),rows.end());  //randomise rows
//   for(i=0;i<9*9*9;i++){
//     row = rows[i].i%9;
//     col = (rows[i].i/9)%9;
//     digit = (rows[i].i/9/9)%9;
//     //    cout<<row<<col<<digit<<endl;  
//     rowData[0]=0*81 + row   + col*9;
//     rowData[1]=1*81 + row*9  + digit;
//     rowData[2]=2*81 + col*9 + digit;
//     rowData[3]=3*81 + (row/3 + 3*(col/3))*9 + digit;
//     df2.addSudokuRow(rowData);

//   }
//   df2.solve(1);
  
//   df2.printSudokuSolution(puzzle);



  return 0;
	   
}
  
