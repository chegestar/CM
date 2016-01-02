#include <Item.h>
#include <Codes.h>

#ifndef __DYNAMITE__H__
#define __DYNAMITE__H__

class Dynamite : public Item {
 private:
  C_CODE c;
 public:
  Dynamite(Level* l, float x_,float y_,C_CODE col);

  void blowup();
};

#endif
