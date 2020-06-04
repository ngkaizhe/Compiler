# compiler command
CC= gcc
CFLAG= -c -g

all: y.tab.o lex.yy.o project2.o
	${CC} y.tab.o lex.yy.o project2.o -o project2

y.tab.o: project2.y
	yacc -d project2.y
	${CC} $(CFLAG) y.tab.c

lex.yy.o: project2.l
	lex project2.l
	${CC} ${CFLAG} lex.yy.c

project2.o: project2.h project2.c
	${CC} ${CFLAG} project2.c
	