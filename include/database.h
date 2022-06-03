
// ifndef guards
#ifndef DATABASE_H
#define DATABASE_H

#include "types.h"
#include <stdlib.h>
#include <string.h>

#define MAX_IMPRESSIONS 20
#define MAX_SYMPTOMS 20

typedef enum { MALE, FEMALE } GENDER;

struct Patient {
  int patientNumber;
  short age;
  String name;
  GENDER gender;
};

void initPatient(struct Patient);

struct Symptom {
  short id;
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
  short id;
  int correspondingSymptoms[MAX_IMPRESSIONS];
};
void initImpression(struct Impression);

struct ImpressionDB {
  int count;
  struct Impression database[];
};

void initImpressionDB(struct ImpressionDB);

#endif
