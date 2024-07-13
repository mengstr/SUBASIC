;-----------------------------------------------------------------------------
cmdDIM:       .proc cmdDIM
;-----------------------------------------------------------------------------
;
; Declare one or more variables named with more than one letter.
;
; DIM FOO,bar,Bletch
;
;-----------------------------------------------------------------------------

;        DEBUGPRINT "[CMDDIM]\r\n" ;debug
@loop:

    CMPEQ tokenPeek CONST_0 @done       ; If the token is an EOL, we're done
    CMPEQ tokenPeek ASCII_COLON @done   ; If the token is an colon, we're done

    ; Get the variable name
    INC tokenMode                       ; Set the token mode to get a (undeclared) name 
    CALL GetParsedToken

    CMPNE tokenType TT_STRING @tryMore
    JMPL0 varIsString @notAstringVariable
    MOV CONST_65 @len                   ; Strings are 64 bytes long + a terminating zero

@notAstringVariable:
;        DEBUGPRINT "INT VARIABLE PEEK=" ;debug
;       PUSH tokenPeek                  ;debug
;       CALL PrintInteger               ;debug
;       PRINTCRLF                       ;debug
    CMPNE tokenPeek ASCII_LEFT_PAREN @notArray

@array:
    INC pCode
;        DEBUGPRINT "pCode=" ;debug
;       PUSH pCode                  ;debug
;       CALL PrintInteger               ;debug

    PUSH pCode
    CALL ATOI

    
    PUSH atoiVal
    CALL InsertVar
    JMP @tryMore


@notArray:
    PUSH tokenStr
    PUSH CONST_1
    CALL InsertVar

@tryMore:
    CMPEQ tokenStr+1 ASCII_COMMA @loop  ; If comma try getting the next variable
    JMP @loop

@done
    JMP Statement

@len:   .data 0

    .endp 

