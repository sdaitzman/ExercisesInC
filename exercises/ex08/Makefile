CC=gcc

GLIBREQS=$(shell pkg-config --cflags --libs gobject-2.0)

ex_compile: ex_compile.c
	gcc -o ex_compile ex_compile.c $(GLIBREQS)

word_count: word_count.c
	gcc -o word_count word_count.c $(GLIBREQS)