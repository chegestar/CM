#include "Crystal.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>

Crystal::Crystal(Level* l, float x_, float y_, float w, float h) : 
  Collectable(l,x_,y_,w,h) {
  shape = new sf::CircleShape(width/2);
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,255));
}

int Crystal::activate() {
  Collectable::activate();
  for (unsigned int i=0;i<doors.size();i++)
    doors[i]->removeCrystal();
  return 10;
}

void Crystal::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
