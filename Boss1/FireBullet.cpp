#include "SpiderBoss.h"
#include <Level.h>
FireBullet::FireBullet(Level* l, float x_, float y_) :
  Actor(l,x_,y_,l->getWidth(),l->getHeight()), Bullet(l,x,y,width,height,0,4) {
  texture_keys.push_back("fire");
}

