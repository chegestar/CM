#include "SpiderBoss.h"
#include <Level.h>
FireBullet::FireBullet(Level* l, float x_, float y_) :
  Actor(l,x_,y_,l->getWidth(),l->getHeight()), Bullet(l,x,y,width,height,0,4) {
  std::vector<std::string> keys;
  for (int i=0;i<5;i++) {
    char key[15];
    sprintf(key,"fire_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
}

