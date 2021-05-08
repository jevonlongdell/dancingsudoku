#include <iostream>
#include <fstream>
#include <vector>
#include "node.hpp"
#include "column_node.hpp"
#include "dancefloor.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
// #include <sys/time.h>

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
  const int puzzle_size = 3;
  vector<int> labels;
  int rowData[4];
  vector<vector<int> > puzzle;
  int ncols;
  //timeval tv;
  //gettimeofday(&tv,NULL);
  //srand(tv.tv_sec+tv.tv_usec);


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
  puzzle.resize(9); // the puzzle has 9 rows
  for(i=0;i<9;i++){
    puzzle[i].resize(9);
    for(j=0;j<9;j++){  //loop over the columns
      for(;;){ //loop until you get a . or a digit
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





  // fill out the dance floor with the givens
  // the dance floor has 324 columns
  // 81 because each square on the grid can only have one number
  // 81 because each row can only have each of one particular digit
  // 81 because each col can only have one of each digit
  // 81 because each box can only have oe of each digit

  // the dance floor has up to 729 rows because there are:
  //  - 9 posibilities for each digit
  //  - 81 possibilities for the location 
  for(row=0;row<9;row++){//row
    for(col=0;col<9;col++){//cols
        if(puzzle[row][col]!=0){
          digit = puzzle[row][col]-1;
	        //this row is a given so add it to the danceloor
	        rowData[0]=0*81 + row   + col*9;  
	        rowData[1]=1*81 + row*9  + digit;
	        rowData[2]=2*81 + col*9 + digit;
	        rowData[3]=3*81 + (row/3 + 3*(col/3))*9 + digit;
	    //	  cout<<df.rowCount<<" "<<row<<" "<<col<<" "<<
	    //	  digit<<" "<<rowData[0]<<" "<<rowData[1]<<" "<<rowData[2]<<" "<<rowData[3]<<endl;
	        df.addGivenSudokuRow(rowData,row+1,col+1,digit+1);
	    //  printf("hello_outside\n");
	    }
    }
  }


  // fill out the dance floor with the unknowns
  for(row=0;row<9;row++){//row
    for(col=0;col<9;col++){//cols
      if(puzzle[row][col]==0) { //no point putting in rows that are not possilbe becaue this box is already full
        for(digit=0;digit<9;digit++){
	        //this row is a given so add it to the dancefloor (unknown right?)
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
  
