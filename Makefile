CC = g++
CFLAGS = -Wall -Wextra -std=c++14 -O3

all: main.cpp adaptive_blockquickselect.hpp
	$(CC) $(CFLAGS) main.cpp -o main

run: all
	./main


