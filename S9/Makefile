#Pour compiler sur une machine de l'ARI
#C_FLAGS = -Wall -g -std=gnu99
#Pour derniere version ubuntu (11.10)
LINK_FLAGS = -Wl,--no-as-needed
#C_FLAGS = -Wall -g -Wl,--no-as-needed
C_FLAGS = -Wall -Wextra -g 
CC ?= gcc

.PHONY: all clean

all : test_sta test_ligne test_connexion test_dijkstra test_aqr metro_v0 metro_v1 metro_v2 metro_v3 metro_v4 treedump

clean :
	rm -f *.o test_sta test_ligne test_connexion test_dijkstra test_aqr metro_v0 metro_v1 metro_v2 metro_v3 metro_v4 treedump


# Most object files
%.o : %.c
	${CC} ${C_FLAGS} -c $<

# Object files that depend on GTK+
metro_callback_v0.o : metro_callback_v0.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v0.c

metro_v0.o : metro_v0.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v0.c

metro_v0 : metro_v0.o metro_callback_v0.o liste.o truc.o ligne.o abr.o
	${CC} ${C_FLAGS} ${LINK_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v0 metro_v0.o metro_callback_v0.o liste.o truc.o ligne.o abr.o

metro_callback_v1.o : metro_callback_v1.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v1.c

metro_v1.o : metro_v1.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v1.c


# Various tests
test_sta : test_sta.o abr.o ligne.o liste.o truc.o
	${CC} ${C_FLAGS} -o $@ $^

test_ligne : test_ligne.o ligne.o
	${CC} ${C_FLAGS} -o $@ $^

test_connexion : test_connexion.o ligne.o abr.o liste.o truc.o
	${CC} ${C_FLAGS} -o $@ $^ -lm

test_dijkstra : test_dijkstra.o ligne.o abr.o liste.o truc.o dijkstra.o
	${CC} ${C_FLAGS} -o $@ -lm $^

test_aqr : test_aqr.o ligne.o abr.o liste.o truc.o aqrtopo.o 
	${CC} ${C_FLAGS} -o $@ -lm $^

treedump : graph.o abr.o ligne.o liste.o truc.o
	${CC} ${C_FLAGS} -o $@ $^


# Fancy GUI stuff
metro_v1 : metro_v1.o metro_callback_v1.o liste.o truc.o ligne.o abr.o
	${CC} ${C_FLAGS} ${LINK_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v1 metro_v1.o metro_callback_v1.o liste.o truc.o ligne.o abr.o

metro_callback_v2.o : metro_callback_v2.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v2.c

metro_v2.o : metro_v2.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v2.c

metro_v2 : metro_v2.o metro_callback_v2.o liste.o truc.o ligne.o abr.o aqrtopo.o
	${CC} ${C_FLAGS} ${LINK_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v2 metro_v2.o metro_callback_v2.o liste.o truc.o ligne.o abr.o aqrtopo.o

metro_callback_v3.o : metro_callback_v3.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v3.c

metro_v3.o : metro_v3.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v3.c

metro_v3 : metro_v3.o metro_callback_v3.o liste.o truc.o ligne.o abr.o aqrtopo.o dijkstra.o
	${CC} ${C_FLAGS} ${LINK_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v3 metro_v3.o metro_callback_v3.o liste.o truc.o ligne.o abr.o aqrtopo.o dijkstra.o

metro_callback_v4.o : metro_callback_v4.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v4.c

metro_v4.o : metro_v4.c
	${CC} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v4.c

metro_v4 : metro_v4.o metro_callback_v4.o liste.o truc.o ligne.o abr.o aqrtopo.o dijkstra.o 
	${CC} ${C_FLAGS} ${LINK_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v4 metro_v4.o metro_callback_v4.o liste.o truc.o ligne.o abr.o aqrtopo.o dijkstra.o 
