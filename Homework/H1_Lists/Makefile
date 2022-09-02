FLAG = -g -Wall -lm -std=c99
 
build: tema1sd

tema1sd:
	gcc -o tema1 main.c operations.c e1.c e2e3.c u.c c.c st.c $(FLAG)

# Regulile de clean 
.PHONY : clean
clean :
	rm -f tema1
	rm -f *.out