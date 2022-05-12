all: main.c mymalloc.c mymalloc.h
	gcc main.c -o main.o -c
	gcc mymalloc.c -o mymalloc.o -c
	gcc -o main main.o mymalloc.o
debug:
	gcc main.c -o main.o -D DEBUG -c
	gcc mymalloc.c -o mymalloc.o -D DEBUG -c
	gcc -o main main.o mymalloc.o
clean:
	rm -f *.o main
