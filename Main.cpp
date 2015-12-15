#include <cassert>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Level.h>

void loadInFiles();

void setupText(sf::Text& text,sf::Font& f,std::string s,int size, sf::Color c,
               float x, float y) {
  text.setFont(f);
  text.setString(s);
  text.setCharacterSize(size);
  text.setColor(c);
  text.setPosition(x,y);
}

int main(int argc, char* argv[]) {
  assert(argc==2);
  srand(time(NULL));
  //Definition of Window
  int width = 20*32;
  int height = 15*32;
  sf::RenderWindow window(sf::VideoMode(width, height), "CM Version 0.0");
  window.setFramerateLimit(60);
  Level* level = new Level(argv[1],window);
  sf::Text score_box, lives_box, ep_box;
  sf::Font f;
  f.loadFromFile("Fonts/arial.ttf");
  int size=18;
  setupText(score_box,f,"Score: 0",size,sf::Color(255,255,255),5,5);
  setupText(lives_box,f,"Lives: 0",size,sf::Color(255,255,255),width/2-70,5);
  setupText(ep_box,f,"Special: 0",size,sf::Color(255,255,255),width-150,5);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::LostFocus) {

      }
      if (event.type== sf::Event::GainedFocus) {

      }
      if (event.type==sf::Event::KeyPressed&&
          event.key.code == sf::Keyboard::Escape)
        window.close();
        
    }
    level->act();
    level->render(window);
    Bob* b = level->getBob();
    char score_text[20];
    sprintf(score_text,"Score: %d",b->getScore());
    char lives_text[10];
    sprintf(lives_text,"Lives: %d",b->getLives());
    char ep_text[10];
    sprintf(ep_text,"Specials: %d",b->getSpecials());
    score_box.setString(std::string(score_text));
    lives_box.setString(std::string(lives_text));
    ep_box.setString(std::string(ep_text));
    window.draw(score_box);
    window.draw(lives_box);
    window.draw(ep_box);
    window.display();
    window.clear(sf::Color(255,255,255));
    
    if (b->getLives()<=0||b->getExit()) {
      window.close();
    }


  }
  delete level;
  return 0;
}

void loadInFiles() {
}
