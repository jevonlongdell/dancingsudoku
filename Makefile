CXXFLAGS=-Wall -g -O3

dance: main.o node.o column_node.o dancefloor.o rowdat.o
	g++ node.o main.o column_node.o dancefloor.o rowdat.o -o dance

main.o: main.cpp
node.o: node.cpp
column_node.o: column_node.cpp
dancefloor.o: dancefloor.cpp
rowdat.o: rowdat.cpp