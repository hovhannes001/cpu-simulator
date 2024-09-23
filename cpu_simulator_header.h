#ifndef CPU_SIMULATOR_HEADER_H
#define CPU_SIMULATOR_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define MEMORY_SIZE 256
#define BUFFER_SIZE 50
#define MAX_COUNT_REGISTERS 2
#define OP_ADD 1
#define OP_SUB 2
#define OP_LOAD 4
#define OP_STORE 5

extern bool WSR;
extern int IP;

typedef struct {
    int r[7];
    int RAM[MEMORY_SIZE];
} CPU;

int register_number(char *);
void memory_print(CPU *);
void ALU(int, CPU *, char *, char *[2]);
void load_and_store(int, CPU *, char *, int);
void mov(CPU *, char *, int);

#endif
