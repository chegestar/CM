#include "Item.h"

Item::Item(Level* l, float x_, float y_, float w, float h) : 
  Collectable(l,x_,y_,w,h) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,255));
}

