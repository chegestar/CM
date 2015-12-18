#ifndef __ACTOR__H__
#define __ACTOR__H__

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <list>
#include <Line.h>
#include <Circle.h>

class Level;
class Collectable;
class Rock;

class Actor {
 public:
  Actor(Level* l,float x_,float y_,float w,float h);
  virtual ~Actor();

  virtual float getX1() const;
  virtual float getX2() const;
  virtual float getY1() const;
  virtual float getY2() const;
  virtual float getWidth() const {return width;}
  virtual float getHeight() const {return height;}
  virtual float getLastX1() const {return getX1();}
  virtual float getLastX2() const {return getX2();}
  virtual float getLastY1() const {return getY1();}
  virtual float getLastY2() const {return getY2();}
    virtual std::vector<Line> getLines() const
    {throw std::runtime_error("NOT IMPLEMENTED");}
  virtual std::vector<Circle> getCircles() const
    {throw std::runtime_error("NOT IMPLEMENTED");}
  bool getDead() const {return isDead;}
  virtual bool isStationary() const {return true;}
  virtual bool doesPause() const {return true;} 

  virtual void setWidth(float w) {width=w;}
  virtual void setHeight(float h) {height = h;}
  virtual void shiftX(float dx) {x+=dx;}
  virtual void shiftY(float dy) {y+=dy;}
  virtual void setPosition(float x_, float y_,bool keepLast=false);
  virtual void setColor(int r, int g, int b) {}
  virtual void setDead() {isDead=true;}
  void linkPosition(Actor** location) {pointer_to_location=location;}
  void linkPosition(Collectable** location) {pointer_to_gem=location;}
  void linkPosition(std::list<Rock*>::iterator& itr) {pointer_to_rock = new std::list<Rock*>::iterator(itr);}
  std::list<Rock*>::iterator* removePosition();
  virtual void act() {}
  virtual int activate() {return 0;}  
  virtual void windowEvent(sf::Event& event) {}
  virtual void render(sf::RenderWindow& window) {}

  friend bool operator==(const Actor& a1, const Actor& a2) {
    return a1.x==a2.x && a1.y == a2.y && a1.width==a2.width && a1.height==a2.height; 
  }

protected:
  Level* level;
  float x,y;
  float width,height;
  bool isDead;
  Actor** pointer_to_location; 
  Collectable** pointer_to_gem; 
  std::list<Rock*>::iterator* pointer_to_rock;
  sf::Drawable* shape;
};

#endif
