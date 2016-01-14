#include "Actor.h"
#include <Level.h>
#include <utilities.h>

Actor::Actor(Level* l, float x_,float y_,float w,float h) {
  level = l;
  x = x_+(level->getWidth()-w)/2;
  y = y_+(level->getHeight()-h)/2;
  width = w;
  height = h;
  isDead=false;
  pointer_to_location=NULL;
  pointer_to_gem=NULL;
  pointer_to_rock=NULL;

  shape=NULL;
  texture_set=texture_step=0;
  old_set=old_step=-1;
}

Actor::~Actor() {
  if (shape) delete shape;
  pointer_to_location=NULL;
  pointer_to_gem=NULL;
  shape=NULL;
}

float Actor::getX1() const {return x-level->getX();}
float Actor::getX2() const {return getX1()+width;}
float Actor::getY1() const {return y-level->getY();}
float Actor::getY2() const {return getY1()+height;}
float Actor::getBoundX1() const {return x-level->getX();}
float Actor::getBoundX2() const {return Actor::getBoundX1()+width;}
float Actor::getBoundY1() const {return y-level->getY();}
float Actor::getBoundY2() const {return Actor::getBoundY1()+height;}

void Actor::setPosition(float x_, float y_,bool keepLast) {
  x=x_+level->getX();
  y=y_+level->getY();
}

std::list<Rock*>::iterator* Actor::removePosition() {
  x=-width*2;
  y=-height*2;
  if (pointer_to_location) *pointer_to_location=NULL;
  if (pointer_to_gem) *pointer_to_gem=NULL;
  return pointer_to_rock;

}

void Actor::render(sf::RenderWindow& window) {
#ifdef COMPILE_DEBUG
  std::vector<Line> lines = getLines();
  std::vector<Circle> circles = getCircles();
  if (lines.size()==0&&circles.size()==0) {
    sf::RectangleShape shp(sf::Vector2f(width,height));
    shp.setPosition(getX1(),getY1());
    window.draw(shp);
  }
  for (unsigned int i=0;i<circles.size();i++) {
    float rad = circles[i].rad;
    sf::CircleShape shp(rad);
    shp.setOrigin(rad,rad);
    shp.setPosition(circles[i].p.first,circles[i].p.second);
    window.draw(shp);
  }

#endif

  int step=(texture_step/3)%texture_keys[texture_set].size();;
  sf::Texture text = getGraphic(texture_keys[texture_set][step]);
  if (has_changed_set()||has_changed_step()) {
    sprite.setTexture(text);
  }
  old_set=texture_set;
  old_step=texture_step;
  sprite.setPosition(getX1(),getY1());
  sprite.setScale(width/32,height/32);
  window.draw(sprite);

#ifdef COMPILE_DEBUG

  for (unsigned int i=0;i<lines.size();i++) {

    sf::Vertex line[] = {

      sf::Vertex(sf::Vector2f(lines[i].p1.first, lines[i].p1.second)),
      sf::Vertex(sf::Vector2f(lines[i].p2.first, lines[i].p2.second))
          
    };
    window.draw(line, 2, sf::Lines);
  }


#endif
}
