#include "../include/utils.h"

void
clear() {
  printf("\e[1;1H\e[2J");
}

void
sleepMs(int milliseconds) {
  fflush(stdout);
#ifdef WIN32 // if the current system is a windows system
  Sleep(milliseconds);
#elif _POSIX_C_SOURCE >=                                                       \
    199309L // if the current system is posix compliant (linux/mac)
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
#else       // if the current system is neither, use system directives
  if (milliseconds >= 1000)
    sleep(milliseconds / 1000);
#endif
}
// char to upper function
char
toUpper(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 'A';
  }
  return c;
}

void
con() {
  printf("\n\nPress [[ENTER]] to continue");
  getchar();
}

int
handleInt() {
  int i;
  int ch = 0;
  while (scanf(" %d", &i) != 1) {
    printf("Error: argument %d is not an integer\n", i);
    printf("Please enter a valid number: ");
    while ((ch = getchar()) != '\n' && ch != EOF)
      ;
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
  int retval;

  retval = 0;
  if ((file = fopen(filename, "r"))) {
    fclose(file);
    retval = 1;
  }

  return retval;
}

void
getStr(char *input) {
  char temp[MAX_STRING_LEN + 1];
  fgets(temp, MAX_STRING_LEN + 1, stdin);
  trim(temp);
  strcpy(input, temp);
}

int
affirmative(const char *question) {
  int retval;

  retval = 0;
  String ans = " ";
  printf("%s\ntype YES (capitalized) if you're sure:\n", question);

  getchar();
  getStr(ans);

  if (strcmp(ans, "YES") == 0) {
    retval = 1;
  }

  return retval;
}

void
trim(char *input) {
  input[strcspn(input, "\n")] = 0;
}

// check if integer is inside array
int
isFound(int *arr, int num, int target) {
  int retval, i;

  retval = 0;
  for (i = 0; i < num; i++) {
    if (arr[i] == target) {
      retval = 1;
    }
  }

  return retval;
}
