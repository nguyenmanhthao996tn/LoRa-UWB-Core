#include "LoRaUWB_Button2.h"

Button2Class::Button2Class(void)
{
#ifdef BOARD_BUTTON_PULLUP
  pinMode(BUTTON, INPUT); // PA8
#else
  pinMode(BUTTON, INPUT_PULLUP); // PA8
#endif

  clearBuffer();
  attachInterrupt(digitalPinToInterrupt(BUTTON), Button2Class::__buttonISR, FALLING);
}

Button2Class::~Button2Class(void)
{
  pinMode(BUTTON, INPUT);
}

ButtonState_t Button2Class::read(void)
{
  // Process buffer
  uint32_t current_millis = millis();
  if (current_millis - __press_millis[__press_millis_current_index] > BUTTON_OVER_THRESHHOLD)
  {
    uint8_t tmp = 0;
    if (__press_millis[__press_millis_current_index] != 0)
    {
      tmp = 1;
      if (__press_millis[__press_millis_current_index] - __press_millis[INDEX4_DECREASE(__press_millis_current_index, 1)] < BUTTON_OVER_THRESHHOLD)
      {
        tmp = 2;
        if (__press_millis[INDEX4_DECREASE(__press_millis_current_index, 1)] - __press_millis[INDEX4_DECREASE(__press_millis_current_index, 2)] < BUTTON_OVER_THRESHHOLD)
        {
          tmp = 3;
        }
      }
    }
    switch (tmp)
    {
    case 1:
      __single_press_counter++;
      break;
    case 2:
      __double_press_counter++;
      break;
    case 3:
      __triple_press_counter++;
      break;
    default:
      break;
    }
    clearBuffer();
  }

  // Return state
  if (__triple_press_counter > 0)
  {
    __triple_press_counter--;
    return BUTTON_TRIPLE_CLICK;
  }
  if (__double_press_counter > 0)
  {
    __double_press_counter--;
    return BUTTON_DOUBLE_CLICK;
  }
  if (__single_press_counter > 0)
  {
    __single_press_counter--;
    return BUTTON_SINGLE_CLICK;
  }
  return BUTTON_NO_CLICK;
}

void Button2Class::clearBuffer(void)
{
  __press_millis_current_index = 0;
  memset(__press_millis, 0, sizeof(uint32_t) * 4);
}

uint32_t Button2Class::__press_millis[4] = {0};
int8_t Button2Class::__press_millis_current_index = 0;
uint8_t Button2Class::__single_press_counter = 0;
uint8_t Button2Class::__double_press_counter = 0;
uint8_t Button2Class::__triple_press_counter = 0;

Button2Class BoardButton;