#ifndef rowdat_hpp
#define rowdat_hpp
#include <string>


class Rowdat
{
public:
  Rowdat(int rw_num,int rw, int cl, int dgt);
  Rowdat(){};
  
  void setDat(int rw, int cl, int dgt);
  int getRow();
  int getCol();
  int getDigit();
  int getRowNumber();
  void setRowNumber(int);
  
private:
  int rowNumber;
  int label;
  int row;
  int col;
  int digit;
};

#endif //node_hpp
