#include "../include/database.h"
#include "../include/interface.h"
#include "../include/utils.h"

/**
 * @Description : A function wrapper that encapsulates the entirety of the
 * doctor's tasks.
 *
 * @Param sDB - The symptom database.
 * @Param iDB - The impression database.
 */
void
DoctorProcess(struct SymptomDB *sDB, struct ImpressionDB *iDB)
{

  printf("\nMENU #2 Doctor\n\n");
  char opt = ' ', exitFlag = 'E';
  int count = 0, impressionID = -1;
  String impression = " ";
  int aff = 0;
  struct Impression imp;
  initImpression(&imp);
  ReferenceInput ref = " ";

  do {
    clear();

    interface(DOCTOR);
    strcpy(ref, "CUDME");
    inputHandler(CHAR, ref, (int *)&opt);

    // capitalize opt for consistency
    opt = toUpper(opt);
    while (
        opt == 'C' &&
        (aff = affirmative("This selection is potentially destructive") != 1)) {
      printf("Doctor please select another input: ");
      inputHandler(CHAR, ref, (int *)&opt);
    }
    switch (opt) {
      case 'C':
        printf("How many symptoms do you want to consider? ");
        strcpy(ref, " ");
        inputHandler(INT, ref, &count);
        createNewSymptomDB(sDB, count);
        printf("How many impressions do you want to consider? ");
        inputHandler(INT, ref, &count);
        createNewImpressionDB(iDB, count, *sDB);
        writeSymptoms(sDB, "Symptoms.txt");
        writeImpressions(iDB, "Impressions.txt");
        con();
        break;
      case 'U':
        if (fileExists("Symptoms.txt")) {
          readSymptomDB(sDB, "Symptoms.txt");
          printf("Symptoms successfully loaded.\n");
        }
        else {
          printf("\nNo symptoms found.\n");
        }

        if (fileExists("Impressions.txt")) {
          readImpressionDB(iDB, "Impressions.txt");
          printf("Impressions successfully loaded.\n");
        }
        else {
          printf("\nNo impressions found.\n");
        }
        getchar();
        con();
        break;
      case 'D':
        getchar();
        printf("\nWhat is the Impression?\n");
        getStr(impression);

        imp = getImpressionFromName(*iDB, impression);
        if (imp.id != TERMINATION_ID) {
          displayImpressionSymptoms(imp, *sDB);
        }
        else {
          printf("\nImpression not found.\n");
        }
        con();
        break;
      case 'M':
        getchar();
        printf("\nWhat is the Impression?\n");
        getStr(impression);
        imp = getImpressionFromName(*iDB, impression);
        if (imp.id == TERMINATION_ID) {
          printf("Impressin not found");
        }
        else {
          impressionID = imp.id;
          printf("\nYou can modify the symptoms of %s.\n", imp.name);
          printf("Below is the list of symptoms:\n");
          modifyImpressionSymptoms(&iDB->database[impressionID - 1], *sDB);
        }
        con();
        break;
      case 'E':
        printf("\nGoodbye Doctor!");
        break;
      default:
        printf("\nInvalid input.\n");
        break;
    }
    sleepMs(700);
  } while (opt != exitFlag);
}
