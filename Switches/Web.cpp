#include "Web.h"
#include <utilities.h>
#include <Level.h>

Web::Web(Level* l, float x_, float y_) : 
  Switch(l,x_,y_,32,32) {
  texture_keys.push_back(std::vector<std::string>(1,"web"));
}

int Web::activate() {
  Switch::activate();
  level->getBob()->web();
  return 0;
}


