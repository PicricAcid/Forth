#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "main.h"

/* definitions.c */
Value pop(Interpreter *inter);
void push(Interpreter *inter, Value val);
int std_add(Interpreter *inter);
int std_sub(Interpreter *inter);
int std_mul(Interpreter *inter);
int std_div(Interpreter *inter);

/*
void add_int(Interpreter *inter);
*/

/*
void print_int_value(Value val);
*/

#endif