#include <Switch.h>

#ifndef __COLLECTABLE__H__
#define __COLLECTABLE__H__

class Collectable : public Switch {
 public:
  Collectable(Level* l, float x_, float y_, float w, float h);

  virtual int activate();


};

#endif
