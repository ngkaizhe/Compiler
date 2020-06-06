# compiler command
CC= g++
CFLAG= -c -g

all: lex.yy.cpp y.tab.cpp project2.h project2.cpp
	${CC} y.tab.cpp project2.cpp -o project2 -ll -ly -std=c++11

lex.yy.cpp: project2.l
	lex -o lex.yy.cpp project2.l

y.tab.cpp: project2.y
	yacc -d project2.y -o y.tab.cpp

clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp
	