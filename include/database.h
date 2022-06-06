
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

struct guessArray getGuessImpressions(struct SymptomDB syDB,
                                      struct ImpressionDB impDB);

struct Impression getImpressionFromID(struct ImpressionDB db, int ID);

struct Patient getPatient();

#endif
