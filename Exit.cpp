#include "Exit.h"
#include <Level.h>

Exit::Exit(Level* l, float x_,float y_) : 
  CheckPoint(l,x_,y_) {
  texture_keys.clear();
  texture_keys.push_back("exit");
};

