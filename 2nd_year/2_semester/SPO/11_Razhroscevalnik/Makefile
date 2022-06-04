all: build run

build:
	gcc -m32 demo_gdb -o main.c
	#gcc -Wall -Wextra -Werror -m32 -o example_1 example_1.c misc.c

run:
	./demo_gdb

clean:
	rm -f demo_gdb