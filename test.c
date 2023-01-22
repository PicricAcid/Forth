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
                    th = th->next;
                }
                else
                {
                    printf("ADD\n");
                    th = th->next;
                }
                break;
            case PRINT:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
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
                    if (inter->origin)
                    {
                        th = inter->origin;
                        inter->origin = NULL;
                    }
                }
                else
                {
                    printf("DEFINITION_END\n");
                    th = th->next;
                }
                inter->mode = NEUTRAL;
                break;
            case CALL_DEFINITION:
                printf("CALL_DEFINITION\n");
                inter->mode = CALL_FUNC;
                Definition *def = search_definition(inter, th->definition_name);
                if (def)
                {
                    inter->origin = th->next;
                    th = def->thread_head;
                }
                else
                {
                    inter->mode = NEUTRAL;
                    th = th->next;
                }
                break;
            case HALT:
            case ROUTINE_TYPE_COUNT:
            default:
                break;
        }
    }
}