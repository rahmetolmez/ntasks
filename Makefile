all:
	gcc -o main main.c list.c card.c -lncurses -g

run:
	./main
