#include "vm.h"
#include <stdio.h>

/*a test function to test all the instructions*/
void test_arith_instruction(VM* vm, const char* instr_name, OpCode code, 
                            _opcode a, _opcode b, _opcode expect_result) {
    printf("=== test %s opcode：%d %s %d = ? ===\n", 
           instr_name, a, instr_name, b);
    
    /*clear the stack*/
    empty(vm->stack);
    /*push two opcode into the stack*/
    if (!push(vm->stack, a)) {
        perror("push the opdata failed\n");
        return;
    }
    if (!push(vm->stack, b)) {
        perror("push the opdata failed\n");
        return;
    }
    
    execute_instruction(vm, code);
    /*pop the result and find if it is true*/
    _opcode actual_result;
    if (pop(vm->stack, &actual_result)) {
        if (actual_result == expect_result) {
            printf("✅ test accepted!the final result is:%d, expected result is:%d\n\n", 
                   actual_result, expect_result);
        } else {
            printf("❌ test failed!final result is:%d, expected:%d\n\n", 
                   actual_result, expect_result);
        }
    } else {
        perror("pop the result failed");
        printf("\n");
    }
}

int main(int argc, char** argv) {
    /*init the vm*/
    VM* vm = init_vm();
    if (NULL == vm) {
        perror("init vm failed");
        return -1;
    }
    printf("init vm successfully\n\n");

    /*test the opcode one by one*/ 
    test_arith_instruction(vm, "ADD", ADD, 10, 20, 30);    // add operation: 10+20=30
    test_arith_instruction(vm, "SUB", SUB, 50, 15, 35);    // sub operation：50-15=35
    test_arith_instruction(vm, "MUL", MUL, 8, 6, 48);      // mul operation：8*6=48
    test_arith_instruction(vm, "DIV", DIV, 24, 4, 6);      // div operation：24/4=6

    /*test the special case: the div num is 0*/
    printf("=== test opcode DIV : the div num is 0 ===\n");
    empty(vm->stack);
    push(vm->stack, 100);
    push(vm->stack, 0);
    /*expected to print the exception information*/
    execute_instruction(vm, DIV);
    printf("\n");

    /*free the vm sources*/
    free_vm(vm);
    printf("free the vm sources successfully\n");
    return 0;
}
