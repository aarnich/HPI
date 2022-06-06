// ifndef guards
#ifndef DBSTRUCTS_H
#define DBSTRUCTS_H

#define MAX_IMPRESSIONS 20
#define MAX_SYMPTOMS 20
#define TERMINATING_STRING "-1"
#define TERMINATION_ID -1
#define ID_LEN 2

#include "types.h"
typedef enum { MALE, FEMALE, NIL } GENDER;

struct guessArray {
  int count;
  String Impression[MAX_IMPRESSIONS];
};

struct Patient {
  int patientNumber;
  short age;
  String name;
  GENDER gender;
};

struct Symptom {
  int id;
  String name;
  String question;
};

struct SymptomDB {
  int count;
  struct Symptom database[MAX_SYMPTOMS];
};

struct Impression {
  String name;
  int id;
  int sympCount;
  int correspondingSymptoms[MAX_SYMPTOMS + 1];
};

struct ImpressionDB {
  int count;
  struct Impression database[MAX_IMPRESSIONS];
};

#endif
