#include "types.h"

typedef enum { MALE, FEMALE } GENDER;

struct Patient {
  int patientNumber;
  short age;
  String name;
  GENDER gender;
};

void initPatient(struct Patient);

struct SymptomDB {
  int count;

  struct Symptom {
    short id;
    String name;
    String question;
  } Symptom;

  struct Symptom database[];
};

void initSymptomDB(struct SymptomDB *);

struct Impression {
  String name;
  short id;
  int correspondingSymptoms[];
};

struct ImpressionDB {
  int count;
  struct Impression database[];
};

void initImpressionDB(struct ImpressionDB *);
