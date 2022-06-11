// ifndef guard
#ifndef HPI_TYPES_H
#define HPI_TYPES_H

#define MAX_STRING_LEN 50
#define MAX_VALID_INPUT_LEN 12

/**
 * @Description : Default string type
 */
typedef char String[MAX_STRING_LEN];

/**
 * @Description : Used to store valid inputs for input handling
 */
typedef char ReferenceInput[MAX_VALID_INPUT_LEN];

/**
 * @Description : ID string used for storing impression and symptom IDs
 */
typedef char ID[3];

// ID type including the nullbyte

// end ifndef guard
#endif
