#include "stdafx.h"
#include "Collectable.h"
#include <utilities.h>
#include <Level.h>
#include <GemDoor.h>

Collectable::Collectable(Level* l, float x_, float y_, float w, float h) : 
  Actor(l,x_,y_,w,h) {}

void Collectable::activate() {
  isDead=true;
  for (unsigned int i=0;i<doors.size();i++)
    doors[i]->removeCrystal();
}

void Collectable::act() {
  /*  if (you->getDead())
    return;
  */

}

void Collectable::render(sf::RenderWindow& window) {
  sf::CircleShape shape(width/2);
  shape.setPosition(x,y);
  shape.setFillColor(sf::Color(0,0,255));
  window.draw(shape);
}
