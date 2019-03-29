main: parseC.c
	gcc -ggdb -std=c99 parseC.c -o parseC
clean:
	rm core.* vgcore.* -f
