// ifndef guards
#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define pass printf("PASS\n")
#define MAX_VALID_INPUT_LEN 12
typedef enum { INT, DOUBLE, STRING, CHAR } TYPE;

// inputHandler is a wrapper function for lower ordered inputhandlers
// Params: inputType - the type of input to be handled
//         input - the address where user input is stored
//         ref - valid input expected by the user
void inputHandler(TYPE inputType, ReferenceInput ref, int *input);

// handleInt is a function that handles integer input and must always return a
// valid integer
// Returns: the integer input by the user
int handleInt();

char handleCh(ReferenceInput ref);

void drProcessor(char opt);

// this function makes sure user input is deliberate
void affirmative(char *c, char danger, ReferenceInput ref);

int fileExists(const char *filename);

void empty_stdin(void);

void getStr(char *input);

#endif
