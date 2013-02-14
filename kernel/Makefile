CC = gcc $(CFLAGS) $(INCLUDES) $(DEFS)
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -Wall -std=c99
LDFLAGS=-Tlink.ld -melf_i386
INCLUDES = -I. -Iinclude/
FILES = src/*.c src/*.S klibc/*.c
DEFS =

all: clean kernel link

kernel:
	@$(CC) -c $(FILES)

link:
	@ld $(LDFLAGS) -o kernel *.o

clean:
	@rm -f *.o kernel
