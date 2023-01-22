#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFINITION_NAME_SIZE 24

typedef enum {
    PUSH,
    POP,
    ADD,
    PRINT,
    DEFINITION,
    DEFINITION_END,
    CALL_DEFINITION,
    HALT,
    ROUTINE_TYPE_COUNT
} RoutineType;

typedef enum {
    NEUTRAL,
    GET_NAME,
    FUNC_DEFINITION,
    CALL_FUNC,
    EXECUTE_MODE_COUNT
} ExecuteMode;

typedef struct Stack_mold {
    int val;
    struct Stack_mold *next;
} Stack;

typedef struct Thread_mold {
    RoutineType type;
    int value;
    char definition_name[DEFINITION_NAME_SIZE];
    struct Thread_mold *next;
} Thread;

typedef struct Definition_mold {
    char name[DEFINITION_NAME_SIZE];
    Thread *thread_head;
    struct Definition_mold *next;
} Definition;

typedef struct {
    Stack *stack_head;
    Thread *thread_head;
    Definition *definition_head;
    ExecuteMode mode;
    Thread *origin;
} Interpreter;

/* main.c */
void parser(char *token, FILE *fp);
int interpret(Interpreter *inter, char *token);
void executer(Interpreter *inter);
Interpreter *init_interpreter(void);
Thread *create_thread(Interpreter *inter, RoutineType type, int value, char *name);
Definition *create_definition(Interpreter *inter, char *name, Thread *th);
Definition *search_definition(Interpreter *inter, char *name);


#endif