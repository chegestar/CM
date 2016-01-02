#ifndef ___SPEECHBUBBLE_H__
#define ___SPEECHBUBBLE_H__
#include <SFML/Graphics.hpp>
#include <string>

class SpeechBubble {
 public:
  SpeechBubble();

  void reset();
  void setup(std::string m);
  
  void act(float x, float y);
  void render(sf::RenderWindow& window);

 protected:
  int ticks;
  float x_,y_;
  float width,height;
  std::string message;
  sf::Font font;
  sf::Text text;
  sf::RectangleShape shape;
  sf::ConvexShape arrow;
};

#endif
