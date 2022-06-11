// ifndef guards
#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define pass printf("PASS\n")
#define MAX_VALID_INPUT_LEN 12

typedef enum { INT, DOUBLE, STRING, CHAR } TYPE;

void inputHandler(TYPE inputType, ReferenceInput ref, int *input);

int handleInt();

int isDigit(char c);

void sleepMs(int milliseconds);

void con();

char toUpper(char c);

char handleCh(ReferenceInput ref);

void drProcessor(char opt);

int affirmative(const char *question);

void clear();

void nullifyString(char *input);

int fileExists(const char *filename);

void getStr(char *input);

void trim(char *input);

int isFound(int *arr, int num, int target);

#endif
