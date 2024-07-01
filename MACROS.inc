
    .include MACROS_MISC.inc    ; In/Out Clr/Set1/Neg Inc/Dec Mov
    .include MACROS_JMP.inc     ; JMP and conditional jumps
    .include MACROS_CMP.inc     ; Comparisons
    .include MACROS_STACK.inc   ; Stack operations

;-------------------------------------------------------------------------------------------

    .macro PRINTCRLF    
        OUT ASCII_CR
        OUT ASCII_LF
    .endm

;--------------------------------------------------------------------------------------------

    .macro MULU a b      ; Unsigned multiply a by b and store in b;
        CLR @result
        MOV a @aa

        MOV CONST_23 @cnt
@loop:
        JMPGE0 @aa @skip
        ADD b @result
@skip:
        ADD @aa @aa
        ADD @result @result
        DEC @cnt
        JMPG0 @cnt @loop

        JMPGE0 @aa @skip1
        ADD b @result
@skip1:

        JMP @done

@result:    .data 0
@aa:        .data 0
@cnt:       .data 0

@done:
        MOV @result b
    .endm


;--------------------------------------------------------------------------------------------

    .macro DIVUx a b                ; Unsigned divide b by a
        ; MACRO START - DIVU        
        CLR tmpA
@loop3:   
        a b @endLoop        ; Subtract until <= 0
        INC   tmpA
        JMP @loop3
@endLoop:    
        CONST_NEG1 b @done         ; If < 0
        INC tmpA
@done:  
        MOV tmpA b
        ; MACRO END - DIVU
    .endm


    .macro DIVU a b

;int32_t divide(int32_t dividend, int32_t divisor) {
;    // Handle division by zero
;    if (divisor == 0) {
;        printf("Division by zero is undefined.\n");
;        return 0;
;    }
;
;    // Handle special case where dividend is INT_MIN and divisor is -1
;    if (dividend == INT32_MIN && divisor == -1) {
;        return INT32_MAX; // Overflow case
;    }
;
;    // Determine sign of the result
;    int32_t sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
;
;    // Take the absolute value of dividend and divisor
;    uint32_t abs_dividend = (dividend < 0) ? -dividend : dividend;
;    uint32_t abs_divisor = (divisor < 0) ? -divisor : divisor;
;
;    uint32_t quotient = 0;
;    uint32_t remainder = abs_dividend;
;
;    // Perform division from least significant bit to most significant bit
;    uint32_t temp_divisor = abs_divisor;
;    uint32_t shifted_one = 1;
;
;    while (remainder >= abs_divisor) {
;        temp_divisor = abs_divisor;
;        shifted_one = 1;
;
;        // Shift left until temp_divisor just exceeds remainder
;        while ((temp_divisor << 1) <= remainder) {
;            temp_divisor <<= 1;
;            shifted_one <<= 1;
;        }
;
;        // Subtract and update quotient
;        remainder -= temp_divisor;
;        quotient += shifted_one;
;    }
;
;    // Adjust the sign of the quotient
;    if (sign < 0) {
;        quotient = -quotient;
;    }
;
;    return quotient;
;}


        CLR @quotient                       ;    uint32_t quotient = 0;
        MOV b @remainder                    ;    uint32_t remainder = abs_dividend;
        MOV a @temp_divisor                 ;    uint32_t temp_divisor = abs_divisor;
        MOV CONST_1 @shifted_one            ;    uint32_t shifted_one = 1;

@loop1: 
        CMPLE @remainder a @skip1          ; while (remainder >= abs_divisor) {
        MOV a @temp_divisor               ;   temp_divisor = abs_divisor;
        MOV CONST_1 @shifted_one           ;   shifted_one = 1;

@loop2:                                     
        MOV @temp_divisor @t               ;   t=temp_divisor
        ADD @t @t                          ;   t = t << 1
        CMPGE @t @remainder @skip2         ;   while ((temp_divisor << 1) <= remainder) {
        ADD @temp_divisor @temp_divisor    ;            temp_divisor <<= 1;
        ADD @shifted_one @shifted_one      ;            shifted_one <<= 1;
        JMP @loop2                         ;  }
@skip2:

        SUB @temp_divisor @remainder        ;        remainder -= temp_divisor;
        ADD @shifted_one @quotient          ;        quotient += shifted_one;

        JMP @loop1                          ;}
@skip1:
        JMP @done

@quotient:         .data 0
@remainder:        .data 0
@temp_divisor:     .data 0
@shifted_one:      .data 0
@t:                .data 0

@done:
    MOV @quotient b
    MOV @remainder divRemaninder
    .endm

;--------------------------------------------------------------------------------------------

    .macro INDEXEDRD srcP dest   ; Copy [srcP] to dest
        ; MACRO START - INDEXEDRD
        MOV srcP @p
        CLR dest        ; The next four instructions are a MOV macro expanded here inline
@p:     0 Z
        Z dest
        CLR Z
        ; MACRO END - INDEXEDRD
    .endm

;--------------------------------------------------------------------------------------------

    .macro INDEXEDWR src destP   ; Copy src to [destP]
        ; MACRO START - INDEXEDWR
        MOV destP (@p1+0) 
        MOV destP (@p1+1)
        MOV destP (@p2+1)

@p1:    0 0                     ; The next instructions are a MOV macro expanded here inline
        src Z
@p2     Z 0
        CLR Z
        ; MACRO END - INDEXEDWR
    .endm


;--------------------------------------------------------------------------------------------


    .macro DEBUGPRINT str
;        PUSH cyan                   ;debug
;        CALL PrintString           ;debug
;        PUSH @yo                   ;debug
;        CALL PrintString           ;debug
;        JMP @bo                    ;debug
;@yo:    .data $+1                  ;debug
;        .data str                  ;debug
;        .data 0                    ;debug
;@bo:                               ;debug
;        PUSH white                   ;debug
;        CALL PrintString           ;debug
    .endm


    .macro cyanChar c
;    PUSH cyan          ;debug
;    CALL PrintString   ;debug
;    OUT c              ;debug
;    PUSH white         ;debug
;    CALL PrintString   ;debug
    .endm

;--------------------------------------------------------------------------------------------




