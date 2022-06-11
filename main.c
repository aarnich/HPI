#include "include/database.h"
#include "include/dbstructs.h"
#include "include/interface.h"
#include "include/utils.h"

int
main()
{
  // initialize necessary database structures
  ReferenceInput ref = " ";
  char exitFlag = 'E';
  char opt = ' ';
  struct ImpressionDB iDB;
  struct SymptomDB sDB;

  initSymptomDB(&sDB);
  initImpressionDB(&iDB);

  do {
    clear();
    // display menu
    interface(MAIN);

    // get user input of type char
    strcpy(ref, "DPE");
    inputHandler(CHAR, ref, (int *)&opt);

    switch (toUpper(opt)) {
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
