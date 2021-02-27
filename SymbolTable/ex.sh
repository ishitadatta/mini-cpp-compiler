lex sym.l
yacc -d sym.y
gcc y.tab.c lex.yy.c 
./a.out<input.cpp