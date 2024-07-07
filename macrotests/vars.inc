p:           .data 0
v:           .data 0

p1:          .data 0
v1:          .data 0
p2:          .data 0
v2:          .data 0
p3:          .data 0
v3:          .data 0

pi:          .data 0
vi:          .data 0
po:          .data 0
vo:          .data 0

tMov:       .data 0
tIdx:       .data 0
tmpA:       .data 0             ;Used by macros
tmpB:       .data 0             ;Used by macros
tmpC:       .data 0             ;Used by macros

T:          .data 0
tokenType:  .data 0     
tokenValue: .data 0
tokenAddr:  .data 0

bitopResult:   .data 0
divRemainder:  .data 0          ; Remainder from DIV operation to be used for modulus operations

val_:       .data val
val:        .data 0


TT_VARIABLE:    .data 2
TT_NOTFOUND:    .data 0
TT_KEYWORD:     .data 1
