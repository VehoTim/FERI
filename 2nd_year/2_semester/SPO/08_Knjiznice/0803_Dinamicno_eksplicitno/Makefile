all: lib build run

build:
	gcc -m32 -Wall -o demo_eksplicitno main.c -ldl

run:
	./demo_eksplicitno abcd! 6 2

clean: 
	rm -f demo_eksplicitno *.o *.so

lib:
	gcc -m32 -fPIC -c -o libXPO.o libXPO.c
	gcc -m32 -shared -o libXPO.so libXPO.o 