CC = g++
CFLAGS = -Wall -Wextra -std=c++14 -O3

all: main.cpp adaptive_blockquickselect.hpp
	$(CC) $(CFLAGS) main.cpp -o main

run: all
	./main

benchmark:
	$(CC) $(CFLAGS) abqs_benchmark.cpp -o abqs_benchmark
	$(CC) $(CFLAGS) abqs_benchmark.cpp -o bqs_benchmark
	$(CC) $(CFLAGS) ninther_benchmark.cpp -o ninther_benchmark
	$(CC) $(CFLAGS) std_benchmark.cpp -o std_benchmark