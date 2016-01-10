
#include <Actor.h>
#include <Mover.h>
#include <queue>
#include <set>
#include <Codes.h>
#ifndef __BOB__H__
#define __BOB__H__

class Collectable;
class Item;

class Bob : public Mover{
 private:
  float startx,starty;
  bool isExit,isSpecial;
  int num_lives;
  int num_coins;
  int score;
  int specials;
  float hp;
  int isInvincible;

  bool isWeb;
  bool isDrain;

  //Inventory storage and item affects

  typedef std::list<Item*> INVENTORY;
  INVENTORY inventory;
  unsigned int* has_item;
  bool has_dropped;
  std::set<Item*> recent_drops;
  I_CODE convertItemToIndex(Item* item);
  bool pushInventory(Item* item);
  Item* popInventory();

  float warmth;
  sf::RectangleShape top_warmth;
  sf::RectangleShape bottom_bar;
  
 public:
  Bob(Level* l,float x_,float y_);
  ~Bob();

  void getStart(float& sx,float& sy) const {sx = startx;sy=starty;}
  bool getExit() const {return isExit;}
  bool getSpecialExit() const {return isSpecial;}
  int getLives() const {return num_lives;}
  int getScore() const {return score;}
  int getSpecials() const {return specials;}
  int getCoins() const {return num_coins;}
  bool isInvuln() const {return isInvincible>0;}

  void web();
  void drain();
  void drainWarmth();
  void warmup();
  void earnEP() {specials++;};
  void earnLife() {num_lives++;};
  void earnCoin() {num_coins++; if (num_coins>=100) {num_coins=0;num_lives++;}}
  void earnMagicRing() {isInvincible=60*10;}
  bool die();
  void setStats(int s,int l, int spe, int c) {specials=spe; num_lives=l;
    score=s; num_coins=c;}
  void setCheckPoint(float x_,float y_) {startx = x_;starty= y_;}
  void setExit() {isExit=true;}
  void setSpecialExit() {isSpecial=true;}

  void act();
  void render(sf::RenderWindow& window);

  bool hasItem(I_CODE c);
  void removeDynamite(C_CODE color);
};

#endif
