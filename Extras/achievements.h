#ifndef __ACHIEVEMENTS_H__
#define __ACHIEVEMENTS_H__
#include "../Actor.h"
#include "../Codes.h"
#include <set>
//Graphic for achievement
class Achievement : public Actor {
 public:
  Achievement() : Actor() {}
  Achievement(A_CODE ach);

  void act() {}
  void render(sf::RenderWindow& window);
  int getAlpha() {return alpha;}

 private:
  std::string name,snippet,desc;
  sf::RectangleShape shape;
  int alpha;
  int tick;
  sf::Font font;
  sf::Text name_text;
  sf::Text snip;
};

//Database for achievements
typedef std::set<A_CODE> Achievements;


#endif
