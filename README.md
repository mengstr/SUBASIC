# SUBLEQ TINY BASIC

```
 __        __        ___  __     ___                __        __     __  
/__` |  | |__) |    |__  /  \     |  | |\ | \ /    |__)  /\  /__` | /  ` 
.__/ \__/ |__) |___ |___ \__\\    |  | | \|  |     |__) /--\ .__/ | \__, 
[[ version 0.03 - (c) 2024 Mats Engstrom - github.com/mengstr/SUBASIC ]]
```

This is an Tiny BASIC interpreter written in SUBLEQ assembly. It's working and can run fairly complex programs but is still a work in progress.

The source requires my own SUBLEQ macro assembler ```SLEQASM``` to assemble into
code. 

I'm targeting this for the hardware implementation of a SUBLEQ machine I'm currently building so
it requres a 24-bit SUBLEQ CPU architecture.  In the SLEQASM repo I have a emulator for it so the code can be run and debugged.

Multiple statemengs can be put on a single line using a colon ```:``` like
``` 10 PRINT "Hello" : PRINT "World"```

When a program is running it can be stopped by typing a CTRL-C.

Variables are all 24 bit signed integers with a range from -8,388,608 to 8,388,607.

## Commands at the prompt

### NEW

The command NEW erases all of the current typed-in BASIC code

### LIST

LIST shows the current BASIC code

### RUN

RUN starts execution of the program at the specified line number. If no line number is given it will start at the first line. If the specified line don't exist then execution will start at the next higher number.

## BASIC Keywords
### END
Halts the execution of the BASIC code and returns to the BASIC command prompt
#### Example
```
10 END
```

### REM
The rest of the line is treated as a comment. The comment can contain both double quotes and colons.
#### Example
``` 
10 REM My awesome basic program
```
 
### LET
Assigns an expression to a variable. See Expressions for more information.
#### Example
``` 
10 REM Convert C(elsius) to F(arenheit)
20 LET C = 100
30 LET F = C * 9 / 5 + 32
40 PRINT F
```

### PRINT
Prints a variable, number, expression or a string. If the PRINT statement is followed by a semicolon ```;``` then the
automatic trailing newline (CRLF) is supressed.
#### Example
``` 
10 PRINT A
20 PRINT 512+512
30 PRINT "Hello world!"
40 PRINT "A is ";A
```

### PRHEX
PRHEX is like PRINT but it prints it as a six-digit hexadecimal number with leading zeros.
#### Example
```
10 PRHEX 513
```

### INPUT
INPUT wait for the user to type a number and assigns it to the specified variable.
#### Example
```
10 INPUT A
20 PRINT "Enter your age: ";
30 INPUT A
```

### GOTO
Continue running the program at the specified line number. If the line number dosen't exist then the line with the next higher number is used. The line number can be an expression, I.E a "Computed GOTO".
#### Example
```
10 LET A=2
20 GOTO A*10+100
100 PRINT "Line onehundred"
110 GOTO 200
120 PRINT "Line onehundredtwenty"
130 GOTO 200
200 END
```

### GOSUB
This is like a GOTO but with the possibility to RETURN to the instruction just after the GOSUB. More or less like a function in other languages. Just as the GOTO the line number can be "computed".
#### Example
```
10 GOSUB 100
20 GOSUB 100 : GOSUB 100
30 END
100 PRINT "HELLO?"
110 RETURN
```

### RETURN
This is the companion command to the GOSUB. It simply returns execution at the point directly after the GOSUB statement.
See the GOSUB for an example.

### IF
IF checks two expressions to see if the specified condition is met. If so it will execute whatever comes after the `THEN` keyword on the same line. If the condition is not met then it will continue on the next line.

The condition can be one of the following:
- &gt; (is larger than)
- &lt; (is less than)
- = (is equal to)
- &lt;&gt; (is not equal to)

#### Example
```
10 LET A=17
20 IF A > 99 THEN PRINT "A is larger than 99": END
30 IF A=17 THEN PRINT "A is 17"
40 PRINT "Hello"
```

### FOR
A FOR loop takes a variable and initialises it to the specified value and then continues executing code until a `NEXT` statement is found. The variable will then be incremented by 1 and execcution will continue at the next statement after the FOR. This will happen until the variable is larger than the second specified value. Multiple FOR statements can be nested.
#### Example
```
10 PRINT "Multiplication table"
20 FOR I=1 TO 9
30 FOR J=1 TO 9
40 PRINT I*J;" ";
50 NEXT : REM Increments and loops the J 
60 PRINT
70 NEXT : REM Increments and loops the I 
```

### NEXT
The NEXT statement is the companion to the FOR. See the FOR command for (pun intended) info and an example.

