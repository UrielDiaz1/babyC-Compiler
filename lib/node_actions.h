#ifndef NODE_ACTIONS_H
#define NODE_ACTIONS_H
#include <stdlib.h>
#include <stdio.h>

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum {ADD_OP, MULT_OP, DIV_OP, SUB_OP, OR_OP, AND_OP, EQ_OP, LE_OP, GE_OP, NE_OP, LT_OP, GT_OP} ASTOp; 

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; 		// The actual operation (add, mult, etc)
	int num;  		// Need to store the actual value for number nodes
	char *name; 	// Need to store the actual variable name for ident nodes
	ASTNode* left;  // Left child
	ASTNode* right; // Right child
	int offset;
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // A pointer used to link statement nodes together in a statement list.

// Depending on your implementation, you may need to add other fields to this struct .
};

// The error function.
extern void yyerror(char *);

// Declare functions to create the different kinds of ASTNodes.
// These functions are called by the code embedded in the grammar.
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateNumNode(int num);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* CreateAssignmentNode(ASTNode* name, ASTNode* expr);
ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList);
ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* stList1, ASTNode* stList2);
ASTNode* CreateOrNode(ASTNode* cond, ASTNode* lterm);
ASTNode* CreateAndNode(ASTNode* lterm, ASTNode* lfactor);
ASTNode* CreateCompareNode(ASTNode* exprLeft, int op, ASTNode* exprRight);
ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList);

// This is the function that generates ILOC code after the construction of the AST
int GenerateILOC(ASTNode* node);
int GetNextReg();
#endif
