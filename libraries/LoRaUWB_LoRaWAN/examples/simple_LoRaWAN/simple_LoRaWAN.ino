#include "LoRaUWB_LoRaWAN.h"

// Keys and device address are MSB
static byte networkKey[] = {
    0xC2, 0xF8, 0x4B, 0x72, 0x6E, 0xDF, 0x52, 0x83, 0xCB, 0x80, 0x85, 0xD2, 0x37, 0xEE, 0x7C, 0x3F};
static byte appKey[] = {
    0xC4, 0x24, 0x6C, 0xAA, 0x32, 0x92, 0xEA, 0xFA, 0x0C, 0x14, 0xBD, 0x8F, 0x6F, 0x28, 0x52, 0x40};
// Replace with your device address
static byte deviceAddress[] = {0x26, 0x0B, 0xE1};

void setup(void)
{
  Serial.begin(9600);
  while (!Serial && (millis() < 5000))
  {
  }
  Serial.println("Simple LoRaWAN for LoRaUWB Board");

  BoardLoRaWAN.setNetworkKey(networkKey);
  BoardLoRaWAN.setAppKey(appKey);
  BoardLoRaWAN.setDeviceAddress(deviceAddress);

  BoardLoRaWAN.begin();
  Serial.print("LoRa Module status: ");
  Serial.println(BoardLoRaWAN.getStatusString());
}

void loop(void)
{
  byte packet[4];
  packet[0] = 'L';
  packet[1] = 'E';
  packet[2] = 'A';
  packet[3] = 'T';

  BoardLoRaWAN.sendPacket(packet, 4);

  Serial.print("Packet sending status: ");
  Serial.println(BoardLoRaWAN.getStatusString());

  delay(10000); // 10s
}