FLAGS = -g -Wall -Werror

all : main

person.o : person.c person.h
	gcc ${FLAGS} person.c -I "include" -c

elevator.o : elevator.c elevator.h
	gcc ${FLAGS} elevator.c -I "include" -c

main.o : main.c
	gcc ${FLAGS} main.c -I "include" -c

main : main.o person.o elevator.o
	gcc ${FLAGS} -o main -L "lib" main.o person.o elevator.o -lncurses 