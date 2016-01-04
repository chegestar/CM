#include "Codes.h"

C_CODE getColor(std::string color) {
  if (color=="RED")
    return RED;
  else if (color=="BLUE")
    return BLUE;
  else if (color=="GREEN")
    return GREEN;
  else if (color=="YELLOW")
    return YELLOW;
  else if (color=="PURPLE")
    return PURPLE;
  else if (color=="BLACK")
    return BLACK;
  else if (color=="WHITE")
    return WHITE;
  else if (color=="COIN")
    return COIN;
  assert(false&&color=="");
  return COIN;
}

int getColorScore(C_CODE color) {
  if (color==RED)
    return 20;
  else if (color==BLUE)
    return 10;
  else if (color==GREEN)
    return 30;
  else if (color==YELLOW)
    return 50;
  else if (color==PURPLE)
    return 100;
  else if (color==BLACK)
    return 150;
  else if (color==WHITE)
    return 300;
  else if (color==COIN)
    return 10;
  return 0;
}

char* getColorString(C_CODE color) {
  if (color==RED)
    return "red";
  else if (color==BLUE)
    return "blue";
  else if (color==GREEN)
    return "green";
  else if (color==YELLOW)
    return "yellow";
  else if (color==PURPLE)
    return "purple";
  else if (color==BLACK)
    return "black";
  else if (color==WHITE)
    return "white";
  else if (color==COIN)
    return "coin";
  return "";
}
