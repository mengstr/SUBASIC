;--------------------------------------------------------------------------------------------

    .macro HALT 
        Z Z (-1)            ; Jump to -1 which halts execution
    .endm

;--------------------------------------------------------------------------------------------

    .macro OUT addr
        addr (-1)           ; Writing to address -1 will output the value to screen
    .endm

;--------------------------------------------------------------------------------------------

    .macro IN addr
        (-1) addr           ; Reading from address -1 will input a value from keyboard
    .endm

;--------------------------------------------------------------------------------------------

    .macro CLR addr
        addr addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro SET1 addr
        CLR addr
        INC addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro INC addr
        MINUS1 addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro DEC addr
        PLUS1 addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro NEG src          ; Negate src
        CLR tmpA
        src tmpA
        MOV tmpA src
    .endm

;--------------------------------------------------------------------------------------------

    .macro SUB a b         ; Subtract a from b and store in b
        a b
    .endm

;--------------------------------------------------------------------------------------------

    .macro ADD a b         ; Add a to b and store in b
        a Z                ; Z = -a
        Z b                ; b = b - Z = b - -a = b + a
        CLR Z
    .endm

;--------------------------------------------------------------------------------------------

    .macro TOGGLE01 dst
        Z dst @zorm             ; If 0 (or negative)
        CLR dst
        JMP @done
@zorm:  CLR dst
        INC dst
@done:
    .endm

;--------------------------------------------------------------------------------------------

    .macro MOV src dest      ; Copy value at src to dest
        CLR dest
        src Z
        Z dest
        CLR Z
    .endm
