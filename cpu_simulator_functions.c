#include "cpu_simulator_header.h"
//register number from operand
int register_number(char *result) {
    while(*result == 'r') {
        result++;
        
    }
    return atoi(result);
}

//--------------------------------------------layo ---------------------------------------------------------------
void memory_print(CPU *cpu) {
    printf("R0: %d,R1: %d,R2:%d,R3: %d,R4: %d,R5: %d,R6: %d,WSR:%d,IP: %d\n",
    cpu->r[0],cpu->r[1],cpu->r[2],cpu->r[3],cpu->r[4],cpu->r[5],cpu->r[6],WSR,IP);
    printf("Memory: [");
    for(int i = 0;i < MEMORY_SIZE;i++) {
        printf("%d, ",cpu->RAM[i]);
    }
    printf("] size(%d)",MEMORY_SIZE);
    printf("\n");
}

//--------------------------------------------add and sub---------------------------------------------------------------
void ALU(int opcode, CPU *cpu, char *result, char *operands[2]) {
    if (opcode == OP_ADD) {
        cpu->r[register_number(result)] = cpu->r[register_number(operands[0])] + cpu->r[register_number(operands[1])];
    }
    else if (opcode == OP_SUB) {
        cpu->r[register_number(result)] = cpu->r[register_number(operands[0])] - cpu->r[register_number(operands[1])];
    }
}
//--------------------------------------------load and store ----------------------------------------------------------------
void load_and_store(int operand,CPU *cpu,char *result, int index) {
    if(index < 0 || index > 256) {
        printf("No such index in arr\n");
        exit(EXIT_FAILURE);
    }
    if(operand == OP_LOAD) {
        cpu->r[register_number(result)] = cpu->RAM[index];
    }
    else if(operand == OP_STORE) {
        cpu->RAM[index] = cpu->r[register_number(result)];
    }
}

//--------------------------------------------mov----------------------------------------------------------------
void mov(CPU *cpu,char *result,int value) {
    cpu->r[register_number(result)] = value;
}