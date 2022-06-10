
// ifndef guards
#ifndef DATABASE_H
#define DATABASE_H

#include "dbstructs.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initSymptomDB(struct SymptomDB *db);

void initImpression(struct Impression *input);

void initPatient(struct Patient *p);

void initImpressionDB(struct ImpressionDB *db);

void readImpressionDB(struct ImpressionDB *db, const char *fileName);

void readSymptomDB(struct SymptomDB *db, const char *fileName);

void createNewImpressionDB(struct ImpressionDB *db, int num,
                           struct SymptomDB symptoms);

void createNewSymptomDB(struct SymptomDB *db, int num);

void writeSymptoms(struct SymptomDB *db, const char *fileName);
void writeImpressions(struct ImpressionDB *db, const char *fileName);

void modifyImpressionSymptoms(struct Impression *imp, struct SymptomDB db);

void initPatient(struct Patient *p);
void getPatient(struct Patient *p);

void getPatientImpressions(struct SymptomDB sDB, struct ImpressionDB iDB,
                           struct userImps *ui, struct userSymps *us);

struct Impression getImpressionFromID(struct ImpressionDB db, int ID);

void writeUserDetails(struct Patient p, struct userImps ui,
                      struct userSymps us);

void displayImpressionSymptoms(struct Impression imp, struct SymptomDB db);

void getAllImpressionIDs(struct ImpressionDB db, int *impressionIDs);

struct Impression getImpressionFromID(struct ImpressionDB db, int ID);

struct Impression getImpressionFromName(struct ImpressionDB db, char *name);

void DoctorProcess(struct SymptomDB *sDB, struct ImpressionDB *iDB);

void PatientProcess(struct SymptomDB sDB, struct ImpressionDB iDB);

#endif
