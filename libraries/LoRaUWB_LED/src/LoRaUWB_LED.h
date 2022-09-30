#ifndef __LORA_UWB_LED_H__
#define __LORA_UWB_LED_H__

#include "Arduino.h"

class LedClass
{
public:
  LedClass(void);
  ~LedClass(void);

  void ledRedOn(void);
  void ledRedOff(void);
  void ledRedBlink(uint8_t num_of_blink = 1);

  void ledBlueOn(void);
  void ledBlueOff(void);
  void ledBlueBlink(uint8_t num_of_blink = 1);
};

extern LedClass BoardLed;

#endif /* __LORA_UWB_LED_H__ */
