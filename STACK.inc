;-----------------------------------------------------------------------------
; STACK.inc
;-----------------------------------------------------------------------------

;-----------------------------------------------------------------------------
    .proc FindVar

@lookFor:      .data 0
@pLookFor:     .data 0
@pVar:     .data 0
@link:     .data 0
@chKey:    .data 0      ; Fetched character from the key
@chVar:    .data 0      ; Fetched character from the variable name
@t:        .data 0

FindVariable:
    DEBUGPRINT "[FINDVARIABLE]\r\n"
    MOV stackVars @pVar                         ; Point to the first variable
    MOV TT_VARINT tokenType                       ; Set type to variable tentatively
    JMP @doFind

FindKeyword:
    DEBUGPRINT "[FINDKEYWORD]\r\n"
    MOV stackKW @pVar                           ; Point to the first variable
    MOV TT_KEYWORD tokenType                       ; Set type to keyword tentatively

@doFind:
    POP @t                                      ; Get the key to search for from the stack
    POP @lookFor                                
    PUSH @t
;    DEBUGPRINT "LOOKING FOR '"  ;debug
;    PUSH @lookFor              ;debug
;    CALL PrintString           ;debug
;    DEBUGPRINT "'\r\n"          ;debug

@loop1:
;    DEBUGPRINT "@pVar="         ;xdebug
;    PUSH @pVar                 ;xdebug
;    CALL PrintHex              ;xdebug
;    OUT ASCII_SPACE            ;xdebug
    MOV @lookFor @pLookFor                      ; Point to the key
    INDEXEDRD @pVar @link                       ; Get the link to next variable address
;   DEBUGPRINT "@link="         ;xdebug
;    PUSH @link                 ;xdebug
;    CALL PrintHex              ;xdebug
;    OUT ASCII_SPACE            ;xdebug
;    PRINTCRLF                  ;xdebug

    JMP0 @link @notFound                        ; If the link is zero, we have reached the end of the list
    MOV @link @pVar                             ; Point to the start of name field
@loop2:
    INDEXEDRD @pVar @chVar                      ; Get the first character of the name
    INDEXEDRD @pLookFor @chKey                      ; Get the first character of the name
    CMPEQ @chKey @chVar @same                   ; Compare the characters

    ;Reset pLookFor and pVar if the characters are not equal
    ;pLookFor is reset in the beginning of @loop1, so we only need to reset pVar 

    MOV @link @pVar
    DEC @pVar
    JMP @loop1  

@same:
    INC @pVar
    INC @pLookFor
    CMPEQ @chKey 0 @found                       ; If the character(s) are zero, we have found the variable
    JMP @loop2

@found:
    MOV @pVar tokenAddr
    INDEXEDRD @pVar tokenValue
    DEBUGPRINT "[FINDxxxx FOUND]\r\n"
    RET

@notFound:
    MOV CONST_0 tokenAddr
    MOV CONST_0 tokenValue
    MOV TT_NOTFOUND tokenType                   
    DEBUGPRINT "[FINDxxxx NOT FOUND]\r\n"
    RET

    .endp


;-----------------------------------------------------------------------------
    
    .proc InsertVar

@dataLen:   .data 1
@nameLen:   .data 2
@link:      .data 0
@px:         .data 0
@ch:        .data 0
@pTs:       .data 0         ; Pointer to the token string
@t:        .data 0


InsertVar:
        POP @t
        POP @dataLen
        PUSH @t

        CLR @nameLen
        MOV tokenStr @pTs
@lenLoop:
        INDEXEDRD @pTs @ch
        CMPEQ @ch CONST_0 @lenDone
        INC @pTs
        INC @nameLen
        JMP @lenLoop
@lenDone:

;        DEBUGPRINT "[INSERTVAR] '"     ;debug
;       PUSH tokenStr                   ;debug
;       CALL PrintString                ;debug
;        DEBUGPRINT "' DataLen="        ;debug
;       PUSH @dataLen                   ;debug
;       CALL PrintInteger               ;debug
;        DEBUGPRINT "' NameLen="        ;debug
;       PUSH @nameLen                   ;debug
;       CALL PrintInteger               ;debug
;       PRINTCRLF                       ;debug

        ; Begin by locating the end of the list
        MOV stackVars @px                             ; Point to the first variable

@loop1:
        INDEXEDRD @px @link                          ; Get the link to next variable address
        INDEXEDRD @link @ch                         ; Get the link to next variable address

        CMPEQ CONST_0 @ch @atEnd                    ; If the link is zero, we have reached the end of the list
        MOV @link @px                                ; Point to the next variable
        DEC @px                                      ; @link is pointing to the start of the current variable,  

        JMP @loop1                                  ; so we need to decrement it to point to the end of the next variable

@atEnd:
        ;backup enough space for the new variable
        DEC @px                                      ; Room for the link address
        SUB @dataLen @px                             ; Make room for the data
        DEC @px                                      ; The name string terminator
        SUB @nameLen @px                             ; Make room for the name
        MOV @px @link                                ; Hold the new link address
        DEC @px                                      ; The list terminating zero

        INDEXEDWR CONST_0 @px                        ; Write the list terminating zero
        INC @px

        MOV tokenStr @pTs                           ; Copy the name string including the terminator
@copyNameLoop:
        INDEXEDRD @pTs @ch
        INDEXEDWR @ch @px                        ; Write the name string terminator
        INC @px
        INC @pTs
        JMPN0 @ch @copyNameLoop


@initDataLoop:
        INC @px
        INDEXEDWR CONST_0 @px                        ; Write the data
        DEC @dataLen
        JMPN0 @dataLen @initDataLoop

        INC @px
        INDEXEDWR @link @px                          ; Write the link

        RET

    .endp


SP:     .data 0                                  ; Stackpointer
        .org $+1024                              ; Reserve space for the stack    
stack_:
stack:  .data $-1                                ; Address to the top (beginning) of the stack
        .org $+1024                              ; Reserve space for the stack    


            .data 0
stackVars:  .data $-1


kwREM:            .equ CONST_1
kwLET:            .equ CONST_2
kwIF:             .equ CONST_3
kwTHEN:           .equ CONST_4
kwGOTO:           .equ CONST_5
kwPRINT:          .equ CONST_6
kwGOSUB:          .equ CONST_7
kwRETURN:         .equ CONST_8
kwFOR:            .equ CONST_9
kwTO:             .equ CONST_10
kwSTEP:           .equ CONST_11
kwNEXT:           .equ CONST_12
kwEND:            .equ CONST_13
kwLIST:           .equ CONST_14
kwNEW:            .equ CONST_15
kwRUN:            .equ CONST_16
kwINPUT:          .equ CONST_17
kwPRHEX:          .equ CONST_18
kwRND:            .equ CONST_19
kwABS:            .equ CONST_20
kwDIM:            .equ CONST_21

kwnREM:            .equ 1
kwnLET:            .equ 2
kwnIF:             .equ 3
kwnTHEN:           .equ 4
kwnGOTO:           .equ 5
kwnPRINT:          .equ 6
kwnGOSUB:          .equ 7
kwnRETURN:         .equ 8
kwnFOR:            .equ 9
kwnTO:             .equ 10
kwnSTEP:           .equ 11
kwnNEXT:           .equ 12
kwnEND:            .equ 13
kwnLIST:           .equ 14
kwnNEW:            .equ 15
kwnRUN:            .equ 16
kwnINPUT:          .equ 17
kwnPRHEX:          .equ 18
kwnRND:            .equ 19
kwnABS:            .equ 20
kwnDIM:            .equ 21

                .data 0
linkREM:        .data "REM"   ,0, kwnREM,    linkREM
linkLET:        .data "LET"   ,0, kwnLET,    linkLET
linkIF:         .data "IF"    ,0, kwnIF,     linkIF
linkTHEN:       .data "THEN"  ,0, kwnTHEN,   linkTHEN
linkGOTO:       .data "GOTO"  ,0, kwnGOTO,   linkGOTO
linkPRINT:      .data "PRINT" ,0, kwnPRINT,  linkPRINT
linkGOSUB:      .data "GOSUB" ,0, kwnGOSUB,  linkGOSUB
linkRETURN:     .data "RETURN",0, kwnRETURN, linkRETURN
linkFOR:        .data "FOR"   ,0, kwnFOR,    linkFOR
linkTO:         .data "TO"    ,0, kwnTO,     linkTO
linkSTEP:       .data "STEP"  ,0, kwnSTEP,   linkSTEP
linkNEXT:       .data "NEXT"  ,0, kwnNEXT,   linkNEXT
linkEND:        .data "END"   ,0, kwnEND,    linkEND
linkLIST:       .data "LIST"  ,0, kwnLIST,   linkLIST
linkNEW:        .data "NEW"   ,0, kwnNEW,    linkNEW
linkRUN:        .data "RUN"   ,0, kwnRUN,    linkRUN
linkINPUT:      .data "INPUT" ,0, kwnINPUT,  linkINPUT
linkPRHEX:      .data "PRHEX" ,0, kwnPRHEX,  linkPRHEX
linkRND:        .data "RND"   ,0, kwnRND,    linkRND
linkABS:        .data "ABS"   ,0, kwnABS,    linkABS
linkDIM:        .data "DIM"   ,0, kwnDIM,    linkDIM

stackKW:        .data $-1

