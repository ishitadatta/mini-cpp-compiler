
%{
    #include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	//#include "lex.yy.c"
	int yylex();
	int yydebug = 0;
	void yyerror(const char*);
	extern int yylineno;
	extern int st[100];
	extern int top;
	extern int count;
	extern void display();
	extern void insert_in_st(char*, char*, int, char*);
	char st1[100][100];
	char i_[2]="0";
	int temp_i = 0;				//current available temporary number
	char tmp_i[10];				//an array to hold temporary variable number as string. We assume this is below 999999999				
	char temp[10]="";			//an array to hold temporary varialbe name as string. We assume this is below T999999999	
	int label[20];
	int lnum = 0;				//current available label number.
	int ltop = 0;
	int abcd = 0;
	int l_while=0;
	int l_for=0;
	int flag_set = 1;
	int stop = -1;				//top of stack
	char G_val[10];
	FILE* ast_tree_output;


	typedef struct quadruples
  	{
  	  char *op;
  	  char *arg1;
  	  char *arg2;
  	  char *res;
  	}quad;
  	int quadindex = 0;			//current index of Q to store the quadruple in.
	quad Q[100];

	void push(char *a)			//push to top of stack
	{
		strcpy(st1[++stop],a);
	}

	// Statements -helper
	void TAC()				//to be called after any expression. say expr is b*c -> pop top three , ti = b*c and insert ti.
	{
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = %s %s %s\n",temp,st1[stop-2],st1[stop],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    Q[quadindex].arg2 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,st1[stop]);
	    strcpy(Q[quadindex].arg1,st1[stop-2]);
	    strcpy(Q[quadindex].arg2,st1[stop - 1]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
	    stop-=2;
	    strcpy(st1[stop],temp);
		temp_i++;
	}

	// Assignment Operations need a different TAC function as the operation performed is different
	void TAC_assign()
	{
	    printf("%s = %s\n",st1[stop-2],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    strcpy(Q[quadindex].op,"=");
	    strcpy(Q[quadindex].arg1,st1[stop - 1]);
	    strcpy(Q[quadindex].res,st1[stop-2]);
	    quadindex++;
	    stop-=2;
	}

	void TAC_assign_back()
	{
		temp_i--;
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
		temp_i++;
		printf("%s = %s\n",G_val,temp);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(G_val));
	    strcpy(Q[quadindex].op,"=");
		strcpy(Q[quadindex].arg1,temp);
	    strcpy(Q[quadindex].res,G_val);
		quadindex++;
	}
	// ICG - While

	// Create label for while
	void While_Loop_Label()
	{
	
	    label[ltop++] = lnum++;			
	    printf("L%d: \n", label[ltop - 1]);			// print label and increase label number for next use	
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);		//a label's quad 	
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum + 2));   //lum + 2 is a safe way to have enough space for L0, L1, ... etc. 
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
		x[0] = '0' + label[ltop - 1];
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// While Loop Condition
	void While_loop_cond()
	{
	 	strcpy(temp,"T");			
	 	sprintf(tmp_i, "%d", temp_i);		//if temp_i = 0, tmp_i has "0"		
	 	strcat(temp,tmp_i);					//temp has "T0"
	 	printf("%s = not %s\n",temp,st1[stop]);		//T0 has not of condition

		//since this is a unary operator, one of the operands is NULL
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

		//if T0 goto label which will be placed after body
		//in this case op -> if, arg1 -> T0 , res -> L1
	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	 	temp_i++;
		
		label[ltop++] = lnum;
		lnum++;
	}

	// End While loop
	void While_END()			// in the end insert goto label and also insert the label which should be branched to if condition fails
	{
		printf("goto L%d \n",label[ltop - 2]);	//ltop - 2 contains the label to be branched if true
		Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(l_while+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x[10];
	    sprintf(x,"%d",label[ltop]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;

	    printf("L%d: \n", label[ltop - 1]);		//ltop - 1 contains the label to be branched if false
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x1[10];
	    sprintf(x1,"%d", label[ltop - 1]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
		ltop -= 2;							//since these labels have been used, decrease ltop by two 
	}

	// ICG - IF

	// Handle Initial IF as well as else if
	void IFSTMT()
	{

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
		
	    label[ltop++] = lnum;
		++lnum;									//increase lnum for next needed label.
		
	}

	void Elif()
	{
		printf("L%d: \n",label[--ltop]);		//print the top in label stack as this is where runtime should come if cond is false
	    										//increase lable for the next time										
		

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
		

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;

	    label[ltop++] = lnum;							//store this as top of label stack and increase ltop
		++lnum;										//increase lnum for next needed label.
	}


	// Handle cleanup

	void if_else_cleanup()
	{
		int y;
		y = label[--ltop];
		printf("L%d: \n",y);
		Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(y+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d",y);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// ICG - For

	//Define Label for "FOR"
	void FOR_label()
	{
		label[ltop++] = lnum++;						//label stack is used for nested loops. Increase lnum for next label use
	    // l_for = lnum;
	    printf("L%d: \n", label[ltop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d", label[ltop - 1]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// Handle Loop Condition
	void FOR_Condition()
	{

	    strcpy(temp,"T");						//lets take condition as b < 4. This effectively says T1 = not T0. Note that expr would have made T0 = b < 4
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);				// if T1 goto L1. Increase labele
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
	    label[ltop++] = lnum;								//store label in stack and increase lnum.
	    lnum++;

	    printf("goto L%d\n",lnum);							//goto body part. goto L2
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x1[10];
	    sprintf(x1,"%d",lnum);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
	    label[ltop++] = lnum++;							//store label in stack and increase lnum.


	
	    printf("L%d: \n",lnum);							//L3:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x2[10];
	    sprintf(x2,"%d",lnum);
	    char l2[]="L";
	    strcpy(Q[quadindex].res,strcat(l2,x2));
	    quadindex++;
		label[ltop++] = lnum++;
	}

	// Increment
	void FOR_INC_Cond()
	{
	    int x;
	    x = label[ltop - 4];							//after processing increment, should go and evaluate condition again. goto L0
	    printf("goto L%d \n",x);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 2]);							//this is where after processing condition you should come to . L2:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 2]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
	}

	// Ending of for
	void FOR_End()
	{
	    int x;
	    x = label[ltop - 1];								//goto L3 (increment condition)
	    printf("goto L%d \n",x);

	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 3]);							//L1:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 3]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
		ltop -= 4;	
	}

	char LineBreaker[] = "\n_______________________________________________________________________________________________________\n";
	
	//node in AST
	typedef struct ASTNode
	{
		struct ASTNode *left;
		struct ASTNode *right;
		char *token;
	} node;
	
	node *Construct_AST(node *left, node *right, char *token)
	{
		node *newnode = (node *)malloc(sizeof(node));
		char *newstr = (char *)malloc(strlen(token)+1);
		strcpy(newstr, token);
		newnode->left = left;
		newnode->right = right;
		newnode->token = newstr;
		return(newnode); 
	}
	
	void Display_tree(node *tree)
	{
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", "(");
		// fprintf(ast_tree_output, " %s ", tree->token);
		// if (tree->left)
		// 	Display_tree(tree->left);
		// if (tree->right)
		// 	Display_tree(tree->right);
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", ")");
	}
%}

%union {
    char *str;
	struct ASTNode *NODE;
}



%define parse.error verbose

%token <str> T_keyword T_int T_main T_type T_return T_for T_if T_else T_while T_InputStream T_OutputStream 
%token <str> T_openParenthesis T_closedParanthesis T_openFlowerBracket T_closedFlowerBracket 
%token <str> T_RelationalOperator T_LogicalOperator T_UnaryOperator 
%token <str> T_AssignmentOperator  T_Semicolon T_identifier T_numericConstants T_stringLiteral
%token <str> T_character T_plus T_minus T_mod T_divide T_multiply error
%token <str> T_whiteSpace T_shortHand

%left T_LogicalAnd T_LogicalOr
%left T_less T_less_equal T_greater T_greater_equal T_equal_equal T_not_equal
%left T_plus T_minus
%left T_multiply T_divide T_mod

%type <NODE> Start block_end_flower block Multiple_stmts stmt
%type <NODE> if_stmt Multiple_stmts_not_if elseif_else_empty stmt_without_if
%type <NODE> expr_without_constants expr expr_or_empty closeflower
%type <NODE> Assignment_stmt
%type <NODE> for_stmt while_stmt 
%type <NODE> idid nc sc
%type <NODE> expr_or_empty_with_semicolon_and_assignment  expr_or_empty_with_assignment_and_closed_parent

%%

/*Flower brackets are mandatory for main*/


Start : T_int T_main T_openParenthesis T_closedParanthesis openflower block_end_flower  	{$$ = $6;}	//openflower is T_openflowerBracket


/* This production assumes flower bracket has been opened*/
block_end_flower : stmt Multiple_stmts 							{$$ = $1;}		//Multiple_stmts closes the flower bracket. 
				| closeflower 									{$$ = Construct_AST(NULL, NULL, ";"); }	//closeflower is T_closedFlowerBracket. 
				//closeflower is only parsed here for an empty block 


/*This takes care of statements like if(...);. Note that to include multiple statements, a block has to open with a flower bracket*/
block :  openflower block_end_flower						{$$ = $2;}		//takes care of {}, {stmt, stmt, ...}
	    | stmt												{$$ = $1;}		//takes care of just a single statement followed by semicolon
	    | T_Semicolon										{$$ = Construct_AST(NULL, NULL, ";"); }
		;

/* block would cover anything following statement. consider the for statement for example. All possiblities are:
for(expr;expr;expr);													(block -> ;)
for(...) stmt          , where stmt contains T_Semicolon				(block -> stmt)
for(...){}																(block -> {block_end_flower -> {})
for(...){stmt, stmt, stmt, ...}											(block -> {block_end_flower -> {smt Multiple_stmts})
for(...){stmt, if/while/for{stmt, stmt.}} , this is achieved implicity because stmt in previous can in turn be if or for while
*/


Multiple_stmts : stmt Multiple_stmts						{$$ = $1;}
		|closeflower 										{$$ = Construct_AST(NULL, NULL, ";"); }
		;

/*
A statement can be if, while, for, assignment or expression not assigned to anything in the scope of this project.
*/

stmt : expr T_Semicolon					{$$ = $1; Display_tree($$); fprintf(ast_tree_output, "\n");}
		| if_stmt						{$$ = $1; Display_tree($$); fprintf(ast_tree_output, "\n");}
		| while_stmt					{$$ = $1; Display_tree($$);fprintf(ast_tree_output, "\n");}
		| for_stmt						{$$ = $1; Display_tree($$); fprintf(ast_tree_output, "\n");}
		| Assignment_stmt T_Semicolon	{$$ = $1; Display_tree($$); fprintf(ast_tree_output, "\n");}
		| error T_Semicolon 			{$$ = Construct_AST(NULL, NULL, ";"); }
		;


//for_stmt : T_for T_openParenthesis expr_with_semicolon expr_with_semicolon expr_or_empty T_closedParanthesis block

for_stmt : T_for T_openParenthesis expr_or_empty_with_semicolon_and_assignment {FOR_label();} expr_or_empty_with_semicolon_and_assignment {FOR_Condition();} expr_or_empty_with_assignment_and_closed_parent {FOR_INC_Cond();} block	{{ 	FOR_End();node* left;
																																	node* right;
																																	left = Construct_AST($5, $7, "Cond_Loopstmts");
																																	right = Construct_AST($3,$5,"Init_&_Increment");
																																	$$ = Construct_AST(left,right,"FOR");
																																	}}



// Condition : 		{}

while_stmt : T_while {While_Loop_Label();} T_openParenthesis expr T_closedParanthesis {While_loop_cond();} block			{While_END();$$ = Construct_AST($3, $5, "While"); }
//While_Loop_Label() and While_loop_cond() are  embedded actions
//while_end() adds goto label 

if_stmt : T_if T_openParenthesis expr T_closedParanthesis {IFSTMT();} block elseif_else_empty {$$ = Construct_AST($3, $6, "IF");}

elseif_else_empty : T_else T_if T_openParenthesis expr T_closedParanthesis {;Elif();} block elseif_else_empty {$$ = Construct_AST($4, $7, "ELSEIF"); }
					| T_else {if_else_cleanup();} Multiple_stmts_not_if {$$ = $3;}
					| T_else {if_else_cleanup();} openflower block_end_flower {$$ = $4;}
					| {if_else_cleanup(); $$ = Construct_AST(NULL, NULL, ";"); }
					;

Multiple_stmts_not_if : stmt_without_if Multiple_stmts {$$ = $1;}
					|T_Semicolon {$$ = Construct_AST(NULL, NULL, ";"); }
					;

stmt_without_if : expr T_Semicolon										{$$ = $1;}
					| Assignment_stmt T_Semicolon						{$$ = $1;Display_tree($$);fprintf(ast_tree_output, "\n");}
					| while_stmt										{$$ = $1;}
					|for_stmt											{$$ = $1;}
					;

Assignment_stmt: 	idid T_AssignmentOperator expr											{push("=");TAC_assign();$$ = Construct_AST($1,$3,"=");}
					| idid T_shortHand expr													{push("se");TAC_assign();$$ = Construct_AST($1,$3,"SE"); }
					| T_type idid T_AssignmentOperator expr_without_constants   			{push("=");strcpy(G_val,$2->token);TAC_assign_back();insert_in_st($1, $2->token, st[top], "j");$$ = Construct_AST($2,$4,"=");}	
					| T_type idid T_AssignmentOperator sc   {push("=");TAC_assign();insert_in_st($1, $2->token, st[top], $4->token);$$ = Construct_AST($2,$4,"=");}
					| T_type idid T_AssignmentOperator nc   {push("=");TAC_assign();insert_in_st($1, $2->token, st[top], $4->token);$$ = Construct_AST($2,$4,"=");}
					| T_int idid T_AssignmentOperator expr_without_constants    			{push("=");strcpy(G_val,$2->token);TAC_assign_back();insert_in_st($1, $2->token, st[top], "j");$$ = Construct_AST($2,$4,"=");}
					| T_int idid T_AssignmentOperator nc    {push("=");TAC_assign();insert_in_st($1, $2->token, st[top], $4->token);$$ = Construct_AST($2,$4,"=");}
				;



expr_without_constants:  idid								{$$ = $1;}
		| expr T_plus expr									{push("+");TAC();$$ = Construct_AST($1, $3, "+");}
		| expr T_minus expr									{push("-");TAC();$$ = Construct_AST($1, $3, "-");}
		| expr T_divide expr								{push("/");TAC();$$ = Construct_AST($1, $3, "/");}
		| expr T_multiply expr								{push("*");TAC();$$ = Construct_AST($1, $3, "*");}
		| expr T_mod expr									{push("%");TAC();$$ = Construct_AST($1, $3, "%");}
		| expr T_LogicalAnd expr							{push("&");TAC();$$ = Construct_AST($1, $3, "&");}
		| expr T_LogicalOr expr								{push("|");TAC();$$ = Construct_AST($1, $3, "|");}
		| expr T_less expr									{push("<");TAC();$$ = Construct_AST($1, $3, "<");}				
		| expr T_less_equal expr							{push("<=");TAC();$$ = Construct_AST($1, $3, "<=");}
		| expr T_greater expr								{push(">");TAC();$$ = Construct_AST($1, $3, ">");}
		| expr T_greater_equal expr							{push(">=");TAC();$$ = Construct_AST($1, $3, ">=");}
		| expr T_equal_equal expr							{push("==");TAC();$$ = Construct_AST($1, $3, "==");}
		| expr T_not_equal expr								{push("!=");TAC();$$ = Construct_AST($1, $3, "!=");}
		;

//an expression without semicolon at end.
expr: 	nc													{$$ = $1;}
		| sc												{$$ = $1;}								
		| idid												{$$ = $1;}
		| expr T_plus expr									{push("+");TAC();$$ = Construct_AST($1, $3, "+");}	//push into stack and call TAC which generates corresponding TAC. Also generate node for AST
		| expr T_minus expr									{push("-");TAC();$$ = Construct_AST($1, $3, "-");}
		| expr T_divide expr								{push("/");TAC();$$ = Construct_AST($1, $3, "/");}
		| expr T_multiply expr								{push("*");TAC();$$ = Construct_AST($1, $3, "*");}
		| expr T_mod expr									{push("%");TAC();$$ = Construct_AST($1, $3, "%");}
		| expr T_LogicalAnd expr							{push("&");TAC();$$ = Construct_AST($1, $3, "&");}
		| expr T_LogicalOr expr								{push("|");TAC();$$ = Construct_AST($1, $3, "|");}
		| expr T_less expr									{push("<");TAC();$$ = Construct_AST($1, $3, "<");}				
		| expr T_less_equal expr							{push("<=");TAC();$$ = Construct_AST($1, $3, "<=");}
		| expr T_greater expr								{push(">");TAC();$$ = Construct_AST($1, $3, ">");}
		| expr T_greater_equal expr							{push(">=");TAC();$$ = Construct_AST($1, $3, ">=");}
		| expr T_equal_equal expr							{push("==");TAC();$$ = Construct_AST($1, $3, "==");}
		| expr T_not_equal expr								{push("!=");TAC();$$ = Construct_AST($1, $3, "!=");}
		;

expr_or_empty_with_semicolon_and_assignment: expr_or_empty T_Semicolon			{$$ = $1;}
	| Assignment_stmt T_Semicolon												{$$ = $1;}

expr_or_empty_with_assignment_and_closed_parent: expr_or_empty T_closedParanthesis							{$$ = $1;}
	| Assignment_stmt T_closedParanthesis																	{$$ = $1;}

idid : T_identifier										{push((char*)yylval.str);$$ = Construct_AST(NULL, NULL, (char*)yylval.str); }	//push in stack. This will be used to generate ICG. Also, create leaf node for AST.
		;
sc 	 : T_stringLiteral									{push((char*)yylval.str);$$ = Construct_AST(NULL, NULL, (char*)yylval.str); }
		;
nc	 : T_numericConstants								{push((char*)yylval.str);$$ = Construct_AST(NULL, NULL, (char*)yylval.str); }
		;

expr_or_empty: expr										{$$ = $1;}
				| {$$ = Construct_AST(NULL, NULL, ";"); }
				;

openflower: T_openFlowerBracket {};
closeflower: T_closedFlowerBracket {};


%%

void yyerror(const char *str) 
{ 
	printf("Error | Line: %d\n%s\n",yylineno,str);
} 

void symboldisplay()
{
	//printf("Hi");
	//printf("%s",LineBreaker);
	//for (int i = 0;i < stop;i++)
	//{
	//	printf("%s\t",st1[i]);
	//}

	// Display Quads
	printf("%s",LineBreaker);
	//printf("Quadruplets\n");
	for(int i=0;i<quadindex;i++)
    {
        printf("%-8s \t %-8s \t %-8s \t %-6s \n",Q[i].op,Q[i].arg1,Q[i].arg2,Q[i].res);
    }
	printf("%s",LineBreaker);
}

int isDigit(char* in)
{
	for(int i = 0; i < strlen(in); ++i)
	{
		if(!isdigit(in[i])) return 0;
	}
	return 1;
}

void icg_optimize()
{
	
	for(int i = 0; i < quadindex; ++i)
	{
		if((strcmp(Q[i].op, "+") == 0 || strcmp(Q[i].op, "-") == 0 || strcmp(Q[i].op, "*") == 0 || strcmp(Q[i].op, "/") == 0
		|| strcmp(Q[i].op, "%") == 0 || strcmp(Q[i].op, "&") == 0 || strcmp(Q[i].op, "|") == 0 || strcmp(Q[i].op, "^") == 0)
		&& isDigit(Q[i].arg1) && isDigit(Q[i].arg2))
		{
			
			int res;
			if(strcmp(Q[i].op, "+") == 0)
				res = atoi(Q[i].arg1) + atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "-") == 0)
				res = atoi(Q[i].arg1) - atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "*") == 0)
				res = atoi(Q[i].arg1) * atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "/") == 0)
				res = atoi(Q[i].arg1) / atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "%") == 0)
				res = atoi(Q[i].arg1) % atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "&") == 0)
				res = atoi(Q[i].arg1) & atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "|") == 0)
				res = atoi(Q[i].arg1) | atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "^") == 0)
				res = atoi(Q[i].arg1) ^ atoi(Q[i].arg2);

			strcpy(Q[i].op, "=");
			sprintf(Q[i].arg1, "%d", res);

			Q[i].arg2 = NULL;

		}
	}
}

int main()
{
 	ast_tree_output = fopen("ast_tree_output.txt", "w");
	if(ast_tree_output == NULL)
	{
		printf("Could not open output file, aborting\n");
		exit(1);
	}
	yyparse();				//parse through the input. This step effectively also fills the symbol table, generates the AST and computes & prints ICG.
	
	printf("\n**************************************Symbol Table****************************************\n");
	
	display();				//display the symbol table. The function is defined in lex.l
	
	printf("\n*************************************************************************************************\n");
	
	printf("Intermediate Code Generation (Quadraple Form):\n");
	symboldisplay();

	/*icg_optimize();

	printf("After Optimization:\n");
	symboldisplay();*/
	fclose(ast_tree_output);
	return 0;
}
