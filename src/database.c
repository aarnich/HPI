#include "../include/database.h"
#include <stdio.h>
void
initImpression(struct Impression input) {

  int idIndex = 0;
  struct Impression prototype = {
      .id = TERMINATING_STRING,
      .name = "NIL",
  };

  for (; idIndex <= MAX_SYMPTOMS; idIndex++) {
    strcpy(prototype.correspondingSymptoms[idIndex], TERMINATING_STRING);
  }
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
readImpression(char *fileName, FILE *file) {

  struct Impression prototype;
  initImpression(prototype);

  char id[10];
  fgets(id, 10, file);
  strcpy(prototype.id, id);
  // get the name

  char name[MAX_STRING];
  fgets(name, MAX_STRING, file);
  strcpy(prototype.name, name);

  // get the string of corresponding symptoms
  char symptoms[100];
  fgets(symptoms, 100, file);
  readSymptomsID(prototype.correspondingSymptoms, symptoms);

  return prototype;
}

void
readImpressions(struct ImpressionDB *db) {
  // open Impressions.txt file
  FILE *file = fopen("impression.txt", "r");
  char line[100];
  fgets(line, 100, file);
  db->count = atoi(line);

  // read the rest of the file
  int i;
  for (i = 0; i < db->count - 1; i++) {
    db->database[i] = readImpression("impression.txt", file);
  }
  fclose(file);
}
