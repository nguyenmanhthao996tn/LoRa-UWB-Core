#include "LoRaUWB_Button.h"

ButtonClass::ButtonClass(void)
{
#ifdef BOARD_BUTTON_PULLUP
  pinMode(BUTTON, INPUT); // PA8
#else
  pinMode(BUTTON, INPUT_PULLUP); // PA8
#endif

  clearInterrupt(); // Clear the extended interrupt

  attachInterrupt(digitalPinToInterrupt(BUTTON), ButtonClass::__buttonISR, FALLING);
  clear();
}

ButtonClass::~ButtonClass(void)
{
  pinMode(BUTTON, INPUT);
}

uint8_t ButtonClass::read(bool clear_cnt)
{
  uint8_t cnt = ButtonClass::__buttonISRCounter;

  if (clear_cnt)
  {
    if (cnt > 0)
    {
      delay(10);
    }

    clear();
  }

  return cnt;
}

void ButtonClass::clear(void)
{
  ButtonClass::__buttonISRCounter = 0;
}

void ButtonClass::interrupt(voidFuncPtr interrupt)
{
  ButtonClass::__extendedButtonISR = interrupt;
}

void ButtonClass::clearInterrupt(void)
{
  ButtonClass::__extendedButtonISR = NULL;
}

uint8_t ButtonClass::__buttonISRCounter = 0;
bool ButtonClass::__buttonISRCounter_flag = true;
voidFuncPtr ButtonClass::__extendedButtonISR = NULL;

ButtonClass BoardButton;