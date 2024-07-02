;--------------------------------------------------------------------------------------------
; int32_t multiply_signed_msb_first(int32_t a, int32_t b) {
;     int32_t result = 0;
; 
;     // Extend to 32 bits to handle sign
;     a = sign_extend_24(a);
;     b = sign_extend_24(b);
; 
;     // Determine the sign of the result
;     int32_t sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
; 
;     // Work with absolute values
;     a = (a < 0) ? -a : a;
;     b = (b < 0) ? -b : b;
; 
;     // Iterate through each bit of b, starting from the MSB (bit 23)
;     for (int i = 23; i >= 0; i--) {
;         result <<= 1; // Left shift the result to make room for the next addition
;         if (b & (1 << i)) { // Check if the i-th bit of b is set
;             result += a; // Add a to the result if the bit is set
;         }
;     }
; 
;     // Apply the sign to the result
;     result *= sign;
; 
;     // Mask the result to ensure it is within the 24-bit signed integer range
;     return sign_extend_24(result);
; }
; 

    .macro MUL a b                 ; Multiply a by b and store in b;
        CLR @result

        CLR @sign                   ; Calculate sign and absolute the a/b values
        JMPGE0 a @aIsPos
        NEG a
        TOGGLE01 @sign
@aIsPos:JMPGE0 b @bIsPos
        NEG b
        TOGGLE01 @sign
@bIsPos:

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
@sign:      .data 0
@aa:        .data 0
@cnt:       .data 0


@done:
        MOV @result b
        JMP0 @sign @done1
        NEG b
@done1:
    .endm

;-----------------------------------------------------------------------------

    .macro DIV a b

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

        MOV a @aa
        MOV b @bb

        CLR @sign                   ; Calculate sign and absolute the a/b values
        JMPGE0 @aa @aIsPos
        NEG @aa
        TOGGLE01 @sign
@aIsPos:JMPGE0 @bb @bIsPos
        NEG @bb
        TOGGLE01 @sign
@bIsPos:

    ; Check if the divisor is zero, then return MAXINT
        JMP0 @aa @divZero

; Else start the division

        CLR @quotient                      ;    uint32_t quotient = 0;
        MOV @bb @remainder                 ;    uint32_t remainder = abs_dividend;
        MOV @aa @temp_divisor              ;    uint32_t temp_divisor = abs_divisor;
        MOV CONST_1 @shifted_one           ;    uint32_t shifted_one = 1;

@loop1: 
        CMPLE @remainder @aa @skip1        ; while (remainder >= abs_divisor) {
        MOV @aa @temp_divisor              ;   temp_divisor = abs_divisor;
        MOV CONST_1 @shifted_one           ;   shifted_one = 1;
@loop2:                                     
        MOV @temp_divisor @t               ;   t=temp_divisor
        ADD @t @t                          ;   t = t << 1
        CMPGE @t @remainder @skip2         ;   while ((temp_divisor << 1) <= remainder) {
        JMPL0 @t @skip2
        ADD @temp_divisor @temp_divisor    ;            temp_divisor <<= 1;
        ADD @shifted_one @shifted_one      ;            shifted_one <<= 1;
        JMP @loop2                         ;  }
@skip2:

        SUB @temp_divisor @remainder        ;        remainder -= temp_divisor;
        ADD @shifted_one @quotient          ;        quotient += shifted_one;

        JMP @loop1                          ;}
@skip1:
        JMP @done

@aa:                .data 0
@bb:                .data 0
@quotient:          .data 0
@remainder:         .data 0
@temp_divisor:      .data 0
@shifted_one:       .data 0
@sign:              .data 0
@t:                 .data 0

@divZero:
        PUSH msgDivZeroError
        CALL PrintString
        JMP Restart


@done:
        MOV @quotient b
        MOV @remainder divRemainder
        JMP0 @sign @done1
        NEG b
@done1:

    .endm
