#include "../include/database.h"
#include "../include/utils.h"
#include <stdio.h>

/**
 * @Description : Initializes an impression struct given its address
 *
 * @Param input impression struct address
 */
void
initImpression(struct Impression *input)
{

  struct Impression prototype = {
      .id = TERMINATION_ID,
      .name = "NIL",
      .sympCount = 0,
      .correspondingSymptoms = {[0 ... MAX_SYMPTOMS] = -1}};

  *input = prototype;
}

/**
 * @Description Initializes the impression database
 *
 * @Param db database struct address
 */
void
initImpressionDB(struct ImpressionDB *db)
{

  int i;
  for (i = 0; i < MAX_IMPRESSIONS; i++)
    initImpression(&db->database[i]);

  db->count = 0;
}

void
/**
 * @Description : Initializes a symptom with default values given its address
 *
 * @Param input symptom struct address
 */
initSymptom(struct Symptom *input)
{

  struct Symptom prototype = {.id = -1, .name = "NIL", .question = "NIL"};
  *input = prototype;
}

/**
 * @Description : Initializes the symptom database
 *
 * @Param db - database struct address
 */
void
initSymptomDB(struct SymptomDB *db)
{

  int i;
  for (i = 0; i < MAX_SYMPTOMS; i++)
    initSymptom(&db->database[i]);

  // copy the contents of the prototype to the db
  db->count = 0;
}

/**
 * @Description : Counts the number of symptoms in the database
 *
 * @Param symptoms - the array of symptoms
 *
 * @Returns the number of symptoms in the given array
 */
int
countSymptoms(int *symptoms)
{
  int i;
  i = 0;
  while (symptoms[i] != TERMINATION_ID) {
    i++;
  }
  return i;
}

/**
 * @Description :Reads a space separated symptom string and converts it to an
 * array of symptom ids
 *
 * @Param dest - the array of symptom ids
 * @Param src - the string to be read
 *
 * @Returns the number of symptom ids in the array
 */
int
readSymptomsID(int *dest, char *src)
{
  int i, j, k;
  char token[3];
  j = k = i = 0;
  int inputlen = strlen(src);
  for (; i <= inputlen; i++) {
    // copy space separated substring input to ID at index
    if (isDigit(src[i])) {
      token[j] = src[i];
      j++;
    }
    else {
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

/**
 * @Description : Reads an impression from an opened file and stores it to the
 * given Impression address
 *
 * @Param file - the file to be read
 * @Param output - the address of the Impression where the data will be stored
 */
void
readImpression(FILE *file, struct Impression *output)
{

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

/**
 * @Description : Reads a symptom from an opened file and stores it to the given
 * symptom address
 *
 * @Param file - the file to be read
 * @Param output - the address of the symptom where the data will be stored
 */
void
readSymptom(FILE *file, struct Symptom *output)
{

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

/**
 * @Description : Reads all symptoms from a given filename and stores all
 * symptoms to the given symptom database address
 *
 * @Param db - the symptom database address
 * @Param fileName - the filename to be read
 */
void
readSymptomDB(struct SymptomDB *db, const char *fileName)
{

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

/**
 * @Description : Reads all impressions from a given filename and stores all
 * impressions to the given impression database address
 *
 * @Param db - the impression database address
 * @Param fileName - the filename to be read
 */
void
readImpressionDB(struct ImpressionDB *db, const char *fileName)
{
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

/**
 * @Description Writes all symptoms in symptom database to a given file
 *
 * @Param db - the symptom database address
 * @Param fileName - the name of the file to be written to
 */
void
writeSymptoms(struct SymptomDB *db, const char *fileName)
{
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

/**
 * @Description : Prints an impression
 *
 * @Param imp - the impression to be printed
 */
void
printImpression(struct Impression imp)
{
  printf("\n%d. %s\n", imp.id, imp.name);
  int i;
  for (i = 0; i <= MAX_SYMPTOMS; i++) {
    printf("%d ", imp.correspondingSymptoms[i]);
  }
}

/**
 * @Description : Saves all impressions to a given file
 *
 * @Param db - the impression database address
 * @Param fileName - the name of the file to be written to
 */
void
writeImpressions(struct ImpressionDB *db, const char *fileName)
{
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

/**
 * @Description : Stores all symptom IDs to a given array
 *
 * @Param db - the symptom database
 * @Param symptomArr - the array which stores the symptom IDs
 */
void
getSymptoms(struct SymptomDB db, int *symptomArr)
{

  int i;
  for (i = 0; i < db.count; i++) {
    printf("\t\t%d. %s\n", db.database[i].id, db.database[i].name);
    symptomArr[i] = db.database[i].id;
  }
}

/**
 * @Description : Gets a symptom from its ID
 *
 * @Param db - the symptom database
 * @Param ID - the ID of the symptom
 *
 * @Returns - the symptom with the given ID
 */
struct Symptom
getSymptomFromID(struct SymptomDB db, int ID)
{
  return db.database[ID - 1];
}

/**
 * @Description : Gets an impression from its ID
 *
 * @Param db - the impression database
 * @Param ID - the ID of the impression
 *
 * @Returns - the impression with the given ID
 */
struct Impression
getImpressionFromID(struct ImpressionDB db, int ID)
{
  return db.database[ID - 1];
}

/**
 * @Description : Gets the impression from its name
 *
 * @Param db - the symptom database
 * @Param name - the name of the impression
 *
 * @Returns - the Impression with the given name if found, returns a default
 * impression otherwise | calls initImpression() to create a default impression
 */
struct Impression
getImpressionFromName(struct ImpressionDB db, char *name)
{
  struct Impression defVal;
  initImpression(&defVal);
  int i;
  int index;

  index = -1;
  for (i = 0; i < db.count; i++) {
    if (strcmp(db.database[i].name, name) == 0) {
      index = i;
    }
  }

  // only return a valid impression if the name is found
  if (index != -1) {
    return db.database[index];
  }

  return defVal;
}

/**
 * @Description : Prints all the symptoms of a given impression
 *
 * @Param imp - the impression to be printed
 * @Param db - the symptom database
 */
void
displayImpressionSymptoms(struct Impression imp, struct SymptomDB db)
{
  printf("The symptoms of %s are: ", imp.name);
  int i;
  struct Symptom symp;
  initSymptom(&symp);
  for (i = 0;
       (i < db.count) && (imp.correspondingSymptoms[i] != TERMINATION_ID);
       i++) {

    symp = getSymptomFromID(db, imp.correspondingSymptoms[i]);
    printf("\n\t%s", symp.name);
  }
}

/**
 * @Description : Creates a new symptom database with a given size and stores
 * all values to the given database address
 *
 * @Param db - the symptom database address
 * @Param num - the size of the symptom database
 */
void
createNewSymptomDB(struct SymptomDB *db, int num)
{
  initSymptomDB(db);

  int i, idNum;
  String temp;

  idNum = 0;
  struct Symptom symptom;

  getchar();
  for (i = 0; i < num; i++) {
    initSymptom(&symptom);

    idNum = i + 1;
    printf("\n\t\tSymptom # %d:\n\t\t", idNum);
    symptom.id = idNum;

    printf("\t\tWhat is the symptom?\n\t\t");
    getStr(temp);
    strcpy(symptom.name, temp);

    printf("\n\t\tHow do you want to ask about the symptom?\n\t\t");
    getStr(temp);
    strcpy(symptom.question, temp);

    db->database[i] = symptom;
    db->count++;
  }
}

/**
 * @Description : Modifies an existing impression within the database
 *
 * @Param imp - the impression to be modified
 * @Param db - the impression database
 */
void
modifyImpressionSymptoms(struct Impression *imp, struct SymptomDB db)
{

  printf("Below is a list of symptoms:\n\n");
  int symptomArr[MAX_SYMPTOMS + 1];
  getSymptoms(db, symptomArr);

  int j, symptomCount, symptomID;
  ReferenceInput ref;

  struct Symptom symp;
  initSymptom(&symp);

  symptomCount = 0;
  symptomID = 0;

  printf("\n\nHow many symptoms are present in a %s case? ", imp->name);
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
    symp = getSymptomFromID(db, imp->correspondingSymptoms[j]);
    printf("\t%s\n", symp.name);
  }
  getchar();
}

/**
 * @Description : Gets all impression IDs from the given database
 *
 * @Param db - the impression database
 * @Param impressionIDs - the array which stores the impression IDs
 */
void
getAllImpressionIDs(struct ImpressionDB db, int *impressionIDs)
{
  int i;
  for (i = 0; i < db.count; i++)
    impressionIDs[i] = db.database[i].id;
}

/**
 * @Description : Creates a new impression database with a given size and stores
 * all values to the given database address
 *
 * @Param db - the impression database address
 * @Param num - the size of the impression database
 * @Param symptoms - the symptom database
 */
void
createNewImpressionDB(struct ImpressionDB *db,
                      int num,
                      struct SymptomDB symptoms)
{

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
    printf("\n\nImpression # %d:\n", idTemp);
    getchar();

    printf("What is the illness?\n");
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
    impression.correspondingSymptoms[j] = TERMINATION_ID;
    impression.id = idTemp;
    strcpy(impression.name, nameTemp);
    db->database[i] = impression;
    db->count++;
  }
}
