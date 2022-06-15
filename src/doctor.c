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

  // default welcoming message
  printf("\nMENU #2 Doctor\n\n");

  char opt = ' ', exitFlag = 'E';

  int count = 0, impressionID = -1, aff = 0;

  String impression = " ";
  ReferenceInput ref = " ";

  // initialize default impression
  struct Impression imp;
  initImpression(&imp);

  do
  {
    clear();

    interface(DOCTOR);
    strcpy(ref, "CUDSME");
    inputHandler(CHAR, ref, (int *)&opt);

    // capitalize opt for consistency
    opt = toUpper(opt);
    while (opt == 'C' &&
           (aff = affirmative(
                      "\n\nThis selection is potentially destructive\n") != 1))
    {
      printf("Since you're unsure, Doctor, please select another input: ");
      inputHandler(CHAR, ref, (int *)&opt);
      opt = toUpper(opt);
    }

    switch (opt)
    {
      case 'C':
        clear();
        // title card
        printf("\nCreate a new list of symptoms and impressions\n\n");

        // get number of symptoms from the user
        printf("How many symptoms do you want to consider? ");
        strcpy(ref, " ");
        inputHandler(INT, ref, &count);

        // create the symptom database from user input
        createNewSymptomDB(sDB, count);

        // save the symptom database to a file
        writeSymptoms(sDB, "Symptoms.txt");

        // create the impression database from user input
        clear();

        // get number of symptoms from the user
        printf("\n\nHow many impressions do you want to consider? ");
        inputHandler(INT, ref, &count);

        createNewImpressionDB(iDB, count, *sDB);

        // save the impression database to a file
        writeImpressions(iDB, "Impressions.txt");

        // prompt the user to continue
        con();
        break;
      case 'U':
        if (fileExists("Symptoms.txt"))
        {
          readSymptomDB(sDB, "Symptoms.txt");
          printf("Symptoms successfully loaded.\n");
        }
        else
          printf("\nNo symptoms found.\n");

        if (fileExists("Impressions.txt"))
        {
          readImpressionDB(iDB, "Impressions.txt");
          printf("Impressions successfully loaded.\n");
        }
        else
          printf("\nNo impressions found.\n");

        // clear extra newline character
        getchar();

        // prompt the user to continue
        con();

        // exit the loop, under the assumption that after this option, the
        // patient will input their details
        opt = exitFlag;
        break;
      case 'D':
        clear();
        // title card
        printf("\nDisplay symptoms\n\n");
        // clear extra newline character
        getchar();

        // get the symptom name from the user
        printf("\nWhat is the Impression?\n");
        getStr(impression);

        // create temporary prototype impression
        imp = getImpressionFromName(*iDB, impression);
        if (imp.id != TERMINATION_ID)
          displayImpressionSymptoms(imp, *sDB);

        else
          printf("\nImpression not found.\n");

        con();
        break;
      case 'S':
        clear();
        // title card
        printf("\nShow Impressions.txt and Symptoms.txt\n\n");
        // clear extra newline character
        getchar();

        printf("\n\n--- Symptoms.txt ---\n\n");
        if (fileExists("Symptoms.txt"))
          printFile("Symptoms.txt");
        else
          printf("\nFILE NOT FOUND.\n");

        printf("\n\n--- Impressions.txt ---\n\n");
        if (fileExists("Impressions.txt"))
          printFile("Impressions.txt");
        else
          printf("\nFILE NOT FOUND.\n");

        con();
        break;
      case 'M':
        clear();
        // title card
        printf("\nModify symptoms\n\n");
        // clear extra newline character
        getchar();

        // get the symptom name from the user
        printf("\nWhat is the impression?\n");
        getStr(impression);

        // create temporary prototype impression
        imp = getImpressionFromName(*iDB, impression);
        if (imp.id == TERMINATION_ID)
          printf("impression not found");

        else
        {
          // if the impression exists, ask the user to modify its symptoms
          impressionID = imp.id;
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
    // sleep to slowdown input
    sleepMs(700);
  } while (opt != exitFlag);
}
