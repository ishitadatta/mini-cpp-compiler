%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
	
	void yyerror(const char*);
	int yylex();
	extern FILE * yyin, *yyout;

	int x=0;
	
	extern int line;
	
	int scope = 0;

	int unaryop = -1;		//unary operator type
	int assignop = -1;		//assignment operator == += -=
	int datatype = -1;		//type specifier
	int assigntype = -1;	//RHS type 
	int idcheck = -1;		//check if ID 
	int check_un = 0;		//check for undeclared variables
	


	struct node{
		char token[20];
		char name[20];
		int dtype;
		int scope;
		int lineno;
		int valid;
		union value{
			float f;
			int i;
			char c;
		}val;
		
		struct node *link;

	}*first = NULL, *tmp, *crt, *lhs;

	struct node * checksym(char *);
	void addsymbol(struct node *,char *);
	
	void addInt(struct node *, int, int);
	void addFloat(struct node *, int, float);
	void addChar(struct node *, int, char);
	void addfunc(struct node *t, int, char *);
	
	void printsymtable();

	struct node * addtosymbol(struct node * n);
	void cleansymbol();

%}

%token  HASH INCLUDE STDIO STDLIB MATH STRING TIME 
%token  STRING_LITERAL HEADER_LITERAL PRINT RETURN
%left 	'+' '-'
%left 	'/' '*' '%'
%right 	'='

%union{
	int ival;
	float fval;
	char cval;
	struct node *ptr;
}


%token <ival> 	INTEGER_LITERAL 
%token <cval> 	CHARACTER_LITERAL
%token <fval> 	FLOAT_LITERAL 
%token <ptr> 	IDENTIFIER  

%token	INC_OP 	DEC_OP 	LE_OP 	GE_OP 	EQ_OP 	NE_OP
%token	MUL_ASSIGN 	DIV_ASSIGN 	MOD_ASSIGN 	ADD_ASSIGN 	SUB_ASSIGN
%token	<ival> 	CHAR 	INT 	FLOAT 	VOID
%token 	FOR 


%type <fval>	assignment_expression 	assignment_operator 
%type <fval>	primary_expression 
%type <fval>	equality_expression 
%type <fval>	relational_expression 
%type <fval>	additive_expression 
%type <fval>	multiplicative_expression 
%type <fval>	unary_expression 	unary_operator
%type <fval>	conditional_expression
%type <fval>	expression 	expression_statement
%type <fval>	postfix_expression 	


%start S

%%
S : program {
		cleansymbol();	
                printsymtable();
                return 0;
            }
  

program
	: HASH INCLUDE '<' libraries '>' program
	| HASH INCLUDE HEADER_LITERAL 	 program
	| translation_unit
	;


translation_unit
	: ext_dec
	| translation_unit ext_dec
	;


ext_dec
	: declaration
	| function_definition	
	;


libraries
	: STDIO
	| STDLIB
	| MATH
	| STRING
	| TIME
	;


compound_statement
	: '{' '}' 
	| '{' block_item_list '}'
	;


block_item_list
	: block_item
	| block_item_list block_item
	;


block_item
	: declaration
	| statement 
	| function_call ';'
	| RETURN expression_statement
	| printstat ';'
	;


printstat
	: PRINT '(' STRING_LITERAL ')' 
	| PRINT '(' STRING_LITERAL ',' expression ')'
	;


declaration
	: type_specifier init_declarator_list  ';' 
	;


statement
	: compound_statement {
						struct node *ftp;
						ftp = first;
						while(ftp!=NULL){
							if(ftp->scope == scope && ftp->valid == 1){
								ftp->valid = 0;
							}
							ftp=ftp->link;
						}
						scope--;

					}
	| expression_statement { }
	| iteration_statement
	;


iteration_statement
	: FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement	
	| FOR '(' declaration expression_statement expression ')' statement
	;


type_specifier
	: VOID 	{	datatype = $1; }	
	| CHAR 	{	datatype = $1; }	
	| INT 	{	datatype = $1; }	
	| FLOAT {	datatype = $1; }	
	;


init_declarator_list
	: init_declarator 
	| init_declarator_list ',' init_declarator
	;


init_declarator
	: IDENTIFIER '=' assignment_expression
					{	
						if($1->dtype !=- 1 && $1->scope < scope && $1->valid == 1){
							// printf("case 1 \n" );
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,$1->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							$1 = nnode;

							if (datatype == 0){	
								
								addInt($1, 0, $3);
								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat($1, 1, $3);
								if(assigntype == 2){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)$3;
								addChar($1, 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							


						}
						else if($1->dtype != -1){							

							printf("Line:%d: ", line);
							printf("\033[1;31m");
							printf("error: ");
							printf("\033[0m");
							printf("redefinition of \'%s\' \n\n",  $1->name);
						}
						else{

							if (datatype == 0){	
								
								addInt($1, 0, $3);
								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat($1, 1, $3);
								if(assigntype == 2){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)$3;
								addChar($1, 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							
						}
					}	

	| IDENTIFIER	{	//previous. a , dtype = 1(int)
						// printf("type = %d\nscope = %d\nvalid = %d", $1->dtype, $1->scope, $1->valid);
						
						if($1->dtype !=- 1 && $1->scope < scope && $1->valid == 1){
							// printf("case 1 \n" );
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,$1->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							$1 = nnode;

							if (datatype == 0){	
								addInt($1, 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat($1, 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar($1, 2, '-');
		
							}
							x = datatype;

						}
						else if($1->dtype !=- 1 ){
							printf("Line:%d: ", line);
							printf("\033[1;31m");
							printf("error: ");
							printf("\033[0m");
							printf("redefinition of \'%s\' \n\n", $1->name);
						
						}else{

							if (datatype == 0){	
								addInt($1, 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat($1, 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar($1, 2, '-');
		
							}
							x = datatype;
						
						}
					}
	;


assignment_expression
	: conditional_expression	{	$$ = $1; 	}
	| unary_expression	{ crt = lhs;  } assignment_operator assignment_expression 	//$1 = $4
			{
			
				switch(assignop){
					case 0: if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$4;
									
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = $4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 1: if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$1 + (int)$4;
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = $1+ $4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$1 + (int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 2:	if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$1 - (int)$4;
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = $1 - $4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$1 - (int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 3:	if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$1 * (int)$4;
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = $1 * $4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$1 * (int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 4:	if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$1 / (int)$4;
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = $1 / $4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$1 / (int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 5:	if(idcheck == 1){
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)$1 % (int)$4;
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (int)$1 % (int)$4;
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)$1 % (int)$4);
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;


				}
				assignop = -1;
				assigntype = -1;
			}


	;


assignment_operator
	: '='			{	assignop = 0;	}
	| ADD_ASSIGN	{	assignop = 1;	}
	| SUB_ASSIGN	{	assignop = 2;	}
	| MUL_ASSIGN	{	assignop = 3;	}
	| DIV_ASSIGN	{	assignop = 4;	}
	| MOD_ASSIGN	{	assignop = 5;	}
	;


conditional_expression
	: equality_expression 	{	$$ = $1;	}
	| equality_expression '?' expression ':' conditional_expression	
			{
				if($1 == 1){
					$$ = $3;

				}else{
					$$ = $5;
				}
			}
	;


expression_statement
	: ';'				{				}
	| expression ';' 	{		}
	;


expression
	: assignment_expression		{		}
	| expression ',' assignment_expression {		}
	;


primary_expression //fval
	: IDENTIFIER 	//struct node
				{	
					idcheck = 1;
					lhs = $1;

					if($1->dtype == -1 && check_un == 0){

						printf("Line:%d: ", line);
						printf("\033[1;31m");
						printf("error: ");
						printf("\033[0m");
						printf("use of undeclared identifier \'%s\' \n\n", $1->name);

						check_un = 0;		// set check_un = -1

					}
					else if($1->dtype == 0){
						$$ = $1->val.i;
						assigntype = 0;
					}
					else if($1->dtype == 1){
						$$ = $1->val.f;
						assigntype = 1;
					}
					else if($1->dtype == 2){
						$$ = $1->val.c;
						assigntype = 2;
					}
				}
	| INTEGER_LITERAL
				{
					$$ = $1;
					assigntype = 0;
				}
	| FLOAT_LITERAL	
				{	
					assigntype = 1;
					if(datatype == 1){
						$$ = $1;
					}
					else if(datatype == 0){
						
						$$ = (int)$1;
					}
					else if(datatype == 2){

						$$ = (int)$1;
					}
				}
	| CHARACTER_LITERAL
				{	
					assigntype = 2;
					if(datatype == 2){
						int tempc = (int)$1;
						$$ =  (float)tempc;
					}
					else if(datatype == 0){
						$$ = (int)$1;
					}
					else if(datatype == 1){
						
						$$ = (int)$1;
					}
				}
	| '(' expression ')'
				{
					$$ = $2;
				}	
	;


/*
Todo : Check order of operation in postfix and prefix ++ --
*/
postfix_expression
	: primary_expression		{	$$ = $1;	}
	| postfix_expression INC_OP	{	$1++; $$ = $1;	}
	| postfix_expression DEC_OP {	$1--; $$ = $1;	}
	;


unary_expression
	: postfix_expression	{	$$ = $1;	}
	| unary_operator unary_expression 
				{
					switch(unaryop){
						case 1:	$$ = $2;
								break;
						case 2:	$$ = -$2;
								break;
						case 3:	$$ = !$2;
								break;
						case 4:	$$ = ~((int)$2);
								break;	
						case 5:	$$ = ++$2;
								break;
						case 6:	$$ = --$2;
								break;		
					}
					unaryop = -1;
				} 
	;


unary_operator
	: '+' 		{	unaryop = 1;	}
	| '-'		{	unaryop = 2;	}
	| '!'		{	unaryop = 3;	}
	| '~'		{	unaryop = 4;	}
	| "INC_OP"	{	unaryop = 5;	}
	| "DEC_OP" 	{	unaryop = 6;	}
	;


equality_expression
	: relational_expression {	$$ = $1;	}
	| equality_expression EQ_OP relational_expression
				{ 
					if($1 == $3)
						$$ = 1;
					else
						$$ = 0;

				}
	| equality_expression NE_OP relational_expression
				{ 
					if($1 != $3)
						$$ = 1;
					else
						$$ = 0;
				}
	;


relational_expression
	: additive_expression	{	$$ = $1;	}
	| relational_expression '<' additive_expression
				{ 
					if($1 < $3)
						$$ = 1;
					else
						$$ = 0;

				}
	| relational_expression '>' additive_expression
				{ 
					if($1 > $3)
						$$ = 1;
					else
						$$ = 0;

				}
	| relational_expression LE_OP additive_expression
				{ 
					if($1 <= $3)
						$$ = 1;
					else
						$$ = 0;

				}
	| relational_expression GE_OP additive_expression
				{ 
					if($1 >= $3)
						$$ = 1;
					else
						$$ = 0;

				}		
	;


additive_expression
	: multiplicative_expression	{	$$ = $1;	}
	| additive_expression '+' multiplicative_expression 	{	$$ = $1 + $3;	}
	| additive_expression '-' multiplicative_expression		{	$$ = $1 - $3;	}
	;


multiplicative_expression
	: unary_expression			{	$$ = $1;	}
	| multiplicative_expression '*' unary_expression 	{	$$ = $1 * $3;	}
	| multiplicative_expression '/' unary_expression	
					{	
						if($3 == 0){
							printf("Line:%d: ", line);
							printf("\033[1;35m"); 
							printf("warning: ");
							printf("\033[0m");
							printf("division by zero is undefined\n\n");
							$$ = INT_MAX;		//junk value in real
						}else
							$$ = $1 / $3;	
					}
	| multiplicative_expression '%' unary_expression	
					{	
						if(assigntype == 1){
							printf("Line:%d: ", line);
							printf("\033[1;31m");
							printf("error: ");
							printf("\033[0m");
							printf("invalid operands to binary expression (\'float\' and \'float\') \n\n");
						}else{
							$$ = (int)$1 % (int)$3;	
						}

				}
									
	;


function_definition
	: type_specifier declarator compound_statement 	
				{
					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;

				}
	| declarator compound_statement 									
				{	
					printf("Line:%d: ", line);
					printf("\033[1;35m"); 
					printf("warning: ");
					printf("\033[0m");
					printf("type specifier missing, defaults to \'int\' \n");

					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;
				}
	;


function_call
	: declarator '(' identifier_list ')'
	| declarator '(' ')'
	;


declarator
	: IDENTIFIER        					
				{	
					addfunc($1, datatype, "function");	 								
				}  
	| declarator '(' parameter_list ')'		{ }			
	| declarator '(' identifier_list ')'	{ }				
	| declarator '(' ')'					{ }
	;


parameter_list
	: parameter_declaration						{}
	| parameter_list ',' parameter_declaration	{}
	;


parameter_declaration
	: type_specifier IDENTIFIER		{	addfunc($2, datatype, "param");	}
	| type_specifier				{}
	;


identifier_list
	: IDENTIFIER						{		}
	| identifier_list ',' IDENTIFIER	{		}
	;


%%


void yyerror(const char *str){
	fflush(stdout);
	printf("Line:%d: ", line);
	printf("\033[1;31m");
	printf("error: ");
	printf("\033[0m");
	printf("%s\n", str);
}


int main(){
	yyout = fopen("output.c", "w");
	printf("\n");
	yyparse();


	fclose(yyout);
	return 0;
}


void addfunc(struct node *t,int type, char *s){
	if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = 0;
        strcpy(t->token, s);
    }
}


void addInt(struct node *t,int type,int val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = val;
        strcpy(t->token, "identifier");
    }
}


void addFloat(struct node *t,int type,float val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.f = (float)val;
        strcpy(t->token, "identifier");
    }
}


void addChar(struct node *t,int type, char val) {
   	if(t->dtype == -1) {
   	    t->dtype = type;
   	    t->val.c = (char)val;
   	    strcpy(t->token, "identifier");
   	}
}


struct node * addtosymbol(struct node * n){
	if(first == NULL){
		first = n;
	}
	else{
		struct  node * ftp = first;
		while(ftp->link !=NULL) {
			ftp = ftp->link;
		}
		ftp->link = n;
	}
	return n;
}


struct node * checksym(char *vname) {
	struct node *ftp;
	struct node *rp;
	struct node *nnode;
	struct node *same;

	//not memory efficient
	// nnode = (struct node *)malloc(sizeof(struct node));
	// addsymbol(nnode,vname);


	if(first == NULL) {
		nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);
	    first = nnode;
	}
	else {
	    ftp = first;
	    while(ftp!=NULL) {

	        if(strcmp(vname,ftp->name) == 0){
	            if(ftp->scope > scope && ftp->valid == 1) {	          	
					same = ftp; 
	            	return same;
	            }	
	            else if(ftp->scope == scope && ftp->valid == 1){
	            	same = ftp;
	            	return same;
	            }          	
	            else if(ftp->scope < scope && ftp->valid == 1){
	         		check_un = 1;	//no error 

	         		same = ftp;
	            	return same;
	         			            		         				         		       	         
	            } 
	          	else if(ftp->scope > scope && ftp->valid == 0){
	          		check_un = 0;	//undeclared
	          	}

	        }            
	        rp = ftp;
	        ftp = ftp->link;
	    }
	    nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);

	    rp->link = nnode;
	}
	return nnode;
}


void addsymbol(struct node *tp, char *vname) {
    strcpy(tp->name,vname);
    tp->dtype = -1;
    tp->link = NULL;
    tp->scope = scope;
    tp->valid = 1;
    tp->lineno = line;
}


void cleansymbol(){
	struct node** pp = &first; 
    while (*pp) { 
  
        struct node* entry = *pp; 
 
        if (entry->dtype == -1  ) { 
            *pp = entry->link; 
            free(entry); 
        }
        else if(strcmp(entry->name,"main")== 0 && strcmp(entry->token, "function")==0){	//remove main entry from symbol table
        	*pp = entry->link; 
            free(entry); 
        }
        // Else move to next 
        else
            pp = &(entry->link); 
    } 
}


void printsymtable(){
	struct node *ftp;
    ftp=first;
    printf("\n\nSymbol Table\n\n");
	printf("   Symbol\t\tName\t  Type\t      Scope\t   Line Number\t       Value \n");
	printf("-------------------------------------------------------------------------------------------------\n");
   
    while(ftp!=NULL) {
        char data_type[10];
        if(ftp->dtype==0)
        	strcpy(data_type,"int");
        if(ftp->dtype==1)
        	strcpy(data_type,"float");
        if(ftp->dtype==2)
        	strcpy(data_type,"char");
        if(ftp->dtype==3)
        	strcpy(data_type,"void");

        printf("%11s\t%12s\t%6s\t\t%d\t\t%d\t\t",ftp->token, ftp->name, data_type, ftp->scope, ftp->lineno);

        if(ftp->dtype == 0){
        	if(ftp->val.i == INT_MIN)
        		printf("-\n");
        	else
           		printf("%d\n",ftp->val.i);
        }
        else if(ftp->dtype == 1){
        	if(ftp->val.f == INT_MIN)
        		printf("-\n");
        	else
           		printf("%f\n",ftp->val.f);
       	}
        else if(ftp->dtype == 2){
            printf("%c\n",ftp->val.c);
        }
        else if(strcmp(ftp->token, "function")==0){
        	printf("-\n");
        }
        else{
	        printf("-	Delete it\n");
	    }
        ftp=ftp->link;
    }
    printf("\n\n\n");
}