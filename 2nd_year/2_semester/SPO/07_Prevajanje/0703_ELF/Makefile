all: build run

build: 
	gcc -m32 -o demo_elf main.c
	
run: 
	./demo_elf -d .text demo_elf

clean:
	rm -f demo_elf