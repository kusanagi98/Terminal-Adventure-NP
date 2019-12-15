CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: termadv

termadv: client.o game.o level.o stage.o monster.o skill.o 
	${CC} client.o game.o level.o stage.o monster.o skill.o  -o termadv

client.o: client.c
	${CC} ${CFLAGS} client.c

game.o: game.c
	${CC} ${CFLAGS} game.c

stage.o: stage.c
	${CC} ${CFLAGS} stage.c

level.o: level.c
	${CC} ${CFLAGS} level.c

monster.o: monster.c
	${CC} ${CFLAGS} monster.c

skill.o: skill.c
	${CC} ${CFLAGS} skill.c

clean:
	rm -f *.o *~