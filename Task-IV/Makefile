main: main.o workWithIO.o workWithList.o workWithMenu.o
	cc main.o workWithIO.o workWithList.o workWithMenu.o -o main

main.o: main.c
	cc -c main.c -o main.o
	
workWithIO.o: workWithIO.c
	cc -c workWithIO.c -o workWithIO.o
	
workWithList.o: workWithList.c
	cc -c workWithList.c -o workWithList.o
	
workWithMenu.o: workWithMenu.c
	cc -c workWithMenu.c -o workWithMenu.o

test: test.o workWithIO.o workWithList.o workWithMenu.o
	cc test.o workWithIO.o workWithList.o workWithMenu.o -o test

test.o: test.c
	cc -c test.c -o test.o

clear:
	-rm -f workWithIO.o workWithList.o workWithMenu.o main.o main.exe test.o test.exe
