/*
 * TODO
 * - VM error handling (stack overflow, etc.)
 *   - different from CPU exceptions?
 * - CPU exception handling
 * - Interrupts
 * - IO
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vm.h"


#define WORD_SEGMENTS 5


const word sample1[] = {
    7,  0,  0,  0,  2, // mov r1 2
    7,  0,  1,  0,  3, // mov r2 3
    34, 0,  0,  1,  0, // mul r1 r2
    63, 0,  0,  0,  0, // hlt
};


void compile(const size_t count, const word *hex, word *instructions)
{
    word op, rr, ra, rb, imm;
    word _word;

    for (
        size_t i = 0, j = 0;
        i < count;
        i += WORD_SEGMENTS, j++
    ) {
        op = (hex[i] << SHIFT_MACHINE_OP) & MASK_MACHINE_OP;
        rr = (hex[i + 1] << SHIFT_RR) & MASK_RR;
        ra = (hex[i + 2] << SHIFT_REG1) & MASK_REG1;
        rb = (hex[i + 3] << SHIFT_REG2) & MASK_REG2;
        imm = (hex[i + 4]) & MASK_IMM_VALUE;
        _word = op | rr | ra | rb | imm;
        // printf("0x%-2x, 0x%-2x, 0x%-2x, 0x%-2x, 0x%-2x\t\t"
        //        "0x%-8x, 0x%-8x, 0x%-8x, 0x%-8x, 0x%-8x\t\t"
        //        "0x%-8x\n",
        //        hex[i], hex[i + 1], hex[i + 2], hex[i + 3], hex[i + 4],
        //        op, rr, ra, rb, imm,
        //        _word
        // );
        instructions[j] = _word;
    }
}


int main(const int argc, const char **argv)
{
    /* FILE *fp; */
    /* char *line = NULL; */
    /* size_t len = 0; */
    /* ssize_t read; */
    /*  */
    /* fp = fopen(argv[1], "r"); */
    /* if (fp == NULL) { */
    /*     return 1; */
    /* } */
    /*  */
    /* while ((read = getline(&line, &len, fp)) != -1) { */
    /*     printf("%s", line); */
    /* } */
    /*  */
    /* fclose(fp); */
    /* if (line) { */
    /*     free(line); */
    /* } */
    /*  */
    /* return 0; */

    const size_t s = WORD_SEGMENTS * 4;
    word rom[s];
    compile(s, sample1, rom);

    Machine mach;
    machine_reset(&mach);
    machine_load(&mach, s, rom);

    machine_dump_state(&mach);
    while (!mach.hlt) {
        printf("Press any to step, q to quit\n");
        char c = getchar();
        if (c == 'q') { break; }

        machine_tick(&mach);
        machine_dump_state(&mach);
    }

    return 0;
}
