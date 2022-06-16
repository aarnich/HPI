#include <stdio.h>
#include <stdlib.h>
int
inputHanlder(int min, int max)
{
  int input;
  scanf("%d", &input);
  while (input < min || input > max)
  {
    printf("Invalid input. ");
    scanf("%d", &input);
  }

  return input;
}
void
startEnglish()
{
  system("./hpi");
}

void
startArabic()
{
  system("./hpi_ar");
}
int
main()
{
  int exitflag = 0;
  int selection;
  printf("\nWelcome to the HPI!\n\n");
  do
  {
    printf("[1] Start\n");
    printf("[2] Credits\n");
    printf("[3] Exit\n\n");
    printf("Selection: ");

    switch (selection = inputHanlder(1, 3))
    {
      case 1:
        printf("\nStarting...\n");
        printf("Please select your language\n");
        printf("[1] English\n");
        printf("[2] Arabic\n");
        printf("[3] Exit\n\n");
        switch (inputHanlder(1, 3))
        {
          case 1:
            startEnglish();
            break;
          case 2:
            printf("\nArabic not yet supported\n");
            break;
          case 3:
            exitflag = 1;
            break;
        }
        break;
      case 2:
        printf("\nCredits:\n");
        printf("\nHPI is a project made by:\n");
        printf("Aaron Nicholas Gumapac of ID121\n");
        break;
      case 3:
        exitflag = 1;
        break;
      default:
        printf("\nInvalid input\n");
        break;
    }
  } while (selection != exitflag);

  return 0;
}
