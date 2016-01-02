#include "Crystal.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>

Crystal::Crystal(Level* l, float x_, float y_, C_CODE col) : 
  Collectable(l,x_,y_,l->getWidth(),l->getHeight()) {
  c=col;
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color((c==RED)*255,0,(c==BLUE)*255));
}

int Crystal::activate() {
  Collectable::activate();
  for (unsigned int i=0;i<doors.size();i++)
    doors[i]->removeCrystal();
  return getColorScore(c);
}

void Crystal::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
