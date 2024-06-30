
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

    .macro MULU a b       ; Unsigned multiply a by b and store in b;
        ; MACRO START - MULU        
        MOV a tmpA
        MOV b tmpB
        CLR b
        INC   tmpA
@loop:  CONST_1 tmpA @done         ; Subtract until aC <= 0
        ; Add a to b
        tmpB Z
        Z b
        JMP @loop
@done:
        ; MACRO END - MULU
    .endm

;--------------------------------------------------------------------------------------------

    .macro DIVU a b                ; Unsigned divide b by a
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




