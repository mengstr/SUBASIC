;-----------------------------------------------------------------------------
; STACK.inc
;-----------------------------------------------------------------------------

;-----------------------------------------------------------------------------
    .proc FindVar

@key:      .data $+1, "PRINT",0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0
@pKey:     .data 0
@pVar:     .data 0
@link:     .data 0
@chKey:    .data 0      ; Fetched character from the key
@chVar:    .data 0      ; Fetched character from the variable name

FindVar:
    MOV stackKW @pVar                         ; Point to the first variable

@loop1:
    MOV @key @pKey                              ; Point to the key
    INDEXEDRD @pVar @link                       ; Get the link to next variable address
    CMPEQ CONST_0 @link @notFound               ; If the link is zero, we have reached the end of the list
    MOV @link @pVar                             ; Point to the start of name field
@loop2:
    INDEXEDRD @pVar @chVar                      ; Get the first character of the name
    INDEXEDRD @pKey @chKey                      ; Get the first character of the name
    OUT @chVar
    CMPEQ @chKey @chVar @same                   ; Compare the characters

    ;Reset pKey and pVar if the characters are not equal
    MOV @link @pVar
    DEC @pVar
    JMP @loop1

@same:
    INC @pVar
    INC @pKey
    CMPEQ @chKey 0 @found                       ; If the character(s) are zero, we have found the variable
    JMP @loop2

@found:
    MOV @pVar tokenAddr
    INDEXEDRD @pVar tokenValue
    RET

@notFound:
    OUT ASCII_UNDERSCORE
    MOV CONST_0 tokenAddr
    MOV CONST_0 tokenValue
    RET

    .endp

SP:         .data 0                                   ; Stackpointer

            .org $+8192                               ; Reserve space for the stack    

stack_:
stack:  .data $-1                                  ; Address to the top (beginning) of the stack



            .data 0
SP4:        .data "ERIK",0,"A STRING",SP4
SP3:        .data "MATS",0,11,11,11,SP3
SP2:        .data "FOO",0,333,SP2
SP1:        .data "FARFISA",0,5555,SP1
stackVars:  .data $-1

kREM:       .data "REM"   ,0,  1, kREM
kLET:       .data "LET"   ,0,  2, kLET
kIF:        .data "IF"    ,0,  3, kIF
kTHEN:      .data "THEN"  ,0,  4, kTHEN
kGOTO:      .data "GOTO"  ,0,  5, kGOTO
kPRINT:     .data "PRINT" ,0,  6, kPRINT
kGOSUB:     .data "GOSUB" ,0,  7, kGOSUB
kRETURN:    .data "RETURN",0,  8, kRETURN
kFOR:       .data "FOR"   ,0,  9, kFOR
kTO:        .data "TO"    ,0, 10, kTO
kSTEP:      .data "STEP"  ,0, 11, kSTEP
kNEXT:      .data "NEXT"  ,0, 12, kNEXT
kEND:       .data "END"   ,0, 13, kEND
kLIST:      .data "LIST"  ,0, 14, kLIST
kNEW:       .data "NEW"   ,0, 15, kNEW
kRUN:       .data "RUN"   ,0, 16, kRUN
kINPUT:     .data "INPUT" ,0, 17, kINPUT
kPRHEX:     .data "PRHEX" ,0, 18, kPRHEX
kRND:       .data "RND"   ,0, 19, kRND
kABS:       .data "ABS"   ,0, 20, kABS
kDIM:       .data "DIM"   ,0, 21, kDIM
stackKW:    .data $-1



