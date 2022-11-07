#ifndef YOUR_CODE_H
#define YOUR_CODE_H

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum {ADD_OP, MULT_OP, DIV_OP, SUB_OP, OR_OP, AND_OP, EQ_OP, NE_OP, LE_OP, GE_OP} ASTOp; 

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list

// Depending on your implementation, you may need to add other fields to this struct 

};

// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:
ASTNode* CreateDeclarationListNode(ASTNode* dn, ASTNode* dnList);
void AddDeclaration(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* CreateAssignmentNode(char* name, ASTNode* expr);
ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateNumNode(int num);
ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList);
ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* stList1, ASTNode* stList2);
ASTNode* CreateOrNode(ASTNode* cond, ASTNode* lterm);
ASTNode* CreateAndNode(ASTNode* lterm, ASTNode* lfactor);
ASTNode* CreateCompareNode(ASTNode* exprLeft, ASTOp op, ASTNode* exprRight);
ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList);

// Need a function to add a declaration to your symbol table
void AddDeclaration(char* name);

// This is the function that generates ILOC code after the construction of the AST
//void GenerateILOC(ASTNode* node);
#endif
