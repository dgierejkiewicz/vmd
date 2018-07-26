#include <stdio.h>
#include <stdbool.h>

///* vm instruction pointer */
//int ip = 0;
//
///* vm stack pointer */
//int sp = -1;

/* vm stack */
int stack[256];

/* vm state until HLT instruction is set */
bool running = true;

/* register def */
typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

/* stack pointer */
#define sp (registers[SP])
/* instruction pointer */
#define ip (registers[IP])


/* instructions set */
typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

/* basic vm program */
const int program[] = {
        PSH, 5,
        PSH, 6,
        ADD,
        POP,
        HLT
};




/* basic instruction evaluation */
void eval(int instr) {
    switch (instr) {
        case HLT: {
            // set state to stop vm
            running = false;
            break;
        }
        case PSH: {
            // increment stack pointer
            sp++;

            // set the value to the the stack
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            // store the value at the stack in val_popped THEN decrement the stack ptr
            int val_popped = stack[sp--];

            // print it out!
            printf("popped %d\n", val_popped);
            break;
        }
        case ADD: {
            // first we pop the stack and store it as 'a'
            int a = stack[sp--];

            // then we pop the top of the stack and store it as 'b'
            int b = stack[sp--];

            // we then add the result and push it to the stack
            int result = b + a;
            sp++; // increment stack pointer **before**
            stack[sp] = result; // set the value to the top of the stack

            // all done!
            break;
        }
        default:
            printf("%d\n", instr);
            break;
    }
}

/* return instruction */
int fetch() {
    return program[ip];
}

/* main vm fn */
int main() {

    while (running) {
        eval(fetch());
        ip++; // increment the ip every iteration
    }
    return 0;

}