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
  virtual float getBoundX1() const;
  virtual float getBoundX2() const;
  virtual float getBoundY1() const;
  virtual float getBoundY2() const;
  virtual float getLastX1() const {return getBoundX1();}
  virtual float getLastX2() const {return getBoundX2();}
  virtual float getLastY1() const {return getBoundY1();}
  virtual float getLastY2() const {return getBoundY2();}
  
  virtual std::vector<Line> getLines() const
    {return std::vector<Line>();}
  virtual std::vector<Circle> getCircles() const
    {return std::vector<Circle>();}
  bool getDead() const {return isDead;}
  virtual bool isStationary() const {return true;}
  virtual bool doesPause() const {return true;} 

  virtual void setWidth(float w) {width=w;}
  virtual void setHeight(float h) {height = h;}
  virtual void shiftX(float dx) {x+=dx;}
  virtual void shiftY(float dy) {y+=dy;}
  virtual void setX(float x_) {x=x_;}
  virtual void setY(float y_) {y=y_;}
  virtual void setPosition(float x_, float y_,bool keepLast=false);
  virtual void setColor(int r, int g, int b) {}
  virtual void setDead() {isDead=true;}
  void linkPosition(Actor** location) {pointer_to_location=location;}
  void linkPosition(Collectable** location) {pointer_to_gem=location;}
  void linkPosition(std::list<Rock*>::iterator& itr) {pointer_to_rock = new std::list<Rock*>::iterator(itr);}
  virtual std::list<Rock*>::iterator* removePosition();
  virtual int activate() {return 0;}  

  virtual void act() {}
  virtual void windowEvent(sf::Event& event) {}
  virtual void render(sf::RenderWindow& window);
  virtual void addLights(sf::RenderTexture& darkness) {}
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
  sf::Sprite sprite;
  std::vector<std::vector<std::string> > texture_keys;
  int texture_set,texture_step;
  int old_set,old_step;

 private:
  bool has_changed_set() const {return old_set!=texture_set;}
  bool has_changed_step() const {return old_step!=texture_step;}


};

#endif
