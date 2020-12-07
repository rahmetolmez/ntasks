all:
	gcc -o main main.c board.c list.c card.c -lncurses -g

run:
	./main

dbg:
	gdb ./main
