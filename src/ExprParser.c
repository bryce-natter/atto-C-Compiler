
#include "../inc/atto-C.h"
int jump_serial;



struct stack_t {
    int token;  // type of token in this stack position
    int expr_after;  // 1 for nonterminal following, 0 for not.
    int integer_value; //Value of the integer
    struct symbol_t *symbol; //Symbol Table Entry for expressions

};

#define STACKMAX 1000
struct stack_t stack[STACKMAX];
int stacktop;   // index of the current top of the stack

//Expression Parser. Calls lexer() for lookahead token, 
//returns token type that ends expression.
int expr_parser()
{
    //asm code
    fprintf(asmfile, "; Line %d\n", line_no);
    if (line_no == 16) {
        line_no = 16;

    }

    //Stack initialization:
    stack[0].token = DOLLAR_TOK; //Adds '$' token to start of stack
    stack[0].expr_after = 0; //Sets expression after to terminal
    stacktop = 0; //Sets index of stack to 0

    //lookahead = lexer(); //Get lookahead from lexer
    while(1)
    {
        if ((lookahead == MINUS_TOK) && !stack[stacktop].expr_after)
            lookahead = UNARY_MINUS_TOK;
        if ((lookahead == UNARY_MINUS_TOK) && stack[stacktop].expr_after)
        lookahead = MINUS_TOK;
        
        switch (action[stack[stacktop].token - 101][lookahead - 101])
        {
        case SH:
            //shift code
            printf("Shift token %d %s line %d\n", lookahead, lexeme, line_no);
            stacktop++;
            if(stacktop < STACKMAX)
            {
                if (lookahead == IDENT_TOK)
                {
                    stack[stacktop].symbol = symbol_lookup(lexeme);
                    if (stack[stacktop].symbol == NULL)
                        stack[stacktop].symbol = push_symbol(lexeme);
                }
                if(lookahead == INTEGER_TOK){
                    stack[stacktop].integer_value = atoi(lexeme); //Convert to int
                }
                stack[stacktop].token = lookahead; //Push lookahead token to stack
                stack[stacktop].expr_after = 0; //Set expression after to terminal
                lookahead = lexer(); //Get next lookahead token
            }
            else { printf("Error, stack overflow");   }
            break;
        case EQ:
            //shift code
            printf("Shift(matching) token %d %s line %d\n", lookahead, lexeme, line_no);
            stacktop++;
            if (stacktop < STACKMAX)
            {
                stack[stacktop].token = lookahead; //Push lookahead token to stack
                stack[stacktop].expr_after = 0; //Set expression after to terminal
                lookahead = lexer(); //Get next lookahead token
            }
            else { printf("Error, stack overflow"); }
            break;

        case RE:
            // reduce code
            
            printf("Reduce\n");
            switch (stack[stacktop].token)
            {
            case DOLLAR_TOK:
                if (stacktop == 0 && stack[0].expr_after == 1)
                {
                    return lookahead;
                }
                else { printf("Error no expression"); exit(7); }
                break;
            case STAR_TOK:

                //ASM_code Generation
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    imul eax,ebx\n");

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case SLASH_TOK:

                //ASM_code Generation
                fprintf(asmfile, "    mov ebx,eax\n");
                fprintf(asmfile, "    pop eax\n");
                fprintf(asmfile, "    cdq              ; sign-extend eax to edx\n");
                fprintf(asmfile, "    idiv ebx\n");

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case MINUS_TOK:

                //ASM_code Generation
                fprintf(asmfile, "    mov ebx,eax\n");
                fprintf(asmfile, "    pop eax\n");
                fprintf(asmfile, "    sub eax,ebx\n");

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case PLUS_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("PLUS without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("PLUS without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_code Generation
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    add eax,ebx\n");

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case LESS_THAN_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("LESS_THAN without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("LESS_THAN without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    jl  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case GRTR_THAN_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("GRTR_THAN without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("GRTR_THAN without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    jg  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case GRTR_THAN_EQ_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("GRTR_THAN_EQ without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("GRTR_THAN_EQ without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    jge  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case LESS_THAN_EQ_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("LESS_THAN_EQ without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("LESS_THAN_EQ without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    jle  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;


                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case DBL_EQUAL_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("DBL_EQ without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("DBL_EQ without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    je  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;


                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case NOT_EQUAL_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("NOT_EQ without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("NOT_EQ without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,ebx\n");
                fprintf(asmfile, "    jne  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;


                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case AND_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("AND without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("AND without preceding expression, line %d\n", line_no); exit(7);
                }


                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,0\n");
                fprintf(asmfile, "    je  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    cmp ebx,0\n");
                fprintf(asmfile, "    je  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                jump_serial += 2;


                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case DOUBLE_PIPE_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("OR without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("OR without preceding expression, line %d\n", line_no); exit(7);
                }

                //ASM_Code Gen
                fprintf(asmfile, "    pop ebx\n");
                fprintf(asmfile, "    cmp eax,0\n");
                fprintf(asmfile, "    je  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 2);

                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    cmp ebx,0\n");
                fprintf(asmfile, "    je  SHORT jumper@%d\n", jump_serial + 1);
                fprintf(asmfile, "    jmp  SHORT jumper@%d\n", jump_serial + 2);
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 1);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "jumper@%d: \n", jump_serial + 2);
                jump_serial += 2;


                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case EQUAL_TOK:
                if (!(stack[stacktop - 2].expr_after) && stack[stacktop - 2].token != DOLLAR_TOK){
                    printf("= with preceding Expression, line %d\n", line_no); exit(7);
                }
                else {

                    if (stack[stacktop - 1].token == IDENT_TOK) {
                        fprintf(asmfile, "    mov DWORD PTR %s,eax\n", stack[stacktop - 1].symbol->asm_name);
                        stacktop--; stacktop--; stack[stacktop].expr_after = 1;
                    }
                }
                break;
            case COMMA_TOK:
				stacktop--; stack[stacktop].expr_after = 1;
                break;
            case IDENT_TOK:
                //Checking to make sure Identifier has been declared
                if (stack[stacktop].symbol->symbol_kind == 0)
                {
                    printf("Undeclared identifier '%s', line %d\n",
                        stack[stacktop].symbol->name, line_no);
                    exit(1);
                }
                if (stack[stacktop].symbol->symbol_kind == FUNCTION)
                {
                    printf("Function name '%s' used as a variable, line %d\n",
                        stack[stacktop].symbol->name, line_no);
                    exit(1);
                }
                fprintf(asmfile, "    push eax\n");
                fprintf(asmfile, "    mov  eax, DWORD PTR %s\n", stack[stacktop].symbol->asm_name);

                stacktop--; stack[stacktop].expr_after = 1;
                break;
            case INTEGER_TOK:

                //ASM_code generation
                fprintf(asmfile, "    push eax\n");
                fprintf(asmfile, "    mov  eax,%d\n", stack[stacktop].integer_value);

				stacktop--; stack[stacktop].expr_after = 1;
                break;
            case NOT_TOK:
                if (!stack[stacktop].expr_after)
                {
                    printf("NOT without following expression, line %d\n", line_no); exit(7);
                }
                if (stack[stacktop - 1].expr_after)
                {
                    printf("NOT with preceding expression, line %d\n", line_no); exit(7);
                }


                fprintf(asmfile, "    cmp eax,0\n");
                fprintf(asmfile, "    jne  SHORT jumper@%d\n", jump_serial);
                fprintf(asmfile, "    mov eax,1\n");
                fprintf(asmfile, "    jmp SHORT jumper@%d\n", jump_serial + 1);

                fprintf(asmfile, "jumper@%d:\n", jump_serial);
                fprintf(asmfile, "    mov eax,0\n");
                fprintf(asmfile, "jumper@%d:\n", jump_serial + 1);


                stacktop--; stack[stacktop].expr_after = 1; 
                break;
            case UNARY_MINUS_TOK:
                if (stack[stacktop - 1].expr_after)
                {
                    printf("'-' with preceding expression, line %d\n", line_no); exit(7);
                }


                fprintf(asmfile, "    neg eax\n");
				stacktop--; stack[stacktop].expr_after = 1;
                break;
            case LEFT_PARA_TOK:
				printf("Error reducing left parathesis"); exit(7);
                break;
            case RIGHT_PARA_TOK:
                if (!stack[stacktop - 1].expr_after)
                {
                    printf("RIGHT PARA without following expression, line %d\n", line_no); exit(7);
                }
                if (!stack[stacktop - 2].token == LEFT_PARA_TOK)
                {
                    printf("RIGHT PARA without matching LEFT PARA, line %d\n", line_no); exit(7);
                }
                stacktop--; stacktop--; stack[stacktop].expr_after = 1;
                break;
            case SEMI_COLON_TOK:
				stacktop--; stack[stacktop].expr_after = 1;
                break;
            case EOF_TOK:
				stacktop--; stack[stacktop].expr_after = 1;
                break; 

            default:
                    printf("Bad stack top token %d\n", stack[stacktop].token);
                    exit(2);
            }

            break;

        case AC:
            // accept code

            fprintf(asmfile, "    pop ebx        ; clean up stack \n");
            return lookahead;

            break;

        case ER:
            printf("Parse error. Line %d, lookahead token %s\n", line_no, lexeme); exit(7);
            // error-handling code
            break;

        }
    }

}
