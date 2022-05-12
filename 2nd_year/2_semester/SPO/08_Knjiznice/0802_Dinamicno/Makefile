all: lib build run

build:
	gcc -m32 -Wall -o demo_implicitno main.c libXPO.so -L. -lXPO

run:
	./demo_implicitno abcd! 6 2

clean: 
	rm -f demo_implicitno *.o *.so

lib:
	# export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	gcc -m32 -fPIC -c -o libXPO.o libXPO.c
	gcc -m32 -shared -o libXPO.so libXPO.o 