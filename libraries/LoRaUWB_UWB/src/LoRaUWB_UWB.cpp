#include "LoRaUWB_UWB.h"

UWBClass::UWBClass(void)
{
  memset((void *)lastest_command, 0, 1024);
  memset((void *)buffer, 0, 1024);
  buffer_index = 0;
  bufferReading = 0;

  /**** GPIO Init ****/
  // LDOs
  pinMode(PWR_UWB_EN, OUTPUT);
  pinMode(PWR_TRANSLATOR_EN, OUTPUT);
  PWR_UWB_off();
  PWR_Translator_off();

  // SKY13438-374LF
  pinMode(RFSW1_V1, OUTPUT);
  pinMode(RFSW1_V2, OUTPUT);
  RFSW_Mode1();

  // UWB Module - BeSpoon MOD1
  pinMode(LVS_BOOTMODE_PIN, OUTPUT);
  digitalWrite(LVS_BOOTMODE_PIN, LOW);

  pinMode(LVS_RESET_PIN, OUTPUT);
  digitalWrite(LVS_RESET_PIN, LOW);

  pinMode(LVS_MODESWITCH_PIN, OUTPUT);
  digitalWrite(LVS_MODESWITCH_PIN, LOW);

  pinMode(LVS_ENABLE_PIN, OUTPUT);
  digitalWrite(LVS_ENABLE_PIN, LOW);
}

UWBClass::~UWBClass(void)
{
}

void UWBClass::PWR_UWB_on(void)
{
  digitalWrite(PWR_UWB_EN, HIGH);
}

void UWBClass::PWR_UWB_off(void)
{
  digitalWrite(PWR_UWB_EN, LOW);
}

void UWBClass::UWB_HardReset(void)
{
  // UWB: Power ON
  PWR_UWB_on();
  delay(100);

  // UWB: Power OFF
  PWR_UWB_off();
  delay(100);

  // UWB: Power ON
  PWR_UWB_on();
  delay(100);
}

void UWBClass::UWB_SoftReset(void)
{
  if (Serial3)
  {
    Serial3.print("reset\n");
  }
}

void UWBClass::PWR_Translator_on(void)
{
  digitalWrite(PWR_TRANSLATOR_EN, HIGH);
}

void UWBClass::PWR_Translator_off(void)
{
  digitalWrite(PWR_TRANSLATOR_EN, LOW);
}

void UWBClass::RFSW_Mode1(void)
{
  digitalWrite(RFSW1_V1, HIGH);
  digitalWrite(RFSW1_V2, LOW);
}

void UWBClass::RFSW_Mode2(void)
{
  digitalWrite(RFSW1_V1, LOW);
  digitalWrite(RFSW1_V2, HIGH);
}

void UWBClass::begin(UWB_Mode_t mode)
{
  Serial3.begin(UWB_SHELL_BAUDRATE);
  while (!Serial3 && (millis() < 5000))
    ;
  Serial3.flush();

  // UWB Boot & Reset pins initialization
  if (mode == BOOTLOADER_MODE)
  {
    digitalWrite(LVS_BOOTMODE_PIN, HIGH);
  }
  else
  {
    digitalWrite(LVS_BOOTMODE_PIN, LOW);
  }
  digitalWrite(LVS_RESET_PIN, HIGH);

  if (mode == MASTER_MODE)
  {
    digitalWrite(LVS_MODESWITCH_PIN, HIGH); // Master
  }
  else
  {
    digitalWrite(LVS_MODESWITCH_PIN, LOW); // Slave or Bootloader
  }

  if (Serial3)
  {
    Serial3.flush();
  }

  PWR_UWB_on();
  PWR_Translator_on();

  // UWB Enable pin initialization
  digitalWrite(LVS_ENABLE_PIN, HIGH);
}

void UWBClass::end(void)
{
  digitalWrite(LVS_ENABLE_PIN, LOW);

  PWR_UWB_off();
  PWR_Translator_off();

  Serial3.flush();
  Serial3.end();
}

void UWBClass::pause(void)
{
  digitalWrite(LVS_ENABLE_PIN, LOW);
}

void UWBClass::unpause(void)
{
  digitalWrite(LVS_ENABLE_PIN, HIGH);
}

bool UWBClass::readLastestData(UWB_1D_Data_t *data)
{
  if (data == NULL)
  {
    return false;
  }

  return parser.parse_1D_JSON(lastest_command, *data);
}

void UWBClass::process(char input)
{
  if (input == '{')
  {
    bufferReading = 1;
    buffer_index = 0;
    memset((void *)buffer, 0, 1024);
  }

  buffer[buffer_index++] = input;

  if ((bufferReading == 1) && (input == '}'))
  {
    // TODO: Parse information from buffer
    memcpy(lastest_command, buffer, buffer_index);
    lastest_command[buffer_index] = '\0';
  }
}

UWBClass BoardUWB;

void serialEvent3(void)
{
  char inChar = 0;
  while (Serial3.available())
  {
    inChar = (char)Serial3.read();
    BoardUWB.process(inChar);
  }
}
