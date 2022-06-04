// ifndef guards
#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>

typedef enum T_UI {
  DOCTOR,
  PATIENT,
  MAIN,
} uiType;

// all functions beginning with v_ are purely visual functions
void v_DrMenu();
void v_PatientMenu();
void v_MainMenu();

void interface(uiType ui);

#endif
