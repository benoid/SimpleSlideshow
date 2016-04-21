build_tests:
	qmake -qt=qt5 test.pro -o build/Makefile && cd build && make

run_tests: ./build/run_tests
	cd build && ./run_tests

clean:
	rm -rf ./build
