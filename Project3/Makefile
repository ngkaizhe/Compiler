# compiler command
CC= g++
CFLAG= -g

all: project2.l project2.y project2.h project2.cpp
	lex -o lex.yy.cpp project2.l
	yacc -d project2.y -o y.tab.cpp
	${CC} ${CFLAG} y.tab.cpp project2.cpp -o project2 -ll -ly -std=c++11

clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp
	