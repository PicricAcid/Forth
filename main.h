#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"

#define DEFINITION_NAME_SIZE 32
#define DEFINITION_MAX 64
#define TH_MAX 64

enum {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    EQ,
    NEQ,
    GT,
    LT,
    GEQ,
    LEQ,
    PRINT,
    DUP,
    JUMP,
    CALL,
    RET,
    IF,
    HALT,
    THREAD_TYPE_COUNT
};

typedef enum {
    INTERPRETATION,
    COMPILATION,
    EXEC_MODE_COUNT
} ExecMode;

typedef struct {
    char name[DEFINITION_NAME_SIZE];
    int p;
} WordDefinition;

typedef struct {
    int mem[MEM_MAX];
    WordDefinition definition_list[DEFINITION_MAX];
    ExecMode mode;
    int thread;
    int call_stack;
    int data_stack;
    int word_definitions;
    int endofloop;
} VM;

/* main.c */
void parser(char *token, FILE *fp);
void interpreter(VM *vm, FILE *fp);
void executer(VM *vm);

VM *init_VM(void);
void init_thread_list(void);

void begin_def(VM *vm, char *token);
void end_def(VM *vm);
int search_definition(VM *vm, char *name);
#endif