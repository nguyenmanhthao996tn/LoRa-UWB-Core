#include "LoRaUWB_UWB.h"

void setup(void)
{
 Serial.begin(9600);
 while (!Serial && (millis() < 5000));

 BoardUWB.begin(MASTER_MODE);

 Serial.println("LoRaUWB_UWB: Master Mode");
}

void loop(void)
{
  delay(1000);
  Serial.println(BoardUWB.readLastestData());
}
