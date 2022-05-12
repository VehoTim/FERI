all: build run

build: build_i build_s build_o
	gcc -m32 -o demo_gcc demo_gcc.o

run:
	./demo_gcc

clean:
	rm -f demo_gcc demo_gcc.i demo_gcc.s demo_gcc.o

build_i:
	gcc -Wall -E -m32 -o demo_gcc.i main.c 

build_s:
	gcc -Wall -S -m32 -o demo_gcc.s demo_gcc.i 

build_o:
	gcc -Wall -m32 -c -o demo_gcc.o demo_gcc.s 