;-----------------------------------------------------------------------------
; KEYBOARD.inc
;-----------------------------------------------------------------------------



    .proc InputString

@ch:            .data 0                 ; Character read from the keyboard
@cnt:           .data 0                 ; Character count
@p:             .data 0                 ; Pointer to the buffer


InputString:
        CLR @cnt                        
        INDEXEDWR CONST_0 buf           ; Clear the buffer

@loop:
        IN @ch                          ; Read a character from the keyboard
        JMPL0 @ch @loop                 ; Continue looping until a character is read

        CMPEQ @ch CONST_3 ControlC      ; Check for a Ctrl-C keypress
        CMPEQ @ch ASCII_CR @done        ; Exit the loop if the character is a carriage return
        CMPEQ @ch ASCII_DEL @delete     ; Remove character in buffer if delete or backspace is pressed
        CMPEQ @ch ASCII_BS @delete
        CMPLE @ch ASCII_SPACE @loop     ; Don't accept control-characters into the buffer

        MOV buf @p                      ; Calculate the position in the buffer
        ADD @cnt @p
        INDEXEDWR @ch @p                ; Store the character in the buffer
        INC @p                          ; Store a null terminator in the buffer
        INDEXEDWR CONST_0 @p
        INC @cnt                        ; Increment the character count
        OUT @ch
        JMP @loop                       ; Continue looping

@delete:
        CMPEQ @cnt CONST_0 @loop        ; Don't backspace past the start of the buffer
        DEC @cnt                        ; Decrement the character count
        OUT ASCII_BS                    ; Clear the character from the screen
        OUT ASCII_SPACE
        OUT ASCII_BS
        JMP @loop                       ; Continue looping

@done:
    RET

    .endp


;-----------------------------------------------------------------------------
; KEYBOARD BUFFER
;-----------------------------------------------------------------------------

buf:        .data $+1
            .data 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,0
            .data 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,0
            .data 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,0
            .data 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,0

