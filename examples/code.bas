NEW
10 LET A=75:LET B=3
20 PRINT "A=";A;" B=";B
30 LET C=A+B
40 LET D=A-B 
50 LET E=A*B 
60 LET F=A/B
70 PRINT "A+B=";C
80 PRINT "A-B=";D
90 PRINT "A*B=";E
100 PRINT "A/B=";F
LIST
RUN


NEW
10 REM This is a comment
20 REM Hello
100 END
LIST
RUN


NEW
10 PRINT 1
20 PRINT A
30 PRINT "Hello"
40 PRINT 2;
50 PRINT B;
60 PRINT "World";
65 PRINT
70 PRINT A;3;"foo";B;4;"bar"
80 END
LIST
RUN


NEW 
10 PRINT 9
20 PRINT 8;
30 PRINT 7
RUN



NEW
10 PRINT 10
11 END
20 PRINT 20
21 END
30 PRINT 30
31 END  



NEW 
10 END

NEW 
10 GOTO 100
100 GOTO 20
20 GOTO 200
199 PRINT "HELLO!"
200 END


NEW
10 PRINT 999:PRINT 888
20 END


NEW
10 PRINT "HELLO";A;"ME"
20 PRINT "A";
30 PRINT "B"
40 PRINT:PRINT:PRINT
50 PRINT 1;2;3;:PRINT 4;5;6
60 END


NEW
10 GOSUB 200:GOSUB 100
30 GOTO 50
40 END
50 PRINT "!"
60 GOTO 40
100 PRINT "World ";
110 RETURN
200 PRINT "Hello ";
210 RETURN

NEW
10 LET A=100
20 GOSUB A
30 LET A=A+100
40 GOSUB A
50 GOSUB A+100
60 END
100 PRINT "AT 100":RETURN
110 PRINT "Error"
200 PRINT "AT 200":RETURN
210 PRINT "Error"
300 PRINT "AT 300":RETURN
310 PRINT "Error"
LIST


NEW
10 LET A=123 : LET B=456 : LET C = 0
20 IF A > B THEN LET C = 789
30 PRINT "A=";A;" B=";B;" C=";C
40 END
LIST


NEW
10 LET A=0
20 IF A<>15 THEN GOTO 25
21 GOTO 40
25 PRINT A;" ";
30 IF A<10 THEN PRINT "LESS"
31 IF A>10 THEN PRINT "GREATER"
32 IF A=10 THEN PRINT "EQUAL"
40 LET A=A+1
50 IF A=20 THEN END
60 GOTO 20
LIST


NEW
10 LET A=0
20 IF A>10 THEN END
30 PRINT A;
40 LET A=A+1
50 GOTO 20
LIST


NEW
10 FOR A=0 TO 9
20 GOSUB 100
30 NEXT
31 PRINT
40 FOR A=101 TO 105:PRINT A:NEXT:PRINT "DONE 40"
99 END
100 PRINT A;" ";
110 RETURN
LIST



NEW
10 REM Day of Week Calculation
20 PRINT "Enter year: "; : INPUT Y 
30 PRINT "Enter month: "; : INPUT M
40 PRINT "Enter day: "; : INPUT D
45 LET Y=1970: LET M=11: LET D=20

50 REM Adjust months and years for Jan & Feb
60 IF M < 3 THEN LET M=M+12 : LET Y=Y-1

100 REM Calculate DOW using Zeller's Congruence

200 REM Original: K = Y MOD 100
210 LET A = Y / 100
220 LET B = 100 * A
230 LET K = Y - B

300 LET J = Y / 100

400 REM Original: F = D + 2*M + (3*(M+1))/5 + K + K/4 + J/4 + 5*J
410 LET C = M + 1
420 LET D = 3 * C
430 LET E = D / 5
440 LET F = 2 * M
450 LET G = K / 4
460 LET H = J / 4
470 LET I = 5 * J
480 LET L = D + E
490 LET M = L + F
500 LET N = M + K
510 LET O = N + G
520 LET P = O + H
530 LET Q = P + I
540 LET F = Q

600 REM Original: F = F MOD 7
610 LET R = F / 7
620 LET S = 7 * R
630 LET F = F - S

700 PRINT "Day of Week is "; : GOTO 1000+F

1000 PRINT "Sunday" : END
1001 PRINT "Monday" : END
1002 PRINT "Tuesday" : END
1003 PRINT "Wednesday" : END
1004 PRINT "Thursday" : END
1005 PRINT "Friday" : END
1006 PRINT "Saturday" : END





10 REM Input year Y, month M, day D
20 LET Y=1965 : REM INPUT "YEAR:", Y
30 LET M=3    : REM INPUT "MONTH:", M
40 LET D=18   : REM INPUT "DAY:", D

50 REM Adjust month and year for January and February
60 IF M < 3 THEN LET M = M + 12
70 IF M > 12 THEN LET Y = Y - 1

80 REM Calculate K and J
85 LET T=Y/100
86 LET T=T*100
90 LET K = Y - T
100 LET J = Y/100

110 REM Calculate parts of Zeller's formula
120 LET P1 = D
130 LET A = M + 1
140 LET P2 = 13 * A / 5
150 LET P3 = K
160 LET P4 = K / 4
170 LET P5 = J / 4
180 LET P6 = 2 * J

190 REM Sum up all parts
200 LET S = P1 + P2 + P3 + P4 + P5 - P6

210 REM Simulate modulus 7 using subtraction
220 LET H = S
230 LET T = H / 7
231 LET T=T*7
240 LET H = H - T

260 LET H = H + 5
270 LET T = H / 7
271 LET T=T*7
280 LET H = H - T


300 PRINT "Day of Week is "; : GOTO 1000+F

1000 PRINT "Saturday" : END
1001 PRINT "Sunday" : END
1002 PRINT "Monday" : END
1003 PRINT "Tuesday" : END
1004 PRINT "Wednesday" : END
1005 PRINT "Thursday" : END
1006 PRINT "Friday" : END




NEW
10 PRINT "Enter year: "; : INPUT Y
20 PRINT "Enter month: "; : INPUT M
30 PRINT "Enter day: "; :INPUT D
40 GOSUB 200
50 PRINT:PRINT "Day of Week is "; 
60 GOTO 100+Z
70 END
100 PRINT "Sunday" : END
101 PRINT "Monday" : END
102 PRINT "Tuesday" : END
103 PRINT "Wednesday" : END
104 PRINT "Thursday" : END
105 PRINT "Friday" : END
106 PRINT "Saturday" : END
200 REM Zeller's Congruence
210 IF M < 3 THEN Y = Y - 1: M = M + 12
220 LET Z=Y
230 LET T=Y/4 : LET Z=Z+T
240 LET T=Y/100 : LET Z=Z-T
250 LET T=Y/400 : LET Z=Z+T
260 LET T=153*M+8 : LET T=T/5
270 LET Z=Z+D+T
280 LET T=Z/7 : LET T=T*7
290 LET Z=Z-T
300 RETURN




NEW
10 LET A=16807
20 LET C=1
30 LET R=12345
40 LET R=R*A+C
50 IF R<0 THEN LET R=0-R
60 PRINT R
70 GOTO 40


NEW
10 PRINT "17 + 5 = 22  We get ";17+5
20 PRINT "17 - 5 = 12  We get ";17-5  
30 PRINT "17 * 5 = 85  We get ";17*5     
40 PRINT "17 / 5 = 3.4 We get ";17/5
50 PRINT "17 & 5 = 1   We get ";17&5
60 PRINT "17 | 5 = 21  We get ";17|5
70 PRINT "17 ^ 5 = 20  We get ";17^5
80 PRINT "17 % 5 = 2   We get ";17%5


NEW
10 FOR A=1 TO 10
20 PRINT A;" ";
30 IF A=5 THEN LET A=8
40 NEXT


#
#NextRandom():
#    feedback = (state >> 23) ^ (state >> 22) ^ (state >> 21) ^ (state >> 16)
#    feedback = feedback & 1  # Extract the least significant bit
#    state = ((state << 1) | feedback) & 0xFFFFFF  # Shift left and insert feedback bit
#    if state > 2^23 - 1:
#        state = state - 2^24
#    return state
#
# 78C29C  F18538  E30A70  C614E0  8C29C0  185381  30A702  614E05  C29C0B  853816
#
#feedback: 0 f23,f22,f21,f16: 1,0,1,0
#feedback: 0 f23,f22,f21,f16: 0,1,1,0
#feedback: 0 f23,f22,f21,f16: 1,1,1,1
#feedback: 0 f23,f22,f21,f16: 1,1,1,1
#feedback: 0 f23,f22,f21,f16: 1,1,0,0
#feedback: 1 f23,f22,f21,f16: 1,0,0,0
#feedback: 0 f23,f22,f21,f16: 0,0,0,0
#feedback: 1 f23,f22,f21,f16: 0,0,1,0
#feedback: 1 f23,f22,f21,f16: 0,1,1,1
#feedback: 0 f23,f22,f21,f16: 1,1,0,0


NEW
1 REM Calculates a PRNG using a 24 bit LFSR
2 REM having taps at bits 24,23,22,17. 
3 REM
4 REM R=Random value A-D=Tap bits, X-Z=XOR bits
5 REM T=Temp value for simulated right shifts
6 REM
7 LET R=1
8 FOR I=1 TO 30
10 LET A=0 : LET B=0 : LET C=0 : LET D=0
20 LET T=R
30 IF T<0 THEN LET A=1
40 LET T=T+T
50 IF T<0 THEN LET B=1
60 LET T=T+T
70 IF T<0 THEN LET C=1
80 LET T=T+T : LET T=T+T : LET T=T+T : LET T=T+T : LET T=T+T
90 IF T<0 THEN LET D=1
95 REM PRINT A;" ";B;" ";C;" ";D
110 LET X=0 : LET Y=0 : LET Z=0
120 IF A<>B THEN LET X=1
130 IF C<>D THEN LET Y=1
140 IF X<>Y THEN LET Z=1
160 LET R=R+R+Z
170 PRHEX R
180 NEXT


