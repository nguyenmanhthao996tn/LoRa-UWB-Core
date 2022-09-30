#ifndef __LORA_UWB_UWB_H__
#define __LORA_UWB_UWB_H__

#include "Arduino.h"

#define UWB_SHELL_BAUDRATE 921600

typedef enum
{
  MASTER_MODE = 0,
  SLAVE_MODE = 1,
  BOOTLOADER_MODE = 2,
} UWB_Mode_t;

class UWBClass
{
public:
  UWBClass(void);
  ~UWBClass(void);

  void PWR_UWB_on(void);
  void PWR_UWB_off(void);
  void UWB_HardReset(void);
  void UWB_SoftReset(void);

  void PWR_Translator_on(void);
  void PWR_Translator_off(void);

  void RFSW_Mode1(void);
  void RFSW_Mode2(void);

  void begin(UWB_Mode_t mode = MASTER_MODE);
  void end(void);

  void pause(void);
  void unpause(void);

  char *readLastestData(void) { return lastest_command; }

  // DO NOT USE: This function is called by serialEvent3 only.
  void process(char input);

private:
  char buffer[1024];
  char lastest_command[1024];
  uint16_t buffer_index;
};

extern UWBClass BoardUWB;

#endif /* __LORA_UWB_UWB_H__ */
