// File: MainParser.c
// Contents: The main parser for the compiler.


#define _CRT_SECURE_NO_WARNINGS
#include "atto-C.h"

int lookahead;
void program(void);
void external_definition(void);
void function_definition(struct symbol_t *s);
void parameter_list(void);
void data_definition(struct symbol_t *s);
void data_definition_2(void);
void declaration_list(void);
void compound_statement(void);
void statement_list(void);
void statement(void);
void expression_statement(void);
void if_statement(void);
void while_statement(void);
void do_statement(void);
void continue_statement(void);
void break_statement(void);
void return_statement(void);


int local_offset; //Offset for local variables 



void program()
{
    int symbol_table_spot;
    printf("Entering: Program\n");
    printf("Starting Program Scope\n");
    symbol_table_spot = start_scope();
    lookahead = lexer();
    while (lookahead != EOF_TOK)
        external_definition();
    end_scope(symbol_table_spot);
    printf("End of Program Scope\n");
    printf("Exiting: Program  Line: %d\n", line_no);
}


void external_definition(){
    struct symbol_t *s;

    printf("Entering: External Definition\n");

    if (lookahead == INT_TOK) {
        lookahead = lexer(); //Eat the INT
        if (lookahead == IDENT_TOK) {
            s = push_symbol(lexeme); //Add token to symbol_table
            printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
            lookahead = lexer(); //Eat the IDENT

            if (lookahead == LEFT_PARA_TOK) {
                function_definition(s); //Send symbol through to function definition
            }
            else if(lookahead == SEMI_COLON_TOK || lookahead == COMMA_TOK)
            {
                data_definition(s); //Send Symbol through to data_definition
            }
            else {
                printf("Error: missing left parathensis, semicolon, or comma. Line %d.", line_no); exit(7);
            }
        }
        else {
            printf("Error: missing IDENT_TOK. Line %d.", line_no); exit(7);
        }
    }
    else if (lookahead == IDENT_TOK)
    {
        s = push_symbol(lexeme); //Add token to symbol_table
        printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
        lookahead = lexer(); //Eat the IDENT
        if (lookahead == LEFT_PARA_TOK) {
            function_definition(s); //Send symbold through to function definition
        }
        else {
            printf("Error: missing LEFT_PARA. Line %d.", line_no); exit(7);
        }
    }
    else
    {
        printf("Error: missing IDENT or INT token. Line %d.", line_no); exit(7);

    }
    printf("Exiting: External Definition\n");
}
void function_definition(struct symbol_t *s){
    printf("Entering: Function Definition\n");

    //---asm creation---
    s->symbol_kind = FUNCTION;
    sprintf(s->asm_name, "_%s", s->name);
    fprintf(asmfile, "\nPUBLIC %s\n", s->asm_name);
    fprintf(asmfile, ";    COMDAT %s\n", s->asm_name);
    fprintf(asmfile, "\n_TEXT    SEGMENT\n");
    fprintf(asmfile,"%s    PROC          ; COMDAT\n\n",s->asm_name);
    
    fprintf(asmfile, "   push  ebp\n");//Save old frame pointer
    fprintf(asmfile, "   mov   ebp,esp\n");//Set current frame pointer
    fprintf(asmfile, "   sub   esp,%s_locals$\n", s->asm_name); //Create space for local variables

    //-----Save Registers----
    fprintf(asmfile, "   push  ebx\n");
    fprintf(asmfile, "   push  esi\n");
    fprintf(asmfile, "   push  edi\n");
    //----------------

    printf("Starting Function Definition Scope\n");
    int symbol_table_spot;
    symbol_table_spot = start_scope();

    lookahead = lexer(); //eat left para
    parameter_list();
    if (lookahead != RIGHT_PARA_TOK) {
        printf("Error in function definition, missing Right parathensis. Line %d.", line_no); exit(7);
    }
    lookahead = lexer(); //eat right para
    local_offset = -4;
    compound_statement(); 
    end_scope(symbol_table_spot);
    printf("End of Function Definition Scope\n");

    //---asm creation---

    //---Pop preserved registers, reverse order
    fprintf(asmfile, "   pop   edi\n");
    fprintf(asmfile, "   pop   esi\n");
    fprintf(asmfile, "   pop   ebx\n");

    fprintf(asmfile, "   mov esp, ebp\n"); //Pop all local variables at once

    fprintf(asmfile, "   pop   ebp\n"); //Restore old stack frame pointer

    fprintf(asmfile, "   ret   0\n"); // Return

    fprintf(asmfile, "%s   ENDP\n", s->asm_name); //End the procedure

    fprintf(asmfile, "%s_locals$ = %d\n", s->asm_name, -local_offset - 4); //Define constant for size of local variables


    fprintf(asmfile, "_TEXT    ENDS\n");
    //-------------------



    printf("Exiting: Function Definition\n");
}
void parameter_list(){
    struct symbol_t *ss; //Local variable for symbol table pointer
    int offset = 8; // Starting offset from EBP

    printf("Entering: Parameter List\n");
    while (lookahead == INT_TOK)  // loop as long as there are more
    {
        lookahead = lexer();  // eat int
        if (lookahead == IDENT_TOK)
        {
            ss = push_symbol(lexeme);
            sprintf(ss->asm_name, "_%s$[ebp]", ss->name);  // make asm offset name 
            ss->symbol_kind = FUNCTION_PARAMETER;
            fprintf(asmfile, "_%s$ = %d\n", ss->name, offset);
            offset += 4;

            printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
            lookahead = lexer();  // eat identifier
        }
        else {
            printf("Error in paramater_list Missing IDENT. Line %d", line_no); exit(1);
        }
        if (lookahead == COMMA_TOK)
            lookahead = lexer();   // eat comma
    }
    printf("EXiting: Parameter List\n");
}
void data_definition(struct symbol_t *s) {
    printf("Entering: Data Defintion\n");
    fprintf(asmfile, "\n_DATA    SEGMENT\n");

    struct symbol_t *ss; //variable for further variable declaration

    //Generate asm_name for first identifier
    s->symbol_kind = GLOBAL_VARIABLE;
    s->asm_name[0] = '_';
    strncpy(s->asm_name + 1, s->name, IDENT_MAX_LENGTH);
    fprintf(asmfile, "COMM  %s:DWORD\n", s->asm_name); //Print out line of assembly code 

    while (lookahead == COMMA_TOK)  // INT_TOK and IDENT_TOK already eaten
    {
        lookahead = lexer();  // eat comma 
        if (lookahead == IDENT_TOK) {
            push_symbol(lexeme); //Add ident to table 
            printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
            
            //Generate asm_name for identifiers
            ss = push_symbol(lexeme);
            ss->symbol_kind = GLOBAL_VARIABLE;
            ss->asm_name[0] = '_';
            strncpy(ss->asm_name + 1, ss->name, IDENT_MAX_LENGTH);
            fprintf(asmfile, "COMM  %s:DWORD\n", ss->asm_name); //Print out line of assembly code 

            lookahead = lexer(); // eat identifier
        }
        else {
            printf("Error in data_definition, missing IDENT lookahead, line %d", line_no); exit(0);
        }
    }
    if (lookahead == SEMI_COLON_TOK)
    {
        lookahead = lexer();  // eat semicolon
    }
    else {
        printf("Error in data_definition, missing semicolon lookahead, line %d", line_no); exit(0);
    }

    /*
    Also, look for "return" anywhere else in data_definition(), and add
           fprintf(asmfile,"_DATA    ENDS\n");
      right before the return.
    */

    fprintf(asmfile, "_DATA    ENDS\n");
    printf("Exiting: Data Defintion\n");
}
void data_definition_2(){
    /*Note to self: Fix redunant code using a better loop*/
    printf("Entering: Data Defintion 2\n");

    struct symbol_t *ss;

    lookahead = lexer(); //eat INT_TOK

    if (lookahead == IDENT_TOK) {

        //asm_name code
        ss = push_symbol(lexeme);
        int serial_number = local_offset / (-4);
        sprintf(ss->asm_name, "_%s$%d[ebp]", ss->name, serial_number);
        ss->symbol_kind = LOCAL_VARIABLE;
        fprintf(asmfile, "_%s$%d = %d\n", ss->name, serial_number, local_offset);
        local_offset -= 4;


        printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
    }
    lookahead = lexer(); //eat the IDENT_TOK
    while (lookahead == COMMA_TOK)  // INT_TOK and IDENT_TOK already eaten
    {
        lookahead = lexer();  // eat comma 
        if (lookahead == IDENT_TOK) {


            //asm_name code
            ss = push_symbol(lexeme);
            int serial_number = local_offset / (-4);
            sprintf(ss->asm_name, "_%s$%d[ebp]", ss->name, serial_number);
            ss->symbol_kind = LOCAL_VARIABLE;
            fprintf(asmfile, "_%s$%d = %d\n", ss->name, serial_number, local_offset);
            local_offset -= 4;

            printf("Adding symbol '%s', table index %d, line %d\n", lexeme, symbol_stack_top, line_no);
            lookahead = lexer(); // eat identifier
        }
        else {
            printf("Error in data_definition, missing IDENT lookahead, line %d", line_no); exit(0);
        }
    }
    if (lookahead == SEMI_COLON_TOK)
    {
        lookahead = lexer();  // eat semicolon
    }
    else {
        printf("Error in data_definition, missing semicolon lookahead, line %d", line_no); exit(0);
    }

    printf("Exiting: Data Defintion 2\n");


}
void declaration_list()
{
    printf("Entering: Declaration List\n");
    while (lookahead == INT_TOK)
            data_definition_2();

    printf("Exiting: Declaration List\n");
}
void compound_statement(){
    int symbol_table_spot;
    printf("Entering: Compound Statement\n");
    printf("Starting Compound Statement Scope\n");
    symbol_table_spot = start_scope();
    if (lookahead != LEFT_BRCKT_TOK)
    {
        printf("Missing left curly brace for compound statement. Line %d.", line_no);
        exit(7);
    }
    lookahead = lexer();  // eat left curly brace

    declaration_list();  // do any local variable declarations

    statement_list();

    if (lookahead != RIGHT_BRCKT_TOK)
    {
        printf("Missing right curly brace at end of compound statement. Line %d.", line_no);
        exit(8);
    }
    lookahead = lexer();  // eat left curly brace
    end_scope(symbol_table_spot);
    printf("End of compound statement scope\n");
    printf("Exiting: Compound Statement\n");
}
void statement_list() { 
    printf("Entering: Statement List\n");
    while (lookahead != RIGHT_BRCKT_TOK) {
        statement();
    }
    printf("Exiting: Statement List\n");
}
void statement(){

    printf("Entering: Statement\n");
    if (lookahead == LEFT_BRCKT_TOK) { compound_statement();}
    else if (lookahead == IF_TOK) { if_statement(); }
    else if (lookahead == WHILE_TOK) { while_statement(); }
    else if (lookahead == DO_TOK) { do_statement(); }
    else if (lookahead == CONTINUE_TOK) { continue_statement(); }
    else if (lookahead == BREAK_TOK) { break_statement(); }
    else if (lookahead == RETURN_TOK) { return_statement(); }
    else if (lookahead == ELSE_TOK) { printf("Error: missing IF statement for while. Line %d", line_no); exit(8); }
    else if (lookahead == IDENT_TOK || lookahead == INTEGER_TOK || lookahead == LEFT_PARA_TOK || lookahead == UNARY_MINUS_TOK || lookahead == NOT_TOK) { expression_statement(); }
    else { printf("Illegal Statement, line %d", line_no); exit(8);  }

    printf("Exiting: Statement\n");

}
void expression_statement() { 
    printf("Entering: Expression\n");
    expr_parser(); 
    if (lookahead == SEMI_COLON_TOK) { lookahead = lexer(); } //Eat semi colon if it is one
    else { printf("Error: Missing semi colon, line %d", line_no); exit(8); }
    printf("Exiting: Expression\n");
}
void if_statement(){
    printf("Entering: IF\n");
    lookahead = lexer();//Eat the IF_TOK
    if (lookahead == LEFT_PARA_TOK) {
        lookahead = lexer(); //eat the left para
    }
    else {
        printf("Error: Missing Left Parathesis. Line %d.", line_no); exit(8);
    }
    expr_parser();
    if (lookahead == RIGHT_PARA_TOK) {
        lookahead = lexer(); //eat the right para
    }
    else {
        printf("End of Expression error. Line %d.", line_no); exit(8);
    }
    statement();
    if (lookahead == ELSE_TOK) {
        lookahead = lexer();//Eat the ELSE_TOK
        statement();
    }
    printf("Exiting: IF\n");
}
void while_statement(){
    printf("Entering: WHILE\n");
    if (lookahead == WHILE_TOK) {
        lookahead = lexer(); //eat the WHILE
    }
    else {
        printf("Missing While. Line %d.", line_no); exit(8);
    }
    if (lookahead == LEFT_PARA_TOK) {
        lookahead = lexer(); //eat the left para
    }
    else {
        printf("Error: Missing Left Parathesis. Line %d.", line_no); exit(8);
    }
    expr_parser();
    if (lookahead == RIGHT_PARA_TOK) {
        lookahead = lexer(); //eat the right para
    }
    else {
        printf("End of Expression error. Line %d.", line_no); exit(8);
    }
    statement();
    printf("Exiting: WHILE\n");
}
void do_statement(){
    printf("Entering: DO\n");
    lookahead = lexer();//Eat the DO_TOK
    statement();
    lookahead = lexer();//Eat the WHILE_TOK
    lookahead = lexer();//Eat the left parathesis
    expr_parser();
    if (lookahead == RIGHT_PARA_TOK) {
        lookahead = lexer(); //eat the right para
    }
    else {
        printf("End of Expression error. Line %d.", line_no); exit(8);
    }
    lookahead = lexer(); //Eat the semicolon
    printf("Exiting: WHILE\n");
}
void continue_statement() {

    printf("Entering: DO\n");
    lookahead = lexer(); lookahead = lexer(); //Eat the continue and semicolon tokens
    printf("Exiting: DO\n");
}
void break_statement(){
    printf("Entering: BREAK\n");
    lookahead = lexer(); lookahead = lexer(); //Eat the break and semicolon tokens
    printf("Exiting: break\n");
}
void return_statement() {

    printf("Entering: RETURN\n");
    lookahead = lexer();//Eat return TOK
    if (lookahead == IDENT_TOK || lookahead == INTEGER_TOK || lookahead == LEFT_PARA_TOK || lookahead == UNARY_MINUS_TOK || lookahead == NOT_TOK) { expression_statement(); }
    else {
        lookahead = lexer(); // Eat the semi-colon
    }
    printf("Exiting: RETURN\n");
}