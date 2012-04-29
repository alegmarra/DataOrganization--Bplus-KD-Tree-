all: main.o FileSequential.o FileAbstract.o Comparator.o
	g++ main.o File/Sequential.o File/Abstract.o Comparator.o -o hello
	
FileAbstract.o:
	g++ -c File/Abstract.cpp -o File/Abstract.o

FileSequential.o:
	g++ -c File/Sequential.cpp -o File/Sequential.o
	
Comparator.o:
	g++ -c Comparator.cpp
	
main.o:
	g++ -c main.cpp
	
clean:
	rm *.o File/*.o hello
