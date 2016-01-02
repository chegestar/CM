#include <Spider.h>

#ifndef __FIREBALL_H__
#define __FIREBALL_H__

class Fireball : public Spider {
 public:
  Fireball(Level* l, float x, float y, bool d);

  virtual int getSpeed() { return 3; }
};
#endif
