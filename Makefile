PROGRAM=gravitar
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
SDLFLAGS=-lSDL2
LDFLAGS=-lm
DEBUG=-g

all: $(PROGRAM)

$(PROGRAM): main.o tda_figuras.o 	tda_fisicaymatematica.o tda_polilineas.o
	$(CC) $(CFLAGS) $(DEBUG) tda_figuras.o tda_fisicaymatematica.o tda_polilineas.o main.o -o $(PROGRAM) $(LDFLAGS) $(SDLFLAGS)

main.o: main.c tda_fisicaymatematica.h tda_figuras.h tda_polilineas.h
	$(CC) $(CFLAGS) $(DEBUG) -c main.c 

tda_fisicaymatematica.o: tda_fisicaymatematica.c tda_fisicaymatematica.h
	$(CC) $(CFLAGS) $(DEBUG) -c tda_fisicaymatematica.c $(LDFLAGS)

tda_figuras.o: tda_figuras.c tda_figuras.h tda_polilineas.h
	$(CC) $(CFLAGS) $(DEBUG) -c tda_figuras.c

tda_polilineas.o: tda_polilineas.c tda_polilineas.h 
	$(CC) $(CFLAGS) $(DEBUG) -c tda_polilineas.c

clean:
	rm -vf *.o $(PROGRAM)