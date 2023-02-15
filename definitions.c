#include "definitions.h"

Value pop(Interpreter *inter)
{
    Value val;
    Stack *current_stack = inter->stack_head;
    Stack *next_stack = current_stack->next;

    val = current_stack->val;

    inter->stack_head = next_stack;
    free(current_stack);

    return val;
}

void push(Interpreter *inter, Value val)
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

int std_add(Interpreter *inter)
{
    Value first_value;
    Value second_value;

    Value result;

    second_value = pop(inter);
    first_value = pop(inter);

    if ((first_value.type == INT_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = INT_VALUE;
        result.u.int_value = first_value.u.int_value + second_value.u.int_value;
    }
    else if ((first_value.type == INT_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = (first_value.u.int_value*second_value.u.ratio_value.denominator) + second_value.u.ratio_value.numerator;
        result.u.ratio_value.denominator = second_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator + (second_value.u.int_value*first_value.u.ratio_value.denominator);
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = (first_value.u.ratio_value.numerator*second_value.u.ratio_value.denominator) + (second_value.u.ratio_value.numerator*first_value.u.ratio_value.denominator);
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator*second_value.u.ratio_value.denominator;
    }

    push(inter, result);

    return 0;
}

int std_sub(Interpreter *inter)
{
    Value first_value;
    Value second_value;

    Value result;

    second_value = pop(inter);
    first_value = pop(inter);

    if ((first_value.type == INT_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = INT_VALUE;
        result.u.int_value = first_value.u.int_value - second_value.u.int_value;
    }
    else if ((first_value.type == INT_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = (first_value.u.int_value*second_value.u.ratio_value.denominator) - second_value.u.ratio_value.numerator;
        result.u.ratio_value.denominator = second_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator - (second_value.u.int_value*first_value.u.ratio_value.denominator);
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = (first_value.u.ratio_value.numerator*second_value.u.ratio_value.denominator) - (second_value.u.ratio_value.numerator*first_value.u.ratio_value.denominator);
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator*second_value.u.ratio_value.denominator;
    }


    push(inter, result);

    return 0;
}

int std_mul(Interpreter *inter)
{
    Value first_value;
    Value second_value;

    Value result;

    second_value = pop(inter);
    first_value = pop(inter);

    if ((first_value.type == INT_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = INT_VALUE;
        result.u.int_value = first_value.u.int_value*second_value.u.int_value;
    }
    else if ((first_value.type == INT_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.int_value*second_value.u.ratio_value.numerator;
        result.u.ratio_value.denominator = second_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator*second_value.u.int_value;
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator*second_value.u.ratio_value.numerator;
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator*second_value.u.ratio_value.denominator;
    }

    push(inter, result);

    return 0;
}

int std_div(Interpreter *inter)
{
    Value first_value;
    Value second_value;

    Value result;

    second_value = pop(inter);
    first_value = pop(inter);

    if ((first_value.type == INT_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.int_value;
        result.u.ratio_value.denominator = second_value.u.int_value;
    }
    else if ((first_value.type == INT_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.int_value*second_value.u.ratio_value.denominator;
        result.u.ratio_value.denominator = second_value.u.ratio_value.numerator;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == INT_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator;
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator*second_value.u.int_value;
    }
    else if ((first_value.type == RATIO_VALUE) && (second_value.type == RATIO_VALUE))
    {
        result.type = RATIO_VALUE;
        result.u.ratio_value.numerator = first_value.u.ratio_value.numerator*second_value.u.ratio_value.denominator;
        result.u.ratio_value.denominator = first_value.u.ratio_value.denominator*second_value.u.ratio_value.numerator;
    }

    push(inter, result);

    return 0;
}
