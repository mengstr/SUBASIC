
;--------------------------------------------------------------------------------------------

    .macro JMP addr         ; Ucondtional JUMP to addr
        Z Z addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro JMP0 v addr      ; Jump to addr if v is zero
        JMPG0 v @done
        CLR tmpA
        v tmpA @L2
        JMP @done
@L2:    CONST_1 tmpA addr
@done:
    .endm

;--------------------------------------------------------------------------------------------

    .macro JMPN0 v addr    ; Jump to addr if v is not zero
        JMP0 v @done
        JMP addr
@done:
    .endm

;--------------------------------------------------------------------------------------------

    .macro JMPG0 v addr    ; Jump to addr if v is positive ( >0 )
        Z v @done
        JMP addr
@done:        
    .endm      

;--------------------------------------------------------------------------------------------

    .macro JMPL0 v addr    ; Jump to addr if v is negative ( <0 )
        JMPG0 v @done
        JMP0 v @done
        JMP addr
@done:
    .endm      

;--------------------------------------------------------------------------------------------

    .macro JMPGE0 v addr    ; Jump to addr if v is greater than or equal to zero ( >=0 )
        JMPG0 v addr
        JMP0 v addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro JMPLE0 v addr    ; Jump to addr if v is less than or equal to zero ( <=0 )
        Z v addr
    .endm

;--------------------------------------------------------------------------------------------    