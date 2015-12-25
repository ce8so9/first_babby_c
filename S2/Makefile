
GCC_FLAGS = -Wall
all: main_triBulle main_triBulleOptimise main_triRapide main_triRapideOptimise

utilitaires_tableaux.o: utilitaires_tableaux.c
	gcc $(GCC_FLAGS) -c utilitaires_tableaux.c

tri_bulle.o: tri_bulle.c
	gcc $(GCC_FLAGS) -c tri_bulle.c

main_triBulle.o: main_triBulle.c
	gcc $(GCC_FLAGS) -c main_triBulle.c

main_triBulle: tri_bulle.o main_triBulle.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triBulle main_triBulle.o tri_bulle.o utilitaires_tableaux.o 

main_triBulleOptimise.o: main_triBulleOptimise.c
	gcc $(GCC_FLAGS) -c main_triBulleOptimise.c

main_triBulleOptimise: tri_bulle.o main_triBulleOptimise.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triBulleOptimise main_triBulleOptimise.o tri_bulle.o \
utilitaires_tableaux.o

tri_rapide.o: tri_rapide.c
	gcc $(GCC_FLAGS) -c tri_rapide.c

main_triRapide.o: main_triRapide.c
	gcc $(GCC_FLAGS) -c main_triRapide.c

main_triRapide: tri_rapide.o main_triRapide.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triRapide main_triRapide.o tri_rapide.o utilitaires_tableaux.o 

main_triRapideOptimise.o: main_triRapideOptimise.c
	gcc $(GCC_FLAGS) -c main_triRapideOptimise.c

main_triRapideOptimise: tri_rapide.o main_triRapideOptimise.o utilitaires_tableaux.o
	gcc $(GCC_FLAGS) -o main_triRapideOptimise main_triRapideOptimise.o tri_rapide.o \
utilitaires_tableaux.o

clean:
	rm -f utilitaires_tableaux.o tri_bulle.o main_triBulle.o main_triBulle \
main_triBulleOptimise.o main_triBulleOptimise tri_rapide.o main_triRapide.o main_triRapide \
main_triRapideOptimise.o main_triRapideOptimise
