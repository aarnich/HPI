#include "../include/dbstructs.h"
#include "../include/utils.h"
#include "stdlib.h"

/**
 * @Description : Initializes a patient struct and stores all values to the
 * given patient struct address;
 *
 * @Param p - the patient struct address
 */
void
initPatient(struct Patient *p)
{
  strcpy(p->patientNumber, "");
  p->gender = ' ';
  p->age = -1;
  strcpy(p->name, "NIL");
}

/**
 * @Description : Gets values for the patient by asking a series of questions
 *
 * @Param p - the address of the patient struct to be modified
 * @Precondition - the pateint struct has already been initalized
 */
void
getPatient(struct Patient *p)
{
  ReferenceInput ref;

  // get patient name
  String name;
  printf("What is your name?\n");
  getStr(name);
  strcpy(p->name, name);

  // get patient number
  String patientNumber;
  printf("What is your patient number?\n");
  getStr(patientNumber);
  strcpy(p->patientNumber, patientNumber);

  // get patient age
  printf("Enter your age:\n");
  inputHandler(INT, ref, &p->age);

  // get patient gender
  printf("Gender (M/F):\n");
  char Gender = ' ';
  strcpy(ref, "MF");
  inputHandler(CHAR, ref, (int *)&Gender);
  p->gender = Gender;
}

/**
 * @Description : Stores all symptoms from the patient where they answered yes
 *
 * @Param db - the symptom database
 * @Param us - the address of the userSymps struct where all symptoms are stored
 * @Precondition - the pateint struct has already been initalized
 */
void
getPatientSymptoms(struct SymptomDB db, struct userSymps *us)
{
  int i;
  char c;
  ReferenceInput ref = "YN";

  c = ' ';
  for (i = 0; i < db.count; i++) {
    printf("%s\n", db.database[i].question);
    inputHandler(CHAR, ref, (int *)&c);
    if (toUpper(c) == 'Y') {
      us->arr[us->count] = db.database[i].id;
      strcpy(us->symName[us->count], db.database[i].name);
      us->count++;
    }
  }
}

/**
 * @Description : Determines whether the given impression is present in the
 * patient
 *
 * @Param input - the impression to be checked
 * @Param us - the collection of user symptoms
 *
 * @Returns - 1 if the impression is present, 0 otherwise
 */
int
validateImpression(struct Impression input, struct userSymps us)
{

  int i;
  int retval = 1;
  for (i = 0; i < input.sympCount; i++) {
    if (!isFound(us.arr, input.sympCount, input.correspondingSymptoms[i])) {
      i = input.sympCount;
      retval = 0;
    }
  }
  return retval;
}

/**
 * @Description : Gets all present impressions from the patient's symptoms
 *
 * @Param sDB - the symptom database
 * @Param iDB - the impression database
 * @Param ui - the address of the userImp struct where all user impressions are
 * stored
 * @Param us - the address of the userSymps struct where all user symptoms are
 * stored
 */
void
getPatientImpressions(struct SymptomDB sDB,
                      struct ImpressionDB iDB,
                      struct userImps *ui,
                      struct userSymps *us)
{
  int i;
  //  initialize userSymps struct
  //  initialize userImps struct
  ui->count = 0;

  // get self report from user
  getPatientSymptoms(sDB, us);

  // loop through impressionDB
  for (i = 0; i < iDB.count; i++) {
    if (validateImpression(iDB.database[i], *us)) {
      ui->arr[ui->count] = iDB.database[i].id;
      strcpy(ui->impName[ui->count], iDB.database[i].name);
      ui->count++;
    }
  }
}

/**
 * @Description : Prints the patient's information
 *
 * @Param p - the patient struct
 */
void
readPatientDetails(struct Patient p)
{

  FILE *fp;
  char fileName[strlen(p.patientNumber) + 5];
  sprintf(fileName, "%s.txt", p.patientNumber);

  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("File not found\n");
    return;
  }

  char line[100];
  printf("\n");
  while (fgets(line, 100, fp) != NULL) {
    printf("%s", line);
  }
}

/**
 * @Description : Savess the patient's information to a text file generated from
 * the user's patient number
 *
 * @Param p - the patient struct
 * @Param ui - the userImp struct where all user impressions are stored
 * @Param us - the userSymps struct where all user symptoms are stored
 * @Precondition : the patient struct has already been initalized
 * @Precondition : the userImps struct has already been initalized
 * @Precondition : the userSymps struct has already been initalized

 */
void
writeUserDetails(struct Patient p, struct userImps ui, struct userSymps us)
{
  int i;
  FILE *fp;
  char fileName[strlen(p.patientNumber) + 5];
  sprintf(fileName, "%s.txt", p.patientNumber);
  fp = fopen(fileName, "w");
  fprintf(fp, "History of Present Illness\n\n");

  fprintf(fp, "%s, patient # ", p.name);
  fprintf(fp, "%s, is a ", p.patientNumber);
  fprintf(fp, "%d year old ", p.age);
  switch (toUpper(p.gender)) {
    case 'M':
      fprintf(fp, "male. He has");
      break;
    case 'F':
      fprintf(fp, "female. She has");
      break;
    default:
      break;
  }

  if (us.count == 0)
    fprintf(fp, " no symptoms!");
  else {
    for (i = 0; i < us.count - 1; i++) {
      fprintf(fp, " %s", us.symName[i]);

      if ((i - us.count - 1) >= 1)
        fprintf(fp, ",");
    }

    if (us.count > 1)
      fprintf(fp, " and");

    fprintf(fp, " %s.\n", us.symName[i]);
  }

  fprintf(fp, " Impressions are");

  if (ui.count == 0)
    fprintf(fp, " none! They are relatively healthy");
  else {
    for (i = 0; i < ui.count - 1; i++) {
      fprintf(fp, " %s", ui.impName[i]);

      if ((i - ui.count - 1) >= 1)
        fprintf(fp, ",");
    }

    if (ui.count > 1)
      fprintf(fp, " and");
    fprintf(fp, " %s.\n", ui.impName[i]);
  }

  fclose(fp);
}

/**
 * @Description : Wrapper function for all patient processes
 *
 * @Param sDB - the symptom database
 * @Param iDB - the impression database
 */
void
PatientProcess(struct SymptomDB sDB, struct ImpressionDB iDB)
{
  getchar(); // clear the trailing newline

  // initialize all necessary structs
  struct Patient p;
  struct userImps ui;
  struct userSymps us;
  initPatient(&p);
  us.count = 0;
  ui.count = 0;

  clear();

  // get patient details
  getPatient(&p);

  // get patient impressions
  getPatientImpressions(sDB, iDB, &ui, &us);

  // write patient details to file
  writeUserDetails(p, ui, us);

  readPatientDetails(p);

  printf("\n\nPatient details saved to %s.txt\n", p.patientNumber);

  getchar();
  sleepMs(500);
  con();
}
