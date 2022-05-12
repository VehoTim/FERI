all: build run

build: 
	gcc -g -m32 main.c skrivna_funkcija.o -o demo_gdb
	
run: 
	./demo_gdb 

clean:
	rm -f demo_gdb

debug:
	gdb ./demo_gdb -ex 'b 10' -ex 'r' -ex 'p lokalna_premenljivka' -ex 'c' -ex 'q'