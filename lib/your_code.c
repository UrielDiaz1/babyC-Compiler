#include "your_code.h"

ident_name *symbol_table[TABLE_SIZE];

/// @brief      Creates a num leaf node.
/// @param num  Integer to be stored in the node.
/// @return     Returns a num leaf node.
ASTNode* CreateNumNode(int num) {
        // Allocate memory to num node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateNumNode.");
        }

        node->type = ASTNODE_NUM; 
        node->num = num;
        return node;
}

/// @brief      Creates an ident node.
/// @param name Pointer of identifier name to be stored in the node.
/// @return     Returns an ident node.
ASTNode* CreateIdentNode(char* name) {
        // Checks if name pointer is null.
        if(!name) {
                yyerror("Null name pointer in CreateIdentNode.");
        }

        // Checks if identifier has been assigned.
        if(!symbol_table_lookup(name)) {
                yyerror("Ident not declared.");
        
        }

        // Allocates memory for ident node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateIdentNode.");
        }

        node->type = ASTNODE_IDENT;
        node->name = name;
        return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList) {
        // Allocates memory for statement list node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateStatementListNode.");
        }
        
        // Attach statement as left child if it's not null.
        if(st) {
                node->left = st;
        }

        // Attach statement list as right child if it's not null.
        if(stList) {
                node->right = stList;
        }
        return node;
}

/// @brief        Creates a declaration list node.
/// @param dn     Reduced declaration node.
/// @param dnList Reduced declaration list node.
/// @return       Returns a declaration list node.
ASTNode* CreateDeclarationListNode(ASTNode* dn, ASTNode* dnList) {
        // Allocates memory for declaration list node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateDeclarationListNode.");
        }

        // Attach declaration as left child if not null.
        if(dn) {
                node->left = dn;
        }

        // Attach declaration list as right child if it's not null.
        if(dnList) {
                node->right = dnList;
        }
        return node;
}

/// @brief      Creates an assignment node.
/// @param name Name of the LHS identifier.
/// @param expr Reduced expression node. 
/// @return     Returns an assignment node.
ASTNode* CreateAssignmentNode(char* name, ASTNode* expr) {
        // Checks if name pointer is null.
        if(!name) {
                yyerror("Null name pointer in CreateAssignmentNode.");
        }

        // Checks if expr node is null.
        if(!expr) {
                yyerror("Null Expr node in CreateAssignmentNode.");
        }

        // Checks if identifier has been assigned.
        if(!symbol_table_lookup(name)) {
                yyerror("Ident not declared.");
        }

        // Allocates memory to assignment node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateAssignmentNode.");
        }
        
        node->left = CreateIdentNode(name);
        node->right = expr;


        node->name = name;
        node->type = ASTNODE_ASSIGN;
        node->op = EQ_OP;
        return node;
}

/// @brief      Creates an addition node.
/// @param expr Reduced expression node.
/// @param term Reduced term node.
/// @return     Returns an addition node.
ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term) {
        // Check if expression node is null.
        if(!expr) {
                yyerror("Null Expr node in addition node.");
        }

        // Checks if term node is null.
        if(!term) {
                yyerror("Null Term node in addition node.");
        }

        // Allocates memory for addition node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateAdditionNode.");
        }

        node->left = expr;
        node->right = term;
        node->op = ADD_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

/// @brief      Creates a subtraction node.
/// @param expr Reduced expression node.
/// @param term Reduced term node. 
/// @return     Returns a subtraction node.
ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term) {
        // Check if expression node is null.
        if(!expr) {
                yyerror("Null Expr node in subtraction node.");
        }

        // Checks if term node is null.
        if(!term) {
                yyerror("Null Term node in subtraction node.");
        }

        // Allocates memory for subtraction node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateSubtractionNode.");
        }

        node->left = expr;
        node->right = term;
        node->op = SUB_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

/// @brief        Creates a multiplication node.
/// @param term   Reduced term node.
/// @param factor Reduced factor node.
/// @return       Returns a multiplication node.
ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor) {
        // Check if term node is null.
        if(!term) {
                yyerror("Null Term node in multiplication node.");
        }

        // Checks if factor node is null.
        if(!factor) {
                yyerror("Null Factor node in multiplication node.");
        }

        // Allocates memory for multiplication node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateMultiplicationNode.");
        }

        node->left = term;
        node->right = factor;
        node->op = MULT_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

/// @brief        Creates a division node.
/// @param term   Reduced term node.
/// @param factor Reduced factor node.
/// @return       Returns a division node.
ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor) {
        // Check if term node is null.
        if(!term) {
                yyerror("Null Term node in division node.");
        }

        // Checks if factor node is null.
        if(!factor) {
                yyerror("Null Factor node in division node.");
        }

        // Allocates memory for division node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateDivisionNode.");
        }

        node->left = term;
        node->right = factor;
        node->op = DIV_OP;
        node->type = ASTNODE_ARITH_OP;
        return node;
}

/// @brief        Creates an if node.
/// @param cond   Reduced condition node.
/// @param stList Reduced statement list node.
/// @return       Returns an if node.
ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList) {
        // Checks if condition node is null.
        if(!cond) {
                yyerror("Null condition node in if node.");
        }

        // Allocates memory for if node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateIfNode.");
        }

        node->left = cond;

        // If the statement list is not empty, set is as the right child.
        // An if statement is allowed to have an empty body.
        if(stList) {
                node->right = stList;
        }

        node->type = ASTNODE_IF;
        return node;
}

/// @brief         Creates an if-else node.
/// @param cond    Reduced condition node.
/// @param stList1 Reduced statement node for when condition is true.
/// @param stList2 Reduced statement node for when condition is false;
/// @return        Returns an if-else node.
ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* stList1, ASTNode* stList2) {
        // Checks if condition node is null.
        if(!cond) {
                yyerror("Null condition node in if-else node.");
        }

        // Allocates memory for the if-else node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateIfElseNode.");
        }

        node->left = cond;

        // In this scenario, the right node is consider the middle child.
        // Set middle child if first statement list reduced node is not null.
        if(stList1) {
                node->right = stList1;
        }

        // Sets rightmost child as the second statement list reduced node if not null.
        if(stList2) {
                node->next = stList2;
        }
        node->type = ASTNODE_IF;
        return node;
}

/// @brief       Creates an Or node.
/// @param cond  Reduced condition node.
/// @param lTerm Reduced lTerm node.
/// @return      Returns an Or node.
ASTNode* CreateOrNode(ASTNode* cond, ASTNode* lTerm) {
        // Checks if reduced condition node is null.
        if(!cond) {
                yyerror("Null reduced condition node in Or node.");
        }

        // Checks if reduced lTerm node is null.
        if(!lTerm) {
                yyerror("Null reduced lTerm node in Or node.");
        }

        // Allocates memory for Or node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateOrNode.");
        }

        node->left = cond;
        node->right = lTerm;
        node->type = ASTNODE_LOGIC_OP;
        node->op = OR_OP;
        return node;
}

/// @brief         Creates an And node.
/// @param lTerm   Reduced lTerm node.
/// @param lFactor Reduced lFactor node. 
/// @return        Returns an And node.
ASTNode* CreateAndNode(ASTNode* lTerm, ASTNode* lFactor) {
        // Checks if reduced lTerm node is null.
        if(!lTerm) {
                yyerror("Null reduced lTerm node in And node.");
        }

        // Checks if reduced lFactor node is null.
        if(!lFactor) {
                yyerror("Null reduced lFactor node in And node.");
        }

        // Allocates memory for And node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateAndNode.\n");
        }

        node->left = lTerm;
        node->right = lFactor;
        node->type = ASTNODE_LOGIC_OP;
        node->op = AND_OP;
        return node;        
}

/// @brief           Creates a compare node.
/// @param exprLeft  Reduced left expression node. 
/// @param op        Operation of comparison.
/// @param exprRight Reduced right expression node. 
/// @return          Returns a compare node.
ASTNode* CreateCompareNode(ASTNode* exprLeft, int op, ASTNode* exprRight) {
        // Checks if left expression is null.
        if(!exprLeft) {
                yyerror("Null left expression in compare node.");
        }

        // Checks if right expression is null.
        if(!exprRight) {
                yyerror("Null right expression in compare node.");
        }

        // Allocates memory for compare node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateCompareNode.\n");
        }

        node->left = exprLeft;
        node->right = exprRight;
        node->type = ASTNODE_COMPARE;
        node->op = op;
        return node;
}

/// @brief        Creates a while node.
/// @param cond   Reduced condition node.
/// @param stList Reduced statement list node.
/// @return       Returns a while node.
ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList) {
        // Checks if condition is null.
        if(!cond) {
                yyerror("Null condition node in while node.");
        }

        if(!stList) {
                yyerror("Null statement list node in while node.");
        }

        // Allocates memory for while node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory to CreateWhileNode.\n");
        }

        node->left = cond;
        node->right = stList;
        node->type = ASTNODE_WHILE;
        return node;
}

/// @brief      Maps an identifier name to an integer value.
/// @param name Name to map. 
/// @return     Returns the integer value that represents the identifier name.
unsigned int hash(char *name) {
        // Checks if name to hash is null.
        if(name == NULL) {
                yyerror("Unable to hash null name pointer.\n");
        }

        // Maps the name to an integer value.
        int length = strnlen(name, MAX_NAME);
        unsigned int hash_value = 0;
        for (int i = 0; i < length; i++) {
                hash_value += name[i];
                hash_value = (hash_value * name[i]) % TABLE_SIZE;
        }
        return hash_value;
}

/// @brief Initializes the symbol table.
void init_symbol_table() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        symbol_table[i] = NULL;
    }
}

/// @brief      Checks if an identifier name has been declared and
///             inserted into the symbol table.
/// @param name Identifier name to look up in the symbol table. 
/// @return     Returns true if name was found, false if not found.
bool symbol_table_lookup(char *name) {
        // Checks if name to look up is null.
        //print_table();
        if(name == NULL) {
                yyerror("Unable to look up null name pointer.\n");
        }

        int index = hash(name);
        ident_name *tmp = symbol_table[index];
        while(tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
                tmp = tmp->next;
        }

        // If name was not found.
        if(tmp == NULL) {
                return false;
        }
        // If name was found.
        else if(strncmp(tmp->name, name, MAX_NAME) == 0) {
                return true;
        }
        else {
                return false;
        }
}

/// @brief    Inserts an identifier name into the symbol table.
/// @param p  Name to insert into symbol table. 
/// @return   Returns true if successful.
bool symbol_table_insert(ident_name *p) {
        // Checks if name to insert is null.
        if(p == NULL) {
                yyerror("Unable to insert null identifier name pointer.\n");
        }

        // Inserts name into symbol table.
        int index = hash(p->name);
        p->next = symbol_table[index];
        symbol_table[index] = p;
        return true;
}

/// @brief      Declares identifier names.
/// @param name Identifier name to declare.
void AddDeclaration(char* name) {
        // Checks if name to be declared is null.
        if(name == NULL) {
                yyerror("Unable to declare null name pointer.\n");
        }

        // Verifies that the identifier has not been declared yet.
        if(symbol_table_lookup(name)) {
                char buf[250];
                snprintf(buf, sizeof(buf), "%s'%s'.", "Multiple declarations of ", name);
                char* b = buf;
                yyerror(b);
        }
        ident_name *ident = (ident_name*)malloc(sizeof(ident_name));
        strncpy(ident->name, name, MAX_NAME);
        symbol_table_insert(ident);
}

// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/