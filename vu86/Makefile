SRCS=main.c vm.h bits.h ops.h
NAME=vu86
CFLAGS=-std=c99 -pedantic -Wall

ifdef DEBUG
	DEBUG_FLAG=-g
else
	DEBUG_FLAG=
endif

${NAME}: ${SRCS}
	gcc ${CFLAGS} ${DEBUG_FLAG} -o $@ $^

.clean:
	rm -f main *.o *.gch
