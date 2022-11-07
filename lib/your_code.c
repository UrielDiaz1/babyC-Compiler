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

void AddDeclaration(char* name)
{
        if(!isalpha(name[0])) {
                printf("Identifier name does not start with an alphabetic character.\n");
                printf("Terminating program.\n");
                EXIT_FAILURE;
        }


}

// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

