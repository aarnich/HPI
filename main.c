#include "include/database.h"
#include "include/dbstructs.h"
#include "include/interface.h"
#include "include/utils.h"

int
main() {
  struct ImpressionDB iDB;
  struct SymptomDB sDB;

  // createNewSymptomDB(&sDB, 3);
  // createNewImpressionDB(&iDB, 3, sDB);

  // writeSymptoms(&sDB, "Symptoms.txt");

  readSymptomDB(&sDB, "Symptoms.txt");
  // createNewImpressionDB(&iDB, 3, sDB);
  // writeImpressions(&iDB, "Impressions.txt");
  readImpressionDB(&iDB, "Impressions.txt");

  struct guessArray ga = getGuessImpressions(sDB, iDB);
  // print all impressions inside ga

  return 0;
}
