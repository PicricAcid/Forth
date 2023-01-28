#include "definitions.h"

int pop(Interpreter *inter)
{
    int val;
    Stack *current_stack = inter->stack_head;
    Stack *next_stack = current_stack->next;

    val = current_stack->val;

    inter->stack_head = next_stack;
    free(current_stack);

    return val;
}

void push(Interpreter *inter, int val)
{
    Stack *new_stack;
    new_stack = (Stack*)malloc(sizeof(Stack)); 

    if (inter->stack_head)
    {
        new_stack->val = val;
        new_stack->next = inter->stack_head;
    }
    else
    {
        new_stack->val = val;
        new_stack->next = NULL;
    }

    inter->stack_head = new_stack;

    return;
}

/*
void print_int_value(Value val)
{

}
*/

int add(Interpreter *inter)
{
    int first_value;
    int second_value;

    second_value = pop(inter);
    first_value = pop(inter);

    push(inter, first_value + second_value);

    return 0;
}

int sub(Interpreter *inter)
{
    int first_value;
    int second_value;

    second_value = pop(inter);
    first_value = pop(inter);

    push(inter, first_value - second_value);

    return 0;
}
