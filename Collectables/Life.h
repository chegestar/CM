#include <Collectable.h>

#ifndef __LIFE__H__
#define __LIFE__H__

class Life : public Collectable {
 public:
  Life(Level* l, float x_, float y_);

  virtual int activate();

};

#endif
