// File: lexer.c
// Contents: The main lexical analyzer routine lex() and associated function


 // Finite State Machine states
#include "atto-C.h"

#define FINAL_STATE         0
#define START_STATE         1
#define INTEGER_STATE       2
#define STRING_STATE        3
#define START_COMM_STATE    4
#define MID_COMM_STATE      5
#define EOL_COMMENT_STATE   6
#define SLASH_STATE         7
#define EQUAL_STATE         8
#define AND_STATE           9
#define LESS_THAN_STATE     10
#define GRTR_THAN_STATE     11
#define NOT_STATE           12
#define PIPE_STATE          13
#define IDENT_STATE         14
#define MID_STRING_BCKSLH   15
#define KEYWORDS_MAX 28
char *keywords[KEYWORDS_MAX] = {
    "auto", "double", "if", "static",
    "break", "else", "int", "struct",
    "case", "enum", "long", "switch",
    "char", "extern", "register", "typedef",
    "continue", "float", "return", "union",
    "default", "for", "short", "unsigned",
    "do", "goto", "sizeof", "while"
};
int keyword_tokens[KEYWORDS_MAX] = { 
    AUTO_TOK, DOUBLE_TOK, IF_TOK, STATIC_TOK,
    BREAK_TOK, ELSE_TOK, INT_TOK, STRUCT_TOK,
    CASE_TOK, ENUM_TOK, LONG_TOK, SWITCH_TOK,
    CHAR_TOK, EXTERN_TOK, REGISTER_TOK, TYPEDEF_TOK,
    CONTINUE_TOK, FLOAT_TOK, RETURN_TOK, UNION_TOK,
    DEFAULT_TOK, FOR_TOK, SHORT_TOK, UNSIGNED_TOK,
    DO_TOK, GOTO_TOK, SIZEOF_TOK, WHILE_TOK,
};



int line_no = 1;
int token_type;  // The type of token found.
int INDENT_MAX_LENGTH = IDENT_MAX_LENGTH;
int next_char; // The next character of input.

char lexeme[MAX_LEXEME];  // The characters of the token.


int lexer()
{
	int state;   // The current state of the FSM.
	int lex_spot; // Current spot in lexeme.

	  // Infinite loop, doing one token at a time.
	while (1)
	{  // Initialize the Finite State Machine.
		state = START_STATE;

		lex_spot = 0;
		// Loop over characters of the token.
		while (state != FINAL_STATE)
		{

			if (next_char == 0)
				next_char = getc(sourcefile);  // get one character from standard input
            if (next_char == EOF) {      // EOF is special character for End-Of-File
                token_type = EOF_TOK;
                return token_type;   
            }
            switch (state)

            {
            case START_STATE:

                //INTERGER
                if (isdigit(next_char))
                {
                    state = INTEGER_STATE;
                    lexeme[lex_spot++] = next_char;  // Add the character to the lexeme
                    next_char = 0;  // eat the character
                }

                //STRING
                else if (next_char == '"') {
                    state = STRING_STATE;
                    lexeme[lex_spot++] = next_char; //Adds " to the lexeme
                    next_char = 0; //eat the "
                }

                //SLASH
                else if (next_char == '/') {
                    state = SLASH_STATE;
                    lexeme[lex_spot++] = next_char; //Adds / to lexeme
                    next_char = 0; //eats the /
                }

                //EQUALS
                else if (next_char == '=') { 
                    state = EQUAL_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }

                //PIPE
                else if (next_char == '|') {
                    state = PIPE_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }

                //NOT
                else if (next_char == '!') {
                    state = NOT_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }

                //LESS THAN
                else if (next_char == '<') {
                    state = LESS_THAN_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }

                //GREATER THAN
                else if (next_char == '>') {
                    state = GRTR_THAN_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }

                //RIGHT BRACKET
                else if (next_char == '}') {
                    lexeme[lex_spot] = 0;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = RIGHT_BRCKT_TOK;
                    return token_type;
                    printf("ACCEPT BRACKET %c\n", next_char);
                    state = FINAL_STATE;
                }

                //LEFT BRACKET
                else if (next_char == '{') {
                    lexeme[lex_spot] = 0;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = LEFT_BRCKT_TOK;
                    return token_type;
                    printf("ACCEPT BRACKET %c\n", next_char);
                    state = FINAL_STATE;
                }

                //MINUS
                else if (next_char == '-') {
                    lexeme[lex_spot] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = MINUS_TOK;
                    return token_type;
                    printf("ACCEPT MINUS %c\n", next_char);
                    state = FINAL_STATE;
                }

                //PLUS
                else if (next_char == '+') {
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = PLUS_TOK;
                    return token_type;
                    printf("ACCEPT PLUS %c\n", next_char);
                    state = FINAL_STATE;
                }

                else if (next_char == '*') {
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = STAR_TOK;
                    return token_type;
                    printf("ACCEPT PLUS %c\n", next_char);
                    state = FINAL_STATE;
                }
                //LEFT PARENTHESIS
                else if (next_char == '(') {
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = LEFT_PARA_TOK;
                    return token_type;
                    printf("ACCEPT PARATHESIS %c\n", next_char);
                    state = FINAL_STATE;
                }

                //RIGHT PARENTHESIS
                else if (next_char == ')') {
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    token_type = RIGHT_PARA_TOK;
                    return token_type;
                    printf("ACCEPT PARATHESIS %c\n", next_char);
                    state = FINAL_STATE;
                }

                //COMMA
                else if (next_char == ',') {
                    lexeme[lex_spot] = 0;
                    token_type = COMMA_TOK;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    return token_type;
                    printf("ACCEPT COMMA %c\n", next_char);
                    state = FINAL_STATE;
                }

                //SEMI-COLON
                else if (next_char == ';') {
                    lexeme[lex_spot] = 0;
                    token_type = SEMI_COLON_TOK;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                    return token_type;
                    printf("ACCEPT SEMI COLON %c\n", next_char);
                    state = FINAL_STATE;
                }

                //NEWLINE AND RETURN
                else if (next_char == '\n' || next_char == '\r') {
                    lexeme[lex_spot] = 0;
                    token_type = NEWLINE_TOK;
                    line_no++;
                    //return token_type;
                    //printf("ACCEPT NEWLINE\n");
                    next_char = 0;
                    state = FINAL_STATE;
                }

                //TAB
                else if (next_char == '\t') {
                    lexeme[lex_spot] = 0;
                    token_type = TAB_TOK;
                    //return token_type;
                    //printf("ACCEPT TAB %c\n", next_char);
                    next_char = 0;
                    state = FINAL_STATE;
                }

                //BLANKSPACE
                else if (next_char == ' ') {
                    lexeme[lex_spot] = 0;
                    token_type = BLANK_TOK;
                    //return token_type;
                    //printf("ACCEPT BLANK %c\n", next_char);
                    next_char = 0;
                    state = FINAL_STATE;
                }

                //AND-STATE
                else if (next_char == '&') {
                    state = AND_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                }

                //IDENT STATE
                else if (next_char == '_' || isalpha(next_char)) {
                    state = IDENT_STATE;
                    token_type = IDENT_TOK;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                    lexeme[lex_spot] = 0;
                }

                //REJECT
                else
                {
                    printf("REJECT %c on line %i\n", next_char, line_no);  // This is not a legal final state
                    state = FINAL_STATE;  // but we want to end the token anyway
                    next_char = 0;   // eat the offending character
                }
                break;  // Need "break" at the end of a case, else you will continue to the next case.

            case INTEGER_STATE:
                if (isdigit(next_char))
                {
                    if (lex_spot == NUMBER_MAX_LENGTH)
                    {
                        printf("ERROR: number too long. Truncating. Line %d\n", line_no);
                        lexeme[lex_spot++] = 0;
                    }
                    else if (lex_spot < NUMBER_MAX_LENGTH)
                    {
                        state = INTEGER_STATE;
                        lexeme[lex_spot++] = next_char;
                        next_char = 0;
                    }
                }
                else
                {
                    lexeme[lex_spot] = 0; // null for end of string
                    token_type = INTEGER_TOK;
                    return token_type;
                    printf("ACCEPT INTEGER %s\n", lexeme);  // This is a final state
                    state = FINAL_STATE;       // leave next_char alone, for next token
                }
                break;

            case STRING_STATE:
                if (next_char == '\n' || next_char == '\b' || next_char == '\t' || lex_spot == MAX_LEXEME-3) {
                    printf("REJECT %c on line%i\n", next_char, line_no);  // This is not a legal final state
                    state = FINAL_STATE;  // but we want to end the token anyway
                    next_char = 0;   // eat the offending character

                }
                else if (next_char == '\\') {
                    state = MID_STRING_BCKSLH;
                    next_char = 0;
                }
                else if (next_char != '"')
                {
                    state = STRING_STATE;
                    lexeme[lex_spot++] = next_char;
                    next_char = 0;
                }
				else
				{
					lexeme[lex_spot++] = next_char;
					lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
					token_type = STRING_TOK;
                    return token_type;
					printf("ACCEPT STRING %s\n", lexeme);  // This is a final state
                    
					state = FINAL_STATE;       // leave next_char alone, for next token
				}
				break;

            case MID_STRING_BCKSLH:
                if(next_char == 'n') {
                    lexeme[lex_spot++] = '\n';
                    next_char = 0;
                    state = STRING_STATE;
                }
                else if(next_char == 'b') {
                    lexeme[lex_spot++] = '\b';
                    next_char = 0;
                    state = STRING_STATE;
                }
                else if(next_char == 't') {
                    lexeme[lex_spot++] = '\t';
                    next_char = 0;
                    state = STRING_STATE;
                }
                else if(next_char == '"') {
                    lexeme[lex_spot++] = '"';
                    next_char = 0;
                    state = STRING_STATE;
                }
                else if (next_char == '\\') {
                    lexeme[lex_spot++] = '\\';
                    next_char = 0;
                    state = STRING_STATE;
                }
            break;

			case SLASH_STATE:
				if (next_char == '/') {
					state = EOL_COMMENT_STATE;  //Set state to End of Line Comment State
					next_char = 0; //eat /
				}
				else if (next_char == '*') {
					state = START_COMM_STATE; //Set state to start of comment state
					next_char = 0; //eat *
				}
				else {
					lexeme[lex_spot++] = 0;  //null for end of string
					lexeme[lex_spot] = next_char; 
					next_char = 0;
					token_type = SLASH_TOK;
                    return token_type;
					printf("ACCEPT SLASH\n");
					state = FINAL_STATE;
				}
				break;

			case START_COMM_STATE:
				if (next_char == '*') {
					state = MID_COMM_STATE;
					next_char = 0;
				}
                else if (next_char == '\n') {
                    next_char = 0;
                    line_no++;
                    state = START_COMM_STATE;
                }
				else {
					state = START_COMM_STATE;
					next_char = 0;
				}
				break;

			case MID_COMM_STATE:
				if (next_char == '/') {
					next_char = 0;
					token_type = COMMENT_TOK;
                    //return token_type;
					//printf("ACCEPT COMMENT TOK\n");
					state = FINAL_STATE;
				}
				else if (next_char == '*') {
					next_char = 0;
					state = MID_COMM_STATE;
				}
                else if (next_char == '\n') {
                    next_char = 0;
                    line_no++;
                    state = MID_COMM_STATE;
                }
				else {
					next_char = 0;
					state = START_COMM_STATE;
				}
				break;

			case EOL_COMMENT_STATE:
				if (next_char == '\n' || next_char =='\r') {
                    line_no++;
					next_char = 0;
					token_type = EOL_COMMENT_TOK;
                    //return token_type;
					//printf("ACCEPT EOL COMMENT TOK\n");
					state = FINAL_STATE;
				}
				else {
					next_char = 0;
					state = EOL_COMMENT_STATE;
				}
                break;

            case EQUAL_STATE:
                if (next_char == '=') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = DBL_EQUAL_TOK;
                    return token_type;
                    printf("ACCEPT DOUBLE EQUAL %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    lexeme[lex_spot] = 0; // null for end of string
                    token_type = EQUAL_TOK;
                    return token_type;
                    printf("ACCEPT EQUAL %s\n", lexeme);
                    state = FINAL_STATE;
                }
                break;

            case PIPE_STATE:
                if (next_char == '|') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = DOUBLE_PIPE_TOK;
                    return token_type;
                    printf("ACCEPT DOUBLE PIPE %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    printf("REJECT %c on line %i\n", next_char, line_no);  // This is not a legal final state
                    state = FINAL_STATE;  // but we want to end the token anyway
                    next_char = 0;   // eat the offending character
                }
                break;

            case AND_STATE:
                if (next_char == '&') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = AND_TOK;
                    return token_type;
                    printf("ACCEPT AND %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    printf("REJECT %c on line %i\n", next_char, line_no);  // This is not a legal final state
                    state = FINAL_STATE;  // but we want to end the token anyway
                    next_char = 0;   // eat the offending character
                }
                break;

            case LESS_THAN_STATE:
                if (next_char == '=') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = LESS_THAN_EQ_TOK;
                    return token_type;
                    printf("ACCEPT LESS THAN EQUAL %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    lexeme[lex_spot] = 0; // null for end of string
                    token_type = LESS_THAN_TOK;
                    return token_type;
                    printf("ACCEPT LESS THAN %s\n", lexeme);
                    state = FINAL_STATE;
                }
                break;

            case GRTR_THAN_STATE:
                if (next_char == '=') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = GRTR_THAN_EQ_TOK;
                    return token_type;
                    printf("ACCEPT GREATER THAN EQUAL %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    lexeme[lex_spot] = 0; // null for end of string
                    token_type = GRTR_THAN_TOK;
                    return token_type;
                    printf("ACCEPT GREATER THAN %s\n", lexeme);
                    state = FINAL_STATE;
                }
                break;

            case NOT_STATE:
                if (next_char == '=') {
                    lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    next_char = 0;
                    token_type = NOT_EQUAL_TOK;
                    return token_type;
                    printf("ACCEPT NOT EQUAL %s\n", lexeme);
                    state = FINAL_STATE;
                }
                else {
                    //lexeme[lex_spot++] = next_char;
                    lexeme[lex_spot] = 0; // null for end of string
                    token_type = NOT_TOK;
                    return token_type;
                    printf("ACCEPT NOT  %s\n", lexeme);
                    state = FINAL_STATE;
                }
                break;

            case IDENT_STATE:
                if (next_char == '_' || isalpha(next_char) || isdigit(next_char)) 
                {
                    if (lex_spot == (IDENT_MAX_LENGTH))
                    {
                        printf("ERROR: identifier too long. Truncating. Line %d\n", line_no);
                        lexeme[lex_spot++] = 0;
                    }
                    else if (lex_spot < IDENT_MAX_LENGTH)
                        lexeme[lex_spot++] = next_char;

                    state = IDENT_STATE;
                    next_char = 0;
                }
                else{
                    //KEY-IDENTIFIERS
                    int k;
                    token_type = IDENT_TOK;
                    lexeme[lex_spot] = 0;
                    for (k = 0; k < KEYWORDS_MAX; k++)
                    {
                        if (strcmp(lexeme, keywords[k]) == 0)
                        {
                            token_type = keyword_tokens[k];
                            break;
                        }
                    }
                    state = FINAL_STATE;
                    return token_type;
                    printf("ACCEPT IDENTIFIER(%d) %s\n", token_type, lexeme);  // Print IDENT token type
                }
                break;
			} // end of switch
		} // end of while state
	}  // end of infinite loop
} // end of main