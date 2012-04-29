CC=g++
CFLAGS=-Isrc/

all: main.o FileSequential.o FileAbstract.o Comparator.o
	$(CC) lib/main.o lib/File/Sequential.o lib/File/Abstract.o lib/Comparator.o -o run $(CFLAGS)
	
FileAbstract.o:
	$(CC) -c src/File/Abstract.cpp -o lib/File/Abstract.o $(CFLAGS)

FileSequential.o:
	$(CC) -c src/File/Sequential.cpp -o lib/File/Sequential.o $(CFLAGS)
	
Comparator.o:
	$(CC) -c src/Comparator.cpp -o lib/Comparator.o $(CFLAGS)
	
main.o:
	$(CC) -c src/main.cpp -o lib/main.o $(CFLAGS)
	
clean:
	rm -rf lib run > /dev/null 2>&1; mkdir -p lib/File
