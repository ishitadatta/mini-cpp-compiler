lex ast.l
yacc -d ast.y
gcc y.tab.c lex.yy.c 
./a.out<input.cpp