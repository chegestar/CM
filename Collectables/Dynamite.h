#include <Item.h>

#ifndef __DYNAMITE__H__
#define __DYNAMITE__H__

class Dynamite : public Item {
 public:
  Dynamite(Level* l, float x_,float y_);

  void blowup();
};

#endif
