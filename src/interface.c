#include "../include/interface.h"

/**
 * @Description : Prints the main menu
 */
void
v_MainMenu()
{
  printf("MENU #1 User Type\n\n");

  printf("D for Doctor\n");
  printf("P for Patient\n");
  printf("E for Exit\n");
  printf("\nEnter your choice: \n");
}

/**
 * @Description : Prints the doctor menu
 */
void
v_DrMenu()
{

  printf("MENU #2 Doctor\n\n");

  printf("\nC for Create a new list of symptoms and impressions\n");
  printf("U for Use the existing list of symptoms and impressions\n");
  printf("D for Display symptoms\n");
  printf("M for Modify symptoms\n");
  printf("S for Show Impressions and Symptoms file\n");
  printf("E for Exit\n");

  printf("\nEnter your choice: \n");
}

/**
 * @Description : Prints the patient menu
 */
void
v_PatientMenu()
{
  printf("MENU #3 Patient\n\n");
}

/**
 * @Description : A wrapper for all menus
 *
 * @Param ui - determines the menu to be displayed
 */
void
interface(uiType ui)
{
  switch (ui)
  {
    case MAIN:
      v_MainMenu();
      break;
    case DOCTOR:
      v_DrMenu();
      break;
    case PATIENT:
      v_PatientMenu();
      break;
  }
}
