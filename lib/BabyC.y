%{
	#include <stdio.h>
	#include "your_code.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here 
%initial-action 
{

}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	struct ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

// Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

// Specify the type for each non-terminal in the grammar. Here are some samples:
// Add the rest of the types for the grammar's symbols
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> If
%type <node> Condition
%type <node> LTerm
%type <node> LFactor
%type <node> Compare
%type <node> Op
%type <node> While

%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot=$6;} // Store the AST root node in gASTRoot
;

// Note that a DeclarationList may be empty
DeclarationList: {$$ = NULL;} 
				| Declaration DeclarationList   {$$ = CreateDeclarationListNode($1,$2); printf("Adding a declaration to a declaration list \n");} 
;

Declaration: "int" IDENT ';' {AddDeclaration($2); printf("Processing declaration of %s\n", $2);}
;

StatementList: {$$ = NULL;} 
               | Statement StatementList	{$$ = CreateStatementListNode($1,$2); printf("Adding a statement to a statement list \n");}
;

Statement: Assignment   {$$ = $1; printf("Creating Assignment Node");}
		 | If           {$$ = $1;}
		 | While        {$$ = $1;}
;

Assignment: IDENT '=' Expr ';'        {$$ = CreateAssignmentNode($1, $3); printf("Creating left-hand IDENT node for %s\n", $1);}
;

Expr: Term              {$$ = $1;}
	| Expr '+' Term     {$$ = CreateAdditionNode($1, $3); printf("Creating Addition node");}
	| Expr '-' Term     {$$ = CreateSubtractionNode($1, $3); printf("Creating Subtraction node");}
;

Term: Factor            {$$ = $1;}
	| Term '*' Factor   {$$ = CreateMultiplicationNode($1, $3); printf("Creating Multiplication node");}
	| Term '/' Factor   {$$ = CreateDivisionNode($1, $3); printf("Creating Division node");}
;

Factor: IDENT 		    {$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
	  | NUM 		    {$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
	  | '('Expr')'	    {$$ = $2; printf("Creating Expression node in parentheses");}
;

If: "if" '(' Condition ')' '{' StatementList '}'								{$$ = CreateIfNode($3, $6); printf("Creating if Statement node");}
  | "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}'   {$$ = CreateIfElseNode($3, $6, $10); printf("Creating if-else Statement node");}
;

Condition: LTerm                  {$$ = $1;}
		 | Condition "||" LTerm   {$$ = CreateOrNode($1, $3); printf("Creating OR node");}
;

LTerm: LFactor                    {$$ = $1;}
	 | LTerm "&&" LFactor         {$$ = CreateAndNode($1, $3); printf("Creating AND node");}
;

LFactor: Compare                  {$$ = $1;}
;

Compare: Expr Op Expr             {$$ = CreateCompareNode($1, $2, $3); printf("Creating Compare node");}
;

Op: "=="	{$$ = $1;}
  | "!="	{$$ = $1;}
  | "<"		{$$ = $1;}
  | ">"		{$$ = $1;}
  | "<="	{$$ = $1;}
  | ">="	{$$ = $1;}
;

While: "while" '(' Condition ')' '{' StatementList '}' {$$ = CreateWhileNode($3, $6); printf("Creating a while loop node\n");}
;


%%
