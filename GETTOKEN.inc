;-----------------------------------------------------------------------------
; GETPARSEDTOKEN.inc
;
; This module provides a function to get the next token from the program source.
;
; Input:
;   pCode points to the current position in the program source. I.E the character 
;   to read and check next.
;
; Outputs:
;   pCode - pointing to the character in the program source to be parsed the next time.
;
;   tokenType  - Type of the token.
;                   0 = EOL
;                   1 = Number
;                   2 = Variable
;                   3 = Keyword
;                   4 = String
;                   5 = Miscellaneous (operator, semicolon, colon, etc)
;
;   tokenValue - Value of the token. 
;                   For numbers, this is the value of the number.
;                   For variables, this is the current value of the variable.
;
;   tokenAddr  - Address of the variable
;
;   tokenStr   - The token as a string
;                   For numbers, this is the string representation of the number.
;                   For variables, this is the name of the variable.
;                   For keywords, this is the keyword.  
;                   For strings, this is the string with the quotes removed
;                   For miscellaneous, this is the character itself
;
;
; Start by skipping any leading spaces.
;
; If the first non-space is EOL, return EOL
;
; If the first non-space chacater is a digit, then start collecting a number.
;   As long as we have digits, we the current value by 10 and add the digit.
;   Also collect them into tokenStr
;   If we reach a non-digit, then return the token as a number
;
; If the first non-space character is a double quote, then start collecting a string.
;   As long as we have characters not a double quote, collect them into tokenStr
;
; If the first non-space charecter is a letter, then start collecting a keyword or a variable.
;   As long as we have letters, digits or underscore collect them into tokenStr
;
; If the first non-space character is anything else then put just that character into tokenStr
;   and return as a miscellaneous token
;
;-----------------------------------------------------------------------------


TT_EOL:           .equ CONST_0
TT_NUMBER:        .equ CONST_1
TT_VARINT:        .equ CONST_2
TT_VARSTR:        .equ CONST_3
TT_KEYWORD:       .equ CONST_4
TT_STRING:        .equ CONST_5
TT_MISC:          .equ CONST_6
TT_NOTFOUND:      .equ CONST_7

tokenType:        .data 0     
tokenValue:       .data 0
tokenAddr:        .data 0
tokenPeek:        .data 0
varIsString:      .data 0

tokenStr:   .data $+1
            .data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
            .data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
            .data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
            .data 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
pTokenStr   .data 0
tokenMode:  .data 0                ; 0 = Normal, 1 = accept non declared variables


pCode:      .data 0                 ; Pointer to the current position in the program source
ch:         .data 0                 ; Current character being processed

      .proc SkipSpaces
SkipSpaces:
            INDEXEDRD pCode ch
            CMPEQ ch CONST_0 @done
            CMPNE ch ASCII_SPACE @done
            INC pCode
            JMP SkipSpaces             
@done:      RET
      .endp

      .proc GetToken
GetParsedToken: 
            DEBUGPRINT "[GETPARSEDTOKEN]\r\n"

            CLR tokenType
            CLR tokenValue
            CLR tokenAddr
            CLR tokenPeek
            MOV tokenStr pTokenStr
            CLR tokenStr+1

            CALL SkipSpaces                           ; Skip any leading spaces

            CMPEQ ch CONST_0 @atEOL                   ; Reached End-of-Line
            CMPEQ ch ASCII_DOUBLEQUOTE @string        ; Collect a String
            JBETWEEN ch ASCII_0 ASCII_9 @number       ; Collect a Number
            JBETWEEN ch ASCII_A ASCII_Z @kwVar        ; Collect a Keyword or Variable
            JBETWEEN ch ASCII_a ASCII_z @kwVar        ; Collect a Keyword or Variable

            MOV ch tokenValue                         ; Store in both tokenValue

            INDEXEDWR ch pTokenStr                    ; and in tokenString
            INC pTokenStr
            INDEXEDWR CONST_0 pTokenStr               ; Terminate the collected tokenString

            INC pCode                                 ; Gobble up the character
            CALL SkipSpaces                           ; Skip trailing spaces
            MOV ch tokenPeek                          ; Store the next non-space character as peek

            MOV TT_MISC tokenType                     ; Return with type as miscellaneous (5)
            RET

@atEOL:     INC pCode
            MOV TT_EOL tokenType                     ; Return with type as EOL (0)
            RET

@string:    INC pCode                                 ; Skip the initial quote
            INDEXEDRD pCode ch
            CMPEQ ch ASCII_DOUBLEQUOTE @stringDone
            CMPEQ ch CONST_0 SyntaxError
            INDEXEDWR ch pTokenStr
            INC pTokenStr
            JMP @string
@stringDone:INC pCode                                 ; Skip the trailing quote
            INDEXEDWR CONST_0 pTokenStr               ; Terminate the collected tokenString

            CALL SkipSpaces                           ; Skip trailing spaces
            MOV ch tokenPeek                          ; Store the next non-space character as peek

            MOV TT_STRING tokenType                     ; Return with type as string (4)
            RET

@number:    INDEXEDWR ch pTokenStr                    ; Append digit to string
            INC pTokenStr

            MUL CONST_10 tokenValue                   ; Compute the current number collected so far
            ADD ch tokenValue
            SUB ASCII_0 tokenValue

            INC pCode                                 ; Get next digit and continue collecting if
            INDEXEDRD pCode ch                        ; it's a digit
            JBETWEEN ch ASCII_0 ASCII_9 @number

            INDEXEDWR CONST_0 pTokenStr               ; Terminate string

            CALL SkipSpaces                           ; Skip trailing spaces
            MOV ch tokenPeek                          ; Store the next non-space character as peek

            MOV TT_NUMBER tokenType                     ; Return with type as numeric (1)
            RET


@kwVar:     CLR varIsString                           ; Set variable as normal integer
@kwVarLoop: JBETWEEN ch ASCII_a ASCII_z @lc
            JMP @uc
@lc:        SUB CONST_32 ch
@uc:        INDEXEDWR ch pTokenStr                    ; Append character to string
            INC pTokenStr

            INC pCode                                 ; Get the next character
            INDEXEDRD pCode ch

            JBETWEEN ch ASCII_A ASCII_Z @kwVarLoop    ; Keep collecting as long we have A-Z, a-z 0-9 or underscore 
            JBETWEEN ch ASCII_a ASCII_z @kwVarLoop  
            JBETWEEN ch ASCII_0 ASCII_9 @kwVarLoop      
            CMPEQ ch ASCII_UNDERSCORE @kwVarLoop      
            CMPEQ ch ASCII_DOLLAR @kwVarDollar        ; We also allow dollar sign in variable names, but that will
            JMP @kwVarDone                            ; terminate the variable name

@kwVarDollar:
            INDEXEDWR ch pTokenStr                    ; Append character to string
            INC pTokenStr
            INC pCode
            INC varIsString                           ; Set variable type as string

@kwVarDone:
            INDEXEDWR CONST_0 pTokenStr               ; Terminate the collected tokenString

            CALL SkipSpaces                           ; Skip trailing spaces
            MOV ch tokenPeek                          ; Store the next non-space character as peek

            ;
            ; Check if it is a keyword
            ;

            PUSH tokenStr
            CALL FindKeyword
            CMPEQ tokenType TT_NOTFOUND @notAKeyword

            CALL SkipSpaces                     ; Skip trailing spaces
            MOV ch tokenPeek                    ; Store the next non-space character as peek
            RET

            ;
            ; It is a variable
            ;
@notAKeyword:
            JMP0 tokenStr+2 @is1CharVar         ; If the token is a single character, then it is a predefined plain integer variable

            ;
            ; Check for long variable name
            ;
            MOV TT_VARINT tokenType           ; Return with type as Variable 
            PUSH tokenStr
            CALL FindVariable
            CMPEQ tokenType TT_NOTFOUND @notVariable
            JMP0 varIsString @doneVar
            MOV TT_VARSTR tokenType           ; Return with type as String Variable 
            JMP @doneVar


@is1CharVar:
            MOV TT_VARINT tokenType           ; Return with type as Integer Variable 
            MOV tokenStr+1 @p                   ; Get the variable name
            SUB ASCII_A @p                      ; Variable A is the first one so we need to offset the pointer
            ADD vars1 @p                        ; Offset to the beginning of the variable table
            MOV @p tokenAddr                    ; Store the address of the variable
            INDEXEDRD tokenAddr tokenValue      ; Get the value of the variable

@doneVar:
            CALL SkipSpaces                     ; Skip trailing spaces
            MOV ch tokenPeek                    ; Store the next non-space character as peek
            CLR tokenMode                       ; Reset the tokenMode
            RET


@notVariable:
            JMP0 tokenMode SyntaxError          ; If we are not accepting non declared variables, then it is an error
            CALL SkipSpaces                     ; Skip trailing spaces
            MOV ch tokenPeek                    ; Store the next non-space character as peek
            CLR tokenMode                       ; Reset the tokenMode
            MOV TT_STRING tokenType             ; Return with type as String (used by DIM statement)
            RET
            
            

@k          .data 0
@p          .data 0


    .endp

