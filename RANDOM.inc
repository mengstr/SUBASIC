
        .proc prng
;
; 78C29C  F18538  E30A70  C614E0  8C29C0  185381  30A702  614E05  C29C0B  853816
;

addSeed: .data 0x123456
incSeed: .data 0xFFFFFF

Prng:
; 10 LET A=0 : LET B=0 : LET C=0 : LET D=0
        CLR @a
        CLR @b
        CLR @c
        CLR @d
; 20 LET T=R
        MOV seed @t
; 30 IF T<0 THEN LET A=1
        JMPGE0 @t @nota
        INC @a
@nota:
; 40 LET T=T+T
        ADD @t @t
; 50 IF T<0 THEN LET B=1
        JMPGE0 @t @notb
        INC @b
@notb:
; 60 LET T=T+T
        ADD @t @t
; 70 IF T<0 THEN LET C=1
        JMPGE0 @t @notc
        INC @c
@notc:
; 80 LET T=T+T : LET T=T+T : LET T=T+T : LET T=T+T : LET T=T+T
        ADD @t @t
        ADD @t @t
        ADD @t @t
        ADD @t @t
        ADD @t @t
; 90 IF T<0 THEN LET D=1
        JMPGE0 @t @notd
        INC @d
@notd:
; 110 LET X=0 : LET Y=0 : LET Z=0
        CLR @x
        CLR @y
        CLR @z
; 120 IF A<>B THEN LET X=1
        CMPEQ @a @b @notx
        INC @x
@notx:
; 130 IF C<>D THEN LET Y=1
        CMPEQ @c @d @noty
        INC @y
@noty:
; 140 IF X<>Y THEN LET Z=1
        CMPEQ @x @y @notz
        INC @z
@notz:
; 160 LET R=R+R+Z
        ADD seed seed
        ADD @z seed
        RET
        
@a:     .data 0
@b:     .data 0
@c:     .data 0
@d:     .data 0
@t:     .data 0
@x:     .data 0
@y:     .data 0
@z:     .data 0

        .endp


        .proc rnd

@max:           .data 0                 ; Reguested maxmimum value
@t:             .data 0                 ; Temporary hold variable
@cnt:           .data 0                 ; Counter for number of bits to extract from seed/random
@r:             .data 0                 ; Random number

Random:
        POP @t                          ; Pop off the return address and parameters
        POP @max
        PUSH @t                         ; Push the return address back onto the stack

@try:
        MOV CONST_4 @cnt

        CALL Prng
        ; PUSH seed
        ; CALL PrintHex
        ; OUT ASCII_SPACE
        ADD addSeed seed
        ADD incSeed addSeed

        MOV seed @r
        CLR rndVal
@loop:
        ADD rndVal rndVal
        JMPGE0 @r @not1
        INC rndVal
@not1:  
        ADD @r @r
        PLUS1 @cnt @done
        JMP @loop

@done:
        ; PUSH rndVal
        ; CALL PrintHex
        ; PRINTCRLF

        CMPLEQ @max rndVal @try
        RET

        .endp
