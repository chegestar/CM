
#include "SpeechBubble.h"


SpeechBubble::SpeechBubble() {

  font.loadFromFile("Fonts/arial.ttf");
  text.setFont(font);
  text.setString("");

  text.setColor(sf::Color(0,0,0));
  text.setPosition(10,10);

  shape.setFillColor(sf::Color(0,0,150,255/2));
  shape.setSize(sf::Vector2f(32*20,100));
  
  arrow.setFillColor(sf::Color(0,0,150,255/2));
  arrow.setPointCount(3);

  reset();
}

void SpeechBubble::reset() {
  width=height=ticks=0;
  shape.setPosition(1000,1000);
  text.setPosition(1000,1000);
  arrow.setPosition(1000,1000);
}
void SpeechBubble::setup(std::string m) {
  message = m;
  text.setString(message);
  text.setOrigin((text.findCharacterPos(message.size()).x-text.findCharacterPos(0).x)/2,0);
}

void SpeechBubble::act(float x, float y) {
  x_ = x;
  y_ = y;
  if (ticks<30) 
    ticks++;
 
  x = x-x/30*ticks;
  width = (32*20-x)/30*ticks;
  bool aimLow=false;
  if (y-32<32*7) {
    y = y+(32*15-100-y)/30.0*ticks;
  }
  else {
    aimLow=true;
    y = y+(32-y)/30.0*ticks;
  }
  height =100.0/30*ticks;
  
  shape.setPosition(x,y);
  shape.setSize(sf::Vector2f(width,height));
  text.setCharacterSize(25.0*ticks/30);
  text.setOrigin((text.findCharacterPos(message.size()).x-text.findCharacterPos(0).x)/2,0);
  text.setPosition(x+width/2,y+10);
  
  arrow.setPosition(0,0);
  arrow.setPoint(0,sf::Vector2f(x_,y_));
  int separation=30;
  arrow.setPoint(1,sf::Vector2f(x+width/2+separation,y+aimLow*height));
  arrow.setPoint(2,sf::Vector2f(x+width/2-separation,y+aimLow*height));
}

void SpeechBubble::render(sf::RenderWindow& window) {

  window.draw(shape);
  window.draw(arrow);
  window.draw(text);
  
}


