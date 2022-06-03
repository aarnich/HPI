#include "../include/utils.h"

int
handleInt() {
  int i;
  while (scanf("%d", &i) != 1) {
    printf("Error: argument %d is not an integer\n", i);
  }

  return i;
}

char
handleCh(ReferenceInput ref) {
  char c = '\0';
  scanf("%c", &c);
  while (strchr(ref, c) == NULL) {
    printf("Error: argument %c is not a valid character\n", c);
    scanf("%c", &c);
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
