GCC_FLAGS = -g -Wall
all: test_csv

test_csv: test_csvl.o csvl.o 
	gcc $(GCC_FLAGS) -o test_csv test_csvl.o csvl.o

test_csvl.o: test_csvl.c
	gcc $(GCC_FLAGS) -c test_csvl.c

csvl.o: csvl.c
	gcc $(GCC_FLAGS) -c csvl.c

clean:
	rm -f test_csv csvl.o test_csvl.o
