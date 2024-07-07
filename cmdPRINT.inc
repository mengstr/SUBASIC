;-----------------------------------------------------------------------------
cmdPRINT:       .proc cmdPRINT
;-----------------------------------------------------------------------------
;
; Print the value of one or more expressions or string litterals.
;
; PRINT 1
; PRINT A
; PRINT "Hello"
; PRINT 2;
; PRINT B;
; PRINT "World";
; PRINT A;3;"foo";B;4;"bar"
;
;-----------------------------------------------------------------------------

    DEBUGPRINT "[cmdPRINT]\r\n"

@loop:
    CMPEQ tokenPeek CONST_0 @doneCrlf       ; If the token is an EOL, we're done
    CMPEQ tokenPeek ASCII_COLON @doneCrlf   ; If the token is an colon, we're done

    CALL ParseExpression
    CMPEQ tokenType TT_STRING @string               ; If the token is a string, print it
    PUSH expression                         ; Else print the integer (constant/variable)
    CALL PrintInteger
    JMP @continue

@string:
    PUSH tokenStr
    CALL PrintString

@continue:
    CMPNE tokenPeek ASCII_SEMICOLON @doneCrlf
    CALL GetParsedToken                     ; Gobble up the semicolon
    JMP @loop                               ; ...and do more printing if required


@doneCrlf
    CMPNE tokenType TT_MISC @crlf
    CMPEQ tokenValue ASCII_SEMICOLON Statement
@crlf:
    PRINTCRLF                               ; Else print a CRLF and continue with the next statement
    JMP Statement

    .endp 


;-----------------------------------------------------------------------------
cmdPRHEX:       .proc cmdPRHEX
;-----------------------------------------------------------------------------
;
; Print the value of one or more expressions or string litterals as hexadecimal.
;
; PRINT 1
; PRINT A
; PRINT "Hello"
; PRINT 2;
; PRINT B;
; PRINT "World";
; PRINT A;3;"foo";B;4;"bar"
;
;-----------------------------------------------------------------------------

@loop:
    CMPEQ tokenPeek CONST_0 @doneCrlf       ; If the token is an EOL, we're done
    CMPEQ tokenPeek ASCII_COLON @doneCrlf   ; If the token is an colon, we're done

    CALL ParseExpression
    CMPEQ tokenType TT_STRING @string               ; If the token is a string, print it
    PUSH expression                         ; Else print the integer (constant/variable)
    CALL PrintHex
    JMP @continue

@string:
    PUSH tokenStr
    CALL PrintString

@continue:
    CMPNE tokenPeek ASCII_SEMICOLON @doneCrlf
    CALL GetParsedToken                     ; Gobble up the semicolon
    JMP @loop                               ; ...and do more printing if required


@doneCrlf
    CMPNE tokenType TT_MISC @crlf
    CMPEQ tokenValue ASCII_SEMICOLON Statement
@crlf:
    PRINTCRLF                               ; Else print a CRLF and continue with the next statement
    JMP Statement

    .endp 
