#include "../include/database.h"
#include <stdio.h>
void
initImpression(struct Impression input) {
  struct Impression prototype = {
      .id = "-1\0",
      .name = "NIL\0",
  };
  input = prototype;
}

void
initImpressionDB(struct ImpressionDB db) {
  struct ImpressionDB prototype = {.count = 0};
  for (int i = 0; i < MAX_IMPRESSIONS; i++) {
    initImpression(prototype.database[i]);
  }

  db = prototype;
}

void
initSymptom(struct Symptom input) {
  struct Symptom prototype = {.id = -1, .name = "NIL", .question = "NIL"};
  input = prototype;
}

void
initSymptomDB(struct SymptomDB db) {
  printf("initializing database of size %d", db.count);
  struct SymptomDB prototype = {.count = 0};
  for (int i = 0; i < MAX_SYMPTOMS; i++) {
    initSymptom(prototype.database[i]);
  }

  // copy the contents of the prototype to the db
  db = prototype;
}

int
isDigit(char c) {
  return c >= '0' && c <= '9';
}

int
isNumerical(char *input) {
  int i = 0;
  while (input[i] != '\0') {
    if (!isDigit(input[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

// check if file exists
int
fileExists(char *fileName) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    fclose(file);
    return 0;
  }
  fclose(file);
  return 1;
}

// convert each space separated string to a symptom id
void
readSymptomsID(ID output[], char *input) {
  int i = 0;
  int j = 0;
  int k = 0;
  int inputlen = strlen(input);
  for (; i < inputlen - 1; i++) {
    // copy space separated substring input to ID at index
    if (input[i] == ' ') {
      // move to the next ID in output
      output[j][k] = '\0';
      k = 0;
      j++;
    } else {
      output[j][k] = input[i];
      k++;
    }
  }

  strcpy(output[j + 1], TERMINATING_STRING);
}

// print symptoms function
void
printSymptomIDs(struct Impression impression) {

  int i;
  i = 0;
  while (strcmp(impression.correspondingSymptoms[i], TERMINATING_STRING) != 0) {
    printf("%s ", impression.correspondingSymptoms[i]);
    i++;
  }
}

struct Impression
readImpression(char *fileName) {
  char line[100];
  FILE *file = fopen(fileName, "r");

  struct Impression prototype;
  initImpression(prototype);

  fgets(line, 100, file);
  strcpy(prototype.id, line);
  // get the name
  fgets(line, 100, file);
  strcpy(prototype.name, line);

  // get the string of corresponding symptoms
  fgets(line, 100, file);
  readSymptomsID(prototype.correspondingSymptoms, line);

  fclose(file);

  return prototype;
}

// Read impressions.txt with the format:

// <number of impressions>
// <Impression number – starts at 1>
// <Impression name>
// <List of Symptoms in numbers >
// <Impression number >
// <Impression name>
// <List of Symptoms in numbers >
// :
// <Impression number >
// <Impression name>
// <List of Symptoms in numbers >

// void
// readImpressions(struct ImpressionDB *db) {
//   // open Impressions.txt file
//   FILE *fp = fopen("Impressions.txt", "r");

//   char line[100];
//   fgets(line, 100, fp);
//   db->count = atoi(line);

//   // read the rest of the file
//   for (int i = 0; i < db->count; i++) {

//     // read the impression number
//     fgets(line, 100, fp);
//     db->database[i].id = atoi(line);

//     // read the impression name
//     fgets(line, 100, fp);
//     strcpy(db->database[i].name, line);

//     // read the list of symptoms separated by \n
//     fgets(line, 100, fp);
//     for (int j = 0; isNumerical(line); j++) {
//       db->database[i].correspondingSymptoms[j] = atoi(line);
//       fgets(line, 100, fp);
//     }
//   }
// }
