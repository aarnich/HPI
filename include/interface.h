#include <stdio.h>

typedef enum T_UI {
  UI_DOCTOR,
  UI_PATIENT,
  UI_MAIN_MENU,
} uiType;

// all functions beginning with v_ are purely visual functions
void v_DrMenu();
void v_PatientMenu();
void v_MainMenu();

void interface(uiType ui);
