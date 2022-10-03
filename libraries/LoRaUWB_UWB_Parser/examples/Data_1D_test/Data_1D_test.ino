#include "LoRaUWB_UWB_Parser.h"

const char *input = "{DT:76,ID:2934,TAGID:1849,LQI:57,DIST:0.78F}";

void setup() {
  Serial.begin(9600);
  while (!Serial && (millis() < 5000)) {}

  Serial.println("UWB 1D Data parse example!");
  delay(500);

  UWB_1D_Data_t data;
  uint32_t start_t = millis();
  bool result = parser.parse_1D_JSON(input, &data);
  uint32_t stop_t = millis();

  if (result)
  {
    Serial.print("ID: ");
    Serial.println(data.id);
    
    Serial.print("TAGID: ");
    Serial.println(data.tag_id);
    
    Serial.print("DT: ");
    Serial.println(data.dt);
    
    Serial.print("LQI: ");
    Serial.println(data.lqi);
    
    Serial.print("DIST: ");
    Serial.println((int)(data.dist * 100));

    Serial.print("Parse time (ms): ");
    Serial.println(stop_t - start_t);
  }
  else
  {
    Serial.println("Parsing failed!");
  }
}

void loop() {

}
