
// ifndef guards
#ifndef DATABASE_H
#define DATABASE_H

#include "dbstructs.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Impression Exlusive Functions
void initImpression(struct Impression *input);

void initImpressionDB(struct ImpressionDB *db);

void readImpressionDB(struct ImpressionDB *db, const char *fileName);

void writeImpressions(struct ImpressionDB *db, const char *fileName);

void createNewImpressionDB(struct ImpressionDB *db,
                           int num,
                           struct SymptomDB symptoms);

//////////////////////////////////

// Symptom Exclusive Functions

/**
 * @Description : Use this function to initialize a symptom database in order to
 * avoid invalid memory accesses. Must be used in tandem with
 * createNewSymptomDB()
 *
 * @Param db - The address of the symptom database to initialize
 */
void initSymptomDB(struct SymptomDB *db);

/**
 * @Description : Creates a new symptom database of a given size. This function
 * overwrites the existing symptom database.
 *
 * @Param db - The address of the symptom database to be created.
 * @Param num - The number of symptoms to be created.
 */
void createNewSymptomDB(struct SymptomDB *db, int num);

/**
 * @Description : Use this function to read all symptoms from a txt file.
 *
 * @Param db - A pointer to a struct SymptomDB.
 * @Param fileName - The name of the file to read from.
 */
void readSymptomDB(struct SymptomDB *db, const char *fileName);

/**
 * @Description : This function will write the symptom database to a file. Use
 * this function to save all symptoms in a txt file.
 *
 * @Param db - The symptom database to be written to a file.
 * @Param fileName - The name of the file to be written to.
 */
void writeSymptoms(struct SymptomDB *db, const char *fileName);

/////////////////////////////////

// Patient Exclusive Functions

/**
 * @Description : Use this function to initalize a patient in order to avoid
 * segfaults. Use in combination with getPatient()
 *
 * @Param p - The patient address to initalize.
 */
void initPatient(struct Patient *p);

/**
 * @Description : Use this function to create a new patient.
 *
 * @Param p - The patient to be created.
 */
void getPatient(struct Patient *p);

/**
 * @Description : This function will get all user impressions and store it
 * inside the address of the given userImps struct.
 *
 * @Param sDB - The symptom database.
 * @Param iDB - The impression database.
 * @Param ui - The address of the userImps struct. This struct will store all
 * user-specific impression data.
 * @Param us - The user's symptoms.
 */
void getPatientImpressions(struct SymptomDB sDB,
                           struct ImpressionDB iDB,
                           struct userImps *ui,
                           struct userSymps *us);

/**
 * @Description : Use this function to save the patient's data to a txt file.
 *
 * @Param p - The patient to be saved.
 * @Param ui - The patient's impressions.
 * @Param us - The patient's symptoms.
 */
void
writeUserDetails(struct Patient p, struct userImps ui, struct userSymps us);

/**
 * @Description : This function serves as the interface for all patient
 * processes. Use this function to start all patient activities within the HPI.
 *
 * @Param sDB - The symptom database. Necessary for fetching patient details
 * regarding symptoms.
 * @Param iDB - The impression database. Necessary for fetching patient details
 * regarding impressions.
 */
void PatientProcess(struct SymptomDB sDB, struct ImpressionDB iDB);

/////////////////////////////////

/**
 * @Description : This function is used to modify an existing Impression's
 * symptoms.
 *
 * @Param imp - The Impression to be modified.
 * @Param db - The SymptomDB to be used as a reference for the new symptoms
 */
void modifyImpressionSymptoms(struct Impression *imp, struct SymptomDB db);

/**
 * @Description : This function displays all the corresponding symptoms of an
 * impression
 *
 * @Param imp - The impression to be displayed
 * @Param db - The symptom database
 */
void displayImpressionSymptoms(struct Impression imp, struct SymptomDB db);

/**
 * @Description : Use this function to get all impression IDs from the database.
 *
 * @Param db - The database to get the IDs from
 * @Param impressionIDs - The array to store the IDs in
 */
void getAllImpressionIDs(struct ImpressionDB db, int *impressionIDs);

/**
 * @Description : Use this function to get the matching impression from its name
 *
 * @Param db - The impression database to search in
 * @Param ID - The ID of the impression to search for
 *
 * @Returns - The matching impression
 */
struct Impression getImpressionFromID(struct ImpressionDB db, int ID);

/**
 * @Description : Use this function to get the matching impression from its name
 *
 * @Param db - The impression database to search in
 * @Param name - The name of the impression to search for
 *
 * @Returns - The matching impression
 */
struct Impression getImpressionFromName(struct ImpressionDB db, char *name);

/**
 * @Description : Use this function to begin the Doctor's part of the HPI
 *
 * @Param sDB - The symptom database address
 * @Param iDB - The impression database address
 */
void DoctorProcess(struct SymptomDB *sDB, struct ImpressionDB *iDB);

#endif
