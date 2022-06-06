// ifndef guards
#ifndef DBSTRUCTS_H
#define DBSTRUCTS_H

#define MAX_IMPRESSIONS 20
#define MAX_SYMPTOMS 20
#define TERMINATING_STRING "-1"
#define TERMINATION_ID -1
#define ID_LEN 2

#include "types.h"

struct userSymps {
  int arr[MAX_SYMPTOMS];
  String symName[MAX_SYMPTOMS];
  int count;
};

struct userImps {
  int arr[MAX_IMPRESSIONS];
  String impName[MAX_IMPRESSIONS];
  int count;
};

struct Patient {
  String patientNumber;
  int age;
  String name;
  char gender;
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
