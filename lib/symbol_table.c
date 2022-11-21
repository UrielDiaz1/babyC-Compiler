#include "node_actions.h"
#include "symbol_table.h"

ident_name *symbol_table[TABLE_SIZE];

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
        int i;
        for(i = 0; i < length; i++) {
                hash_value += name[i];
                // Ensures mapped value is within the scope of the table's size.
                hash_value = (hash_value * name[i]) % TABLE_SIZE;
        }
        return hash_value;
}

/// @brief Initializes the symbol table.
void init_symbol_table() {
        int i;
        for(i = 0; i < TABLE_SIZE; i++) {
                symbol_table[i] = NULL;
        }
}

/// @brief      Checks if an identifier name has been declared and
///             inserted into the symbol table.
/// @param name Identifier name to look up in the symbol table. 
/// @return     Returns true if name was found, false if not found.
bool symbol_table_lookup(char *name) {
        // Checks if name to look up is null.
        if(name == NULL) {
                yyerror("Unable to look up null name pointer.\n");
        }

        // Checks the hash index for a matching name, and any linked
        // entries that previously collided during declaration.
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
                char* error_statement = buf;
                yyerror(error_statement);
        }

        // Proceeds to declare the identifier name.
        ident_name *ident = (ident_name*)malloc(sizeof(ident_name));
        strncpy(ident->name, name, MAX_NAME);
        symbol_table_insert(ident);
}