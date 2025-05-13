Pars : main.o parser.o
	gcc main.o parser.o -o Pars

main.o : main.c
	gcc -c main.c -o main.o

parser.o : parser.c
	gcc -c parser.c -o parser.o

clean:
	rm -rf *.o
