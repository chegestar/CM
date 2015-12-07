#include <cassert>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Level.h"
void loadInFiles();

int main(int argc, char* argv[]) {
  assert(argc==2);
  srand(time(NULL));
  //Definition of Window
  int width = 20*32;
  int height = 20*32;
  sf::RenderWindow window(sf::VideoMode(width, height), "CM Version 0.0");
  window.setFramerateLimit(60);
  Level* level = new Level(argv[1],window);
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
    window.display();
    window.clear(sf::Color(255,255,255));


  }
  delete level;
  return 0;
}

void loadInFiles() {
}
