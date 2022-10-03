#include "LoRaUWB_Button2.h"

void setup() {
  Serial.begin(9600);
  while (!Serial && (millis() < 5000)) {}
}

void loop() {
  switch (BoardButton.read())
  {
    case BUTTON_NO_CLICK:
      Serial.println("BUTTON_NO_CLICK");
      break;
    case BUTTON_SINGLE_CLICK:
      Serial.println("BUTTON_SINGLE_CLICK");
      break;
    case BUTTON_DOUBLE_CLICK:
      Serial.println("BUTTON_DOUBLE_CLICK");
      break;
    case BUTTON_TRIPLE_CLICK:
      Serial.println("BUTTON_TRIPLE_CLICK");
      break;
    default:
      break;
  }

  Serial.println();

  delay(5000);
}
