        .proc LIST
;-----------------------------------------------------------------------------
PromptLIST:
;-----------------------------------------------------------------------------
        MOV program_ @p                     ; Assume list to start from the beginning
        MOV CONST_MAXINT @lastLineNo        ; Assume list to end of the program

        CALL GetParsedToken                 ; Get the line number to start listing from
        JMP0 tokenValue @loop1              ; If not given, list all lines
        MOV tokenValue @lastLineNo          ; If we have a start lineNo then assume it's also the last
        PUSH tokenValue                     ; Find the line number
        CALL FindLine
        MOV pFound @p                       ; And start from there

        JMP0 tokenPeek @loop1               ; If the last line number is not given, list all lines

        CALL GetParsedToken                 ;  Get the last line number to list
        JMPL0 tokenValue @loop1             ; If not given, list all lines
        MOV tokenValue @lastLineNo


@loop1: 
        INDEXEDRD @p @lineNo                ; Get Linenumber of current line as a binary value
        INC @p
        JMP0 @lineNo @done                  ; Reached the end of the code?
        CMPGE @lineNo @lastLineNo @done     ; Is this line number greater than the last line number?

        PUSH @lineNo                        ; Print the line number and a space
        CALL PrintInteger
        OUT ASCII_SPACE

        INC @p                              ; Skip the offset to the next line

@loop2:
        INDEXEDRD @p @ch                    ; Get Linenumber of current line as a binary value
        INC @p
        JMP0 @ch @eol                       ; Reached the end of the line?
        OUT @ch                             ; Print the character
        JMP @loop2      

@eol:
        PRINTCRLF                           ; Print a CRLF and go print the next line
        JMP @loop1

@done:
        JMP Restart

@p:             .data 0                     ; Pointer to current location in the program
@lineNo:        .data 0                     ; Line number;
@lastLineNo:    .data 0                     ; Last line number to list
@ch:            .data 0                     ; Tempporary storage for the character

        .endp

