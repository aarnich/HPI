#include "../include/database.h"
#include "../include/utils.h"
#include <stdio.h>
// TODO: Add error handling

void
initImpression(struct Impression *input) {

  int idIndex;

  idIndex = 0;
  struct Impression prototype = {
      .id = TERMINATING_STRING,
      .name = "NIL",
  };

  for (; idIndex <= MAX_SYMPTOMS; idIndex++)
    strcpy(prototype.correspondingSymptoms[idIndex], TERMINATING_STRING);

  *input = prototype;
}

void
initImpressionDB(struct ImpressionDB *db) {

  int i;
  for (i = 0; i < MAX_IMPRESSIONS; i++)
    initImpression(&db->database[i]);

  db->count = 0;
}

void
initSymptom(struct Symptom *input) {
  struct Symptom prototype = {.id = "-1", .name = "NIL", .question = "NIL"};
  *input = prototype;
}

void
initSymptomDB(struct SymptomDB *db) {

  int i;
  for (i = 0; i < MAX_SYMPTOMS; i++)
    initSymptom(&db->database[i]);

  // copy the contents of the prototype to the db
  db->count = 0;
}

int
isDigit(char c) {
  return c >= '0' && c <= '9';
}

int
isNumerical(char *input) {

  int i;
  i = 0;

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
  int i, j, k;
  j = k = i = 0;

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

void
readImpression(const char *fileName, FILE *file, struct Impression *output) {

  struct Impression prototype;
  initImpression(&prototype);

  ID id;
  fgets(id, 10, file);
  trim(id);
  strcpy(prototype.id, id);
  // get the name

  String name;
  fgets(name, MAX_STRING_LEN, file);
  trim(name);
  strcpy(prototype.name, name);

  // get the string of corresponding symptoms
  char symptoms[100];
  fgets(symptoms, 100, file);
  trim(symptoms);
  readSymptomsID(prototype.correspondingSymptoms, symptoms);

  *output = prototype;
}

void
readSymptom(const char *fileName, FILE *file, struct Symptom *output) {

  struct Symptom prototype;
  initSymptom(&prototype);

  ID id;
  fgets(id, 10, file);
  trim(id);
  strcpy(prototype.id, id);

  String name;
  fgets(name, MAX_STRING_LEN, file);
  trim(name);
  strcpy(prototype.name, name);

  String question;
  fgets(question, MAX_STRING_LEN, file);
  trim(question);
  strcpy(prototype.question, question);

  *output = prototype;
}

void
readSymptomDB(struct SymptomDB *db, const char *fileName) {

  FILE *file = fopen(fileName, "r");
  char count[ID_LEN + 1];
  fgets(count, ID_LEN + 1, file);
  db->count = atoi(count);

  int i;
  // read the rest of the file
  for (i = 0; i < db->count; i++) {
    readSymptom(fileName, file, &db->database[i]);
  }

  fclose(file);
}

void
readImpressionDB(struct ImpressionDB *db, const char *fileName) {
  // open Impressions.txt file
  FILE *file = fopen(fileName, "r");
  char line[ID_LEN + 1];
  fgets(line, ID_LEN + 1, file);
  db->count = atoi(line);

  // read the rest of the file
  int i;
  for (i = 0; i < db->count - 1; i++) {
    readImpression(fileName, file, &db->database[i]);
  }
  fclose(file);
}

void
writeSymptoms(struct SymptomDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);

  int i;
  for (i = 0; i < db->count; i++) {
    fprintf(file, "\n%s", db->database[i].id);
    fprintf(file, "\n%s", db->database[i].name);
    fprintf(file, "\n%s", db->database[i].question);
  }
  fclose(file);
}

void
printImpression(struct Impression imp) {
  printf("\n%s. %s\n", imp.id, imp.name);
  int i;
  for (i = 0; i <= MAX_SYMPTOMS; i++) {
    printf("%s ", imp.correspondingSymptoms[i]);
  }
}

void
writeImpressions(struct ImpressionDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);

  int i, j;
  for (i = 0; i < db->count; i++) {
    fprintf(file, "\n%s", db->database[i].id);
    fprintf(file, "\n%s\n", db->database[i].name);
    while (strcmp(db->database[i].correspondingSymptoms[j],
                  TERMINATING_STRING) != 0) {
      fprintf(file, "%s ", db->database[i].correspondingSymptoms[j]);
      j++;
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

  int i;
  for (i = 0; i < db.count; i++) {
    printf("%s. %s\n", db.database[i].id, db.database[i].name);
    symptomArr[i] = atoi(db.database[i].id);
  }
}

void
printSymptomsAtIndex(struct SymptomDB db, int index) {
  printf("\t\t%s\n", db.database[index].name);
}

void
displayImpressionSymptoms(struct Impression imp, struct SymptomDB db) {
  printf("The symptoms of %s are: ", imp.name);
  int i;
  for (i = 0; i < MAX_SYMPTOMS; i++) {
    if (strcmp(imp.correspondingSymptoms[i], TERMINATING_STRING) == 0) {
      break;
    }
    printSymptomsAtIndex(db, atoi(imp.correspondingSymptoms[i]));
  }
}

void
createNewSymptomDB(struct SymptomDB *db, int num) {
  initSymptomDB(db);

  int i, idNum;
  String temp;

  idNum = 0;
  struct Symptom symptom;
  for (i = 0; i < num; i++) {
    initSymptom(&symptom);

    idNum = i + 1;
    printf("\n#############################");
    printf("\nSymptom Number: %d\n", idNum);
    toString(idNum, symptom.id);

    // check if valid string input

    printf("\nWhat is the symptom? ");
    getStr(temp);
    printf("\ntemp : %s\n", temp);

    emptyStdin();
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
    strcpy(symptom.question, temp);

    db->database[i] = symptom;
    db->count++;

    emptyStdin();
  }
}

// check if integer is inside array
int
isFound(int *arr, int num, int target) {
  int retval, i;

  retval = 0;
  for (i = 0; i < num; i++) {
    if (arr[i] == target) {
      retval = 1;
    }
  }

  return retval;
}

void
modifyImpressionSymptoms(struct Impression *imp, struct SymptomDB db) {
  int *symptomArr;

  printf("You can modify the symptoms of %s.\n", imp->name);
  printf("Below is the list of symptoms:n");
  printSymptoms(db, symptomArr);

  int i, j;
  int symptomCount = 0;
  int symptomID = 0;

  String symptomTemp;

  printf("How many symptoms are present in the %s case? ", imp->name);
  inputHandler(INT, "", &symptomCount);
  printf("\nEnter the corresponding number of each symptom\n");
  for (j = 0; j < symptomCount; j++) {
    printf("Symptom # %d: ", j + 1);
    inputHandler(INT, "", &symptomID);
    while (!isFound(symptomArr, db.count, symptomID)) {
      printf("Not in dataset, try again.\n");
      printf("Symptom # %d: ", j + 1);
      inputHandler(INT, "", &symptomID);
    }
    toString(symptomID, symptomTemp);
    strcpy(imp->correspondingSymptoms[j], symptomTemp);
  }
  strcpy(imp->correspondingSymptoms[j], TERMINATING_STRING);
  printf("Here are the NEW SYMPTOMS of %s: \n", imp->name);
  displayImpressionSymptoms(*imp, db);
}

void
createNewImpressionDB(struct ImpressionDB *db, int num,
                      struct SymptomDB symptoms) {
  int i, j, symptomCount, symptomID;
  int symptomIDs[symptoms.count];
  String idTemp, nameTemp, symptomTemp;

  int impressionCounter;

  impressionCounter = symptomID = symptomCount = 0;

  // building the impression
  struct Impression impression;

  for (i = 0; i < num; i++) {
    initImpression(&impression);

    printf("Impression # %d\n", i + 1);
    toString(i + 1, idTemp);

    printf("What is the illness? ");
    getStr(nameTemp);
    trim(nameTemp);
    emptyStdin();

    printf("Below is a list of symptoms: \n");
    printSymptoms(symptoms, symptomIDs);

    printf("How many symptoms are present in the %s case? ", nameTemp);
    inputHandler(INT, "", &symptomCount);
    printf("\nEnter the corresponding number of each symptom\n");
    for (j = 0; j < symptomCount; j++) {
      printf("Symptom # %d: ", j + 1);
      inputHandler(INT, "", &symptomID);
      while (!isFound(symptomIDs, symptoms.count, symptomID)) {
        printf("Not in dataset, try again.\n");
        printf("Symptom # %d: ", j + 1);
        inputHandler(INT, "", &symptomID);
      }
      toString(symptomID, symptomTemp);
      strcpy(impression.correspondingSymptoms[j], symptomTemp);
    }
    strcpy(impression.correspondingSymptoms[j], TERMINATING_STRING);
    strcpy(impression.id, idTemp);
    strcpy(impression.name, nameTemp);
    db->database[i] = impression;
    db->count++;
  }
}
