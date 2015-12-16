
#include <Actor.h>
#include <Mover.h>

#ifndef __BOB__H__
#define __BOB__H__
class Bob : public Mover{
 private:
  float startx,starty;
  bool isExit;
  int num_lives;
  int num_coins;
  int score;
  int specials;

  bool isWeb;
 public:
  Bob(Level* l,float x_,float y_);

  bool getExit() const {return isExit;}
  int getLives() const {return num_lives;}
  int getScore() const {return score;}
  int getSpecials() const {return specials;}

  void web();
  void earnEP() {specials++;};
  void earnLife() {num_lives++;};
  void earnCoin() {num_coins++; if (num_coins>=100) {num_coins=0;num_lives++;}}
  void die() {x=startx; y = starty; num_lives--;}

  void act();
  void render(sf::RenderWindow& window);
};

#endif
