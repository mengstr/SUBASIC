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
    CMPEQ tokenStr+1 ASCII_COMMA @loop  ; If comma try getting the next variable

    MOV vars2 @vp                        ; Point to the list of long variable names

    ; Find an empty slot in the list
@findempty:    
    INDEXEDRD @vp @ch
    CMPEQ @ch ASCII_SPACE @empty
    ADD CONST_8 @vp                           ; Nope, try the next slot
    JMP @findempty

    ; Found an empty slot, copy the variable name to the list
@empty:
    MOV tokenStr @tp
    MOV CONST_8 @cnt

@copyloop:
    INDEXEDRD @tp @ch
    INDEXEDWR @ch @vp
    INC @tp
    INC @vp

    DEC @cnt
    JMPN0 @cnt @copyloop
    JMP @loop

@done
    JMP Statement

@vp:        .data 0
@tp:        .data 0
@ch:        .data 0
@cnt:       .data 0

    .endp 

