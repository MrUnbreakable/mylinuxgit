CC=gcc
LD=ld
CFLAGS=${CFLAGS:-}
CFLAGS += -I../../.. -g 

all: test.exe

test.exe: test.o
	${CC} -g -L. -o test test.o -lsqlite3 -lpthread -ldl
test.o: test.c
