#include "your_code.h"
#include <stdlib.h>
#include <stdio.h>


// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_NUM; 
        node->num = num;
        return node;
}


ASTNode* CreateIdentNode(char* name)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_IDENT;
        node->name = name;
        return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
        ASTNode* node = stList;
        node->next = st;
        return node;
}

ASTNode* CreateDeclarationListNode(ASTNode* dn, ASTNode* dnList)
{
        ASTNode* node = dnList;
        node->next = dn;
        return node;
}

ASTNode* CreateAssignmentNode(char* name, ASTNode* expr)
{
        ASTNode* node = expr;
        node->name = name;
        node->type = ASTNODE_ASSIGN;
        return node;
}

ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = expr;
        node->right = term;
        node->op = ADD_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = expr;
        node->right = term;
        node->op = SUB_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = term;
        node->right = factor;
        node->op = MULT_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = term;
        node->right = factor;
        node->op = DIV_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = cond;
        node->right = stList;
        node->type = ASTNODE_IF;
        return node;
}

ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* stList1, ASTNode* stList2)
{
        ASTNode* node = stList1;
        node->left = cond;
        node->right = stList2;
        node->type = ASTNODE_IF;
        return node;
}

ASTNode* CreateOrNode(ASTNode* cond, ASTNode* lTerm)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = cond;
        node->right = lTerm;
        node->type = ASTNODE_LOGIC_OP;
        node->op = OR_OP;
        return node;
}

ASTNode* CreateAndNode(ASTNode* lTerm, ASTNode* lFactor)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = lTerm;
        node->right = lFactor;
        node->type = ASTNODE_LOGIC_OP;
        node->op = AND_OP;
        return node;        
}

ASTNode* CreateCompareNode(ASTNode* exprLeft, ASTOp op, ASTNode* exprRight)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = exprLeft;
        node->right = exprRight;
        node->type = ASTNODE_COMPARE;
        node->op = op;
        return node;
}

ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->left = cond;
        node->right = stList;
        node->type = ASTNODE_WHILE;
        return node;
}

////////////////////////////////////////////////////////////////////////////

#define MAX_NAME 256
#define TABLE_SIZE 20

typedef struct ident_name {
    char name[MAX_NAME];
    struct ident_name *next;
} ident_name;

ident_name *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

bool check_name_validity(char* name) {
    if(!isalpha(name[0])) {
        printf("Identifier name '%s' does not start with an alphabetic character.\n", name);
        printf("Terminating program.\n");
        EXIT_FAILURE;
    }
    return true;
}

void *hash_table_lookup(char *name) {
    int index = hash(name);
    ident_name *tmp = hash_table[index];
    while(tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        tmp = tmp->next;
    }
    if(tmp != NULL) {
        printf("The identifier name %s is already in used.\n", tmp->name);
        printf("Terminating program.\n");
        EXIT_FAILURE;
    }
}

bool hash_table_insert(ident_name *p) {
    if(p == NULL) {
        printf("Unable to insert null ident_name pointer.\n")
        EXIT_FAILURE;
    }
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

void AddDeclaration(char* name)
{
        if(check_name_validity) {
                hash_table_lookup(name);
                ident_name ident = {.name = name};
                hash_table_insert(&ident);
        }
}

// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

