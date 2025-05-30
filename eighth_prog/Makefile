Signal : main.o mysignal.o
	gcc -std=gnu99 main.o mysignal.o -o Signal

main.o : main.c
	gcc -std=gnu99 -c main.c -o main.o

mysignal.o : mysignal.c
	gcc -std=gnu99 -c mysignal.c -o mysignal.o

clean:
	rm -rf *.o *.exe Signal