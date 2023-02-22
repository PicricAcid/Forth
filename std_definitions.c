#include "std_definitions.h"

void std_pop(VM *vm)
{
    vm->data_stack--;

    return;
}

void std_push(VM *vm)
{
    vm->mem[++vm->data_stack] = vm->mem[vm->thread++];

    return;
}

void std_add(VM *vm)
{
    int first_value = vm->mem[vm->data_stack - 1];
    int second_value = vm->mem[vm->data_stack];

    vm->mem[vm->data_stack - 1] = first_value + second_value;
    vm->data_stack--;

    return;
}

void std_sub(VM *vm)
{
    int first_value = vm->mem[vm->data_stack - 1];
    int second_value = vm->mem[vm->data_stack];

    vm->mem[vm->data_stack - 1] = first_value - second_value;
    vm->data_stack--;

    return;
}

void std_mul(VM *vm)
{
    int first_value = vm->mem[vm->data_stack - 1];
    int second_value = vm->mem[vm->data_stack];

    vm->mem[vm->data_stack - 1] = first_value * second_value;
    vm->data_stack--;

    return;
}

void std_div(VM *vm)
{
    int first_value = vm->mem[vm->data_stack - 1];
    int second_value = vm->mem[vm->data_stack];

    vm->mem[vm->data_stack - 1] = first_value / second_value;
    vm->data_stack--;

    return;
}

void std_print(VM *vm)
{
    printf("%d\n", vm->mem[vm->data_stack]);

    return;
}

void std_jump(VM *vm)
{
    vm->thread = vm->mem[vm->thread + 1];

    return;
}

void std_call(VM *vm)
{
    vm->mem[++vm->call_stack] = vm->thread + 1;
    vm->thread = vm->mem[vm->thread];

    return;
}

void std_return(VM *vm)
{
    if (vm->mem[vm->call_stack])
    {
        vm->thread = vm->mem[vm->call_stack--];
    }

    return;
}

void std_halt(VM *vm)
{
    vm->endofloop = 1;

    return;
}