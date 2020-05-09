#!/bin/bash
# test run shell script
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "Test start run"

if [ $# -eq 2 ]
then 
    test ! -f $1 && echo "input file not exist!" && exit 1

    lex project1.l
    gcc project1.c lex.yy.c -o test.out
    ./test.out $1 $2
else
    lex project1.l
    gcc project1.c lex.yy.c -o test.out
    ./test.out "test/example1Input" "test/example1Output"
fi

echo "Test finish run"
exit 0