#ifndef __CODES_H__
#define __CODES_H__
#include <string>
#include <cassert>

typedef enum INVENTORY_CODE {
  NO_ITEM=-1,
  FIRE_BOOT,
  DYNAMITE,
  MAX_INVENTORY
} I_CODE;

typedef enum LEVEL_TYPE {
  NORMAL,
  GRID,
  CONTINUOUS,
  AUTOSCROLL
} L_TYPE;

typedef enum COLOR_CODE {
  RED,
  BLUE,
  YELLOW,
  COIN
} C_CODE;

C_CODE getColor(std::string color);

int getColorScore(C_CODE c);
 
#endif
