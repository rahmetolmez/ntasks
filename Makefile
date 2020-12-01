all:
	gcc -o main main.c card.c image.c -lncurses -g

run:
	./main
