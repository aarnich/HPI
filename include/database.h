
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
#define ID_LEN 2

typedef enum { MALE, FEMALE } GENDER;

struct Patient {
  int patientNumber;
  short age;
  String name;
  GENDER gender;
};

void initPatient(struct Patient);

struct Symptom {
  ID id;
  String name;
  String question;
};

struct SymptomDB {
  int count;
  struct Symptom database[MAX_SYMPTOMS];
};

void initSymptomDB(struct SymptomDB);

struct Impression {
  String name;
  ID id;
  ID correspondingSymptoms[21];
};
void initImpression(struct Impression input);

struct ImpressionDB {
  int count;
  struct Impression database[];
};

void initImpressionDB(struct ImpressionDB db);

void readImpressionDB(struct ImpressionDB *db, const char *fileName);

void readSymptomDB(struct SymptomDB *db, const char *fileName);

struct ImpressionDB createNewImpressionDB(int num, struct SymptomDB symptoms);

struct SymptomDB createNewSymptomDB(int num);

void writeSymptoms(struct SymptomDB *db, const char *fileName);

#endif
