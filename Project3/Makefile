# compiler command
CC= g++
CFLAG= -g
testFileName = HelloWorld
.PHONY: jasm javaa java clean

all:
	lex -o lex.yy.cpp project3.l
	yacc -d project3.y -o y.tab.cpp
	${CC} ${CFLAG} y.tab.cpp project3.cpp -o project3 -ll -ly -std=c++11

jasm: 
	./project3 scala/${testFileName}.scala jasm/${testFileName}.jasm

javaa:
	javaa jasm/${testFileName}.jasm

java:
	java ${testFileName}

run:
	./project3 scala/${testFileName}.scala jasm/${testFileName}.jasm
	javaa jasm/${testFileName}.jasm
	java HelloWorld

clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp project3 *.class jasm/*.jasm
	