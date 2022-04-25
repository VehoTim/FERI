all: build run

build: 
	gcc -g -m32 -o demo_gdb main.c
	
run: 
	./demo_gdb

clean:
	rm -f demo_gdb

debug:
	gdb ./demo_gdb