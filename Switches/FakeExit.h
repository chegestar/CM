#include <Switch.h>

#ifndef __FAKEEXIT_H__
#define __FAKEEXIT_H__

class FakeExit : public Switch {
 private:
  float newx,newy;
 public:
  FakeExit(Level* l, float x_, float y_, float nx, float ny);

  int activate();
};

#endif
