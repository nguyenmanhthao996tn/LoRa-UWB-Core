#include "LoRaUWB_LED.h"

void setup(void)
{
  // Set both LEDs on for 2 seconds
  BoardLed.ledBlueOn();
  BoardLed.ledRedOn();
  delay(2000);

  BoardLed.ledBlueOff();
  BoardLed.ledRedOff();
}

void loop(void)
{
  // Blink
  BoardLed.ledBlueBlink(2); // Blink 2 times
  delay(500);

  BoardLed.ledRedBlink(2); // Blink 2 times
  delay(500);
}
