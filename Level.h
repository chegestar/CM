#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Actor.h>
#include <Bob.h>
#ifndef __LEVEL__H__
#define __LEVEL__H__

class Actor;
class Bob;
class Collectable;
class GemDoor;

class Level {
 private:
  typedef  std::map<int,Actor*> ACTORS;
  int level_type;
  int rows,cols;
  float width,height;
  Actor*** stationary;
  Collectable*** gems;
  ACTORS actors; 
  Bob* bob;
  int max_depth;
  void addStationary(Actor* actor,int r, int c);
  void addGem(Collectable* g, int r, int c, GemDoor* doors[], int num) ;
  void insert(Actor* actor,int depth=-1);
 public:
  Level();
  Level(std::string filename,sf::RenderWindow& window);
  ~Level();

  float getWidth() const {return width;}
  float getHeight() const {return height;}
  Bob* getBob() const {return bob;}


  void act();
  void render(sf::RenderWindow& window) {ACTORS::iterator itr; 
    for (itr=actors.begin();itr!=actors.end();itr++) {
      if (!(dynamic_cast<Bob*>(itr->second)))
	itr->second->render(window);
    }
    bob->render(window);
  }

  Actor** testHitStationary(Actor* actor);
  Collectable** testHitCollectable(Actor* actor);

};

#endif
