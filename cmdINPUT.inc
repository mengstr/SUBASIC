;-----------------------------------------------------------------------------
cmdINPUT:        .proc cmdINPUT
;-----------------------------------------------------------------------------
;
; Read a value from the user and store it in a variable
;
; INPUT A
;
;-------|-----------------------------------|-------------------------------------

       CALL GetParsedToken
       MOV tokenAddr @var1     ; Get the address of the variable to receive the input data

       CALL InputString
       CMPEQ tokenType TT_VARINT @isInt
       CMPEQ tokenType TT_VARSTR @isString
       JMP SyntaxError

@isString:
       MOV buf @src
@isStringLoop:
       INDEXEDRD @src @ch
       INDEXEDWR @ch @var1
       INC @src
       INC @var1
       JMPN0 @ch @isStringLoop       
       JMP @done

@isInt:
       PUSH buf
       CALL ATOI
       INDEXEDWR atoiVal @var1

@done:
       PRINTCRLF
       JMP Statement

@var1:        .data 0
@src:         .data 0
@ch:          .data 0

        .endp
