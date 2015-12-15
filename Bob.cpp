#include "Bob.h"
#include <Block.h>
#include <Level.h>
#include <Exit.h>
#include <utilities.h>
#include <Collectable.h>

Bob::Bob(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()*2/3,l->getHeight()*2/3), 
  Mover(l,x,y,width,height),
  startx(x), starty(y){
  isExit=false;
  num_lives=3;
  score=0;
  specials=0;

  shape = new sf::RectangleShape(sf::Vector2f(width,height));
  static_cast<sf::RectangleShape*>(shape)->setFillColor(sf::Color(255,255,0));
}

void Bob::act() {
  Mover::act();
  float speed = 3;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    y-=getMovementCorrectionY(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    y+=getMovementCorrectionY(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    x-=getMovementCorrectionX(speed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    x+=getMovementCorrectionX(speed);
  Actor** bs;
  bs = level->testHitStationary(this);
  for (int i=0;i<4;i++) {
    if (!bs[i]) continue;
    if (dynamic_cast<Block*>(bs[i])) {
      int dir = getApproachDir(this,bs[i]);
      if (dir==0&&getLastX1()!=bs[i]->getX2()&&getLastX2()!=bs[i]->getX1()) {
        setPosition(getX1(),bs[i]->getY2());
      }
      else if (dir==1)
        setPosition(bs[i]->getX1()-width,getY1());
      else if (dir==2&&getLastX1()!=bs[i]->getX2()&&getLastX2()!=bs[i]->getX1())
        setPosition(getX1(),bs[i]->getY1()-height);
      else if (dir==3)
        setPosition(bs[i]->getX2(),getY1());
    }
    else if (dynamic_cast<Collectable*>(bs[i])) {
      int s =bs[i]->activate();
      score+=s;
    }
    else if (dynamic_cast<Exit*>(bs[i])) {
      isExit=true;
    }
    else if (dynamic_cast<CheckPoint*>(bs[i])) {
      startx = bs[i]->getX1()+level->getX();
      starty = bs[i]->getY1()+level->getY();
    }
  }
  delete [] bs;
  Collectable** bs2 = level->testHitCollectable(this);
  
  for (int i=0;i<4;i++) {
    if (!bs2[i]) continue;
    int s = bs2[i]->activate();
    score+=s;
  }
  delete [] bs2;

}

void Bob::render(sf::RenderWindow& window) {
  static_cast<sf::RectangleShape*>(shape)->setPosition(getX1(),getY1());
  window.draw(*shape);
}
