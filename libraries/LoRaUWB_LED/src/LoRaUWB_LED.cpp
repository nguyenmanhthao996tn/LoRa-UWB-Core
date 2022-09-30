#include "LoRaUWB_LED.h"

LedClass::LedClass(void)
{
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

LedClass::~LedClass(void)
{
  pinMode(LED_RED_PIN, INPUT);
  pinMode(LED_BLUE_PIN, INPUT);
}

void LedClass::ledRedOn(void)
{
  digitalWrite(LED_RED_PIN, HIGH);
}

void LedClass::ledRedOff(void)
{
  digitalWrite(LED_RED_PIN, LOW);
}

void LedClass::ledRedBlink(uint8_t num_of_blink)
{
  for (; num_of_blink > 0; num_of_blink--)
  {
    ledRedOn();
    delay(50);
    ledRedOff();
    delay(150);
  }
}

void LedClass::ledBlueOn(void)
{
  digitalWrite(LED_BLUE_PIN, HIGH);
}

void LedClass::ledBlueOff(void)
{
  digitalWrite(LED_BLUE_PIN, LOW);
}

void LedClass::ledBlueBlink(uint8_t num_of_blink)
{
  for (; num_of_blink > 0; num_of_blink--)
  {
    ledBlueOn();
    delay(50);
    ledBlueOff();
    delay(150);
  }
}

LedClass BoardLed;
