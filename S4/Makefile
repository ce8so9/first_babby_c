GCC_FLAGS = -Wall -g

all : main

main : main.o repertoire.o
	gcc $(GCC_FLAGS) -o main main.o repertoire.o

main.o : main.c
	gcc $(GCC_FLAGS) -c main.c

repertoire.o : repertoire.c
	gcc $(GCC_FLAGS) -c repertoire.c

clean :
	rm main main.o repertoire.o repertoire.txt
