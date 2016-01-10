#include <fstream>
#include <list>
#include <vector>
#include <cmath>
#include <cassert>

#include <Actor.h>
#include <Bob.h>
#include <Codes.h>
#ifndef __LEVEL__H__
#define __LEVEL__H__

class Actor;
class Bob;
class Collectable;
class Crystal;
class GemDoor;
class Rock;

class Level {
 public:
  //Data Structure for the actors
  typedef  std::map<int,Actor*> ACTORS;

 private:

  //Level type variables
  L_TYPE level_type;
  Z_TYPE zone;
  std::vector<Z_TYPE> hub_grid;
  bool isSpecial;
  int num_levels;
  sf::Sprite background;
  bool isHalted,isWrapped;
  bool isVertical;
  int dir;

  int rows,cols; // number of rows and cols for a single room
  int grows,gcols; //number of grids spaces of rooms
  int max_rows,max_cols; //total number of rows and columns in the level

  //Level dimensions
  float x_,y_;
  float window_width,window_height;
  float width,height;

  //Actor containers
  Actor*** stationary;
  Collectable*** gems;
  std::list<Rock*> rocks;
  ACTORS actors; 
  Bob* bob;

  int min_depth;
  int wall_depth,monster_depth,door_depth,gem_depth,stationary_depth;

  //SpiderBoss variables
  std::vector<int> chase_indices;

  Actor* getStationary(std::string key,int x, int y,std::ifstream& in_str);
  void addGem(Crystal* g, int r, int c) ;
  void insert(Actor* actor,int& depth);
  bool isBlock(int i,int j);
  void setBlocks();
  int getRow() {return ceil(y_/window_height);}
  int getCol() {return ceil(x_/window_width);}

 public:
  Level();
  Level(std::string filename,sf::RenderWindow& window, int tot_levels,bool isS=false);
  ~Level();

  Z_TYPE getZone() const {return zone;}
  Z_TYPE getHubZone(int x,int y) const;
  bool getSpecial() const {return isSpecial;}
  float getX() const {return x_;}
  float getY() const {return y_;}
  float getWidth() const {return width;}
  float getHeight() const {return height;}
  float getWindowWidth() const {return window_width;}
  float getWindowHeight() const {return window_height;}
  float getLevelWidth() const {return max_cols*width;}
  float getLevelHeight() const {return max_rows*height;}
  Bob* getBob() const {return bob;}
  const std::list<Rock*>& getRocks() const {return rocks;}
  void findOpenPosition(int& r,int& c) const;

  bool isOutOfBounds(Actor* actor) const ;

  void setLevelType(L_TYPE type) {level_type=type;}
  void halt() {isHalted=true;}
  void unhalt() {isHalted=false;}
  void addActor(Actor* actor) {insert(actor,min_depth);}
  void addStationary(Actor* actor,int r, int c, bool needs_adding=true);
  void setSpiders(bool isR);

  //SpiderBoss functions
  void resetSpiderBoss(int index);

  void act();
  void render(sf::RenderWindow& window);

  ACTORS::iterator beginActor() {return actors.begin();}
  ACTORS::iterator iterateActor(ACTORS::iterator& itr) {
    assert(itr!=endActor());
    itr++;
    return itr;
  }
  ACTORS::iterator endActor() {return actors.end();}

  void testHitStationary(Actor* actor, std::vector<Actor*>& hits);
  void testHitCollectable(Actor* actor, std::vector<Collectable*>& hits);

};

#endif
