compile:
	gcc main.c parse.c execute.c -o shell
run:
	./shell
clear:
	rm ./shell *.txt
