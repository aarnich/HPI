#include "../include/interface.h"
void
v_MainMenu() {
  printf("MENU #1 User Type\n\n");

  printf("D for Doctor\n");
  printf("P for Patient\n");
  printf("E for Exit\n");

  printf("\nEnter your choice: \n");
}

void
v_DrMenu() {
  printf("MENU #2 Doctor\n\n");

  printf("C for Create a new list of symptoms and impressions\n");
  printf("U for Use the existing list of symptoms and impressions\n");
  printf("D for Display symptoms\n");
  printf("M for Modify symptoms\n");
  printf("E for Exit\n");

  printf("\nEnter your choice: \n");
}

void
v_PatientMenu() {
  printf("MENU #3 Patient\n\n");
}

void
interface(uiType ui) {
  switch (ui) {
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
