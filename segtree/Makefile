CC = g++

GFLAGS = -Wall

.PHONY: all send clean

all: buildTests/Test

buildTests/Test: buildTests/Test.o
	$(CC) $(GFLAGS) buildTests/Test.o -o buildTests/Test

buildTests/Test.o: buildTests/.Test_send.cpp
	$(CC) $(GFLAGS) -c buildTests/.Test_send.cpp -o buildTests/Test.o

buildTests/.Test_send.cpp: tests/Test.cpp
	rm -f Test_send.cpp
	mkdir -p buildTests
	$(CC) $(GFLAGS) -E -I include tests/Test.cpp -o buildTests/.Test_send.cpp

send: buildTests/.Test_send.cpp
	cp buildTests/.Test_send.cpp Test_send.cpp

clean:
	rm -rf buildTests Test_send.cpp 
