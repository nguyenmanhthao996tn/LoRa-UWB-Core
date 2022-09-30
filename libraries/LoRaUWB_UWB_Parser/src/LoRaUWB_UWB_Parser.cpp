#include "LoRaUWB_UWB_Parser.h"

ParserClass::ParserClass(void)
{
}

ParserClass::~ParserClass(void)
{
}

bool ParserClass::parse_1D_JSON(const char *input, UWB_1D_Data_t &data)
{
#ifdef PARSE_1D_JSON_MAX_SEARCH_CHAR
#undef PARSE_1D_JSON_MAX_SEARCH_CHAR
#endif
#define PARSE_1D_JSON_MAX_SEARCH_CHAR 127

  if (input == NULL)
  {
    return false;
  }

  uint8_t i = 0;
  uint8_t loopFlag = 1;

  uint8_t bracketCnt = 0;
  uint8_t commaCnt = 0;
  uint8_t dotCnt = 0;

  int8_t dt_index = -1;
  int8_t id_index = -1;
  int8_t tagid_index = -1;
  int8_t lqi_index = -1;
  int8_t dist_index = -1;

  int8_t *counter_pointer = NULL;
  int8_t dt_counter = 0;
  int8_t id_counter = 0;
  int8_t tagid_counter = 0;
  int8_t lqi_counter = 0;
  int8_t dist_counter = 0;

  do
  {
    switch (input[i])
    {
    case '\0':
      counter_pointer = NULL;
      loopFlag = 0;
      break;

    case '{':
    case '}':
      counter_pointer = NULL;
      bracketCnt++;
      break;

    case ',':
      counter_pointer = NULL;
      commaCnt++;
      break;

    case '.':
      dotCnt++;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (counter_pointer != NULL)
      {
        (*counter_pointer)++;
      }
      else
      {
        // TODO: Invalid case
      }
      break;

    case 'D':
      counter_pointer = NULL;
      if ((dt_index == -1) && (input[i + 1] == 'T') && (input[i + 2] == ':'))
      {
        i += 2;
        dt_index = i + 1;
        counter_pointer = &dt_counter;
      }
      else if ((dist_index == -1) && (input[i + 1] == 'I') && (input[i + 2] == 'S') && (input[i + 3] == 'T') && (input[i + 4] == ':'))
      {
        i += 4;
        dist_index = i + 1;
        counter_pointer = &dist_counter;
      }
      break;

    case 'I':
      counter_pointer = NULL;
      if ((id_index == -1) && (input[i + 1] == 'D') && (input[i + 2] == ':'))
      {
        i += 2;
        id_index = i + 1;
        counter_pointer = &id_counter;
      }
      break;

    case 'T':
      counter_pointer = NULL;
      if ((tagid_index == -1) && (input[i + 1] == 'A') && (input[i + 2] == 'G') && (input[i + 3] == 'I') && (input[i + 4] == 'D') && (input[i + 5] == ':'))
      {
        i += 5;
        tagid_index = i + 1;
        counter_pointer = &tagid_counter;
      }
      break;

    case 'L':
      counter_pointer = NULL;
      if ((lqi_index == -1) && (input[i + 1] == 'Q') && (input[i + 2] == 'I') && (input[i + 3] == ':'))
      {
        i += 3;
        lqi_index = i + 1;
        counter_pointer = &lqi_counter;
      }
      break;

    default:
      counter_pointer = NULL;
      break;
    }

    i++;
  } while (loopFlag == 1);

  if ((dt_index == -1) || (dt_counter == 0) ||
      (id_index == -1) || (id_counter == 0) ||
      (tagid_index == -1) || (tagid_counter == 0) ||
      (lqi_index == -1) || (lqi_counter == 0) ||
      (dist_index == -1) || (dist_counter == 0) ||
      (dotCnt > 1))
  {
    return false;
  }

  char buffer[32];

  /* dt_index */
  memset(buffer, '\0', 32);
  memcpy(buffer, (char *)(input + dt_index), dt_counter);
  data.dt = atoi(buffer);

  /* id_index */
  memset(buffer, '\0', 32);
  memcpy(buffer, (char *)(input + id_index), id_counter);
  data.id = atoi(buffer);

  /* tagid_index */
  memset(buffer, '\0', 32);
  memcpy(buffer, (char *)(input + tagid_index), tagid_counter);
  data.tag_id = atoi(buffer);

  /* lqi_index */
  memset(buffer, '\0', 32);
  memcpy(buffer, (char *)(input + lqi_index), lqi_counter);
  data.lqi = atoi(buffer);

  /* dist_index */
  memset(buffer, '\0', 32);
  memcpy(buffer, (char *)(input + dist_index), dist_counter);
  data.dist = atof(buffer);

  return true;
}
