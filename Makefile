.PHONY: config reconfig build rebuild run clean

.ONESHELL:

run:
	cd build
	./OcctTest

clean:
	rm -f build/OcctTest
	rm -f build/pyRpOCCT.cpython-39-x86_64-linux-gnu.so

build:
	cd build
	cmake ..
	make

rebuild:
	cd build
	rm -f CMakeCache.txt
	cmake ..
	make

config:
	cd build
	cmake ..

reconfig:
	cd build
	rm -f CMakeCache.txt
	cmake ..
