// File: symbol_table.c


#include "atto-C.h"


struct symbol_t symbol_table[MAXSYMBOL];
int symbol_stack_top;


struct symbol_t *push_symbol(char *name)
{
    symbol_stack_top++;
    strncpy_s(symbol_table[symbol_stack_top].name,IDENT_MAX_LENGTH, name, IDENT_MAX_LENGTH);
    return symbol_table + symbol_stack_top;
}

//Procedure to start symbol table:
int start_scope() { return symbol_stack_top; }

//Procedure to pop a scope off stack
void end_scope(int prev_stack_top) { symbol_stack_top = prev_stack_top; }

//Procedure to look up identifiers: 
struct symbol_t *symbol_lookup(char *name)
{
    int k;

    for (k = symbol_stack_top; k > 0; k--)
    {
        if (strcmp(name, symbol_table[k].name) == 0)
            return symbol_table + k;
    }
    return NULL;
}