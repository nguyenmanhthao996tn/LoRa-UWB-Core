#include "LoRaUWB_Button.h"

uint8_t counter;

void button_interrupt(void);

void setup(void)
{
  Serial.begin(9600);
  while (!Serial && (millis() < 5000))
  {
  }

  Serial.println("LoRaUWB_Button Example: Interrupt");

  BoardButton.interrupt(button_interrupt);
}

void loop(void)
{
 
}

void button_interrupt(void)
{
  Serial.print("Key press detected! ");
  Serial.println(counter++);
}
