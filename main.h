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
    PRINT,
    JUMP,
    CALL,
    RET,
    HALT,
    THREAD_TYPE_COUNT
};

typedef struct {
    char name[DEFINITION_NAME_SIZE];
    int p;
} WordDefinition;

typedef struct {
    int mem[MEM_MAX];
    WordDefinition definition_list[DEFINITION_MAX];
    int thread;
    int call_stack;
    int data_stack;
    int endofloop;
} VM;

/* main.c */
void parser(char *token, FILE *fp);
void interpret(VM *vm, char *token);
void executer(VM *vm);
VM *init_VM(void);
void init_thread_list(void);
int search_definition(VM *vm, char *name);

#endif