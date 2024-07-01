;--------------------------------------------------------------------------------------------

   .macro PUSH var
        INDEXEDWR var SP
        INC SP
    .endm

;--------------------------------------------------------------------------------------------

    .macro POP var
        DEC SP
        INDEXEDRD SP var
    .endm

;--------------------------------------------------------------------------------------------

  .macro CALL addr
        PUSH @ra
        JMP addr
@ra:    .data $+1
    .endm

;--------------------------------------------------------------------------------------------

    .macro RET
        POP @j
        .data 0,0
@j:     .data 0x555555
    .endm

;--------------------------------------------------------------------------------------------

