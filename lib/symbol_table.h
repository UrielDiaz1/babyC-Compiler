#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_NAME 50		// Identifier name length.
#define TABLE_SIZE 900  // Symbol table size.

typedef struct ident_name {
    char name[MAX_NAME];
    struct ident_name *next;
    int offset;
} ident_name;
extern ident_name *symbol_table[TABLE_SIZE];

// Declares symbol table management functions.
unsigned int hash(char *name);
void init_symbol_table();
ident_name* symbol_table_lookup(char *name);
bool symbol_table_insert(ident_name *p);
void AddDeclaration(char* name);

#endif