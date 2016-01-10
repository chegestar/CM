
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
  float startx,starty; //The current Checkpoint location
  bool isExit,isSpecial; //if hit exit, if hit special exit respectively
  int old_lives,old_coins,old_score,old_specials; //values of each stat going into stage
  int num_lives;// lives left
  int num_coins; // coins earned in this level
  int score; //score in this level
  int specials; //specials earned in this level
  float hp; //hp (used for lavapaths)
  int isInvincible; //if you are invincible from magic ring
  int justDied;  //a count of invincibility after dying

  bool isWeb; //if you hit a web this frame
  bool isDrain; // if you were drained hp this frame

  //Inventory storage and item affects

  typedef std::list<Item*> INVENTORY; 
  INVENTORY inventory;//list of bob's items
  unsigned int* has_item; //array of number of a certain item held
  bool has_dropped; //if bob dropped an item this frame
  std::set<Item*> recent_drops; //list of the drops bob is still hitting
  I_CODE convertItemToIndex(Item* item);
  bool pushInventory(Item* item);
  Item* popInventory();

  float warmth; //hp for ice stages
  sf::RectangleShape top_warmth;
  sf::RectangleShape bottom_bar;
  
 public:
  Bob(Level* l,float x_,float y_);
  ~Bob();

  void getStart(float& sx,float& sy) const {sx = startx;sy=starty;}
  bool getExit() const {return isExit;}
  bool getSpecialExit() const {return isSpecial;}
  int getLives() const {return old_lives+num_lives;}
  int getScore() const {return old_score+score;}
  int getSpecials() const {return old_specials+specials;}
  int getCoins() const {return old_coins+num_coins;}
  int getOldLives() const {return old_lives;}
  int getOldScore() const {return old_score;}
  int getOldSpecials() const {return old_specials;}
  int getOldCoins() const {return old_coins;}
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
  void setStats(int s,int l, int spe, int c) {old_specials=spe; old_lives=l;
    old_score=s; old_coins=c;}
  void setCheckPoint(float x_,float y_) {startx = x_;starty= y_;}
  void setExit() {isExit=true;}
  void setSpecialExit() {isSpecial=true;}

  void act();
  void render(sf::RenderWindow& window);

  bool hasItem(I_CODE c);
  void removeDynamite(C_CODE color);
};

#endif
