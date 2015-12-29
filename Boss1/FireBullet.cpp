#include "SpiderBoss.h"

FireBullet::FireBullet(Level* l, float x_, float y_) :
  Actor(l,x_,y_,15,32), Bullet(l,x,y,width,height,0,4) {
}

