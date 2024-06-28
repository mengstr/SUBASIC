;-----------------------------------------------------------------------------
; PARSEEXPRESSION.inc
;-----------------------------------------------------------------------------

    .proc ParseExpression


expression:     .data 0
@op:            .data 0

ParseExpression:
;        DEBUGPRINT "ParseExpression\r\n" ;debug
        CLR expression
        CLR @op

@loop:
        JBETWEEN tokenPeek ASCII_A ASCII_Z @peekOk
        JBETWEEN tokenPeek ASCII_z ASCII_z @peekOk
        JBETWEEN tokenPeek ASCII_0 ASCII_9 @peekOk
        CMPEQ tokenPeek ASCII_DOUBLEQUOTE @peekOk
        CMPEQ tokenPeek ASCII_PLUS @peekOk              ; Operand + addition
        CMPEQ tokenPeek ASCII_MINUS @peekOk             ; Operand - subtraction
        CMPEQ tokenPeek ASCII_ASTERISK @peekOk          ; Operand * multiplication
        CMPEQ tokenPeek ASCII_SLASH @peekOk             ; Operand / division
        CMPEQ tokenPeek ASCII_VERTICAL_BAR @peekOk      ; Operand | OR
        CMPEQ tokenPeek ASCII_AMPERSAND @peekOk         ; Operand & AND
        CMPEQ tokenPeek ASCII_CARET @peekOk             ; Operand ^ XOR
        
        RET

@peekOk:
        MOV pCode @pCodeHold

        CALL GetParsedToken
        CMPEQ tokenType CONST_3 @isKeyword

;       CALL debugToken                 ;debug
;        PRINTCRLF                      ;debug;

        CMPEQ tokenType CONST_1 @isNum          ; Number
        CMPEQ tokenType CONST_2 @isVar          ; Variable
        CMPEQ tokenType CONST_5 @isOp           ; Operand
        RET

@isKeyword:
        MOV @pCodeHold pCode                    ; If the expression is terminated by a keyword we need to
        RET                                     ; roll back that keyword so it can be processsed properly.


@isOp:
        CMPEQ tokenValue ASCII_PLUS @opOk
        CMPEQ tokenValue ASCII_MINUS @opOk
        CMPEQ tokenValue ASCII_ASTERISK @opOk
        CMPEQ tokenValue ASCII_SLASH @opOk
        CMPEQ tokenValue ASCII_VERTICAL_BAR @opOk      ; Operand | OR
        CMPEQ tokenValue ASCII_AMPERSAND @opOk         ; Operand & AND
        CMPEQ tokenValue ASCII_CARET @opOk             ; Operand ^ XOR
        JMP @loop
@opOk:
        MOV tokenValue @op
        JMP @loop

@isNum:
@isVar:
        CMPEQ @op ASCII_PLUS @addition
        CMPEQ @op ASCII_MINUS @subtraction
        CMPEQ @op ASCII_ASTERISK @multiplication
        CMPEQ @op ASCII_SLASH @division
        CMPEQ @op ASCII_VERTICAL_BAR @or      ; Operand | OR
        CMPEQ @op ASCII_AMPERSAND @and         ; Operand & AND
        CMPEQ @op ASCII_CARET @xor             ; Operand ^ XOR
        MOV tokenValue expression
        JMP @loop

@addition
        ADD tokenValue expression
        CLR @op
        JMP @loop

@multiplication:
        MULU tokenValue expression
        CLR @op
        JMP @loop

@division
        DIVU tokenValue expression
        CLR @op
        JMP @loop

@subtraction:
        SUB tokenValue expression
        CLR @op
        JMP @loop

@or:
        PUSH tokenValue
        PUSH expression
        CALL OR
        MOV bitopResult expression
        CLR @op
        JMP @loop

@and:
        PUSH tokenValue
        PUSH expression
        CALL AND
        MOV bitopResult expression
        CLR @op
        JMP @loop

@xor:
        PUSH tokenValue
        PUSH expression
        CALL XOR
        MOV bitopResult expression
        CLR @op
        JMP @loop

@pCodeHold: .data 0                     ; To back up to the previous token when required

    .endp
