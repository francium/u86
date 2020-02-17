ifdef DEBUG
	DEBUG_FLAG=-g
else
	DEBUG_FLAG=
endif
CFLAGS=-Wall
TEST_CFLAGS=-Wall
TEST_LIBS=-lcriterion
INCLUDE_FLAGS=-I../dynstr -I../libfr

default: _bin/vec.o

_bin/vec.o: vec.h
	gcc $(CFLAGS) $(INCLUDE_FLAGS) -o _bin/vec.o vec.h

.test: _bin/vec_test
	./_bin/vec_test

_bin/vec_test: _bin vec_test.c vec.h
	gcc $(TEST_CFLAGS) $(TEST_LIBS) ${DEBUG_FLAG} $(INCLUDE_FLAGS) -o _bin/vec_test vec_test.c

_bin:
	mkdir -p _bin
