    .proc ATOI

@p:         .data 0  ; Pointer to the string to convert
@t:         .data 0  ; Temporary hold variable
@digit:     .data 0

ATOI:
    POP @t              ; Pop off the return address and parameters
    POP @p
    PUSH @t             ; Push the return address back onto the stack

    CLR atoiVal

@loop:
    INDEXEDRD @p @digit
    JBETWEEN @digit ASCII_0 ASCII_9 @valid ; If the character is not a digit, we are done
    RET

@valid:
    ASCII_0 @digit              ; Make the ascii digit to a number
    MULU CONST_10 atoiVal          ; Collect the digit into the result
    ADD @digit atoiVal

    INC @p                      ; Point to the next character
    JMP @loop                   ; Loop back and continue processing digits

    .endp


