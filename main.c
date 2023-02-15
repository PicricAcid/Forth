#include "main.h"
#include "definitions.h"
#include "test.h"

#define TOKEN_BUF_SIZE 32

int main(int argc, char *argv[])
{
    char token[TOKEN_BUF_SIZE];
    Interpreter *inter;
    Thread *thread_p;
    int endofloop = 0;

    FILE *fp;

    fp = fopen(argv[1], "r");

    inter = init_interpreter();

    while (1)
    {   
        parser(token, fp);
        endofloop = interpret(inter, token);

        if (token[0] == '\0' || endofloop)
        {
            break;
        }
    }

    fclose(fp);

    executer(inter);
    /* print_thread(inter); */
    return 0;
}

void parser(char *token, FILE *fp)
{
    token[0] = '\0';
    if (fscanf(fp, "%s%*[^ \t\n\r]", token))
    {
        getc(fp);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int interpret(Interpreter *inter, char *token)
{
    int int_val;
    int endofloop;

    int_val = atoi(token);
    if (int_val)
    {
        Value val;
        val.type = INT_VALUE;
        val.u.int_value = int_val;
        create_thread(inter, PUSH, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, "0") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, PUSH, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, "+") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, ADD, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, "-") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, SUB, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, "*") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, MUL, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, "/") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, DIV, val, NULL);
        endofloop = 0;
    }
    else if (strcmp(token, ".") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, PRINT, val, NULL);
        endofloop = 1;
    }
    else if (strcmp(token, ":") == 0)
    {
        inter->mode = GET_NAME;
        endofloop = 0;
    }
    else if (strcmp(token, ";") == 0)
    {
        Value val;
        val.type = NULL_VALUE;
        create_thread(inter, DEFINITION_END, val, NULL);
        endofloop = 0;
    }
    else
    {
        if (inter->mode == GET_NAME)
        {
            if (strlen(token) < DEFINITION_NAME_SIZE)
            {
                Value val;
                val.type = NULL_VALUE;
                Thread *th = create_thread(inter, DEFINITION, val, NULL);
                create_definition(inter, token, th);
                inter->mode = NEUTRAL;
            }
        }
        else
        {
            if (strlen(token) < DEFINITION_NAME_SIZE)
            {
                Value val;
                val.type = NULL_VALUE;
                create_thread(inter, CALL_DEFINITION, val, token);
            }
        }
        endofloop = 0;
    }

    return endofloop;
}

void executer(Interpreter *inter)
{
    Thread *th = inter->thread_head;
    
    while(th)
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
                    push(inter, th->value);
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
                    pop(inter);
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
                    std_add(inter);
                    th = th->next;
                }
                break;
            case SUB:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    th = th->next;
                }
                else
                {
                    std_sub(inter);
                    th = th->next;
                }
                break;
            case MUL:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    th = th->next;
                }
                else
                {
                    std_mul(inter);
                    th = th->next;
                }
                break;
            case DIV:
                if (inter->mode == FUNC_DEFINITION)
                {
                    /* pass */
                    th = th->next;
                }
                else
                {
                    std_div(inter);
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
                    print_stack(inter);
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
                    }
                }
                else if (inter->mode == FUNC_DEFINITION)
                {
                    th = th->next;
                    inter->mode = NEUTRAL;
                }
                else
                {
                    th = th->next;
                }
                break;
            case CALL_DEFINITION:
                if (inter->mode == FUNC_DEFINITION)
                {
                    th = th->next;
                }
                else
                {
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

    return;
}

Interpreter *init_interpreter(void)
{
    Interpreter *inter;

    inter = (Interpreter*)malloc(sizeof(Interpreter));
    inter->stack_head = NULL;
    inter->thread_head = NULL;
    inter->definition_head = NULL;
    inter->mode = NEUTRAL;
    inter->call_stack_head = NULL;

    return inter;
}

Thread *create_thread(Interpreter *inter, RoutineType type, Value value, char *name)
{
    Thread *th;

    th = (Thread*)malloc(sizeof(Thread));
    th->type = type;
    th->value = value;
    if (name)
    {
        strcpy(th->definition_name, name);
    }
    th->next = NULL;

    Thread *p = inter->thread_head;

    if (p)
    {
        while(p->next)
        {
            p = p->next;
        }
        p->next = th;
    }
    else
    {
        inter->thread_head = th;
    }

    return th;
}

Definition *create_definition(Interpreter *inter, char *name, Thread *th)
{
    Definition *def;

    def = (Definition*)malloc(sizeof(Definition));
    if (name)
    {
        strcpy(def->name, name);
    }
    def->thread_head = th;
    def->next = NULL;

    Definition *p = inter->definition_head;

    if(p)
    {
        while(p->next)
        {
            p = p->next;
        }
        p->next = def;
    }
    else
    {
        inter->definition_head = def;
    }

    return def;
}

Definition *search_definition(Interpreter *inter, char *name)
{
    Definition *p = inter->definition_head;

    while (p)
    {
        if (strcmp(p->name, name) == 0)
        {
            break;
        }
        else
        {
            p = p->next;
        }
    }

    return p;
}

Thread *pop_call_stack(Interpreter *inter)
{
    Thread *th;
    CallStack *current_stack = inter->call_stack_head;
    CallStack *next_stack = current_stack->next;

    th = current_stack->return_p;

    inter->call_stack_head = next_stack;
    free(current_stack);

    return th;
}

void push_call_stack(Interpreter *inter, Thread *p)
{
    CallStack *new_stack;
    new_stack = (CallStack*)malloc(sizeof(CallStack));

    if (inter->call_stack_head)
    {
        new_stack->return_p = p;
        new_stack->next = inter->call_stack_head;
    }
    else
    {
        new_stack->return_p = p;
        new_stack->next = NULL;
    }

    inter->call_stack_head = new_stack;

    return;
}