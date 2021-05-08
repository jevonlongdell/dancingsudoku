#include "rowdat.hpp"

//holds data about each row in the dancefloor
Rowdat::Rowdat(int rw_num,int rw, int cl, int dgt){
  rowNumber=rw_num;
  col=cl;
  row=rw;
  digit=dgt;
}

int Rowdat::getRow(){return row;};
int Rowdat::getCol(){return col;};
int Rowdat::getDigit(){return digit;};

int Rowdat::getRowNumber(){return rowNumber;};
void Rowdat::setRowNumber(int r){rowNumber=r;};
