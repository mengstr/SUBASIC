```
 __        __        ___  __     ___                __        __     __  
/__` |  | |__) |    |__  /  \     |  | |\ | \ /    |__)  /\  /__` | /  ` 
.__/ \__/ |__) |___ |___ \__\\    |  | | \|  |     |__) /--\ .__/ | \__, 
[[ version 0.03 - (c) 2024 Mats Engstrom - github.com/mengstr/SUBASIC ]]
```

This is an Tiny BASIC interpreter written in SUBLEQ assembly.

The source requires my own SUBLEQ macro assembler ```SLEQASM``` to assemble into
code. 

I'm targeting this for the hardware implementation of a SUBLEQ machine I'm currently building so
it requres a 24-bit SUBLEQ CPU architecture.  In the SLEQASM repo I have a emulator for it so the code
can be run and debugged.

## Commands at the prompt

### NEW

The command NEW erases all of the current typed-in BASIC code

### LIST

LIST shows the current BASIC code

### RUN

RUN starts execution of the program at the specified line number. If no line number is given it will start at the first line. If the specified line don't exist then execution will start at the next higher number.

## Keywords
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


### GOSUB

### RETURN

### IF

### FOR

### NEXT



