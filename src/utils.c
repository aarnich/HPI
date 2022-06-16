#include "../include/utils.h"

/**
 * @Description : Clears the terminal screen
 */
void
clear()
{
  printf("\e[1;1H\e[2J");
}

/**
 * @Description : Prints all the contents of a given file if it exists
 *
 * @Param fileName - the name of the file to be printed
 */
void
printFile(const char *fileName)
{
  FILE *fp;
  char c;
  fp = fopen(fileName, "r");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  while ((c = fgetc(fp)) != EOF)
  {
    printf("%c", c);
  }
  fclose(fp);
}

/**
 * @Description : Determines whether a given character is a digit
 *
 * @Param c - the character to be checked
 *
 * @Returns - 1 if the character is a digit, 0 otherwise
 */
int
isDigit(char c)
{
  return c >= '0' && c <= '9';
}

/**
 * @Description : Nullifies a string by setting all characters to '\0'
 *
 * @Param input - the string to be nullified
 */
void
nullifyString(char *input)
{
  int i, len;
  i = 0;

  len = strlen(input);
  for (; i < len; i++)
    input[i] = '\0';
}

/**
 * @Description : Sleeps the program for a given number of miliseconds
 *
 * @Param milliseconds - the number of miliseconds to sleep
 */
void
sleepMs(int milliseconds)
{
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

/**
 * @Description : Capitalizes a given character
 *
 * @Param c - the character to be capitalized
 *
 * @Returns : the capitalized character
 */
char
toUpper(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 'A';

  return c;
}

/**
 * @Description : Asks the user to continue with the program
 */
void
con()
{
  printf("\n\nPress [[ENTER]] to continue");
  getchar();
}

/**
 * @Description : handles an input of type INT
 *
 * @Returns : A valid inteeer
 */
int
handleInt()
{
  int i;
  int ch = 0;
  while (scanf(" %d", &i) != 1)
  {
    printf("Error: argument %d is not an integer\n", i);
    printf("Please enter a valid number: ");
    // clear the buffer
    while ((ch = getchar()) != '\n' && ch != EOF)
      ;
  }

  return i;
}

/**
 * @Description : handles an input of type CHAR and checks whether the character
 * is valid
 *
 * @Param ref - the reference string that limits valid characters
 *
 * @Returns : a character within the referenceInput
 */
char
handleCh(ReferenceInput ref)
{
  char c = '\0';
  scanf(" %c", &c);
  while (strchr(ref, toUpper(c)) == NULL)
  {
    printf("Error: argument %c is not a valid character\n", c);
    printf("Please enter a valid character: ");
    scanf(" %c", &c);
  }

  return c;
}

/**
 * @Description : handles an input of type STRING and checks whether the string
 * is a substring of the referenceInput
 *
 * @Param ref - the reference string that limits valid characters
 * @Param input - the string to be checked
 */
void
handleStr(ReferenceInput ref, char *input)
{
  String str;
  getStr(str);

  // locate str substring inside ref
  while (strstr(ref, str) == NULL)
  {
    printf("Not in dataset, try again\n");
    getStr(str);
  }

  strcpy(input, str);
}

/**
 * @Description : Handles input for the program
 *
 * @Param inputType - the type of input to be handled
 * @Param ref - the reference string that contains valid characters, optional
 * for INT
 * @Param input - the string to be handled
 */
void
inputHandler(TYPE inputType, ReferenceInput ref, int *input)
{
  switch (inputType)
  {
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

/**
 * @Description : Checks whether a file exists in the directory
 *
 * @Param filename - the name of the file to be checked
 *
 * @Returns : 1 if the file exists, 0 otherwise
 */
int
fileExists(const char *filename)
{
  FILE *file;
  int retval;

  retval = 0;
  if ((file = fopen(filename, "r")))
  {
    fclose(file);
    retval = 1;
  }

  return retval;
}

/**
 * @Description : Gets a string from the user
 *
 * @Param input - the address of the string to be filled
 */
void
getStr(char *input)
{
  char temp[MAX_STRING_LEN + 1];
  fgets(temp, MAX_STRING_LEN + 1, stdin);
  trim(temp);
  strcpy(input, temp);
}

/**
 * @Description : Confirms the user's input
 *
 * @Param question - the question to be asked
 *
 * @Returns : 1 if the user confirms, 0 otherwise
 */
int
affirmative(const char *question)
{
  int retval = 0;
  String ans = " ";
  printf("%s\ntype YES (capitalized) if you're sure:\n\n", question);

  getchar();
  getStr(ans);

  if (strcmp(ans, "YES") == 0)
    retval = 1;

  return retval;
}

/**
 * @Description : Removes newlines and spaces from the end of a string
 *
 * @Param input - the string to be trimmed
 */
void
trim(char *input)
{
  input[strcspn(input, "\n")] = 0;
}

/**
 * @Description : Checks whether an integer is found within the given array
 *
 * @Param arr - the array containing valid integers
 * @Param num - the number of elements in the array
 * @Param target - the integer to be checked
 *
 * @Returns : 1 if the integer is found, 0 otherwise
 */
int
isFound(int *arr, int num, int target)
{
  int retval, i;

  retval = 0;
  for (i = 0; i < num; i++)
    if (arr[i] == target)
      retval = 1;

  return retval;
}
