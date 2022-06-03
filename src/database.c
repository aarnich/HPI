#include "../include/database.h"
void
initImpression(struct Impression input) {
  struct Impression prototype = {
      .id = -1, .name = "NIL", .correspondingSymptoms = {-1}};
  input = prototype;
}

void
initImpressionDB(struct ImpressionDB db) {
  struct ImpressionDB prototype = {.count = 0};
  for (int i = 0; i < MAX_IMPRESSIONS; i++) {
    initImpression(prototype.database[i]);
  }

  db = prototype;
}

void
initSymptom(struct Symptom input) {
  struct Symptom prototype = {.id = -1, .name = "NIL", .question = "NIL"};
  input = prototype;
}

void
initSymptomDB(struct SymptomDB db) {
  struct SymptomDB prototype = {.count = 0};
  for (int i = 0; i < MAX_SYMPTOMS; i++) {
    initSymptom(prototype.database[i]);
  }

  db = prototype;
}
