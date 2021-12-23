# Makefile
CXX_FLAG = --std=c++11 -g

all: main tests

main: main.o movies.o
	g++ $(CXX_FLAG) -o runMovies main.o

tests: tests.o movies.o
	g++ $(CXX_FLAG) -o tests tests.o movies.o

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

tests.o: tests.cpp
	g++ -c $(CXX_FLAG) tests.cpp

movies.o: movies.cpp
	g++ -c $(CXX_FLAG) movies.cpp

clean:
	rm -f main movies *.o