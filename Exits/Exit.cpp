#include "Exit.h"
#include <Level.h>

Exit::Exit(Level* l, float x_,float y_) : 
  CheckPoint(l,x_,y_) {
  texture_keys.clear();
  if (l->getSpecial()) 
    texture_keys.push_back(std::vector<std::string>(1,"door"));
  else
    texture_keys.push_back(std::vector<std::string>(1,"exit"));
};

