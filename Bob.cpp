#include "Bob.h"
#include <Block.h>
#include <Level.h>
#include <CheckPoint.h>
#include <utilities.h>
#include <Collectable.h>

void Bob::act() {
  Mover::act();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    y-=3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    y+=3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    x-=3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    x+=3;
  Actor** bs;
  bs = level->testHitStationary(this);
  for (int i=0;i<4;i++) {
    if (!bs[i]) continue;
    if (dynamic_cast<Block*>(bs[i])) {
      int dir = getApproachDir(this,bs[i]);
      if (dir==0&&getLastX1()!=bs[i]->getX2()&&getLastX2()!=bs[i]->getX1()) {
	setPosition(x,bs[i]->getY2());
      }
      else if (dir==1)
	setPosition(bs[i]->getX1()-width,y);
      else if (dir==2&&getLastX1()!=bs[i]->getX2()&&getLastX2()!=bs[i]->getX1())
	setPosition(x,bs[i]->getY1()-height);
      else if (dir==3)
	setPosition(bs[i]->getX2(),y);
    }
    else if (dynamic_cast<CheckPoint*>(bs[i])) {
      startx = bs[i]->getX1();
      starty = bs[i]->getY1();
    }
  }
  delete [] bs;
  Collectable** bs2 = level->testHitCollectable(this);
  
  for (int i=0;i<4;i++) {
    if (!bs2[i]) continue;
    bs2[i]->activate();
  }
  delete [] bs2;

}

void Bob::render(sf::RenderWindow& window) {
  sf::RectangleShape shape(sf::Vector2f(width,height));
  shape.setPosition(x,y);
  shape.setFillColor(sf::Color(255,255,0));
  window.draw(shape);
}
