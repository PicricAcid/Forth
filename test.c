#include "test.h"

void print_stack(Interpreter *inter)
{
    Stack *stk;
    for (stk = inter->stack_head; stk; stk = stk->next)
    {
        if (stk)
        {
            printf("%d\n", stk->val);
        }
        else
        {
            printf("It's all");
        }
    }
}

void print_thread(Interpreter *inter)
{
    Thread *th = inter->thread_head;

    while (th)
    {
        switch (th->type)
        {
            case PUSH:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    printf(" PUSH\n");
                    th = th->next;
                }
                else
                {
                    printf("PUSH\n");
                    th = th->next;
                }
                break;
            case POP:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    printf(" POP\n");
                    th = th->next;
                }
                else
                {
                    printf("POP\n");
                    th = th->next;
                }
                break;
            case ADD:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    printf(" ADD\n");
                    th = th->next;
                }
                else
                {
                    printf("ADD\n");
                    th = th->next;
                }
                break;
            case SUB:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    printf(" SUB\n");
                    th = th->next;
                }
                else
                {
                    printf("SUB\n");
                    th = th->next;
                }
                break;
            case PRINT:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    printf(" PRINT\n");
                    th = th->next;
                }
                else
                {
                    printf("PRINT\n");
                    th = th->next;
                }
                break;
            case DEFINITION:
                if (inter->mode == CALL_FUNC)
                {
                    th = th->next;
                }
                else
                {
                    printf("DEFINITION\n");
                    inter->mode = FUNC_DEFINITION;
                    th = th->next;
                }
                break;
            case DEFINITION_END:
                if (inter->mode == CALL_FUNC)
                {
                    if (inter->call_stack_head)
                    {
                        th = pop_call_stack(inter);
                        printf("RETURN\n");
                    }
                }
                else if (inter->mode == FUNC_DEFINITION)
                {
                    printf("DEFINITION_END\n");
                    th = th->next;
                    inter->mode = NEUTRAL;
                }
                else
                {
                    printf("DEFINITION_END\n");
                    th = th->next;
                }
                break;
            case CALL_DEFINITION:
                if (inter->mode == FUNC_DEFINITION)
                {
                    printf(" CALL_DEFINITION\n");
                    th = th->next;
                }
                else
                {
                    printf("CALL_DEFINITION\n");
                    inter->mode = CALL_FUNC;
                    Definition *def = search_definition(inter, th->definition_name);
                    if (def)
                    {
                        push_call_stack(inter, th->next);
                        th = def->thread_head;
                    }
                    else
                    {
                        inter->mode = NEUTRAL;
                        th = th->next;
                    }
                }
                break;
            case HALT:
            case ROUTINE_TYPE_COUNT:
            default:
                break;
        }
    }
}