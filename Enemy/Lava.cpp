#include "Lava.h"
#include <Level.h>
#include <FireBoot.h>

Lava::Lava(Level* l, float x, float y) : 
  Actor(l,x,y,l->getWidth(),l->getHeight()), Die(l,x,y,width,height) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,0));


}

bool Lava::hitBob(Bob* b) {
  FireBoot* item = new FireBoot(level,0,0);
  bool isHit = false;
  if (!b->hasItem(item)) {
    isHit = Die::hitBob(b);
  }
  delete item;
  return isHit;
}

void Lava::render(sf::RenderWindow& window) {

  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);

}
