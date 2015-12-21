
#include <Actor.h>
#include <Mover.h>
#include <queue>
#include <Codes.h>
#ifndef __BOB__H__
#define __BOB__H__

class Collectable;

class Bob : public Mover{
 private:
  float startx,starty;
  bool isExit;
  int num_lives;
  int num_coins;
  int score;
  int specials;
  float hp;

  bool isWeb;
  bool isDrain;

  //Inventory storage and item affects

  typedef std::queue<Collectable*> INVENTORY;
  INVENTORY inventory;
  bool* has_item;
  I_CODE convertCollectableToIndex(Collectable* item);
 public:
  Bob(Level* l,float x_,float y_);
  ~Bob();

  bool getExit() const {return isExit;}
  int getLives() const {return num_lives;}
  int getScore() const {return score;}
  int getSpecials() const {return specials;}

  void web();
  void drain();
  void earnEP() {specials++;};
  void earnLife() {num_lives++;};
  void earnCoin() {num_coins++; if (num_coins>=100) {num_coins=0;num_lives++;}}
  void die() {x=startx; y = starty; num_lives--; hp=100;}

  void act();
  void render(sf::RenderWindow& window);

  bool pushInventory(Collectable* item);
  Collectable* popInventory();
  bool hasItem(I_CODE c);
};

#endif
