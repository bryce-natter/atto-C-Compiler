; Assembly program generated by Bryce Natter's compiler.

    TITLE  expression-test-2.c
    .686P
    .model  flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES


_DATA    SEGMENT
COMM  _a:DWORD
COMM  _b:DWORD
COMM  _c:DWORD
_DATA    ENDS

PUBLIC _func
;    COMDAT _func

_TEXT    SEGMENT
_func    PROC          ; COMDAT

   push  ebp
   mov   ebp,esp
   sub   esp,_func_locals$
   push  ebx
   push  esi
   push  edi
_param1$ = 8
_param2$ = 12
_param3$ = 16
_local1$1 = -4
_local2$2 = -8
_local3$3 = -12
; Line 7
    push eax
    mov  eax,11
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 8
    push eax
    mov  eax,7
    mov DWORD PTR _b,eax
    pop ebx        ; clean up stack 
; Line 9
    push eax
    mov  eax,3
    mov DWORD PTR _c,eax
    pop ebx        ; clean up stack 
; Line 10
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    add eax,ebx
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 11
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _a
    mov ebx,eax
    pop eax
    sub eax,ebx
    mov DWORD PTR _c,eax
    pop ebx        ; clean up stack 
; Line 12
    push eax
    mov  eax, DWORD PTR _a
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    imul eax,ebx
    mov DWORD PTR _b,eax
    pop ebx        ; clean up stack 
; Line 13
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    mov ebx,eax
    pop eax
    cdq              ; sign-extend eax to edx
    idiv ebx
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 16
    push eax
    mov  eax, DWORD PTR _param1$[ebp]
    push eax
    mov  eax, DWORD PTR _param2$[ebp]
    pop ebx
    add eax,ebx
    mov DWORD PTR _local1$1[ebp],eax
    pop ebx        ; clean up stack 
; Line 17
    push eax
    mov  eax, DWORD PTR _param1$[ebp]
    push eax
    mov  eax, DWORD PTR _param2$[ebp]
    mov ebx,eax
    pop eax
    sub eax,ebx
    mov DWORD PTR _local2$2[ebp],eax
    pop ebx        ; clean up stack 
; Line 18
    push eax
    mov  eax, DWORD PTR _param1$[ebp]
    push eax
    mov  eax, DWORD PTR _param2$[ebp]
    pop ebx
    imul eax,ebx
    mov DWORD PTR _local3$3[ebp],eax
    pop ebx        ; clean up stack 
; Line 19
    push eax
    mov  eax, DWORD PTR _local1$1[ebp]
    push eax
    mov  eax, DWORD PTR _local2$2[ebp]
    mov ebx,eax
    pop eax
    cdq              ; sign-extend eax to edx
    idiv ebx
    push eax
    mov  eax, DWORD PTR _local3$3[ebp]
    pop ebx
    add eax,ebx
    mov DWORD PTR _param1$[ebp],eax
    pop ebx        ; clean up stack 
; Line 22
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    je  SHORT jumper@0
    mov eax,0
    jmp SHORT jumper@1
jumper@0:
    mov eax,1
jumper@1: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 23
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    jne  SHORT jumper@2
    mov eax,0
    jmp SHORT jumper@3
jumper@2:
    mov eax,1
jumper@3: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 24
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    jl  SHORT jumper@4
    mov eax,0
    jmp SHORT jumper@5
jumper@4:
    mov eax,1
jumper@5: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 25
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    jg  SHORT jumper@6
    mov eax,0
    jmp SHORT jumper@7
jumper@6:
    mov eax,1
jumper@7: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 26
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    jge  SHORT jumper@8
    mov eax,0
    jmp SHORT jumper@9
jumper@8:
    mov eax,1
jumper@9: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 27
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,ebx
    jle  SHORT jumper@10
    mov eax,0
    jmp SHORT jumper@11
jumper@10:
    mov eax,1
jumper@11: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 30
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,0
    je  SHORT jumper@12
    mov eax,1
    jmp SHORT jumper@14
jumper@12:
    cmp ebx,0
    je  SHORT jumper@13
    jmp  SHORT jumper@14
jumper@13: 
    mov eax,0
jumper@14: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 31
    push eax
    mov  eax, DWORD PTR _b
    push eax
    mov  eax, DWORD PTR _c
    pop ebx
    cmp eax,0
    je  SHORT jumper@14
    cmp ebx,0
    je  SHORT jumper@14
    mov eax,1
    jmp SHORT jumper@15
jumper@14:
    mov eax,0
jumper@15: 
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 34
    push eax
    mov  eax, DWORD PTR _b
    cmp eax,0
    jne  SHORT jumper@16
    mov eax,1
    jmp SHORT jumper@17
jumper@16:
    mov eax,0
jumper@17:
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
; Line 35
    push eax
    mov  eax, DWORD PTR _b
    neg eax
    mov DWORD PTR _a,eax
    pop ebx        ; clean up stack 
   pop   edi
   pop   esi
   pop   ebx
   mov esp, ebp
   pop   ebp
   ret   0
_func   ENDP
_func_locals$ = 12
_TEXT    ENDS
END