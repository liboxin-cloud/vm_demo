/**
 * @file vm.h
 * @brief Header file for a Lightweight Stack-Based Virtual Machine
 * 
 * This file declares core data structures (VM, Stack), opcodes, macros, and function prototypes
 * for the stack-based VM. It defines the public interface that can be included and used by other
 * source files (e.g., main.c).
 * 
 * @author liboxin
 * @date 2025-10-29
 * @version 1.0
 */

#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 1024
#define MEMORY_BAD_ALLOCATE -1

typedef unsigned int _opcode;

typedef enum OpCode {
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOV
} OpCode;


typedef struct _vm_stack {
    _opcode* data;
    _opcode* top;
    _opcode* bottom;
    int size;
} _vm_stack;


typedef struct VM {
    int* pc;
    struct _vm_stack* stack;
} VM;



_vm_stack* init_vm_stack(void);
bool push(_vm_stack* stack, _opcode data);
bool pop(_vm_stack* stack, _opcode* popped_data);
void empty(_vm_stack* stack);
bool isEmpty(_vm_stack* stack);


VM* init_vm();
void execute_instruction(VM* vm, _opcode code);
void free_vm(VM* vm);

#endif

