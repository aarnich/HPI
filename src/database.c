#include "../include/database.h"
#include "../include/utils.h"
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
  struct Symptom prototype = {.id = "-1", .name = "NIL", .question = "NIL"};
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
readImpression(const char *fileName, FILE *file) {

  struct Impression prototype;
  initImpression(prototype);

  ID id;
  fgets(id, 10, file);
  strcpy(prototype.id, id);
  // get the name

  String name;
  fgets(name, MAX_STRING_LEN, file);
  strcpy(prototype.name, name);

  // get the string of corresponding symptoms
  char symptoms[100];
  fgets(symptoms, 100, file);
  readSymptomsID(prototype.correspondingSymptoms, symptoms);

  return prototype;
}

struct Symptom
readSymptom(const char *fileName, FILE *file) {

  struct Symptom prototype;
  initSymptom(prototype);

  ID id;
  fgets(id, 10, file);
  strcpy(prototype.id, id);

  String name;
  fgets(name, MAX_STRING_LEN, file);
  strcpy(prototype.name, name);

  String question;
  fgets(question, MAX_STRING_LEN, file);
  strcpy(prototype.question, question);

  return prototype;
}

void
readSymptomDB(struct SymptomDB *db, const char *fileName) {

  FILE *file = fopen(fileName, "r");
  char count[ID_LEN];
  fgets(count, ID_LEN, file);
  db->count = atoi(count);

  // read the rest of the file
  for (int i = 0; i < db->count - 1; i++) {
    db->database[i] = readSymptom(fileName, file);
  }

  fclose(file);
}

void
readImpressionDB(struct ImpressionDB *db, const char *fileName) {
  // open Impressions.txt file
  FILE *file = fopen(fileName, "r");
  char line[ID_LEN];
  fgets(line, ID_LEN, file);
  db->count = atoi(line);

  // read the rest of the file
  int i;
  for (i = 0; i < db->count - 1; i++) {
    db->database[i] = readImpression(fileName, file);
  }
  fclose(file);
}

void
writeSymptoms(struct SymptomDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);
  for (int i = 0; i < db->count; i++) {
    fprintf(file, "\n%s", db->database[i].id);
    fprintf(file, "\n%s", db->database[i].name);
    fprintf(file, "\n%s", db->database[i].question);
  }
  fclose(file);
}

void
writeImpressions(struct ImpressionDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);
  for (int i = 0; i < db->count; i++) {
    fprintf(file, "\n%s", db->database[i].id);
    fprintf(file, "\n%s", db->database[i].name);
    while (strcmp(db->database[i].correspondingSymptoms[i],
                  TERMINATING_STRING) != 0) {
      fprintf(file, "\n%s", db->database[i].correspondingSymptoms[i]);
    }
  }
  fclose(file);
}

// convert integer  to string
void
toString(int input, char *output) {
  sprintf(output, "%d", input);
}

// check if valid string
int
isValidString(char *input) {
  int retval;

  retval = 1;
  if (input[0] == '\0')
    retval = 0;
  else if (input[0] == '\n')
    retval = 0;

  return retval;
}

void
printSymptoms(struct SymptomDB db, int *symptomArr) {
  for (int i = 0; i < db.count; i++) {
    printf("%s. %s\n", db.database[i].id, db.database[i].name);
    symptomArr[i] = atoi(db.database[i].id);
  }
}

struct SymptomDB
createNewSymptomDB(int num) {
  struct SymptomDB db;
  initSymptomDB(db);

  int i, idNum;
  String temp;

  idNum = 0;
  struct Symptom symptom;
  for (i = 0; i < num; i++) {
    initSymptom(symptom);

    idNum = i + 1;
    printf("\n#############################");
    printf("\nSymptom Number: %d\n", idNum);
    toString(idNum, symptom.id);

    // check if valid string input

    printf("\nWhat is the symptom? ");
    getStr(temp);
    printf("\ntemp : %s\n", temp);

    empty_stdin();
    while (!isValidString(temp)) {

      printf("Invalid input. Please try again.\n");
      printf("What is the symptom? ");
      getStr(temp);
    }
    strcpy(symptom.name, temp);

    printf("\nHow do you want to ask about the symptom?\n");
    getStr(temp);
    while (!isValidString(temp)) {

      printf("Invalid input. Please try again.");
      printf("\nHow do you want to ask about the symptom?\n");

      getStr(temp);
    }

    db.database[i] = symptom;
    db.count++;

    empty_stdin();
  }

  return db;
}

// check if integer is inside array
int
isFound(int *arr, int num, int target) {
  int retval;
  retval = 0;
  for (int i = 0; i < num; i++) {
    if (arr[i] == target) {
      retval = 1;
      break;
    }
  }
  return retval;
}

struct ImpressionDB
createNewImpressionDB(int num, struct SymptomDB symptoms) {
  struct ImpressionDB db;
  initImpressionDB(db);

  int i, j, idNum, symptomCount, symptomID;
  int symptomIDs[symptoms.count];
  String temp;

  symptomID = symptomCount = idNum = 0;
  struct Impression impression;
  for (i = 0; i < num; i++) {
    initImpression(impression);

    idNum = i + 1;
    printf("Impression Number: %d\n", idNum);
    toString(idNum, impression.id);

    // check if valid string input
    printf("\nWhat is the impression? ");

    getStr(temp);
    while (!isValidString(temp)) {
      printf("Invalid input. Please try again.\n");
      printf("What is the impression? ");

      getStr(temp);
    }
    strcpy(impression.name, temp);

    // print the symptoms
    printSymptoms(symptoms, symptomIDs);

    // ask how many of these symptoms are present in the impression
    printf("\nHow many symptoms are present in the impression? ");
    inputHandler(INT, "", &symptomCount);

    // input the ID of the symptoms
    printf("Enter the number of each corresponding symptom\n");
    for (j = 0; j < symptomCount; j++) {
      inputHandler(INT, "", &symptomID);

      while (!isFound(symptomIDs, symptoms.count, symptomID)) {
        printf("Invalid input. Please try again.\n");
        printf("Enter the number of each corresponding symptom\n");
        inputHandler(INT, "", &symptomID);
      }

      toString(symptomID, temp);
      strcpy(db.database[i].correspondingSymptoms[j], temp);
    }
  }

  return db;
}
