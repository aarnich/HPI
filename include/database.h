
// ifndef guards
#ifndef DATABASE_H
#define DATABASE_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IMPRESSIONS 20
#define MAX_SYMPTOMS 20
#define TERMINATING_STRING "-1"
#define TERMINATION_ID -1
#define ID_LEN 2

typedef enum { MALE, FEMALE } GENDER;

struct Patient {
  int patientNumber;
  short age;
  String name;
  GENDER gender;
};

void initPatient(struct Patient *p);

struct Symptom {
  ID id;
  String name;
  String question;
};

struct SymptomDB {
  int count;
  struct Symptom database[MAX_SYMPTOMS];
};

void initSymptomDB(struct SymptomDB *db);

struct Impression {
  String name;
  int id;
  int correspondingSymptoms[21];
};
void initImpression(struct Impression *input);

struct ImpressionDB {
  int count;
  struct Impression database[MAX_IMPRESSIONS];
};

void initImpressionDB(struct ImpressionDB *db);

void readImpressionDB(struct ImpressionDB *db, const char *fileName);

void readSymptomDB(struct SymptomDB *db, const char *fileName);

void createNewImpressionDB(struct ImpressionDB *db, int num,
                           struct SymptomDB symptoms);

void createNewSymptomDB(struct SymptomDB *db, int num);

void writeSymptoms(struct SymptomDB *db, const char *fileName);
void writeImpressions(struct ImpressionDB *db, const char *fileName);

#endif
