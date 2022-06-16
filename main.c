/*************************************************************************************************
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned. I have constructed the
functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that
I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

 Aaron Nicholas Gumapac, DLSU ID# 12113495
*************************************************************************************************/
#include "include/database.h"
#include "include/dbstructs.h"
#include "include/interface.h"
#include "include/utils.h"

int
main()
{

  struct ImpressionDB iDB;
  struct SymptomDB sDB;

  ReferenceInput ref = " ";

  char exitFlag = 'E';
  char opt = ' ';

  // initialize necessary database structures
  initSymptomDB(&sDB);
  initImpressionDB(&iDB);

  do
  {
    clear();
    // display the interface
    interface(MAIN);

    // valid inputs are D, P, and E
    strcpy(ref, "DPE");
    inputHandler(CHAR, ref, (int *)&opt);

    switch (toUpper(opt))
    {
      case 'D':
        DoctorProcess(&sDB, &iDB);
        break;
      case 'P':
        PatientProcess(sDB, iDB);
        break;
      case 'E':
        printf("Exiting...\n");
        break;
    }

  } while (toUpper(opt) != exitFlag);

  return 0;
}
