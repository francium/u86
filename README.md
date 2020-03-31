## u86
A x86-like bytecode


## u86asm
Assembler for u86 bytecode


## vu86
u86 virtual machine


## u86 Reference


### Memory Layout
This example assumes 64K RAM, 32K ROM, 1K stack
```
,------------------------,
| 00000 -   start of ROM |
| .....   .............. |
| 32767 -     end of rom |
|------------------------|
| 32768 - start of stack |
| ..... - .............. |
| 33791 -   end of stack |
|------------------------|
| 33792 -    end of heap |
| ..... - .............. |
| 65535 -  start of heap |
'------------------------'
```


### Machine word
```
  _________32 byte word_________
 /                              \
,--------------------------------,
|______--____----,_______________|
   |   |  |   |         |
   |   |  |   |         '- (16 bytes) immediate val
   |   |  |   '- (4 bytes) dest register
   |   |  '- (4 bytes) src register
   |   '- (2 bytes) reserved
   '- (6 bytes opcode)
```


### OP-Types
```
,-------------------,----------,---------,---------------,
| base instruction  | dest reg | src reg | immediate val |
|-------------------|----------|---------|---------------|
| xxxr              | reg      | reg     | --            |
| xxxfm             | reg      | --      | memory addr   |
| xxxtm             | --       | src reg | memory addr   |
| xxxi              | reg      | --      | value         |
'-------------------'----------'---------'---------------'
```


### Registers
```
,-------------------,------------------------------------,
| register          | Notes                              |
|-------------------|------------------------------------|
| brp               | base rom pointer                   |
| bsp               | base stack pointer                 |
| bhp               | Base heap pointer                  |
| clock             | system clock                       |
| sp                | stack pointer                      |
| pc                | program counter                    |
| mar               | memory address register            |
| mbr               | memory buffer register             |
| jf                | jump flag                          |
| itrpt             | interrupt flag                     |
| hlt               | halt flag                          |
| r0                | general purpose register           |
| r1                | general purpose register           |
| r2                | general purpose register           |
| r3                | general purpose register           |
'-------------------'------------------------------------'
```


### Opcode table
```
,--------------,---------,--------------------------------------,------------------------,----------------------------------------------,
| Instruction  | Opcode  | Machine word                         | Assembly Example       | Notes                                        |
|--------------|---------|--------------------------------------|------------------------|----------------------------------------------|
| 00  0x00     | call    | 000000 .. REG1 .... ................ | call    [r1]           | Transfer control to subroutine at [r1]       |
| 01  0x01     | ret     | 000001 .. .... .... ................ | ret                    | set pc to mem[sp]; sp must be set prior      |
| 02  0x02     | push    | 000010 .. REG1 .... ................ | push    r1             | stack.push(r1)                               |
| 03  0x03     | pop     | 000011 .. REG1 .... ................ | pop     r1             | r1 = stack.pop()                             |
| 04  0x04     | movr    | 000100 .. REG1 REG2 ................ | mov     r1   r2        | r1 = r2                                      |
| 05  0x05     | movfm   | 000101 .. REG1 REG2 ................ | mov     r1  [r2]       | r1 = *r2                                     |
| 06  0x06     | movtm   | 000110 .. REG1 REG2 ................ | mov    [r1]  r2        | *r1 = r2                                     |
| 07  0x07     | movi    | 000111 .. REG1 .... IMMEDIATE-VALUE- | mov     r1       1234  | r1 = 1234                                    |
| 08  0x08     | cmp     | 001000 .. REG1 REG2 ................ | cmp     r1   r2        | jf = r1 == r2 ? 0 : r1 > r2 : 1 : -1         |
| 09  0x09     | jmp     | 001001 .. REG1 .... ................ | jmp     r1             | unconditional jump to address stored in [r1] |
| 10  0x0a     | je      | 001010 .. REG1 .... ................ | je      r1   r2        |                                              |
| 12  0x0b     | jz      | 001011 .. REG1 .... ................ | jz      r1             |                                              |
| 13  0x0c     | jg      | 001100 .. REG1 .... ................ | jg      r1   r2        |                                              |
| ...          | ...     | ...... ..                            |                        |                                              |
| 32  0x20     | add     | 100000 .. REG1 REG2 ................ | add     r1 r2          | r1 = r1 + r2                                 |
| 33  0x21     | sub     | 100001 .. REG1 REG2 ................ | sub     r1 r2          | r1 = r1 - r2                                 |
| 34  0x22     | mul     | 100010 .. REG1 REG2 ................ | mul     r1 r2          | r1 = r1 * r2                                 |
| 35  0x23     | div     | 100011 .. REG1 REG2 ................ | div     r1 r2          | r1 = r1 / r2                                 |
| 36  0x24     | or      | 100100 .. REG1 REG2 ................ | or      r1 r2          | r1 = r1 | r2                                 |
| 37  0x25     | and     | 100101 .. REG1 REG2 ................ | and     r1 r2          | r1 = r1 & r2                                 |
| 38  0x26     | xor     | 100110 .. REG1 REG2 ................ | xor     r1 r2          | r1 = r1 ^ r2                                 |
| 39  0x27     | not     | 100111 .. REG1 REG2 ................ | not     r1             | r1 = !r1                                     |
| 40  0x28     | lshift  | 101000 .. REG1 REG2 ................ | lshift  r1 r2          |                                              |
| 41  0x29     | lshifti | 101001 .. REG1 REG2 IMMEDIATE-VALUE- | lshift  r2       1234  |                                              |
| 42  0x2a     | rshift  | 101010 .. REG1 REG2 ................ | rshift  r1 r2          |                                              |
| 43  0x2b     | rshifti | 101011 .. REG1 REG2 IMMEDIATE-VALUE- | rshift  r1       1234  |                                              |
| ...          | ...     | ...... .. .... .... ................ |                        |                                              |
| 63  0x3f     | hlt     | 111111 .. .... .... ................ | hlt                    | halt                                         |
'--------------'---------'--------------------------------------'------------------------'----------------------------------------------'
```

#### Returning from a subroutine call
The stack pointer must be point to the address of the return prior to being
called. See calling convention.

#### Pointer Arithmetic
To handle pointer arithmetic, the value of the register must be manipulated
directly prior to use. Inline pointer arithmetic is not supported.

Example, instead of,
```
mov r1 sp
mov r3 [r1 + 1]
```
You have to,
```
mov r1 sp
mov r2 1
add r1 r2
mov r3 [r1]
```

### Calling Convention
- Caller
  - push args (n, n-1, ..., 2, 1) onto stack in that order
  - push current bsp
  - set bsp to mem[sp-1]
  - call
    - push pc
    - set pc to called routine
- Callee
  - run subroutine
    - access args using mem[BSP-(1..n)]
  - ret
    - set pc to mem[bsp + 1] // saved sp
- Caller
  - set bsp to mem[bsp]
  - set sp to [sp - num_args]
