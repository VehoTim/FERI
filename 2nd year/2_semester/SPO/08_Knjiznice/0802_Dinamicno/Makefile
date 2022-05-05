all: lib build run

build:
	gcc -m32 -Wall -o demo_implicitno main.c libXPO.so -I. -fPIC -llibXPO

run:
	./demo_implicitno abcd! 6 2

clean: 
	rm -f demo_implicitno *.o *.so

lib:
	gcc -m32 -c -I. -o libXPO.o libXPO.c
	gcc -m32 -shared -I. -o libXPO.so libXPO.o