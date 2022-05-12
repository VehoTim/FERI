all: lib build run

build:
	gcc -m32 main.c -o demo_staticno libXPO.a

run:
	./demo_staticno abcd! 6 2

clean: 
	rm -f demo_staticno *.o *.a

lib:
	gcc -m32 -c libXPO.c -o libXPO.o
	ar rcs libXPO.a libXPO.o