// ifndef guards
#ifndef DBSTRUCTS_H
#define DBSTRUCTS_H

#define MAX_IMPRESSIONS 20
#define MAX_SYMPTOMS 20
#define TERMINATING_STRING "-1"
#define TERMINATION_ID -1
#define ID_LEN 2

#include "types.h"

/**
 * @Description : Stores the data for Patient symptoms
 * @Attribute int* arr - Array of symptom IDs
 * @Attribute String* arr - Array of symptom names
 * @Attribute int count - Number of symptoms
 */
struct userSymps {
  int arr[MAX_SYMPTOMS];
  String symName[MAX_SYMPTOMS];
  int count;
};

/**
 * @Description : Stores the data for Patient impressions
 * @Attribute int* arr - Stores impression IDs
 * @Attribute String* impName - Stores impression names
 * @Attribute int count - Stores the number of impressions
 */
struct userImps {
  int arr[MAX_IMPRESSIONS];
  String impName[MAX_IMPRESSIONS];
  int count;
};

/**
 * @Description : Stores innate patient data
 * @Attribute int age - age of the patient
 * @Attribute int height - height of the patient
 * @Attribute String patientNumber - patient number of the patient
 * @Attribute char gender - the patient's gendder represented by M/F
 */
struct Patient {
  String patientNumber;
  int age;
  String name;
  char gender;
};

/**
 * @Description : Default symptom type
 * @Attribute int id - the ID used to identify the symptom
 * @Attribute String name - the symptom's name
 * @Attribute String question - question that is asked to confirm the existence
 * of the symptom
 */
struct Symptom {
  int id;
  String name;
  String question;
};

/**
 * @Description : Symptom database
 * @Attribute count - the number of symptoms in the database
 * @Attribute database - the array containing the symptoms
 */
struct SymptomDB {
  int count;
  struct Symptom database[MAX_SYMPTOMS];
};

/**
 * @Description : Default impression type
 * @Attribute int id - the ID used to identify the impression
 * @Attribute String name - the impression's name
 * @Attribute int sympCount - the number of symptoms associated with the
 * impression
 * @Attribute int* correspondingSymptoms - the array containing the symptom IDs
 * for all symptoms associated with the impression
 */
struct Impression {
  String name;
  int id;
  int sympCount;
  int correspondingSymptoms[MAX_SYMPTOMS + 1];
};

/**
 * @Description : Impression database
 * @Attribute int count - the number of impressions in the database
 * @Attribute Impression* - database - the array containing the impressions
 */
struct ImpressionDB {
  int count;
  struct Impression database[MAX_IMPRESSIONS];
};

#endif
