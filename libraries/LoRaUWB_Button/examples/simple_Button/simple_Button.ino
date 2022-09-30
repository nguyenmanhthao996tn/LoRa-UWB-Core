#include "LoRaUWB_Button.h"

uint8_t counter;

void setup(void)
{
 Serial.begin(9600);
 while (!Serial && (millis() < 5000)) {}

 Serial.println("LoRaUWB_Button Example: Polling");

 BoardButton.clear(); // Clear previous status/press
 counter = 1;
}

void loop(void)
{
  if (BoardButton.read() > 0)
  {
    Serial.print("Key press detected! ");
    Serial.println(counter++);
  }
}
