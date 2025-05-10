Mylab : main.o thread.o
	gcc main.o thread.o -o First

main.o : main.c
	gcc -c main.c -o main.o

thread.o : thread.c
	gcc -c thread.c -o thread.o

clean:
	rm -rf *.o