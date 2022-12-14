#include "node_actions.h"
#include "symbol_table.h"

int reg_counter = 0;
int lbl = 0;
FILE* fp;

/// @brief      Creates a num leaf node.
/// @param num  Integer to be stored in the node.
/// @return     Returns a num leaf node.
ASTNode* CreateNumNode(int num) {
        // Allocate memory to num node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateNumNode.");
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
        ident_name* tmp = symbol_table_lookup(name);
        if(!tmp) {
                yyerror("Ident not declared.");
        }

        // Allocates memory for ident node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateIdentNode.");
        }

        node->type = ASTNODE_IDENT;
        node->name = name;
        node->offset = tmp->offset;
        return node;
}

/// @brief        Take a statement node and a statement list node and connect them together
///               to form a bigger statement list node (add the statement to the statement list).
/// @param st     A reduced statement node.
/// @param stList A node with linked reduced statement nodes.
/// @return       Return a pointer to the bigger list that resulted from this linking 
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList) {
        // Checks if the statement node is null.
        // Statements cannot be null, therefore an error must be thrown.
        if(!st) {
                yyerror("Null statement node in CreateStatementListNode.");
        }

        // Checks if the statement list node is null.
        // This doesn't cause an error because statement lists are allowed to be empty.
        if(!stList) {
                // Since there's no list of statements, just return the single one.
                return st;
        }

        st->next = stList;
        return st;
}

/// @brief      Creates an assignment node.
/// @param name Name of the LHS identifier.
/// @param expr Reduced expression node. 
/// @return     Returns an assignment node.
ASTNode* CreateAssignmentNode(ASTNode* ident, ASTNode* expr) {
        // Checks if name pointer is null.
        if(!ident) {
                yyerror("Null Ident pointer in CreateAssignmentNode.");
        }

        // Checks if expr node is null.
        if(!expr) {
                yyerror("Null reduced Expr node in CreateAssignmentNode.");
        }

        // Allocates memory to assignment node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateAssignmentNode.");
        }
        
        node->left = ident;
        node->right = expr;
        node->type = ASTNODE_ASSIGN;
        return node;
}

/// @brief      Creates an addition node.
/// @param expr Reduced expression node.
/// @param term Reduced term node.
/// @return     Returns an addition node.
ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term) {
        // Check if expression node is null.
        if(!expr) {
                yyerror("Null reduced Expr node in CreateAdditionNode.");
        }

        // Checks if term node is null.
        if(!term) {
                yyerror("Null reduced Term node in CreateAdditionNode.");
        }

        // Allocates memory for addition node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateAdditionNode.");
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
                yyerror("Null reduced Expr node in CreateSubtractionNode.");
        }

        // Checks if term node is null.
        if(!term) {
                yyerror("Null reduced Term node in CreateSubtractionNode.");
        }

        // Allocates memory for subtraction node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateSubtractionNode.");
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
                yyerror("Null reduced Term node in CreateMultiplicationNode.");
        }

        // Checks if factor node is null.
        if(!factor) {
                yyerror("Null reduced Factor node in CreateMultiplicationNode.");
        }

        // Allocates memory for multiplication node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateMultiplicationNode.");
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
                yyerror("Null reduced Term node in CreateDivisionNode.");
        }

        // Checks if factor node is null.
        if(!factor) {
                yyerror("Null reduced Factor node in CreateDivisionNode.");
        }

        // Allocates memory for division node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateDivisionNode.");
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
                yyerror("Null Condition node in CreateIfNode.");
        }

        // Allocates memory for if node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateIfNode.");
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
                yyerror("Null Condition node in CreateIfElseNode.");
        }

        // Allocates memory for the if-else node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateIfElseNode.");
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
                yyerror("Null Condition node in CreateOrNode.");
        }

        // Checks if reduced lTerm node is null.
        if(!lTerm) {
                yyerror("Null reduced lTerm node in CreateOrNode.");
        }

        // Allocates memory for Or node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateOrNode.");
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
                yyerror("Null reduced lTerm node in CreateAndNode.");
        }

        // Checks if reduced lFactor node is null.
        if(!lFactor) {
                yyerror("Null reduced lFactor node in CreateAndNode.");
        }

        // Allocates memory for And node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateAndNode.\n");
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
        // Checks if operator is invalid.
        if(op < 6 || op > 11) {
                yyerror("Invalid Operator.");
        }

        // Checks if left expression is null.
        if(!exprLeft) {
                yyerror("Null left reduced Expr in CreateCompareNode.");
        }

        // Checks if right expression is null.
        if(!exprRight) {
                yyerror("Null right reduced Expr in CreateCompareNode.");
        }

        // Allocates memory for compare node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateCompareNode");
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
                yyerror("Null Condition node in CreateWhileNode.");
        }

        if(!stList) {
                yyerror("Null reduced StatementList node in CreateWhileNode.");
        }

        // Allocates memory for while node.
        ASTNode* node;
        if((node = (ASTNode*)malloc(sizeof(ASTNode))) == NULL) {
                yyerror("Unable to allocate memory for CreateWhileNode.\n");
        }

        node->left = cond;
        node->right = stList;
        node->type = ASTNODE_WHILE;
        return node;
}

/// @brief      Recursively generates ILOC code based on the provided AST. Upon every recursive call,
///             the tree gets traversed and the root gets temporarily shifted, to the point it reaches
///             a leaf node.
/// @param node The current root node of the provided tree.
/// @return     The register containing a result.
int GenerateILOC(ASTNode* node) {
        int res;
        int t1;
        int t2;
        int offset;

        // Checks if the AST is null.
        if(!node) {
                return -1;
        }

        // Check the node's type, then perform actions based on that type.
        switch(node->type) {
                case ASTNODE_NUM:
                        res = GetNextReg();
                        fprintf(fp, "\tloadi %d -> r%d\n", node->num, res);
                        break;
                case ASTNODE_IDENT:
                        res = GetNextReg();
                        fprintf(fp, "\tloadAI rarp, %d -> r%d\n", node->offset, res);
                        break;
                case ASTNODE_ASSIGN:
                        // Ensures LHS is an ident node.
                        if(!node->left) {
                                yyerror("LHS of Assignment is null.");
                        }
                        if(!(node->left->type == ASTNODE_IDENT)) {
                                yyerror("LHS of Assignment is not an ident node.");
                        }

                        t2 = GenerateILOC(node->right);
                        offset = node->left->offset;
                        fprintf(fp, "\tstoreAI r%d -> rarp, %d\n", t2, offset);
                        break;
                case ASTNODE_ARITH_OP:
                        t1 = GenerateILOC(node->left);
                        t2 = GenerateILOC(node->right);
                        res = GetNextReg();

                        switch(node->op) {
                                case ADD_OP:
                                        fprintf(fp, "\tadd r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case SUB_OP:
                                        fprintf(fp, "\tsub r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case MULT_OP:
                                        fprintf(fp, "\tmult r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case DIV_OP:
                                        fprintf(fp, "\tdiv r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                default:
                                        yyerror("Invalid arithmetic operator.");
                        }
                        break;
                case ASTNODE_COMPARE:
                        t1 = GenerateILOC(node->left);
                        t2 = GenerateILOC(node->right);
                        res = GetNextReg();

                        switch(node->op) {
                                case EQ_OP:
                                        fprintf(fp, "\tcmp_EQ r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case LE_OP:
                                        fprintf(fp, "\tcmp_LE r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case GE_OP:
                                        fprintf(fp, "\tcmp_GE r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case NE_OP:
                                        fprintf(fp, "\tcmp_NE r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case LT_OP:
                                        fprintf(fp, "\tcmp_LT r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case GT_OP:
                                        fprintf(fp, "\tcmp_GT r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                default:
                                        yyerror("Invalid relational operator.");
                        }
                        break;
                case ASTNODE_LOGIC_OP:
                        t1 = GenerateILOC(node->left);
                        t2 = GenerateILOC(node->right);
                        res = GetNextReg();

                        switch(node->op) {
                                case AND_OP:
                                        fprintf(fp, "\tand r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                case OR_OP:
                                        fprintf(fp, "\tor r%d, r%d -> r%d\n", t1, t2, res);
                                        break;
                                default:
                                        yyerror("Invalid arithmetic operator.");
                        }
                        break;
                case ASTNODE_IF:
                        IncreaseNestingLevel();

                        // Deals with the compare.
                        t1 = GenerateILOC(node->left);

                        // Checks if its an if-else statement.
                        if(!node->next) {
                                fprintf(fp, "\tcbr r%d -> L%d_T, L%d_M\n", t1, lbl, lbl);
                        }
                        else {
                                fprintf(fp, "\tcbr r%d -> L%d_T, L%d_E\n", t1, lbl, lbl);
                        }

                        // Deals with condition being true.
                        fprintf(fp, "L%d_T:\n", lbl);
                        GenerateILOC(node->right);

                        if(node->next) {
                                // Jump to avoid going into the else statements.
                                fprintf(fp, "\tjumpi -> L%d_M\n", lbl);
                                
                                // Deals with else body.
                                fprintf(fp, "L%d_E:\n", lbl);
                                GenerateILOC(node->next);
                        }

                        // Label for when it's out of if statement.
                        fprintf(fp, "L%d_M:\n", lbl);

                        DecreaseNestingLevel();
                        break;
                case ASTNODE_WHILE:
                        IncreaseNestingLevel();

                        // Deals with the compare.
                        fprintf(fp, "L%d_C:\n", lbl);
                        t1 = GenerateILOC(node->left);
                        fprintf(fp, "\tcbr r%d -> L%d_B, L%d_O\n", t1, lbl, lbl);

                        // Deals with body.
                        fprintf(fp, "L%d_B:\n", lbl);
                        t2 = GenerateILOC(node->right);
                        fprintf(fp, "\tjumpi -> L%d_C\n", lbl);

                        // Label for when it's out of while loop.
                        fprintf(fp, "L%d_O:\n", lbl);

                        DecreaseNestingLevel();
                        break;
                default:
                        yyerror("Invalid node type.");
        }
        
        // Checks if this is a stList node.
        // The next nodes are the appended statements, so they have precedence.
        if(node->next && node->type != ASTNODE_IF) {
                GenerateILOC(node->next);
        }

        return res;
}

/// @brief  Updates the register counter.
/// @return The latest register number.
int GetNextReg() {
        reg_counter += 1;
        return reg_counter;
}

/// @brief Increments the nesting level used for asm labels.
void IncreaseNestingLevel() {
        lbl++;
}

/// @brief Decrements the nesting level used for asm labels.
void DecreaseNestingLevel() {
        lbl--;
}