#include <GemDoor.h>


#ifndef _EPDOOR_H_
#define _EPDOOR_H_

class EpDoor : public GemDoor{
 public:
  EpDoor(Level* l,int x,int y,int tot_levels);

  void act();
  
  void render(sf::RenderWindow& window);

};

#endif
