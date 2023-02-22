#include "main.h"
#include "std_definitions.h"
#include "test.h"
#include "mem.h"

#define TOKEN_BUF_SIZE 32
#define TOKEN_LIST_BUF_SIZE 1024

/* global variables　*/
void (*thread_list[TH_MAX])(VM *vm);

int get_name;
int definition_p;
int endofloop;

int main(int argc, char *argv[])
{
    char token[TOKEN_BUF_SIZE];
    VM *vm;

    FILE *fp;

    fp = fopen(argv[1], "r");

    init_thread_list();

    vm = init_VM();

    while (1)
    {   
        parser(token, fp);
        interpret(vm, token);

        if (token[0] == '\0' || endofloop)
        {
            break;
        }
    }

    fclose(fp);

    executer(vm);
    /* print_thread(vm); */
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

    return;
}

void interpret(VM *vm, char *token)
{
    int int_val;

    int_val = atoi(token);
    if (int_val)
    {
        vm->mem[vm->thread++] = PUSH;
        vm->mem[vm->thread++] = int_val;
    }
    else if (strcmp(token, "0") == 0)
    {
        vm->mem[vm->thread++] = PUSH;
        vm->mem[vm->thread++] = 0;
    }
    else if (strcmp(token, "+") == 0)
    {
        vm->mem[vm->thread++] = ADD;
    }
    else if (strcmp(token, "-") == 0)
    {
        vm->mem[vm->thread++] = SUB;
    }
    else if (strcmp(token, "*") == 0)
    {
        vm->mem[vm->thread++] = MUL;
    }
    else if (strcmp(token, "/") == 0)
    {
        vm->mem[vm->thread++] = DIV;
    }
    else if (strcmp(token, ".") == 0)
    {
        vm->mem[vm->thread++] = PRINT;
    }
    else if (strcmp(token, ":") == 0)
    {
        get_name = 1;
    }
    else if (strcmp(token, ";") == 0)
    {
        vm->mem[vm->thread++] = RET;
    }
    else if (strcmp(token, "HALT") == 0)
    {
        vm->mem[vm->thread++] = HALT;
        endofloop = 1;
    }
    else
    {
        if (get_name)
        {
            if (strlen(token) < DEFINITION_NAME_SIZE)
            {
                get_name = 0;

                strcpy(vm->definition_list[definition_p].name, token);
                vm->definition_list[definition_p++].p = vm->thread;
            }
        }
        else
        {
            if (strlen(token) < DEFINITION_NAME_SIZE)
            {
                int call_p = search_definition(vm, token);
                vm->mem[vm->thread++] = CALL;
                vm->mem[vm->thread++] = call_p;
            }
        }
    }

    return;
}

void executer(VM *vm)
{
    vm->thread = MEM_BLOCK;
    while(!vm->endofloop)
    {
        (*thread_list[vm->mem[vm->thread++]])(vm);
    }

    return;
}

VM *init_VM(void)
{
    VM *vm;
    vm = (VM*)malloc(sizeof(VM));
    vm->thread = MEM_BLOCK;
    vm->call_stack = MEM_BLOCK*2;
    vm->data_stack = MEM_BLOCK*3;
    vm->endofloop = 0;

    return vm;
}

void init_thread_list(void)
{
    thread_list[PUSH] = std_push;
    thread_list[POP] = std_pop;
    thread_list[ADD] = std_add;
    thread_list[SUB] = std_sub;
    thread_list[MUL] = std_mul;
    thread_list[DIV] = std_div;
    thread_list[PRINT] = std_print;
    thread_list[JUMP] = std_jump;
    thread_list[CALL] = std_call;
    thread_list[RET] = std_return;
    thread_list[HALT] = std_halt;

    return;
}

int search_definition(VM *vm, char *name)
{
    int result = 0;

    for (int p = 0; p < definition_p; p++)
    {
        if (strcmp(vm->definition_list[p].name, name) == 0)
        {
            result = vm->definition_list[p].p;
            break;
        }
    }

    return result;
}