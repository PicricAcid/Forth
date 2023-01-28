#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "main.h"

/* definitions.c */
int pop(Interpreter *inter);
void push(Interpreter *inter, int val);
int add(Interpreter *inter);
int sub(Interpreter *inter);

/*
void add_int(Interpreter *inter);
*/

/*
void print_int_value(Value val);
*/

#endif