#include "test.h"
#include "mem.h"

void debug_executer(VM *vm)
{
    vm->thread = MEM_BLOCK;
    while(!vm->endofloop)
    {
        print_thread(vm);
    }

    return;
}

int print_thread(VM *vm)
{
    int endofloop = 0;

    switch(vm->mem[vm->thread]) {
        case PUSH:
            printf("%d: PUSH, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case POP:
            printf("%d: POP, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case ADD:
            printf("%d: ADD, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case SUB:
            printf("%d: SUB, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case MUL:
            printf("%d: MUL, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case DIV:
            printf("%d: DIV, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case PRINT:
            printf("%d: PRINT, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case JUMP:
            printf("%d: JUMP, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case CALL:
            printf("%d: CALL, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case RET:
            printf("%d: RET, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        case HALT:
            printf("%d: HALT, %d\n", vm->thread, vm->mem[vm->thread]);
            endofloop = 1;
            break;
        case THREAD_TYPE_COUNT:
        default:
            printf("%d: ERR, %d\n", vm->thread, vm->mem[vm->thread]);
            break;
        }

    return endofloop;
}