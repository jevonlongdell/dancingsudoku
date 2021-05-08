#ifndef dancefloor_hpp
#define dancefloor_hpp
#include <vector>
#include "column_node.hpp"
#include "node.hpp"
#include "rowdat.hpp"
class DanceFloor
{
public:
  DanceFloor(std::vector<int> labels); //labels 1..9 by default
  ColumnNode getFirstColumn();
  void addSudokuRow(int*,int,int,int);
  void addGivenSudokuRow(int*,int,int,int);
  void addRow(std::vector<int>);
  int maxSolns;
  void solve(int);
  int rowCount;
  void test();
  int printSudokuSolution( std::vector<std::vector<int> >);
private:
  int givenCount;
  ColumnNode root;
  std::vector<ColumnNode> columns;
  std::vector<Node*> solution;
  std::vector<std::vector<Node*> > solutions;
  std::vector<Node*> givens;
  std::vector<int> givenCols;
  void search();
  void hideColumn(ColumnNode* col);
  void unhideColumn(ColumnNode* col);
  int print_explain;

};


#endif //dancefloor_hpp
