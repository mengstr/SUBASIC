;-----------------------------------------------------------------------------
cmdDIM:       .proc cmdDIM
;-----------------------------------------------------------------------------
;
; Declare one or more variables named with more than one letter.
;
; DIM FOO,bar,Bletch
;
;-----------------------------------------------------------------------------

@loop:

    CMPEQ tokenPeek CONST_0 @done       ; If the token is an EOL, we're done
    CMPEQ tokenPeek ASCII_COLON @done   ; If the token is an colon, we're done

    ; Get the variable name
    INC tokenMode                       ; Set the token mode to get a variable name 
    CLR @len                            ; We assume a standard 1 triword variable
    INC @len
    CALL GetParsedToken
    CMPNE tokenType TT_STRING @notNewVariable
    JMPL0 varIsString @notAstringVariable
    MOV CONST_65 @len                   ; Strings are 64 bytes long + a terminating zero
@notAstringVariable:
    PUSH @len
    CALL InsertVar

@notNewVariable:
    CMPEQ tokenStr+1 ASCII_COMMA @loop  ; If comma try getting the next variable
    JMP @loop

@done
    JMP Statement

@len:   .data 0

    .endp 

