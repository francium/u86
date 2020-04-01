#include <stdbool.h>
#include <stdio.h>

#include "bits.h"
#include "ops.h"


#ifndef _VU86_VM
#define _VU86_VM


// Machine specs
#define REGISTER_COUNT 4
#define RAM_SIZE 2048
#define ROM_SIZE 1024
#define STACK_SIZE 128
#define HEAP_SIZE (RAM_SIZE - ROM_SIZE - STACK_SIZE)

#define BASE_RAM_PTR 1

#define MIN_ROM_POINTER BASE_RAM_PTR
#define MAX_ROM_POINTER (MIN_ROM_POINTER + ROM_SIZE - 1)

#define MIN_STACK_POINTER (MAX_ROM_POINTER + 1)
#define MAX_STACK_POINTER (MIN_STACK_POINTER + STACK_SIZE - 1)

#define MIN_HEAP_POINTER (MAX_STACK_POINTER + 1)
#define MAX_HEAP_POINTER (MIN_HEAP_POINTER + HEAP_SIZE - 1)

// Masks and shifts
#define SHIFT_MACHINE_OP 26
#define SHIFT_RR 24
#define SHIFT_REG1 20
#define SHIFT_REG2 16
#define MASK_MACHINE_OP 0xfc000000 // 1111 1100 0000 0000 0000 0000 0000 0000
#define MASK_RR         0x03000000 // 0000 0011 0000 0000 0000 0000 0000 0000
#define MASK_REG1       0x00f00000 // 0000 0000 1111 0000 0000 0000 0000 0000
#define MASK_REG2       0x000f0000 // 0000 0000 0000 1111 0000 0000 0000 0000
#define MASK_IMM_VALUE  0x0000ffff // 0000 0000 0000 0000 1111 1111 1111 1111


typedef byte MachineOp;

typedef struct {
    MachineOp op;
    byte ra;
    byte rb;
    byte __padding;
    word imm;
} MachineWord;

typedef struct {
    word clock;
    word pc;                        // program counter
    word mar;                       // memory address register
    word mbr;                       // memory buffer register
    word sp;                        // stack pointer
    byte jf;                        // jump flag
    byte itrpt;                     // interrupt flag
    byte hlt;                       // halt flag
    word registers[REGISTER_COUNT];
    // We index starting at 1, so last index needs to be RAM_SIZE
    word ram[RAM_SIZE + 1];
    size_t rom_ptr;                   // base rom pointer
    size_t stack_ptr;                 // base stack pointer
    size_t heap_ptr;                  // base heap pointer
} Machine;


const MachineOp MachineOpMap[] =  {
    OP_CALL,
    OP_RET,
    OP_PUSH,
    OP_POP,
    OP_MOVR,
    OP_MOVFM,
    OP_MOVTM,
    OP_SET,
    OP_CMP,
    OP_JMP,
    OP_JE,
    OP_JZ,
    OP_JG,
    OP__RES13,
    OP__RES14,
    OP__RES15,
    OP__RES16,
    OP__RES17,
    OP__RES18,
    OP__RES19,
    OP__RES20,
    OP__RES21,
    OP__RES22,
    OP__RES23,
    OP__RES24,
    OP__RES25,
    OP__RES26,
    OP__RES27,
    OP__RES28,
    OP__RES29,
    OP__RES30,
    OP__RES31,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_OR,
    OP_AND,
    OP_XOR,
    OP_NOT,
    OP_LSHIFT,
    OP_RSHIFT,
    OP__RES42,
    OP__RES43,
    OP__RES44,
    OP__RES45,
    OP__RES46,
    OP__RES47,
    OP__RES48,
    OP__RES49,
    OP__RES50,
    OP__RES51,
    OP__RES52,
    OP__RES53,
    OP__RES54,
    OP__RES55,
    OP__RES56,
    OP__RES57,
    OP__RES58,
    OP__RES59,
    OP__RES60,
    OP__RES61,
    OP__RES62,
    OP_HLT,
};


void decode_word(MachineWord *machine_word, const word _word)
{
    machine_word->op = MachineOpMap[(_word & MASK_MACHINE_OP) >> SHIFT_MACHINE_OP];
    switch (machine_word->op) {
        case OP_CALL:
            break;

        case OP_RET:
            break;

        case OP_PUSH:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            break;

        case OP_POP:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            break;

        case OP_MOVR:
        case OP_MOVFM:
        case OP_MOVTM:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            machine_word->rb = (_word & MASK_REG2) >> SHIFT_REG2;
            break;

        case OP_SET:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            machine_word->imm = _word & MASK_IMM_VALUE;
            break;

        case OP_CMP:
            break;

        case OP_JMP:
            break;

        case OP_JE:
            break;

        case OP_JZ:
            break;

        case OP_JG:
            break;

        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_OR:
        case OP_AND:
        case OP_XOR:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            machine_word->rb = (_word & MASK_REG2) >> SHIFT_REG2;
            break;

        case OP_NOT:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            break;

        case OP_LSHIFT:
        case OP_RSHIFT:
            machine_word->ra = (_word & MASK_REG1) >> SHIFT_REG1;
            machine_word->rb = (_word & MASK_REG2) >> SHIFT_REG2;
            break;

        case OP_HLT:
            break;

        default:
            break;
    }
}


void machine_call(Machine *state, const MachineWord *ins)
{
    printf("Instruction call\n");
    // TODO
}


void machine_ret(Machine *state, const MachineWord *ins)
{
    printf("Instruction ret\n");
    // TODO
}


void machine_push(Machine *state, const MachineWord *ins)
{
    printf("Instruction push into register %d\n", ins->ra);
    state->ram[state->stack_ptr + state->sp] = state->registers[ins->ra];
    state->sp++;
}


void machine_pop(Machine *state, const MachineWord *ins)
{
    printf("Instruction pop into register %d\n", ins->ra);
    state->registers[ins->ra] = state->ram[state->stack_ptr + state->sp];
    state->sp--;
}


void machine_movr(Machine *state, const MachineWord *ins)
{
    printf("Instruction movr register %d into register %d\n", ins->rb, ins->ra);
    state->registers[ins->ra] = state->registers[ins->rb];
}


void machine_movfm(Machine *state, const MachineWord *ins)
{
    printf(
        "Instruction movfm memory at %d into register %d\n",
        state->mar,
        ins->ra
    );
    state->registers[ins->ra] = state->mbr;
}


void machine_movtm(Machine *state, const MachineWord *ins)
{
    printf("Instruction movtm register %d into memory at %d\n", ins->ra, state->mar);
    state->ram[state->mar] = state->registers[ins->ra];
}


void machine_set(Machine *state, const MachineWord *ins)
{
    printf("Instruction set value %d into register %d\n", ins->imm, ins->ra);
    state->registers[ins->ra] = ins->imm;
}


void machine_add(Machine *state, const MachineWord *ins)
{
    printf("Instruction add\n");
    state->registers[ins->ra] += state->registers[ins->rb];
}


void machine_sub(Machine *state, const MachineWord *ins)
{
    printf("Instruction sub\n");
    state->registers[ins->ra] -= state->registers[ins->rb];
}


void machine_mul(Machine *state, const MachineWord *ins)
{
    printf("Instruction mul\n");
    state->registers[ins->ra] *= state->registers[ins->rb];
}


void machine_div(Machine *state, const MachineWord *ins)
{
    printf("Instruction div\n");
    state->registers[ins->ra] /= state->registers[ins->rb];
}


void machine_or(Machine *state, const MachineWord *ins)
{
    printf("Instruction or\n");
    state->registers[ins->ra] |= state->registers[ins->rb];
}


void machine_and(Machine *state, const MachineWord *ins)
{
    printf("Instruction and\n");
    state->registers[ins->ra] &= state->registers[ins->rb];
}


void machine_xor(Machine *state, const MachineWord *ins)
{
    printf("Instruction xor\n");
    state->registers[ins->ra] ^= state->registers[ins->rb];
}


void machine_not(Machine *state, const MachineWord *ins)
{
    printf("Instruction not\n");
    state->registers[ins->ra] ^= state->registers[ins->ra];
}


void machine_lshift(Machine *state, const MachineWord *ins)
{
    printf("Instruction not\n");
    state->registers[ins->ra] <<= state->registers[ins->rb];
}


void machine_lshifti(Machine *state, const MachineWord *ins)
{
    printf("Instruction not\n");
    state->registers[ins->ra] <<= ins->imm;
}


void machine_rshift(Machine *state, const MachineWord *ins)
{
    printf("Instruction not\n");
    state->registers[ins->ra] >>= state->registers[ins->rb];
}


void machine_rshifti(Machine *state, const MachineWord *ins)
{
    printf("Instruction not\n");
    state->registers[ins->ra] >>= ins->imm;
}


void machine_cmp(Machine *state, const MachineWord *ins)
{
    printf("Instruction cmp\n");
    // TODO
    // const v1 = state->registers[ins->ra];
    // const v2 = state->registers[ins->rb];
    // state->flag = v1 - v2;
    // state->pc++;
}


void machine_jmp(Machine *state, const MachineWord *ins)
{
    printf("Instruction jmp\n");
    // TODO
    // state->pc = addr;
}


void machine_je(Machine *state, const MachineWord *ins)
{
    printf("Instruction je\n");
    // TODO
    // if (state->flag == 0) { state->pc = addr; }
}


void machine_jne(Machine *state, const MachineWord *ins)
{
    printf("Instruction jne\n");
    // TODO
    // if (state->flag != 0) { state->pc = addr; }
}


void machine_hlt(Machine *state)
{
    printf("Instruction hlt\n");
    state->hlt = true;
}


void machine_execute(Machine *state, const MachineWord *ins)
{
    switch (ins->op) {
        case OP_CALL:
            // TODO
            break;

        case OP_RET:
            // TODO
            break;

        case OP_PUSH:
            machine_push(state, ins);
            break;

        case OP_POP:
            machine_pop(state, ins);
            break;

        case OP_MOVR:
            machine_movr(state, ins);
            break;

        case OP_MOVFM:
            machine_movfm(state, ins);
            break;

        case OP_MOVTM:
            machine_movtm(state, ins);
            break;

        case OP_SET:
            machine_set(state, ins);
            break;

        case OP_CMP:
            // TODO
            break;

        case OP_JMP:
            // TODO
            break;

        case OP_JE:
            // TODO
            break;

        case OP_JZ:
            // TODO
            break;

        case OP_JG:
            // TODO
            break;

        case OP_ADD:
            machine_add(state, ins);
            break;

        case OP_SUB:
            machine_sub(state, ins);
            break;

        case OP_MUL:
            machine_mul(state, ins);
            break;

        case OP_DIV:
            machine_div(state, ins);
            break;

        case OP_OR:
            machine_or(state, ins);
            break;

        case OP_AND:
            machine_and(state, ins);
            break;

        case OP_XOR:
            machine_xor(state, ins);
            break;

        case OP_NOT:
            machine_not(state, ins);
            break;

        case OP_LSHIFT:
            machine_lshift(state, ins);
            break;

        case OP_RSHIFT:
            machine_rshift(state, ins);
            break;

        case OP_HLT:
            machine_hlt(state);
            break;

        default:
            break;
    }
}


static void machine_fetch(Machine *state, MachineWord *ins)
{
    const size_t ptr = state->rom_ptr + state->pc;
    const word _word = state->ram[ptr];
    decode_word(ins, _word);
}


static void machine_decode(Machine *state, const MachineWord *ins)
{
    switch (ins->op) {
        case OP_MOVFM:
            state->mar = state->registers[0];
            state->mbr = state->ram[state->mar];
            break;
        case OP_MOVTM:
            state->mar = state->registers[0];
            break;

        default:
            break;
    }
}


void machine_tick(Machine *state)
{
    if (state->hlt) { return; }

    MachineWord ins;
    machine_fetch(state, &ins);
    machine_decode(state, &ins);
    state->pc++;
    machine_execute(state, &ins);
}


void machine_reset(Machine *state)
{
    state->clock     = 0;
    state->pc        = 0;
    state->mar       = 0;
    state->mbr       = 0;
    state->sp        = 0;
    state->jf        = 0;
    state->itrpt     = 0;
    state->hlt       = false;
    state->rom_ptr   = MIN_ROM_POINTER;
    state->stack_ptr = MIN_STACK_POINTER;
    state->heap_ptr  = MIN_HEAP_POINTER;

    // Reset registers
    for (int i = 0; i < REGISTER_COUNT; i++) {
        state->registers[i] = 0;
    }

    // Reset RAM
    for (int i = 0; i < RAM_SIZE; i++) {
        state->ram[i] = 0;
    }
}


void machine_load(Machine *state, const size_t rom_size, const word *rom)
{
    const size_t n = (state->rom_ptr + rom_size);
    for (
        size_t i = state->rom_ptr, j = 0;
        i < n;
        i++, j++
    ) {
        state->ram[i] = rom[j];
    }
}


void machine_dump_specs()
{
    printf("Machine Specs\n");
    printf("REGISTER_COUNT\t\t%d\n", REGISTER_COUNT);
    printf("RAM_SIZE\t\t%d\n", RAM_SIZE);
    printf("ROM_SIZE\t\t%d\n", ROM_SIZE);
    printf("STACK_SIZE\t\t%d\n", STACK_SIZE);
    printf("HEAP_SIZE\t\t%d\n", HEAP_SIZE);
    printf("\n");
    printf("BASE_RAM_PTR\t\t%d\n", BASE_RAM_PTR);
    printf("\n");
    printf("MIN_ROM_POINTER\t\t%d\n", MIN_ROM_POINTER);
    printf("MAX_ROM_POINTER\t\t%d\n", MAX_ROM_POINTER);
    printf("\n");
    printf("MIN_STACK_POINTER\t%d\n", MIN_STACK_POINTER);
    printf("MAX_STACK_POINTER\t%d\n", MAX_STACK_POINTER);
    printf("\n");
    printf("MIN_HEAP_POINTER\t%d\n", MIN_HEAP_POINTER);
    printf("MAX_HEAP_POINTER\t%d\n", MAX_HEAP_POINTER);
}


void machine_dump_state(const Machine *state)
{
    printf("Machine State\n");
    printf("clock\t%d\n", state->clock);
    printf("pc\t%d\n", state->pc);
    printf("mar\t%d\n", state->mar);
    printf("mbr\t%d\n", state->mbr);
    printf("sp\t%d\n", state->sp);
    printf("jf\t%d\n", state->jf);
    printf("itrpt\t%d\n", state->itrpt);
    printf("hlt\t%d\n", state->hlt);
    printf("Registers\n");
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("r%d\t%d\n", i, state->registers[i]);
    }
}


// TODO
// void exception(const MachineState *state, const char *msg)
// {
//     printf("Exception: %s\n", msg);
//     dump(state);
//     exit(1);
// }
//
//
// void assert_machine_state(const MachineState *state)
// {
//     if (state->pc < 0) { exception(machine, "Invalid program counter"); }
//     if (state->sp > STACK_SIZE) { exception(machine, "Stack overflow"); }
//     if (state->sp < 0) { exception(machine, "Stack underflow"); }
// }


#endif
