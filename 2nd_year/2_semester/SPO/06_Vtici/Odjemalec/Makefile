all: build run

build:
	gcc -m32 main.c -o demo_client

run:
	./demo_client localhost 3000 test.txt
clean:
	rm -f demo_client