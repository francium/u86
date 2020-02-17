## u86
A x86-like bytecode


## uasm
Assembler u86 bytecode


## vu86
u86 virtual machine


## u86 Reference


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


### Opcode table
```
,--------------,---------,--------------------------------------,------------------------,---------------------------------------------,
| Instruction  | Opcode  | Machine word                         | Assembly Example       | Notes                                       |
|--------------|---------|--------------------------------------|------------------------|---------------------------------------------|
| 00  0x00     | call    | 000000 .. REG1 .... ................ |                        |                                             |
| 01  0x01     | ret     | 000001 .. .... .... ................ |                        |                                             |
| 02  0x02     | push    | 000010 .. REG1 .... ................ | push    r1             | stack.push(r1)                              |
| 03  0x03     | pop     | 000011 .. REG1 .... ................ | pop     r1             | r1 = stack.pop()                            |
| 04  0x04     | movr    | 000100 .. REG1 REG2 ................ | mov     r1   r2        | r1 = r2                                     |
| 05  0x05     | movfm   | 000101 .. REG1 REG2 ................ | mov     r1  [r2 +/- n] | r1 = *(r2 +/- n) // n is some word multiple |
| 06  0x06     | movtm   | 000110 .. REG1 REG2 ................ | mov    [r1]  r2        | *r1 = r2                                    |
| 07  0x07     | movi    | 000111 .. REG1 .... IMMEDIATE-VALUE- | mov     r1       1234  | r1 = 1234                                   |
| 08  0x08     | cmp     | 001000 .. REG1 REG2 ................ | cmp     r1   r2        | jf = r1 == r2 ? 0 : r1 > r2 : 1 : -1        |
| 09  0x09     | jmpr    | 001001 .. REG1 .... ................ |                        |                                             |
| 10  0x0a     | je      | 001010 .. REG1 .... ................ |                        |                                             |
| 12  0x0b     | jz      | 001011 .. REG1 .... ................ |                        |                                             |
| 13  0x0c     | jg      | 001100 .. REG1 .... ................ |                        |                                             |
| ...          | ...     | ...... ..                            |                        |                                             |
| 32  0x20     | add     | 100000 .. REG1 REG2 ................ | add     r1 r2          | r1 = r1 + r2                                |
| 33  0x21     | sub     | 100001 .. REG1 REG2 ................ | sub     r1 r2          | r1 = r1 - r2                                |
| 34  0x22     | mul     | 100010 .. REG1 REG2 ................ | mul     r1 r2          | r1 = r1 * r2                                |
| 35  0x23     | div     | 100011 .. REG1 REG2 ................ | div     r1 r2          | r1 = r1 / r2                                |
| 36  0x24     | or      | 100100 .. REG1 REG2 ................ | or      r1 r2          | r1 = r1 | r2                                |
| 37  0x25     | and     | 100101 .. REG1 REG2 ................ | and     r1 r2          | r1 = r1 & r2                                |
| 38  0x26     | xor     | 100110 .. REG1 REG2 ................ | xor     r1 r2          | r1 = r1 ^ r2                                |
| 39  0x27     | not     | 100111 .. REG1 REG2 ................ | not     r1             | r1 = !r1                                    |
| 40  0x28     | lshift  | 101000 .. REG1 REG2 ................ | lshift  r1 r2          |                                             |
| 41  0x29     | lshifti | 101001 .. REG1 REG2 IMMEDIATE-VALUE- | lshift  r2       1234  |                                             |
| 42  0x2a     | rshift  | 101010 .. REG1 REG2 ................ | rshift  r1 r2          |                                             |
| 43  0x2b     | rshifti | 101011 .. REG1 REG2 IMMEDIATE-VALUE- | rshift  r1       1234  |                                             |
| ...          | ...     | ...... .. .... .... ................ |                        |                                             |
| 63  0x3f     | hlt     | 111111 .. .... .... ................ | hlt                    | halt                                        |
'--------------'---------'--------------------------------------'------------------------'---------------------------------------------'
```


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


## Calling Convention
```
,------------------------,
|                        |
|                        |
| pc for ret             |
| arg 1                  |
| arg 2                  |
| arg ....               |
| arg n-1                |
| arg n                  |
| bsp ptr for main fn    |
| main fn item ...       | <-- before `call`, previous `sp`
| main fn item ...       |
| main fn item 2         |
| main fn item 1         | <-- previous `bsp`
| arg 1                  | <-,
| arg 2                  |   | Previous function's args and saved register values
| arg ...                |   |
| arg n                  |   |
| pc ptr                 |   |
| bsp ptr                |   |
| retp ptr               | <-'
| ...                    |
'------------------------'
```

- Calling convention
  - Caller
    - Push bsp
    - push args (n, n-1, ..., 2, 1) onto stack in that order
    - call
      - push pc
      - set pc to called routine
    - pop stack of (just manipulate sp)
    -
  - Callee
    - ...
    - ret
      - set pc to mem[bsp + (num args) + 1]
