#ifndef __LORA_UWB_BUTTON_H__
#define __LORA_UWB_BUTTON_H__

#include "Arduino.h"

#define BOARD_BUTTON_PULLUP // Comment this line if Pull-up resistor R1 is not available
#define BUTTON_DEBOUNCE_ENABLE
#define BUTTON_UNDER_THRESHHOLD 50 // millisecond(s)
#define BUTTON_OVER_THRESHHOLD 400 // millisecond(s)

/*** MACRO ***/
#define INDEX4_INCREASE(_index, _inc_value) ((_index + _inc_value) & 0x03)
#define INDEX4_DECREASE(_index, _dec_value) ((_index - _dec_value) & 0x03)

typedef enum {
  BUTTON_NO_CLICK = 0,
  BUTTON_SINGLE_CLICK = 1,
  BUTTON_DOUBLE_CLICK = 2,
  BUTTON_TRIPLE_CLICK = 3
} ButtonState_t;

class Button2Class
{
public:
  Button2Class(void);
  ~Button2Class(void);

  ButtonState_t read(void);
  void clearBuffer(void);

private:
  static uint32_t __press_millis[4];
  static int8_t __press_millis_current_index;
  
  static uint8_t __single_press_counter;
  static uint8_t __double_press_counter;
  static uint8_t __triple_press_counter;
  
  static void __buttonISR(void)
  {
    uint32_t current_millis = millis();

    if (current_millis > (__press_millis[__press_millis_current_index] + BUTTON_UNDER_THRESHHOLD))
    {
      __press_millis_current_index = INDEX4_INCREASE(__press_millis_current_index, 1);
      __press_millis[__press_millis_current_index] = current_millis;
    }
  }
};

extern Button2Class BoardButton;

#endif /* __LORA_UWB_BUTTON_H__ */
