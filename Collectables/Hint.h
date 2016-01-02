#include <Switch.h>
#include <SpeechBubble.h>

#ifndef __HINT_H__
#define __HINT_H__

class Hint : public Switch {
 private:
  SpeechBubble bubble;
  bool was_hit;
 public:
  Hint(Level* l, float x_, float y_, std::string message);

  int activate();

  void act();
  void render(sf::RenderWindow& window);
};

#endif
