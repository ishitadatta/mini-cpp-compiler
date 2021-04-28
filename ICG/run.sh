yacc -d --warning=none Yacc.y
lex lex.l
gcc -w y.tab.c lex.yy.c
