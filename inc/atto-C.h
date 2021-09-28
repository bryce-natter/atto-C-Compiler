// File: atto-c.h
// Contents: headerfile

#ifndef _ATTO_C_H_
#define _ATTO_C_H_
#pragma once


#include <stdio.h>    // standard input-output declarations: printf, stdin
#include <stdlib.h>   // standard library declarations: exit
#include <ctype.h>    // character type test declarations:  isdigit, isalpha, isalnum
#include <string.h>   // string comparision: strcmp


//TABLE ENTRY VALUES:
#define SH  1
#define RE  2
#define EQ  3
#define AC  4
#define ER  5


#ifndef action
static int action[23][23]={
    // $   *   /   +  -    <   >   <=  >= ==  !=  &&  ||   =   ,  IDENT	 NUM   !   -   (   )   ;  EOF
    { AC, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, ER, SH,    SH,  SH, SH, SH, SH, AC, AC, AC}, // $
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // *
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // /
    { RE, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // +
    { RE, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // -
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // <
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // >
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // >=
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // <=
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // ==
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // !=
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // &&
    { RE, SH, SH, SH, SH, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // ||
    { RE, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, ER, RE,    SH,  SH, SH, SH, SH, RE, RE, ER}, // =
    { RE, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, ER, ER,    SH,  SH, SH, SH, SH, ER, RE, ER}, // ,
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, EQ, RE,    ER,  ER, RE, SH, ER, RE, RE, ER}, // IDENT
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    ER,  ER, RE, SH, ER, RE, RE, ER}, // NUM
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // !
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    SH,  SH, RE, RE, SH, RE, RE, ER}, // -
    { ER, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, ER, SH,    SH,  SH, SH, SH, SH, EQ, RE, ER}, // (
    { RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, RE, ER, RE,    ER,  ER, ER, ER, ER, RE, RE, ER}, // )
    { AC, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, SH, ER, SH,    SH,  SH, SH, SH, SH, ER, AC, AC}, // ;
    { ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,    ER,  ER, ER, ER, ER, ER, ER, ER}, // EOF
    };
#endif

// Token types
#define DOLLAR_TOK          101
#define STAR_TOK            102
#define SLASH_TOK           103
#define MINUS_TOK           104
#define PLUS_TOK            105
#define LESS_THAN_TOK       106
#define GRTR_THAN_TOK       107
#define GRTR_THAN_EQ_TOK    108
#define LESS_THAN_EQ_TOK    109
#define DBL_EQUAL_TOK       110
#define NOT_EQUAL_TOK       111
#define AND_TOK             112
#define DOUBLE_PIPE_TOK     113
#define EQUAL_TOK           114
#define COMMA_TOK           115
#define IDENT_TOK           116
#define INTEGER_TOK         117
#define NOT_TOK             118
#define UNARY_MINUS_TOK     119
#define LEFT_PARA_TOK       120
#define RIGHT_PARA_TOK      121
#define SEMI_COLON_TOK      122
#define EOF_TOK             123


#define STRING_TOK          202
#define COMMENT_TOK         204
#define EOL_COMMENT_TOK     204
#define RIGHT_BRCKT_TOK     213
#define LEFT_BRCKT_TOK      214
#define NEWLINE_TOK         219
#define BLANK_TOK           220
#define TAB_TOK             221
#define AUTO_TOK            223
#define BREAK_TOK           224
#define CASE_TOK            225
#define CHAR_TOK            226
#define CONTINUE_TOK        227
#define DEFAULT_TOK         228
#define DO_TOK              229
#define DOUBLE_TOK          230
#define ELSE_TOK            231
#define ENUM_TOK            232
#define EXTERN_TOK          233
#define FLOAT_TOK           234
#define FOR_TOK             235
#define GOTO_TOK            236
#define IF_TOK              237
#define INT_TOK             238
#define LONG_TOK            239
#define REGISTER_TOK        240
#define RETURN_TOK          241
#define SHORT_TOK           242
#define SIZEOF_TOK          243
#define STATIC_TOK          244
#define STRUCT_TOK          245
#define SWITCH_TOK          246
#define TYPEDEF_TOK         247
#define UNION_TOK           248
#define UNSIGNED_TOK        249
#define WHILE_TOK           250



//Lexer
extern int line_no;
#define MAX_LEXEME 200
#define IDENT_MAX_LENGTH 50
#define NUMBER_MAX_LENGTH 10
extern char lexeme[MAX_LEXEME]; //The characters of the token
int lexer(void);

//Expression Parser 
int expr_parser(void);
extern int jump_serial;


//Main Parser:
extern int lookahead; 

//Symbol Table: 
struct symbol_t {
    char name[IDENT_MAX_LENGTH + 1];
    char asm_name[IDENT_MAX_LENGTH + 2];
    int symbol_kind;
    #define GLOBAL_VARIABLE    1
    #define LOCAL_VARIABLE     2
    #define FUNCTION_PARAMETER 3
    #define FUNCTION           4
};
#define MAXSYMBOL 1000
extern struct symbol_t symbol_table[MAXSYMBOL];
extern int symbol_stack_top;
struct symbol_t *push_symbol(char *name);
int start_scope(void);
void end_scope(int prev_stack_top);
struct symbol_t *symbol_lookup(char *name);

//Main Driver:
extern FILE *sourcefile;
extern FILE *asmfile;
void preamble(char *sourcefilename);
void postamble(void);
void program(void);

#endif
