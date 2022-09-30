#include "LoRaUWB_UWB.h"

void setup(void)
{
 Serial.begin(9600);
 while (!Serial && (millis() < 5000));

 BoardUWB.begin(BOOTLOADER_MODE);

 Serial.println("LoRaUWB_UWB: Firmware Uploader");
}

void loop(void)
{
}
