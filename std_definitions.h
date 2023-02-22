#ifndef STD_DEFINITIONS_H
#define STD_DEFINITIONS_H

#include "main.h"

/* std_definitions.c */
void std_pop(VM *vm);
void std_push(VM *vm);
void std_add(VM *vm);
void std_sub(VM *vm);
void std_mul(VM *vm);
void std_div(VM *vm);
void std_print(VM *vm);
void std_jump(VM *vm);
void std_call(VM *vm);
void std_return(VM *vm);
void std_halt(VM *vm);

#endif