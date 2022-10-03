#ifndef __LORAUWB_UWB_PARSER_H__
#define __LORAUWB_UWB_PARSER_H__

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
  int32_t dt;
  int32_t id;
  int32_t tag_id;
  int8_t lqi;
  float dist;
} UWB_1D_Data_t;

class ParserClass
{
public:
  ParserClass(void);
  ~ParserClass(void);

  bool parse_1D_JSON(const char *input, UWB_1D_Data_t *data);

  // private:
  // void memcopy(char *dest, char *source, uint8_t num);
};

extern ParserClass parser;

#endif /* __LORAUWB_UWB_PARSER_H__ */
