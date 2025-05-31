Fifo : main.o myfifo.o
	gcc main.o myfifo.o -o Fifo

main.o : main.c
	gcc -c main.c -o main.o

myfifo.o : myfifo.c
	gcc -c myfifo.c -o myfifo.o

clean:
	rm -rf *.o *.exe Fifo
