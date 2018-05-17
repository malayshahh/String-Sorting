all: stringsorter  stringsorter.c
	gcc -Wall -Werror -fsanitize=address -o  stringsorter stringsorter.c

clean:
	rm -f stringsorter
