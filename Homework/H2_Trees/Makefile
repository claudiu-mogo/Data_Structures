FLAG = -g -Wall -lm -std=c99
 
build: tema1sd

tema1sd:
	gcc -o quadtree main.c $(FLAG)

# Regulile de clean 
.PHONY : clean
clean :
	rm -f quadtree
	rm -f *.out