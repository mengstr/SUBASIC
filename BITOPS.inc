;-----------------------------------------------------------------------------
    .proc AND
;-----------------------------------------------------------------------------

@numA:          .data 0
@numB:          .data 0
@t:             .data 0                 ; Temporary hold variable
@cnt            .data 0                 ; Count 24 bits

AND:
        POP @t                          ; Pop off the return address and parameters
        POP @numB
        POP @numA
        PUSH @t                         ; Push the return address back onto the stack

        CLR bitopResult
        MOV CONST_24 @cnt
@loop:

@TestA:
        CLR @t
        @numA @t @Atestmore
        @t @t @A1bit
@Atestmore: 
        CONST_1 @t @A0bit         
@A1bit:
        JMP @TestB                         ; TODO: Check @numB
@A0bit:
        JMP @isFalse                         ; For AND - is a bit is 0, then the result must be 0

@TestB:
        CLR @t
        @numB @t @Btestmore
        @t @t @B1bit
@Btestmore: 
        CONST_1 @t @B0bit         
@B1bit:
        JMP @isTrue                         ; Both A and B bits are 1, so the result is 1
@B0bit:
        JMP @isFalse                        ; For AND - is a bit is 0, then the result must be 0

@isTrue:
        ADD bitopResult bitopResult                   ; Left shift result
        INC bitopResult                          ; And inset a 1
        JMP @continue

@isFalse:
        ADD bitopResult bitopResult                   ; Left shift result

@continue:
        ADD @numA @numA                     ; Left shift numA
        ADD @numB @numB                     ; Left shift numB

        DEC @cnt                            ; Loop until cnt = 0
        JMPN0 @cnt @loop                         

        RET

    .endp


;-----------------------------------------------------------------------------
    .proc OR
;-----------------------------------------------------------------------------

@numA:          .data 0
@numB:          .data 0
@t:             .data 0                 ; Temporary hold variable
@cnt            .data 0                 ; Count 24 bits

OR:
        POP @t                          ; Pop off the return address and parameters
        POP @numB
        POP @numA
        PUSH @t                         ; Push the return address back onto the stack

        CLR bitopResult
        MOV CONST_24 @cnt
@loop:

@TestA:
        CLR @t
        @numA @t @Atestmore
        @t @t @A1bit
@Atestmore: 
        CONST_1 @t @A0bit         
@A1bit:
        JMP @isTrue                         ; For OR - is a bit is 1, then the result must be 1
@A0bit:
        JMP @TestB                         ; Check @numB

@TestB:
        CLR @t
        @numB @t @Btestmore
        @t @t @B1bit
@Btestmore: 
        CONST_1 @t @B0bit         
@B1bit:
        JMP @isTrue                         ; B is 1, so the result is 1
@B0bit:
        JMP @isFalse                        ; For OR - both A and B are 0, so the result is 0

@isTrue:
        ADD bitopResult bitopResult                   ; Left shift result
        INC bitopResult                          ; And inset a 1
        JMP @continue

@isFalse:
        ADD bitopResult bitopResult                   ; Left shift result

@continue:
        ADD @numA @numA                     ; Left shift numA
        ADD @numB @numB                     ; Left shift numB

        DEC @cnt                            ; Loop until cnt = 0
        JMPN0 @cnt @loop                         

        RET

    .endp



;-----------------------------------------------------------------------------
    .proc XOR
;-----------------------------------------------------------------------------

@numA:          .data 0
@numB:          .data 0
@t:             .data 0                 ; Temporary hold variable
@cnt            .data 0                 ; Count 24 bits
@v              .data 0                 ; holds the result of the tests

XOR:
        POP @t                          ; Pop off the return address and parameters
        POP @numB
        POP @numA
        PUSH @t                         ; Push the return address back onto the stack

        CLR bitopResult
        MOV CONST_24 @cnt
@loop:
        CLR @v
@TestA:
        CLR @t
        @numA @t @Atestmore
        @t @t @A1bit
@Atestmore: 
        CONST_1 @t @A0bit         
@A1bit:
        INC @v
@A0bit:

@TestB:
        CLR @t
        @numB @t @Btestmore
        @t @t @B1bit
@Btestmore: 
        CONST_1 @t @B0bit         
@B1bit:
        INC @v
@B0bit:

        DEC @v
        JMPN0 @v @isFalse

@isTrue:
        ADD bitopResult bitopResult                   ; Left shift result
        INC bitopResult                          ; And inset a 1
        JMP @continue

@isFalse:
        ADD bitopResult bitopResult                   ; Left shift result

@continue:
        ADD @numA @numA                     ; Left shift numA
        ADD @numB @numB                     ; Left shift numB

        DEC @cnt                            ; Loop until cnt = 0
        JMPN0 @cnt @loop                         

        RET

    .endp

