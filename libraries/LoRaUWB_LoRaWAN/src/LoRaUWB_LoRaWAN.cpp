#include "LoRaUWB_LoRaWAN.h"

LoRaWANControlClass::LoRaWANControlClass(void)
{
  lsCreateDefaultSX126xConfig(&cfg, BOARD_VERSION);

  cfg.nssPin = NSS_E22_PIN;
  cfg.resetPin = NRST_E22_PIN;
  cfg.antennaSwitchPin = RXEN_E22_PIN;
  cfg.busyPin = BUSY_E22_PIN;
  cfg.dio1Pin = DIO1_E22_PIN;

  memset((void *)networkKey, 0, 16);
  memset((void *)appKey, 0, 16);
  memset((void *)deviceAddress, 0, 4);

  spreadingFactor = DEFAULT_SPREADING_FACTOR;
  frequency = DEFAULT_FREQUENCY; // in Hz
}

LoRaWANControlClass::~LoRaWANControlClass(void)
{
}

int LoRaWANControlClass::getStatus(void)
{
  return status;
}

char const *LoRaWANControlClass::getStatusString(void)
{
  return lsErrorToString(status);
}

bool LoRaWANControlClass::setNetworkKey(byte nwkSKey[])
{
  memcpy(this->networkKey, nwkSKey, 16);

  return true;
}

bool LoRaWANControlClass::setAppKey(byte appSKey[])
{
  memcpy(this->appKey, appSKey, 16);

  return true;
}

bool LoRaWANControlClass::setDeviceAddress(byte devID[])
{
  memcpy(this->deviceAddress, devID, 4);

  return true;
}

bool LoRaWANControlClass::begin(void)
{
  status = lsInitSX126x(&cfg, REGION);
  if (status != 0)
  {
    return false;
  }
  lsCreateDefaultLoraWANParams(&loraWANParams, networkKey, appKey, deviceAddress);
  loraWANParams.txPort = 1;
  loraWANParams.rxEnable = false;

  lsCreateDefaultLoraTxParams(&txParams, REGION);
  txParams.spreadingFactor = this->spreadingFactor;
  txParams.frequency = this->frequency;

  return true;
}

bool LoRaWANControlClass::sendPacket(byte payload[], uint8_t payload_length, uint32_t fPort)
{
  loraWANParams.txPort = fPort;
  status = lsSendLoraWAN(&loraWANParams, &txParams, payload, payload_length);
  if (status != 0) {
    return false;
  }

  return true;
}

LoRaWANControlClass BoardLoRaWAN;