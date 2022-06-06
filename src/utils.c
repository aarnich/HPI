#include "../include/utils.h"

// char to upper function
char
toUpper(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 'A';
  }
  return c;
}

int
handleInt() {
  int i;
  while (scanf(" %d", &i) != 1) {
    printf("Error: argument %d is not an integer\n", i);
    printf("Please enter a valid number: ");
    emptyStdin();
  }

  return i;
}

char
handleCh(ReferenceInput ref) {
  char c = '\0';
  scanf(" %c", &c);
  while (strchr(ref, toUpper(c)) == NULL) {
    printf("Error: argument %c is not a valid character\n", c);
    printf("Please enter a valid character: ");
    scanf(" %c", &c);
  }

  return c;
}

void
handleStr(ReferenceInput ref, char *input) {
  String str;
  getStr(str);

  // locate str substring inside ref
  while (strstr(ref, str) == NULL) {
    printf("Not in dataset, try again\n");
    getStr(str);
  }
  strcpy(input, str);
}

void
inputHandler(TYPE inputType, ReferenceInput ref, int *input) {
  switch (inputType) {
    case INT:
      *input = handleInt();
      break;
    case CHAR:
      *(char *)input = handleCh(ref);
      break;
    case STRING:
      handleStr(ref, (char *)input);
      break;
    default:
      printf("Error: invalid input type\n");
      break;
  }
}

int
fileExists(const char *filename) {
  FILE *file;
  if ((file = fopen(filename, "r"))) {
    fclose(file);
    return 1;
  }
  return 0;
}

void
getStr(char *input) {
  scanf(" %49[0-9a-zA-Z ]", input);
}

void
affirmative(char *c, ReferenceInput ref) {
  int sure = 0;
  char answer;
  while (!sure) {
    printf(
        "\nThis selection is potentially destructive, are you sure? (Y/N): ");
    ReferenceInput answerRef = "YN";
    inputHandler(CHAR, answerRef, (int *)&answer);
    if (answer == 'Y')
      sure = 1;
    else {
      printf("\nPlease select another input:");
      inputHandler(CHAR, ref, (int *)c);
    }
  }
}

void
emptyStdin(void) {
  int c = getchar();

  while (c != '\n' && c != EOF)
    c = getchar();
}

void
trim(char *input) {
  input[strcspn(input, "\n")] = 0;
}
