CC = g++

GFLAGS = -Wall

.PHONY: all send clean

all: buildTests/Test

buildTests/Test: buildTests/Test.o
	$(CC) $(GFLAGS) buildTests/Test.o -o buildTests/Test

buildTests/Test.o: tests/Test.cpp include/segtree.h src/segtree.cpp
	rm -f Test_send.cpp
	mkdir -p buildTests
	$(CC) $(GFLAGS) -c -I include tests/Test.cpp -o buildTests/Test.o

send: tests/Test.cpp
	$(CC) $(GFLAGS) -E -I include -D DO_NOT_INCLUDE_SYS_LIBS tests/Test.cpp -o Test_send.cpp

clean:
	rm -rf buildTests Test_send.cpp 
