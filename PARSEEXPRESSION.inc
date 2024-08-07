;-----------------------------------------------------------------------------
; PARSEEXPRESSION.inc
;-----------------------------------------------------------------------------

    .proc ParseExpression


expression:     .data 0
@op:            .data 0
@funcValue:     .data 0

ParseExpression:
        DEBUGPRINT "[PARSEEXPRESSION]\r\n"
        CLR expression
        CLR @op
        CLR @unaryFlag

@loop:
        JBETWEEN tokenPeek ASCII_A ASCII_Z @peekOk
        JBETWEEN tokenPeek ASCII_a ASCII_z @peekOk
        JBETWEEN tokenPeek ASCII_0 ASCII_9 @peekOk
        CMPEQ tokenPeek ASCII_DOUBLEQUOTE @peekOk
        CMPEQ tokenPeek ASCII_PLUS @peekOk              ; Operand + addition
        CMPEQ tokenPeek ASCII_MINUS @peekOk             ; Operand - subtraction
        CMPEQ tokenPeek ASCII_ASTERISK @peekOk          ; Operand * multiplication
        CMPEQ tokenPeek ASCII_SLASH @peekOk             ; Operand / division
        CMPEQ tokenPeek ASCII_VERTICAL_BAR @peekOk      ; Operand | OR
        CMPEQ tokenPeek ASCII_AMPERSAND @peekOk         ; Operand & AND
        CMPEQ tokenPeek ASCII_CARET @peekOk             ; Operand ^ XOR
        CMPEQ tokenPeek ASCII_PERCENT @peekOk           ; Operand % MODULUS
        
;       DEBUGPRINT "[TOKENPEEK FAIL] got " ;debug
;       PUSH tokenPeek                      ;debug
;       CALL PrintInteger                   ;debug
;       PRINTCRLF                           ;debug
        RET

@peekOk:
        MOV pCode @pCodeHold

        CALL GetParsedToken
        CMPEQ tokenType TT_KEYWORD @isKeyword           ; Keyword
        CMPEQ tokenType TT_NUMBER @isNum                ; Number
        CMPEQ tokenType TT_VARINT @isVar                ; Variable
        CMPEQ tokenType TT_MISC @isOp                   ; Operand
        RET

@isKeyword:
        CMPEQ tokenValue kwRND @isRND
        CMPEQ tokenValue kwABS @isABS
        CMPEQ tokenValue kwSQRT @isSQRT
        MOV @pCodeHold pCode                    ; If the expression is terminated by a keyword we need to
        RET                                     ; roll back that keyword so it can be processsed properly.

@isRND:
        CALL GetParsedToken
        CMPNE tokenValue ASCII_LEFT_PAREN SyntaxError

        CALL GetParsedToken
        PUSH tokenValue
        CALL Random
        MOV rndVal @funcValue

        CALL GetParsedToken
        CMPNE tokenValue ASCII_RIGHT_PAREN SyntaxError

        MOV @funcValue tokenValue
        JMP @isFunc

@isSQRT:
        CALL GetParsedToken
        CMPNE tokenValue ASCII_LEFT_PAREN SyntaxError

        CALL GetParsedToken
        MOV tokenValue @funcValue 

;;; FUNCTION IntegerSqrt(N)
;;;     DIM guess AS INTEGER
;;;     DIM last_guess AS INTEGER
;;;     guess = N / 2  ' Initial guess
;;;     last_guess = 0
;;; 
;;;     IF N = 0 THEN
;;;         IntegerSqrt = 0
;;;         EXIT FUNCTION
;;;     END IF
;;; 
;;;     WHILE ABS(guess - last_guess) > 1
;;;         last_guess = guess
;;;         guess = (guess + N / guess) / 2  ' Babylonian method iteration
;;;     WEND
;;; 
;;;     ' Ensure the result is correct by checking the guess and the next integer
;;;     IF (guess + 1) * (guess + 1) <= N THEN
;;;         guess = guess + 1
;;;     END IF
;;; 
;;;     IntegerSqrt = guess
;;; END FUNCTION
;;; 
        DIV CONST_2 @funcValue  ; Initial guess. funcValue=funcValue/2
        CLR @last_x

sqrtLoop:
        SUB @funcValue @last_x
;       PUSH @last_x
;       CALL PrintInteger
;       PRINTCRLF
        JBETWEEN @last_x MINUS1 CONST_1 @sqrtDone
        MOV @funcValue @last_x                ; last_x = x

        MOV tokenValue @foo     
        DIV @funcValue @foo
        MOV @foo @funcValue

        ADD @last_x @funcValue 
        DIV CONST_2 @funcValue
        JMP sqrtLoop

@sqrtDone:

        CALL GetParsedToken
        CMPNE tokenValue ASCII_RIGHT_PAREN SyntaxError

        MOV @funcValue tokenValue
        JMP @isFunc


@isABS:
        CALL GetParsedToken
        CMPNE tokenValue ASCII_LEFT_PAREN SyntaxError

        CALL GetParsedToken
        MOV tokenValue @funcValue 
        JMPGE0 @funcValue @abs1
        NEG @funcValue
@abs1: 

        CALL GetParsedToken
        CMPNE tokenValue ASCII_RIGHT_PAREN SyntaxError

        MOV @funcValue tokenValue
        JMP @isFunc

@isOp:
        CMPEQ tokenValue ASCII_MINUS @testUnary        ;Operand - subtraction
        CMPEQ tokenValue ASCII_PLUS @opOk              ; Operand + addition
        CMPEQ tokenValue ASCII_ASTERISK @opOk          ; Operand * multiplication
        CMPEQ tokenValue ASCII_SLASH @opOk             ; Operand / division
        CMPEQ tokenValue ASCII_VERTICAL_BAR @opOk      ; Operand | OR
        CMPEQ tokenValue ASCII_AMPERSAND @opOk         ; Operand & AND
        CMPEQ tokenValue ASCII_CARET @opOk             ; Operand ^ XOR
        CMPEQ tokenValue ASCII_PERCENT @opOk           ; Operand % MODULUS
        JMP @loop

; If the previous token was an operand then this is a unary operator
@testUnary:
        JMP0 @op @opOk         
        INC @unaryFlag
        JMP @loop

@opOk:
        MOV tokenValue @op
        JMP @loop


@isNum:
@isVar:
@isFunc:
        JMP0 @unaryFlag @notUnary      ; If we are in unary mode then negate the value
        NEG tokenValue
        CLR @unaryFlag
@notUnary:
        CMPEQ @op ASCII_PLUS @addition
        CMPEQ @op ASCII_MINUS @subtraction
        CMPEQ @op ASCII_ASTERISK @multiplication
        CMPEQ @op ASCII_SLASH @division
        CMPEQ @op ASCII_VERTICAL_BAR @or       ; Operand | OR
        CMPEQ @op ASCII_AMPERSAND @and         ; Operand & AND
        CMPEQ @op ASCII_CARET @xor             ; Operand ^ XOR
        CMPEQ @op ASCII_PERCENT @modulus       ; Operand % MODULUS
        MOV tokenValue expression
        JMP @loop

@addition
        ADD tokenValue expression
        CLR @op
        JMP @loop

@multiplication:
        MUL tokenValue expression
        CLR @op
        JMP @loop

@division
        DIV tokenValue expression
        CLR @op
        JMP @loop

@subtraction:
        SUB tokenValue expression
        CLR @op
        JMP @loop

@modulus
        MOV expression @tmp
        DIV tokenValue @tmp
        MOV divRemainder expression
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

@unaryFlag: .data 0
@pCodeHold: .data 0                     ; To back up to the previous token when required
@tmp:       .data 0
@last_x:    .data 0
@foo:       .data 0

    .endp
