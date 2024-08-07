# Tiny BASIC Interpreter in SUBLEQ Assembly

```
 __        __        ___  __     ___                __        __     __  
/__` |  | |__) |    |__  /  \     |  | |\ | \ /    |__)  /\  /__` | /  ` 
.__/ \__/ |__) |___ |___ \__\\    |  | | \|  |     |__) /--\ .__/ | \__, 
[[ version 0.06 - (c) 2024 Mats Engstrom - github.com/mengstr/SUBASIC ]]
```

This project is a Tiny BASIC interpreter written in SUBLEQ assembly. It is currently functional and capable of running fairly complex programs, although it is still a work in progress.

## Requirements

To assemble the source code, you need to use my custom SUBLEQ macro assembler, SLEQASM. The target is a hardware implementation of a SUBLEQ machine with a 24-bit SUBLEQ CPU architecture. The SLEQASM repository includes an emulator for running and debugging the code.

## Features

*Multi-statement Lines:* Multiple statements can be placed on a single line using a colon `:`.

```10 PRINT "Hello" : PRINT "World"```

*Interrupt Handling:* When a program is running, it can be stopped by typing CTRL-C.

*Variable Support:* Variables are all 24-bit signed integers with a range from -8,388,608 to 8,388,607. Single letter variables can be used directly, but longer names needs to be declared with a DIM statement. Variables are case insensitive.

## Commands

### NEW

Erases all the current typed-in BASIC code

### LIST [start lineNo] [end lineNo]

Displays the current BASIC code. If no lines numbers are given then show all lines. If just the starting line number is given then show just that line. If both start and stop lines are given show the lines between those.

### RUN [lineNo]

Starts execution of the program at the specified line number. If no line number is given, it will start at the first line. If the specified line does not exist, execution will start at the next higher number.

## Functions

### RND(max)
Returns a random number between 0 and max-1. Currently the max value can't be a full expression, only single numbers or variables are allowed.
#### Example
```
10 LET A=100+RND(10) : REM Number between 100 and 109
```

## BASIC Keywords

### END
Halts the execution of the BASIC code and returns to the BASIC command prompt
#### Example
```
10 END
```

### REM
Adds a comment. Comments are always the rest of the line
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

### DIM
The DIM statement creates variables with names that can be longer than a single letter. Variable names can be up to six characters long. There is a limit of 40 DIMmed variables in a program.
#### Example
``` 
10 DIM Foo5
20 DIM BAR,bletch
30 LET foo5=11 : LET bar=88
40 LET BLETCH=foo5+bar
50 PRINT "Bletch=";Bletch
```

### PRINT
Prints a variable, number, expression, or string. If followed by a semicolon `;`, the automatic trailing newline (CRLF) is suppressed.
#### Example
``` 
10 PRINT A
20 PRINT 512+512
30 PRINT "Hello world!"
40 PRINT "A is ";A
```

### PRHEX
Prints a variable as a six-digit hexadecimal number with leading zeros.
#### Example
```
10 PRHEX 513
```

### INPUT
Waits for the user to type a number and assigns it to the specified variable.
#### Example
```
10 INPUT A
20 PRINT "Enter your age: ";
30 INPUT A
```

### GOTO
Continues running the program at the specified line number. If the line number does not exist, the next higher number is used. The line number can be an expression (computed GOTO).
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
Functions like GOTO but with the possibility to return to the instruction right after the GOSUB. The line number can be computed.
#### Example
```
10 GOSUB 100
20 GOSUB 100 : GOSUB 100
30 END
100 PRINT "HELLO?"
110 RETURN
```

### RETURN
Returns execution to the point directly after the GOSUB statement.

### IF
Evaluates a condition and executes the statement after THEN if the condition is met. Conditions can be &gt;, <, =, or <>.

#### Example
```
10 LET A=17
20 IF A > 99 THEN PRINT "A is larger than 99": END
30 IF A=17 THEN PRINT "A is 17"
40 PRINT "Hello"
```

### FOR
Initializes a variable and runs code until a NEXT statement is found. The variable is incremented by 1 each loop iteration until it exceeds the specified value. Multiple FOR statements can be nested.
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

## Oddities
Currently the CTRL-C used to stop the running program is handled OOB of the normal flow of incoming characters. It is polled by reading from location -2. Some day it will probably be handled in the normal (-1) input reading of characters, but that would require a key-buffer to be held internally in the interpreter.

## Change log
`v0.06` Implements ABS() function, DIM for long variable names

`v0.05` Implements rudimentary RND() function

`v0.04` LIST command can list parts of the source
