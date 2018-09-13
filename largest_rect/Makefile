all: main.o
	gcc main.c -Wall -o main
debug: main.o
	gcc main.c -Wall -o main -g
alt: main2.o min.o
	gcc main2.c min.c -Wall -o main2
alt_BIN: main2.o min.o
	gcc main2.c min.c -Wall -o main2 -DBIN -g
alt_debug: main2.o min.o
	gcc main2.c min.c -Wall -o main2 -g
