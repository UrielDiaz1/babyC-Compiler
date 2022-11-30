#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node_actions.h"
#include "symbol_table.h"

extern FILE* yyin;
extern FILE* fp;
extern int yyparse();

// A global variable that holds a pointer to the AST root
ASTNode* gASTRoot;

int main(int argc, char**argv) {
        if (argc != 2) {
                 printf("ERROR: Invalid number of command-line arguments. Usage: bcc File_Name.bc\n");
                 exit(1);
        }
    	yyin = fopen(argv[1], "r" );
        if (yyin == NULL) {
                 printf("ERROR: Failed to open the input file\n");
                 exit(1);
        }

        // Call the parser. 
        // Add embedded actions to the parser (in BabyC.y) to construct the AST and store its root in gASTRoot. 
        yyparse();
        fclose(yyin);

        // Extracts the argument filename, excluding the extension.
        char filename[128];
        int i = 0;
        int len = strlen(argv[1]);
        while(i < len) {
            if(argv[1][i] == '.') {
                break;
            }
            strncat(filename, &argv[1][i++], 1);
        }

        // Appends the iloc file extension into the filename.
        strncat(filename, ".iloc", 6);

        // Opens file with write permission. It also cleans the file before writing.
        fp = fopen(filename, "w");
        if(fp == NULL) {
                 printf("ERROR: Failed to open the input file\n");
                 exit(1);
        }

        // Ensures the AST is not null.
        if(!gASTRoot) {
            printf("ERROR: gASTRoot is null. Unable to generate ILOC.");
        }
        
        // Now that the AST has been constructed, pass its root to the function that traverses it and generates the ILOC code.
        GenerateILOC(gASTRoot);
        fclose(fp);
}
