#include "cpu_simulator_header.h"
bool WSR;
int IP;
int main() {
    CPU *cpu = malloc(sizeof(CPU));
    assert(cpu);
    char *instruction = malloc(sizeof(char) * BUFFER_SIZE);
    assert(instruction);
    char *token = malloc(sizeof(char) * BUFFER_SIZE);
    assert(token);
    char *result = malloc(sizeof(char) * BUFFER_SIZE);
    assert(result);
    char *operands[MAX_COUNT_REGISTERS];
    for (int i = 0;i < MAX_COUNT_REGISTERS;i++) {
        operands[i] = malloc(sizeof(char) * BUFFER_SIZE);
        assert(operands[i]);
    }
    int file = open("./database.txt",O_TRUNC | O_APPEND | O_RDWR);
    assert(file);
    
    printf("Initial CPU State\n");
    memory_print(cpu);
    while(true) {
        fgets(instruction,BUFFER_SIZE - 2,stdin);
        token = strtok(instruction, " ");
        if(strncmp(token,"start",strlen("start")) == 0) {
            if(WSR == 0){
                WSR = 1;
                IP++;
                printf("WSR: %d,IP %d\n",WSR,IP);
            }
        }
        else if(WSR == 0 && strncmp(token,"exit",strlen("exit"))) {
            printf("Enter first 'start'\n");
        }
        else if(strncmp(token,"exit",strlen("exit")) == 0) {
            if(WSR == 0) {
                printf("Terminating CPU Simulator...\n\n\n");
                printf("Final CPU State\n");
                memory_print(cpu);
                break;
            }
            else {
                WSR = 0;
                printf("WSR: %d,IP %d\n",WSR,IP);
                memset(cpu->RAM,0,MEMORY_SIZE);
            }
            IP++;
        }
        else if(strncmp(token,"layo",strlen("layo")) == 0) {
                printf("CPU State: \n");
                IP++;
                memory_print(cpu);
        }
        else if(!strncmp(token,"mov",strlen("mov"))) {
            result = strtok(NULL, " ,");
            operands[0] = strtok(NULL,", \n");
            mov(cpu,result,atoi(operands[0]));
        }
        else if(!strncmp(token,"load",strlen("load")) || !strncmp(token,"store",strlen("store"))){
            result = strtok(NULL, " ,");
            operands[0] = strtok(NULL,", \n");
            if(!strncmp(token,"load",strlen("load"))) {
                load_and_store(OP_LOAD,cpu,result,atoi(operands[0]));
            }
            if(!strncmp(token,"store",strlen("store"))) {
                load_and_store(OP_STORE,cpu,result,atoi(operands[0]));
            }
        }

        else if(!strncmp(token,"add",strlen("add")) || !strncmp(token,"sub",strlen("sub"))){       
            result = strtok(NULL, " ,");
            for(int i = 0;i < MAX_COUNT_REGISTERS;i++) {
                strcpy(operands[i],strtok(NULL,", \n"));            
            }
            if(!strncmp(token,"add",strlen("add"))) {
                ALU(OP_ADD,cpu,result,operands);              
            }
            else if(!strncmp(token,"sub",strlen("sub"))) {
                ALU(OP_SUB,cpu,result,operands);
            }
            else {
                printf("Invalid input\n");
            }
            if(write(file,cpu,sizeof(cpu)) < 0) {
                perror("write failed: ");
                exit(EXIT_FAILURE);
            }
        }
    else if (!strncmp(token, "disc", strlen("disc"))) {
        operands[0] = strtok(NULL, ", \n");
        printf("operand: %s\n",operands[0]);
        int records_back = atoi(operands[0]);
        
        off_t file_size = lseek(file, 0, SEEK_END);

        if (file_size < sizeof(CPU)) {
            printf("File doesn't contain enough CPU data.\n");
            exit(EXIT_FAILURE);
        }

        if (records_back < 1 || sizeof(CPU) * records_back > file_size) {
            printf("Invalid records_back value or insufficient file data.\n");
            exit(EXIT_FAILURE);
        }

        
        if (lseek(file, -(sizeof(CPU) * records_back), SEEK_END) < 0) {
            perror("lseek failed");
            exit(EXIT_FAILURE);
        }

        if (read(file, cpu, sizeof(CPU)) < 0) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }

        printf("Loaded previous CPU state.\n");
        memory_print(cpu);  
    }


        else{
                printf("Invalid input\n");
            }
        if (write(file, cpu, sizeof(CPU)) < 0) {
            perror("write failed: ");
            exit(EXIT_FAILURE);
        }
    }
    close(file);
    free(result);
    free(token);
    for (int i = 0; i < MAX_COUNT_REGISTERS; i++){
    free(operands[i]);
    } 
    free(instruction);
    free(cpu);
    return 0;
}

