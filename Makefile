all: clear build

clear:
	rm -f gen gof

build:
	g++ main.cpp -lraylib -o gof
	g++ gen.cpp -o gen
