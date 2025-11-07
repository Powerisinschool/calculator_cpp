.PHONY: all build run test clean

# Default target – handy if you just type `make`
all: run

build:
	mkdir -p build
	cd build && cmake .. && make

run: build
	./build/src/calc

test: build
	./build/tests/calc_tests

clean:
	rm -rf build
