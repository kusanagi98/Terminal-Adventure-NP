CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: termadv server

server: server.o mysocket.o user.o gamemaster.o serverfunc.o
	${CC} server.o mysocket.o gamemaster.o user.o serverfunc.o -o server

termadv: client.o game.o level.o stage.o monster.o skill.o mysocket.o user.o clientfunc.o
	${CC} client.o game.o level.o stage.o monster.o skill.o  mysocket.o user.o clientfunc.o -o termadv

clientfunc.o: clientfunc.c
	${CC} ${CFLAGS} clientfunc.c

serverfunc.o: serverfunc.c
	${CC} ${CFLAGS} serverfunc.c

gamemaster.o: gamemaster.c
	${CC} ${CFLAGS} gamemaster.c

user.o: user.c
	${CC} ${CFLAGS} user.c

server.o: server.c
	${CC} ${CFLAGS} server.c

client.o: client.c
	${CC} ${CFLAGS} client.c

mysocket.o: mysocket.c
	${CC} ${CFLAGS} mysocket.c

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