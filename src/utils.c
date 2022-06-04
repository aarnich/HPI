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
  }

  return i;
}

char
handleCh(ReferenceInput ref) {
  char c = '\0';
  scanf(" %c", &c);
  while (strchr(ref, toUpper(c)) == NULL) {
    printf("Error: argument %c is not a valid character\n", c);
    scanf(" %c", &c);
  }

  return c;
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
    default:
      printf("Error: invalid input type\n");
      break;
  }
}

int
file_exists(char *filename) {
  FILE *file;
  if ((file = fopen(filename, "r"))) {
    fclose(file);
    return 1;
  }
  return 0;
}

void
createList() {
}

void
drProcessor(char opt) {
  switch (opt) {
    // creates a new list of symptoms and impressions
    case 'C':
      createList();
      break;
  }
}

void
affirmative(char *c, char danger, ReferenceInput ref) {
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
