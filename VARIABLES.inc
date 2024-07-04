
;-----------------------------------------------------------------------------
; VARIABLES A..Z
; All single letter variables are stored in the same memory location and are
; pre-allocated so they don't need to be created with a DIM statement.
;-----------------------------------------------------------------------------
vars1:  .data $+1
        .data 0,0,0,0,0         ; Variables A..E
        .data 0,0,0,0,0         ;           F..J
        .data 0,0,0,0,0         ;           K..O
        .data 0,0,0,0,0         ;           P..T
        .data 0,0,0,0,0         ;           U..Y
        .data 0                 ;           Z

;-----------------------------------------------------------------------------
; VARIABLES ALLOCATED BY DIM
;-----------------------------------------------------------------------------
vars2:  .data $+1
        .data "ABCDEF",0,1234567
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data "      ",0,0
        .data 0,0,0,0,0,0,0,0
        