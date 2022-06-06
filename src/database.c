#include "../include/database.h"
#include "../include/utils.h"
#include <stdio.h>
// TODO: Add error handling

void
initImpression(struct Impression *input) {

  struct Impression prototype = {
      .id = TERMINATION_ID,
      .name = "NIL",
      .sympCount = 0,
      .correspondingSymptoms = {[0 ... MAX_SYMPTOMS] = -1}};

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
  struct Symptom prototype = {.id = -1, .name = "NIL", .question = "NIL"};
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

void
nullifyString(char *input) {
  int i, len;
  i = 0;

  len = strlen(input);
  for (; i < len; i++) {
    input[i] = '\0';
  }
}

// convert each space separated string to a symptom id

int
countSymptoms(int *symptoms) {
  int i, count;
  i = 0;
  count = 0;
  while (symptoms[i] != TERMINATION_ID) {
    count++;
    i++;
  }
  return count;
}
int
readSymptomsID(int *dest, char *src) {
  int i, j, k;
  char token[3];
  j = k = i = 0;
  int inputlen = strlen(src);
  for (; i <= inputlen; i++) {
    // copy space separated substring input to ID at index
    if (isDigit(src[i])) {
      token[j] = src[i];
      j++;
    } else {
      token[j] = '\0';
      dest[k] = atoi(token);
      nullifyString(token);
      j = 0;
      k++;
    }
  }

  dest[k - 1] = TERMINATION_ID;
  return k - 1;
}

void
readImpression(FILE *file, struct Impression *output) {

  struct Impression prototype;
  initImpression(&prototype);

  ID idstr;
  fgets(idstr, 3, file);
  trim(idstr);
  int id = atoi(idstr);
  prototype.id = id;
  // get the name

  String name;
  fgets(name, MAX_STRING_LEN, file);
  trim(name);
  strcpy(prototype.name, name);

  // get the string of corresponding symptoms
  String symptoms;
  fgets(symptoms, MAX_STRING_LEN, file);
  trim(symptoms);
  prototype.sympCount =
      readSymptomsID(prototype.correspondingSymptoms, symptoms);

  *output = prototype;
}

void
readSymptom(FILE *file, struct Symptom *output) {

  struct Symptom prototype;
  initSymptom(&prototype);

  ID id;
  fgets(id, 3, file);
  trim(id);
  prototype.id = atoi(id);

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
    readSymptom(file, &db->database[i]);
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
  for (i = 0; i < db->count; i++) {
    readImpression(file, &db->database[i]);
  }
  fclose(file);
}

void
writeSymptoms(struct SymptomDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);

  int i;
  for (i = 0; i < db->count; i++) {
    fprintf(file, "\n%d", db->database[i].id);
    fprintf(file, "\n%s", db->database[i].name);
    fprintf(file, "\n%s", db->database[i].question);
  }
  fclose(file);
}

void
printImpression(struct Impression imp) {
  printf("\n%d. %s\n", imp.id, imp.name);
  int i;
  for (i = 0; i <= MAX_SYMPTOMS; i++) {
    printf("%d ", imp.correspondingSymptoms[i]);
  }
}

void
writeImpressions(struct ImpressionDB *db, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  fprintf(file, "%d", db->count);

  int i, j;

  for (i = 0; i < db->count; i++) {
    fprintf(file, "\n%d", db->database[i].id);
    fprintf(file, "\n%s\n", db->database[i].name);
    j = 0;
    while (db->database[i].correspondingSymptoms[j] != TERMINATION_ID) {
      fprintf(file, "%d ", db->database[i].correspondingSymptoms[j]);
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

void
getSymptoms(struct SymptomDB db, int *symptomArr) {

  int i;
  for (i = 0; i < db.count; i++) {
    printf("%d. %s\n", db.database[i].id, db.database[i].name);
    symptomArr[i] = db.database[i].id;
  }
}

struct Symptom
getSymptomFromID(struct SymptomDB db, int ID) {
  return db.database[ID - 1];
}

void
displayImpressionSymptoms(struct Impression imp, struct SymptomDB db) {
  printf("The symptoms of %s are: ", imp.name);
  int i;
  struct Symptom symp;
  initSymptom(&symp);
  for (i = 0;
       (i < MAX_SYMPTOMS) && (imp.correspondingSymptoms[i] != TERMINATION_ID);
       i++) {
    symp = getSymptomFromID(db, imp.correspondingSymptoms[i]);
    printf("\t%s, ", symp.name);
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
    symptom.id = idNum;

    printf("\nWhat is the symptom? \n");
    getStr(temp);
    strcpy(symptom.name, temp);

    printf("\nHow do you want to ask about the symptom?\n");
    getStr(temp);
    strcpy(symptom.question, temp);

    db->database[i] = symptom;
    db->count++;
  }
}

void
modifyImpressionSymptoms(struct Impression *imp, struct SymptomDB db) {
  int symptomArr[MAX_SYMPTOMS + 1];
  printf("You can modify the symptoms of %s.\n", imp->name);
  printf("Below is the list of symptoms:\n");
  getSymptoms(db, symptomArr);

  int j, symptomCount, symptomID;
  ReferenceInput ref;

  struct Symptom symp;
  initSymptom(&symp);

  symptomCount = 0;
  symptomID = 0;
  printf("How many symptoms are present in the %s case? ", imp->name);
  inputHandler(INT, ref, &symptomCount);
  printf("\nEnter the corresponding number of each symptom\n");
  for (j = 0; j < symptomCount; j++) {
    printf("Symptom # %d: ", j + 1);
    inputHandler(INT, ref, &symptomID);
    while (!isFound(symptomArr, db.count, symptomID)) {
      printf("Not in dataset, try again.\n");
      printf("Symptom # %d: ", j + 1);
      inputHandler(INT, ref, &symptomID);
    }
    imp->correspondingSymptoms[j] = symptomID;
    imp->sympCount++;
  }
  imp->correspondingSymptoms[j] = TERMINATION_ID;
  printf("Here are the NEW SYMPTOMS of %s: \n", imp->name);
  for (j = 0; j < symptomCount; j++) {
    getSymptomFromID(db, imp->correspondingSymptoms[j]);
    printf("\t%s, ", symp.name);
  }
}

void
createNewImpressionDB(struct ImpressionDB *db, int num,
                      struct SymptomDB symptoms) {

  int i, j, symptomCount, symptomID, idTemp, symptomIDs[symptoms.count];
  db->count = 0;

  String nameTemp;
  ReferenceInput ref;
  symptomID = symptomCount = 0;

  // building the impression
  struct Impression impression;

  for (i = 0; i < num; i++) {
    initImpression(&impression);

    idTemp = i + 1;
    printf("Impression # %d\n", idTemp);
    getchar();

    printf("What is the illness? \n");
    getStr(nameTemp);

    printf("Below is a list of symptoms: \n");
    getSymptoms(symptoms, symptomIDs);

    printf("How many symptoms are present in the %s case? ", nameTemp);
    inputHandler(INT, ref, &symptomCount);
    printf("\nEnter the corresponding number of each symptom\n");
    for (j = 0; j < symptomCount; j++) {
      printf("Symptom # %d: ", j + 1);
      inputHandler(INT, ref, &symptomID);
      while (!isFound(symptomIDs, symptoms.count, symptomID)) {
        printf("Not in dataset, try again.\n");
        printf("Symptom # %d: ", j + 1);
        inputHandler(INT, ref, &symptomID);
      }
      impression.correspondingSymptoms[j] = symptomID;
      impression.sympCount++;
    }
    printf("symptomID = %d\n", symptomID);
    impression.correspondingSymptoms[j] = TERMINATION_ID;
    printf("impression.correspondingSymptoms[j] = %d\n",
           impression.correspondingSymptoms[j]);
    impression.id = idTemp;
    strcpy(impression.name, nameTemp);
    db->database[i] = impression;
    db->count++;
  }
}
