
        .proc prng


; 
;         ; https://wikiti.brandonw.net/index.php?title=Z80_Routines:Math:Random
;         ; https://floooh.github.io/visualz80remix/
;         ;
;         ; Combined LFSR/LCG, 16-bit seeds
;         ;
;         ; This is a very fast, quality pseudo-random number generator. It combines a 
;         ; 16-bit Linear Feedback Shift Register and a 16-bit LCG.
;         ;
; prng16:
;         ;Inputs:
;         ;   (seed1) contains a 16-bit seed value
;         ;   (seed2) contains a NON-ZERO 16-bit seed value
;         ;Outputs:
;         ;   HL is the result
;         ;   BC is the result of the LCG, so not that great of quality
;         ;   DE is preserved
;         ;Destroys:
;         ;   AF
;         ;cycle: 4,294,901,760 (almost 4.3 billion)
;         ;160cc
;         ;26 bytes
;
;     ld hl,(seed1)
;     ld b,h
;     ld c,l
;     add hl,hl
;     add hl,hl
;     inc l
;     add hl,bc
;     ld (seed1),hl
;
;     ld hl,(seed2)
;     add hl,hl
;     sbc a,a
;     and %00101101
;     xor l
;     ld l,a
;     ld (seed2),hl
;
;     add hl,bc
;     ret
; 
; On their own, LCGs and LFSRs don't produce great results and are generally very cyclical, 
; but they are very fast to compute. The 16-bit LCG in the above example will bounce around 
; and reach each number from 0 to 65535, but the lower bits are far more predictable than 
; the upper bits. The LFSR mixes up the predictability of a given bit's state, but it hits 
; every number except 0, meaning there is a slightly higher chance of any given bit in the 
; result being a 1 instead of a 0. It turns out that by adding together the outputs of 
; these two generators, we can lose the predictability of a bit's state, while ensuring it 
; has a 50% chance of being 0 or 1. As well, since the periods, 65536 and 65535 are coprime, 
; then the overall period of the generator is 65535*65536, which is over 4 billion.
; 
; Example values from Z80   
;
; HL    seed1  seed2
;-------------------
; bf24   5b05   acf0 
; b4d2   c71a   59cd
; 7ab4   e383   b39a
; 4a9c   7190   6719
; 3fc2   37d1   ce32
; d41a   1716   9c49
; 4fd5   736f   38bf
; e4ed   412c   717e
; 2428   45dd   e2fc
; 0bb2   5d52   c5d5
; E8D9   d29b   8b87

;
; // BASIC version
;
; uint16_t seed1 = 0x1234; // Example seed value
; uint16_t seed2 = 0x5678; // Example non-zero seed value
;
; uint16_t prng16(uint16_t *seed1, uint16_t *seed2) {
;    uint32_t hl,bc,h,l,a;
;
;    hl = *seed1; bc = hl;
;
;    hl=hl*4;
;    hl=hl+1;
;    hl=hl+bc; 
;    if (hl>65535) {
;        hl=hl-65536;
;    }
;    *seed1=hl;
;
;    hl=*seed2;                
;    hl=hl*2;                  
;    if (hl>65535) {
;        hl=hl-65536;
;        hl=hl^0x2d;
;    }
;    *seed2=hl;
;    hl=hl+bc;                 
;    if (hl>65535) {
;        hl=hl-65536;
;    }
;    return hl;
;} 
;


@t:             .data 0                 ; Temporary hold variable

Prng:
        POP @t                          ; Pop off the return address and parameters
        PUSH @t                         ; Push the return address back onto the stack
        
        MOV seed1 @hl           ;  uint16_t hl = *seed1;
        MOV seed1 @bc           ;  uint16_t bc = *seed1;

                                ;  // First part: modifying seed1
        ADD @hl @hl             ;  hl += hl; // add hl, hl (equivalent to hl * 2)
        ADD @hl @hl             ;  hl += hl; // add hl, hl (equivalent to hl * 4)
        INC @hl                 ;  hl += 1;  // inc l
        ADD @bc @hl             ;  hl += bc; // add hl, bc
@loop1: CMPLE @hl CONST_65536 @skip1
        SUB CONST_65536 @hl
        JMP @loop1
@skip1: MOV @hl seed1           ;  *seed1 = hl;

                                ;  // Second part: modifying seed2
        MOV seed2 @hl           ; 
        ADD @hl @hl             ;  hl += hl; // add hl, hl (equivalent to hl * 2)
        CMPLE @hl CONST_65536 @skip2
        SUB CONST_65536 @hl
        PUSH @hl
        PUSH CONST_x2D
        CALL XOR
        MOV bitopResult @hl
@skip2: MOV @hl seed2
        ADD @bc @hl                     ;     hl += bc; // add hl, bc
        CMPLE @hl CONST_65536 @skip3
        SUB CONST_65536 @hl

@skip3: MOV @hl prngVal                  ;     return hl;
        RET

@hl:            .data 0
@bc:            .data 0

        .endp


r1:            .data 0                 
r2:            .data 0                 

        .proc rnd

@max:           .data 0                 ; Reguested maxmimum value
@t:             .data 0                 ; Temporary hold variable
@cnt:           .data 0                 ; Counter for number of bits to extract from seed/random
@r:             .data 0                 ; Random number

Random:
         POP @t                          ; Pop off the return address and parameters
         POP r1
         PUSH @t                         ; Push the return address back onto the stack

        CALL Prng
        MOV prngVal r2
        DIV r1 r2
        MOV divRemainder rndVal
        RET

        .endp
