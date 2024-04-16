all: clear build

clear:
	rm -f gof

build:
	g++ main.cpp -lraylib -o gof

windows:
	x86_64-w64-mingw32-g++ main.cpp -L /tmp/raylib/lib/ -lwinmm -lraylib -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
