#include "Codes.h"

C_CODE getColor(std::string color) {
  if (color=="RED")
    return RED;
  else if (color=="BLUE")
    return BLUE;
  else if (color=="YELLOW")
    return YELLOW;
  else if (color=="COIN")
    return COIN;
  assert(false&&color=="");
  return COIN;
}

int getColorScore(C_CODE c) {
  if (c==RED)
    return 20;
  else if (c==BLUE)
    return 10;
  else if (c==YELLOW)
    return 50;
  else if (c==COIN)
    return 10;
  return 0;
}
