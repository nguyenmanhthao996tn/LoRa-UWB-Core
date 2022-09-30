#ifndef __LORA_UWB_BUTTON_H__
#define __LORA_UWB_BUTTON_H__

#include "Arduino.h"

#define BOARD_BUTTON_PULLUP // Comment this line if Pull-up resistor R1 is not available
#define BUTTON_DEBOUNCE_ENABLE

class ButtonClass
{
public:
  ButtonClass(void);
  ~ButtonClass(void);

  uint8_t read(bool clear_cnt = true);
  void clear(void);

  void interrupt(voidFuncPtr interrupt);
  void clearInterrupt(void);

private:
  static uint8_t __buttonISRCounter;
  static bool __buttonISRCounter_flag;
  static void __buttonISR(void)
  {
    if (__buttonISRCounter_flag)
    {
      __buttonISRCounter++;
    }

    if (__extendedButtonISR != NULL)
    {
      __extendedButtonISR();
    }
  }

  static voidFuncPtr __extendedButtonISR;
};

extern ButtonClass BoardButton;

#endif /* __LORA_UWB_BUTTON_H__ */
