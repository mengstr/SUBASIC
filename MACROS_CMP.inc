;--------------------------------------------------------------------------------------------

    .macro CMPEQ v1 v2 addr ; OK Compare and jump to addr if v1 = v2 (Equal)
        MOV v2 tmpB
        v1 tmpB
        JMP0 tmpB addr
    .endm

;--------------------------------------------------------------------------------------------

    .macro CMPNE v1 v2 addr ; OK Compare and jump to addr if v1 != v2 (Not Equal)
        CMPEQ v1 v2 @done
        JMP addr
@done:
    .endm

;--------------------------------------------------------------------------------------------

; bool is_less_(int8_t i1, int8_t i2) {         // Handle direct comparison cases based on sign
;   if (i1 < 0 && i2 >= 0) return true;         // Negative i1 is always less than or equal to positive i2
;   if (i1 >= 0 && i2 < 0) return false;        // Positive i1 is always greater than negative i2
;   int8_t diff = i2 - i1;                      // If both are of the same sign, perform subtraction
;   // If both numbers are non-negative or both are negative, return true if diff > 0
;   return diff > 0;
; }

    .macro CMPLE v1 v2 addr ; Compare and jump to addr if v1 < v2 (Less than)
        JMPGE0 v1 @notPos1Neg2
        JMPL0 v2 @notPos1Neg2
        JMP addr

@notPos1Neg2:
        JMPL0 v1 @notNeg1Pos2
        JMPGE0 v2 @notNeg1Pos2
        JMP @done

@notNeg1Pos2:
        MOV v2 tmpB
        SUB v1 tmpB
        JMPG0 tmpB addr

@done:
    .endm

;--------------------------------------------------------------------------------------------

; bool is_less_or_equal(int8_t i1, int8_t i2) { // Handle direct comparison cases based on sign
;   if (i1 < 0 && i2 >= 0) return true;         // Negative i1 is always less than or equal to positive i2
;   if (i1 >= 0 && i2 < 0) return false;        // Positive i1 is always greater than negative i2
;   int8_t diff = i2 - i1;                      // If both are of the same sign, perform subtraction
;   // If both numbers are non-negative or both are negative, return true if diff >= 0
;   return diff >= 0;
; }

    .macro CMPLEQ v1 v2 addr ; Compare and jump to addr if v1 <= v2 (Less than or equal)
        JMPGE0 v1 @notPos1Neg2
        JMPL0 v2 @notPos1Neg2
        JMP addr

@notPos1Neg2:
        JMPL0 v1 @notNeg1Pos2
        JMPGE0 v2 @notNeg1Pos2
        JMP @done

@notNeg1Pos2:
        MOV v2 tmpB
        SUB v1 tmpB
        JMPGE0 tmpB addr

@done:
    .endm

;--------------------------------------------------------------------------------------------

; bool is_greater(int8_t i1, int8_t i2)  {   // Handle direct comparison cases based on sign
;  if (i1 >= 0 && i2 < 0) return true;      // Positive i1 is always greater than negative i2
;  if (i1 < 0 && i2 >= 0) return false;     // Negative i1 is always less than or equal to positive i2
;  int8_t diff = i1 - i2;                   // If both are of the same sign, perform subtraction
;  // If both numbers are non-negative or both are negative, return true if diff > 0
;  return diff > 0;
; }

    .macro CMPGE v1 v2 addr ; Compare and jump to addr if v1 > v2 (Greater than)
        JMPL0 v1 @notPos1Neg2
        JMPGE0 v2 @notPos1Neg2
        JMP addr

@notPos1Neg2:
        JMPGE0 v1 @notNeg1Pos2
        JMPL0 v2 @notNeg1Pos2
        JMP @done

@notNeg1Pos2:
        MOV v1 tmpB
        SUB v2 tmpB
        JMPG0 tmpB addr

@done:
    .endm

;--------------------------------------------------------------------------------------------

; bool is_greater_or_equal(int8_t i1, int8_t i2) {   // Handle direct comparison cases based on sign
;  if (i1 >= 0 && i2 < 0) return true;              // Positive i1 is always greater than or equal to negative i2
;  if (i1 < 0 && i2 >= 0) return false;             // Negative i1 is always less than positive i2
;  int8_t diff = i1 - i2;                           // If both are of the same sign, perform subtraction
;  // If both numbers are non-negative or both are negative, return true if diff >= 0
;  return diff >= 0;
; } 

    .macro CMPGEQ v1 v2 addr ; Compare and jump to addr if v1 >= v2 (Greater than or equal)
        JMPL0 v1 @notPos1Neg2
        JMPGE0 v2 @notPos1Neg2
        JMP addr

@notPos1Neg2:
        JMPGE0 v1 @notNeg1Pos2
        JMPL0 v2 @notNeg1Pos2
        JMP @done

@notNeg1Pos2:
        MOV v1 tmpB
        SUB v2 tmpB
        JMPGE0 tmpB addr

@done:
    .endm


;--------------------------------------------------------------------------------------------

    .macro JBETWEEN val A B addr    ; Jump to addr if val is between A and B (inclusive)
    CMPLE val A @done
    CMPGE val B @done
    JMP addr
@done:
    .endm

;--------------------------------------------------------------------------------------------
