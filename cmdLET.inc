;-----------------------------------------------------------------------------
cmdLET:        .proc cmdLET
;-----------------------------------------------------------------------------
;
; Assign an expression to a variable
; 
; LET A = 1
; LET A = A + 1
;
;-------|-----------------------------------|-------------------------------------

        DEBUGPRINT "[cmdLET]\r\n"

        CALL GetParsedToken                 ; Get the variable name
        MOV tokenAddr @dest

        CALL GetParsedToken                 ; Get the equals sign

        CALL ParseExpression                ; Get the value expression
;       DEBUGPRINT "tokenType="             ;debug
;       PUSH tokenType                      ;debug
;       CALL PrintInteger                   ;debug
;       PRINTCRLF                           ;debug

        CMPEQ tokenType TT_NUMBER @isNum     ; If the value is a number
        CMPEQ tokenType TT_VARINT @isNum     ; If the value is a integer variable
        CMPEQ tokenType TT_STRING @isString  ; If the value is a string
        JMP SyntaxError

@isNum:
        INDEXEDWR expression @dest          ; Store the value in the variable
        JMP Statement

@isString:
        MOV tokenStr @src
;       DEBUGPRINT "tokenStr='"    ;debug
;        PUSH @src              ;debug
;        CALL PrintString       ;debug
;        PRINTCRLF             ;debug
@isStringLoop:
        INDEXEDRD @src @ch
        INDEXEDWR @ch @dest             ; Store the value in the variable
        INC @src
        INC @dest
        JMPN0 @ch @isStringLoop
        JMP Statement

@src:  .data 0
@dest:  .data 0
@ch:    .data 0

        .endp
