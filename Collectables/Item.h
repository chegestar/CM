#include <Collectable.h>

#ifndef __ITEM__H__
#define __ITEM__H__

class Item : public Collectable {
 public:
  Item(Level* l, float x_, float y_, float w, float h);

};

#endif
