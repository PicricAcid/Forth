#include "main.h"
#include "std_definitions.h"
#include "test.h"
#include "mem.h"

#define TOKEN_BUF_SIZE 32
#define TOKEN_LIST_BUF_SIZE 1024

/* global variables　*/
void (*thread_list[TH_MAX])(VM *vm);

int definition_p;

/* main.c */
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");

    VM *vm = (VM*)malloc(sizeof(VM));
    vm = init_VM();
    init_thread_list();

    interpreter(vm, fp);
    executer(vm);

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

void interpreter(VM *vm, FILE *fp)
{
    int get_name = 0;
    int buf_p = 0;
    int buf[64];

    while(1)
    {
        char token[TOKEN_BUF_SIZE];
        parser(token, fp);
        
        if (token[0] == '\0') break;
        /* word interpret */
        int word_p = search_definition(vm, token);

        if (word_p)
        {
            vm->mem[vm->thread++] = CALL;
            vm->mem[vm->thread++] = word_p;
            continue;
        }

        /* value interpret */
        int int_val = atoi(token);

        if (int_val) 
        {
            vm->mem[vm->thread++] = PUSH;
            vm->mem[vm->thread++] = int_val;
            continue;
        }
        if (strcmp(token, "0") == 0)
        {
            vm->mem[vm->thread++] = PUSH;
            vm->mem[vm->thread++] = 0;
            continue;
        }

        /* builtin word interpret */
        if (strcmp(token, ":") == 0)
        {
            get_name = 1;
            continue;
        }
        if (get_name)
        {
            get_name = 0;
            begin_def(vm, token);
            continue;
        }
        if (strcmp(token, ";") == 0)
        {
            end_def(vm);
            continue;
        }
        if (strcmp(token, "+") == 0) { vm->mem[vm->thread++] = ADD; continue;}
        if (strcmp(token, "-") == 0) { vm->mem[vm->thread++] = SUB; continue;}
        if (strcmp(token, "*") == 0) { vm->mem[vm->thread++] = MUL; continue;}
        if (strcmp(token, "/") == 0) { vm->mem[vm->thread++] = DIV; continue;}
        if (strcmp(token, "=") == 0) { vm->mem[vm->thread++] = EQ; continue;}
        if (strcmp(token, "/=") == 0) { vm->mem[vm->thread++] = NEQ; continue;}
        if (strcmp(token, "<") == 0) { vm->mem[vm->thread++] = GT; continue;}
        if (strcmp(token, ">") == 0) { vm->mem[vm->thread++] = LT; continue;}
        if (strcmp(token, "<=") == 0) { vm->mem[vm->thread++] = GEQ; continue;}
        if (strcmp(token, ">=") == 0) { vm->mem[vm->thread++] = LEQ; continue;}
        if (strcmp(token, ".") == 0) { vm->mem[vm->thread++] = PRINT; continue;}
        if (strcmp(token, "IF") == 0)
        {
            vm->mem[vm->thread++] = IF;
            buf[++buf_p] = vm->thread++;
            continue;
        }
        if (strcmp(token, "ELSE") == 0)
        {
            int tmp = buf[buf_p--];
            vm->mem[vm->thread++] = JUMP;
            buf[buf_p] = vm->thread++;
            vm->mem[tmp] = vm->thread;
            continue;
        }
        if (strcmp(token, "THEN") == 0)
        {
            int tmp = buf[buf_p--];
            vm->mem[tmp] = vm->thread;
            continue;
        }
        if (strcmp(token, "HALT") == 0) { vm->mem[vm->thread++] = HALT; break;}
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

    vm->mode = INTERPRETATION;
    vm->thread = MEM_BLOCK;
    vm->call_stack = MEM_BLOCK*2;
    vm->data_stack = MEM_BLOCK*3;
    vm->word_definitions = MEM_BLOCK*4;
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
    thread_list[EQ] = std_eq;
    thread_list[NEQ] = std_neq;
    thread_list[GT] = std_gt;
    thread_list[LT] = std_lt;
    thread_list[GEQ] = std_geq;
    thread_list[LEQ] = std_leq;
    thread_list[PRINT] = std_print;
    thread_list[JUMP] = std_jump;
    thread_list[CALL] = std_call;
    thread_list[RET] = std_return;
    thread_list[IF] = std_if;
    thread_list[HALT] = std_halt;

    return;
}

void begin_def(VM *vm, char *token)
{
    strcpy(vm->definition_list[definition_p].name, token);
    vm->definition_list[definition_p++].p = vm->word_definitions;

    int wd = vm->word_definitions;
    vm->word_definitions = vm->thread;
    vm->thread = wd;

    return;
}

void end_def(VM *vm)
{
    vm->mem[vm->thread++] = RET;

    int wd = vm->word_definitions;
    vm->word_definitions = vm->thread;
    vm->thread = wd;

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
