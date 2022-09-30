#ifndef __LORA_UWB_LORAWAN_H__
#define __LORA_UWB_LORAWAN_H__

#ifndef REGION
#define REGION R_EU868
#endif

#include "Arduino.h"
#include <LibLacuna.h>
#include <SPI.h>

#define DEFAULT_FREQUENCY 868100000
#define DEFAULT_SPREADING_FACTOR lsLoraSpreadingFactor_9

class LoRaWANControlClass
{
public:
  LoRaWANControlClass(void);
  ~LoRaWANControlClass(void);

  int getStatus(void);
  char const *getStatusString(void);

  bool setNetworkKey(byte nwkSKey[]);
  bool setAppKey(byte appSKey[]);
  bool setDeviceAddress(byte devID[]);
  byte* getNetworkKey(void) { return networkKey; }
  byte* getAppKey(void) { return appKey; }
  byte* getDeviceAddress(void) { return deviceAddress; }

  bool begin(void);
  bool sendPacket(byte payload[], uint8_t payload_length, uint32_t fPort = 1);

private:
  lsSX126xConfig cfg;
  int status;
  uint32_t frequency;
  lsLoraSpreadingFactor spreadingFactor;

  lsLoraWANParams loraWANParams;
  lsLoraTxParams txParams;

  byte networkKey[16];
  byte appKey[16];
  byte deviceAddress[4];
};

extern LoRaWANControlClass BoardLoRaWAN;

#endif /* __LORA_UWB_LORAWAN_H__ */
