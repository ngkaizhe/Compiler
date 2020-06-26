# compiler command
CC= g++
CFLAG= -g

all: project3.l project3.y project3.h project3.cpp
	lex -o lex.yy.cpp project3.l
	yacc -d project3.y -o y.tab.cpp
	${CC} ${CFLAG} y.tab.cpp project3.cpp -o project3 -ll -ly -std=c++11

clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp project3
	