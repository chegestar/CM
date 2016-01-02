#include <fstream>
#include <list>
#include <vector>
#include <cmath>
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
 private:
  //Data Structure for the actors
  typedef  std::map<int,Actor*> ACTORS;

  //Level type variables
  L_TYPE level_type;
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

  int max_depth;

  Actor* getStationary(std::string key,int x, int y,std::ifstream& in_str);
  void addGem(Crystal* g, int r, int c, GemDoor* doors[], int num) ;
  void insert(Actor* actor,int depth=-1);
  int getRow() {return ceil(y_/window_height);}
  int getCol() {return ceil(x_/window_width);}

 public:
  Level();
  Level(std::string filename,sf::RenderWindow& window);
  ~Level();

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

  bool isOutOfBounds(Actor* actor);

  void setLevelType(L_TYPE type) {level_type=type;}
  void halt() {isHalted=true;}
  void unhalt() {isHalted=false;}
  void addActor(Actor* actor) {insert(actor);}
  void addStationary(Actor* actor,int r, int c);

  void act();
  void render(sf::RenderWindow& window);

  void testHitStationary(Actor* actor, std::vector<Actor*>& hits);
  void testHitCollectable(Actor* actor, std::vector<Collectable*>& hits);

};

#endif
