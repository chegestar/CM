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
  assert(argc==2||argc==1);
  srand(time(NULL));

  //Definition of Window
  int width = 20*32;
  int height = 15*32;
  sf::RenderWindow window(sf::VideoMode(width, height), "CM Version 0.0");
  window.setFramerateLimit(60);
  sf::Text score_box, lives_box, ep_box;
  sf::Font f;
  f.loadFromFile("Fonts/arial.ttf");
  int size=18;
  int color=200;
  setupText(score_box,f,"Score: 0",size,sf::Color(color,color,color),5,5);
  setupText(lives_box,f,"Lives: 0",size,sf::Color(color,color,color),width/2-70,5);
  setupText(ep_box,f,"Special: 0",size,sf::Color(color,color,color),width-150,5);

  std::vector<std::vector<std::string> > worlds;
  Level* level;
  unsigned int level_index=0;
  unsigned int world_index=0;
  if (argc==1) {
    std::ifstream in_str("Level_order.txt");
    char c;
    while (in_str>>c) {
      int num;
      in_str>>num;
      std::vector<std::string> world;
      std::string level_file;
      for (int i=0;i<num;i++) {
        in_str>>level_file;
        world.push_back(level_file);
      }
      worlds.push_back(world);
    }
    level = new Level(worlds[world_index][level_index],window);
  }
  else
    level = new Level(argv[1],window);

  //Global Bob stats
  int score,lives,num_spe,num_coins;
  bool isPause=false;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::LostFocus) {
        isPause=true;
      }
      if (event.type== sf::Event::GainedFocus) {
        isPause=false;
      }
      if (event.type==sf::Event::KeyPressed&&
          event.key.code == sf::Keyboard::Escape)
        window.close();
        
    }
    if (!isPause)
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
    if (b->getLives()<=0)
      window.close();
    if (b->getExit()) {
      if (worlds.size()==0) {
        window.close();
      }
      else {
        score = b->getScore();
        lives = b->getLives();
        num_spe = b->getSpecials();
        num_coins = b->getCoins();
        level_index++;
        if (level_index>=worlds[world_index].size()-1) {
          level_index=0;
          world_index++;
        }
        if (world_index>=worlds.size())
          window.close();
        else {
          delete level;
          level = new Level(worlds[world_index][level_index],window);
          Bob* b2 = level->getBob();
          b2->setStats(score,lives,num_spe,num_coins);
        }
      }
    }


  }
  delete level;
  return 0;
}

void loadInFiles() {
}
