all: lib build run

build:
	gcc -m32 -Wall -o demo_implicitno main.c libXPO.so -fPIC -L"/mnt/f/FERI/FERI/2nd year/2_semester/SPO/08_Knjiznice/0802_Dinamicno" -lXPO

run:
	./demo_implicitno abcd! 6 2

clean: 
	rm -f demo_implicitno *.o *.so

lib:
	gcc -m32 -fPIC -c -o libXPO.o libXPO.c
	ldconfig -v -n .
	gcc -m32 libXPO.o -shared -o libXPO.so