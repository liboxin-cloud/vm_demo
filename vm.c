/**
 * @file vm.c
 * @brief Implementation of the Lightweight Stack-Based Virtual Machine
 * 
 * This file contains the concrete implementation of all functions declared in vm.h,
 * including stack operations (push/pop), VM initialization, instruction parsing,
 * and memory cleanup. It defines the internal logic of the VM.
 * 
 * Key features:
 * - LIFO stack management with overflow/underflow checks
 * - Arithmetic operations with division-by-zero protection
 * - Safe memory allocation/free to prevent leaks
 * 
 * @author liboxin
 * @date 2025-10-29
 * @version 1.0
 */


#include "vm.h"



_vm_stack* init_vm_stack() {
    _vm_stack* stack = (_vm_stack*)malloc(sizeof(_vm_stack));
    if (NULL == stack) {
        perror("memory allocate failed\n");
        return NULL;
    }
    stack->data = (_opcode*)malloc(sizeof(_opcode) * STACK_MAX_SIZE);
    stack->bottom = stack->data;
    stack->top = stack->bottom;
    stack->size = 0;

    return stack;
}

bool push(_vm_stack* stack, _opcode data) {
    if (NULL == stack) {
        perror("unknown error\n");
        return false;
    }

    if (stack->size >= STACK_MAX_SIZE) {
        perror("stack overflow\n");
        return false;
    }
    stack->data[stack->size] = data;
    stack->size++;
    stack->top = stack->data + stack->size;
    
    return true;
}

bool pop(_vm_stack* stack, _opcode* popped_data) {
    if (NULL == stack) {
        perror("the stack is NULL\n");
        return false;
    }

    if (isEmpty(stack)) {
        perror("the stack is empty\n");
        return false;
    }
    *popped_data = *(stack->top - 1);
    stack->top--;
    stack->size--;
    return true;
}

void empty(_vm_stack* stack) {
    if (NULL == stack) {
        perror("the stack is NULL\n");
        return;
    }

    stack->top = stack->bottom;
    stack->size = 0;
}


bool isEmpty(_vm_stack* stack) {
    if (NULL == stack) {
        perror("the stack is NULL\n");
        return false;
    }

    return stack->top == stack->bottom;

}

void execute_instruction(VM* vm, _opcode code) {
    if (NULL == vm) {
        perror("the vm is NULL\n");
        return;
    }

    if (code < POP || code > MOV) {
        perror("unknown instruction\n");
        return;
    }

    switch (code) {
        case POP: {
            printf("code POP\n");
            _opcode popped_data;
            if (pop(vm->stack, &popped_data)) {
                printf("pop the data is: %d\n", popped_data);
            }
            break;
        }


        case ADD: {
            printf("code ADD\n");
            _opcode _data1;
            _opcode _data2;
            _opcode result;

            if (!pop(vm->stack, &_data1) || 
            !pop(vm->stack, &_data2)) {
                perror("the data of the stack is not enough\n");
                break;
            }
            result = _data1 + _data2;
            /*push the result to the vm stack*/
            if (!push(vm->stack, result)) {
                perror("push the result data failed\n");
                break;
            }
            break;
        }

        case SUB: {
            printf("code SUB\n");
            _opcode _data1;
            _opcode _data2;
            _opcode result;

            if (!pop(vm->stack, &_data2) || 
            !pop(vm->stack, &_data1)) {
                perror("the data of the stack is not enough\n");
                break;
            }
            result = _data1 - _data2;
            /*push the result to the vm stack*/
            if (!push(vm->stack, result)) {
                perror("push the result data failed\n");
                break;
            }

            break;
        }

        case MUL: {
            printf("code MUL\n");
            _opcode _data1;
            _opcode _data2;
            _opcode result;

            if (!pop(vm->stack, &_data2) || 
            !pop(vm->stack, &_data1)) {
                perror("the data of the stack is not enough\n");
                break;
            }
            result = _data1 * _data2;
            /*push the result to the vm stack*/
            if (!push(vm->stack, result)) {
                perror("push the result data failed\n");
                break;
            }

            break;
        }

        case DIV: {
            printf("code DIV\n");
            _opcode _data1;
            _opcode _data2;
            _opcode result;

            if (!pop(vm->stack, &_data2) || 
            !pop(vm->stack, &_data1)) {
                perror("the data of the stack is not enough\n");
                break;
            }


            /*handle the zero*/
            if (0 == _data2) {
                perror("error! divided by the zero, this is illegal\n");
                break;
            }   

            result = _data1 / _data2;
            /*push the result to the vm stack*/
            if (!push(vm->stack, result)) {
                perror("push the result data failed\n");
                break;
            }

            break;
        }

        case MOV: {
            printf("the code of MOV\n");

            _opcode data;
            if (!pop(vm->stack, &data)) {
                perror("the code MOV execute failed\n");
                break;
            }

            push(vm->stack, data);

            break;
        }

        default: {
            perror("unknown code\n");
            break;
        }


    }

    (*vm->pc)++;

}


void free_vm(VM* vm) {
    if (NULL == vm) {
        return;
    }


    if (NULL == vm->stack) {
        return;
    }

    
    free(vm->stack->data);
    free(vm->stack);
    free(vm->pc);
    free(vm);
}



VM* init_vm() {
    VM* vm = (VM*)malloc(sizeof(VM));

    if (NULL == vm) {
        perror("init the vm failed\n");
        return NULL;
    }

    vm->stack = init_vm_stack();
    if (NULL == vm->stack) {
        free(vm);
        perror("init the vm stack failed\n");;
        return NULL;
    }

    vm->pc = (int*)malloc(sizeof(int));

    if(NULL == vm->pc) {
        perror("pc init failed\n");

        free(vm->stack);
        free(vm);

        return NULL;
    }

    *vm->pc = 0;

    return vm;
}