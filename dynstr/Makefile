ifdef DEBUG
	DEBUG_FLAG=-g
else
	DEBUG_FLAG=
endif
CFLAGS=-Wall
TEST_CFLAGS=-Wall
TEST_LIBS=-lcriterion

default: _bin/dynstr.o

_bin/dynstr.o: dynstr.h
	gcc $(CFLAGS) -o _bin/dynstr.o dynstr.h

.test: _bin/dynstr_test
	./_bin/dynstr_test

_bin/dynstr_test: _bin dynstr_test.c dynstr.h
	gcc $(TEST_CFLAGS) $(TEST_LIBS) ${DEBUG_FLAG} -o _bin/dynstr_test dynstr.h dynstr_test.c

_bin:
	mkdir -p _bin
