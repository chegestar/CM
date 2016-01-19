#include "Light.h"
#include <utilities.h>
#include <Level.h>

Light::Light(Level* l, float x_, float y_,float radius) : 
  Switch(l,x_,y_,radius*2,radius*2) {
  light.setRadius(radius);
  if (level->getZone()==ICE)
    light.setFillColor(sf::Color(255,255,150,75));
  if (level->getZone()==DARK)
    light.setFillColor(sf::Color(255,255,255,0));

}

int Light::activate() {
  level->getBob()->warmup();
  return 0;
}

void Light::render(sf::RenderWindow& window) {
  light.setPosition(getX1(),getY1());
  window.draw(light);
}

void Light::addLights(sf::RenderTexture& darkness) {
  light.setPosition(getX1(),level->getWindowHeight()-getY1());
  darkness.draw(light,sf::BlendNone);
}
