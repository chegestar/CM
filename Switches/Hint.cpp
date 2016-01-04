#include "Hint.h"
#include <Level.h>
Hint::Hint(Level*l, float x_,float y_, std::string message) :
  Switch(l,x_,y_,l->getWidth(),l->getHeight()){
  bubble.setup(message);
  was_hit=false;
  static_cast<sf::CircleShape*>(shape)->setFillColor(sf::Color(0,0,255));
}



int Hint::activate() {
  bubble.act(getX1()+width/2,getY1()+height/2);
  was_hit=true;
  return 0;
}

void Hint::act() {
  Switch::act();
  if (!was_hit)
    bubble.reset();
  was_hit=false;
}

void Hint::render(sf::RenderWindow& window) {
  static_cast<sf::CircleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
  bubble.render(window);
}
