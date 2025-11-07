build:
	mkdir -p build
	cd build && cmake .. && make

run:
	./build/calc

test:
	./build/calc_tests

clean:
	rm -rf build
