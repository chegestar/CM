#include "Item.h"

Item::Item(Level* l, float x_, float y_, float w, float h) : 
  Collectable(l,x_,y_,w,h) {
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(255,0,255));
}


bool Item::removePosition(std::list<Rock*>::iterator*& itr) {
  isDead=false;
  x=-width;
  y=-height;
  if (pointer_to_location) *pointer_to_location=NULL;
  if (pointer_to_gem) *pointer_to_gem=NULL;
  itr=NULL;
  return false;

}
