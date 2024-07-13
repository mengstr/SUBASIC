
    .include MACROS_MISC.inc    ; In/Out Clr/Set1/Neg Inc/Dec Mov
    .include MACROS_JMP.inc     ; JMP and conditional jumps
    .include MACROS_CMP.inc     ; Comparisons
    .include MACROS_STACK.inc   ; Stack operations
    .include MACROS_MULDIV.inc  ; Stack operations

;-------------------------------------------------------------------------------------------

    .macro PRINTCRLF    
        OUT ASCII_CR
        OUT ASCII_LF
    .endm

;--------------------------------------------------------------------------------------------

    .macro INDEXEDRD srcP dest   ; Copy [srcP] to dest
        MOV srcP @p
        CLR dest
        CLR tIdx
@p:     0 tIdx
        tIdx dest
    .endm

;--------------------------------------------------------------------------------------------

    .macro INDEXEDWR src destP  ; Copy src to [destP]
        MOV destP (@p1+0) 
        MOV destP (@p1+1)
        MOV destP (@p2+1)
        tIdx tIdx               ; T=0
        src tIdx                ; T=-src
@p1:    0 0                     ; [destP] = 0
@p2:    tIdx 0                  ; [destP+1] = T-[destP]
    .endm

;--------------------------------------------------------------------------------------------

    .macro INDEXEDCP srcP destP  ; Copy [srcP] to [destP]
    .endm        


;;; ; Add a to b
;;; .macro      add   a b
;;;             sble  a z
;;;             sble  z b
;;;             sble  z z
;;; .endm
;;; 
;;; ; Copy value at src to dest
;;; .macro      copy  src dest
;;;             sble  dest dest
;;;             add   src dest
;;; .endm
;;; 

;;; ; Copy value pointed to by 'srcPtr' to address pointed to by 'destPtr'
;;; ; TODO: Rename
;;; .macro      copy_pp srcPtr destPtr
;;;             copy  destPtr cpyWord
;;;             copy  destPtr cpyWord+1
;;;             copy  srcPtr  cpyWord+3
;;;             copy  destPtr cpyWord+7
;;; 
;;;             ; Copy a word from src to dest
;;; cpyWord:    sble  0 0
;;;             sble  0 z
;;;             sble  z 0
;;;             sble  z z
;;; .endm
;;; 
;;; 


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




