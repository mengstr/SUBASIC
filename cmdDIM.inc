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
    CALL GetParsedToken
    CMPNE tokenType TT_STRING @notNewVariable

    CALL InsertVar

@notNewVariable:
    CMPEQ tokenStr+1 ASCII_COMMA @loop  ; If comma try getting the next variable
    JMP @loop

@done
    JMP Statement

    .endp 

