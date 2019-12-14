CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: termadv server

server: server.o mysocket.o user.o gamemaster.o serverfunc.o helper.o
	${CC} server.o mysocket.o gamemaster.o user.o serverfunc.o helper.o -o server

termadv: client.o game.o level.o stage.o monster.o skill.o mysocket.o user.o clientfunc.o
	${CC} client.o game.o level.o stage.o monster.o skill.o  mysocket.o user.o clientfunc.o -o termadv

clientfunc.o: interface/clientfunc.c
	${CC} ${CFLAGS} interface/clientfunc.c

serverfunc.o: interface/serverfunc.c
	${CC} ${CFLAGS} interface/serverfunc.c

gamemaster.o: game/gamemaster.c
	${CC} ${CFLAGS} game/gamemaster.c

user.o: struct/user.c
	${CC} ${CFLAGS} struct/user.c

server.o: server.c
	${CC} ${CFLAGS} server.c

client.o: client.c
	${CC} ${CFLAGS} client.c

mysocket.o: helper/mysocket.c
	${CC} ${CFLAGS} helper/mysocket.c

game.o: game/game.c
	${CC} ${CFLAGS} game/game.c

stage.o: struct/stage.c
	${CC} ${CFLAGS} struct/stage.c

level.o: struct/level.c
	${CC} ${CFLAGS} struct/level.c

monster.o: struct/monster.c
	${CC} ${CFLAGS} struct/monster.c

skill.o: struct/skill.c
	${CC} ${CFLAGS} struct/skill.c

helper.o: helper/helper.c
	${CC} ${CFLAGS} helper/helper.c

clean:
	rm -f *.o *~