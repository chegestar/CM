#include <cassert>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Level.h>
#include <utilities.h>

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
  loadInFiles();

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
    window.clear(sf::Color(200,200,200));
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
  addGraphic("cave","graphics/backgrounds/cave.png",true);
  addGraphic("crystal","graphics/backgrounds/crystal.png",true);
  addGraphic("lava","graphics/backgrounds/lava.png",true);
  addGraphic("sand","graphics/backgrounds/sand.png",true);

  addGraphic("blue_gem","graphics/Crystals/gem_blue_sparkle_strip32.png");
  addGraphic("red_gem","graphics/Crystals/gem_red_sparkle_strip32.png");
  addGraphic("green_gem","graphics/Crystals/gem_green_sparkle_strip32.png");
  addGraphic("yellow_gem","graphics/Crystals/gem_yellow_sparkle_strip32.png");
  addGraphic("purple_gem","graphics/Crystals/gem_purple_sparkle_strip32.png");
  addGraphic("black_gem","graphics/Crystals/gem_dark_sparkle_strip32.png");
  addGraphic("white_gem","graphics/Crystals/gem_light_sparkle_strip32.png");
  addGraphic("Ep_gem","graphics/Crystals/supreme_strip32.png");

  addGraphic("blue_gate","graphics/gates/crystal.png");
  addGraphic("red_gate","graphics/gates/lock_copper.png");
  addGraphic("green_gate","graphics/gates/emerald.png");
  addGraphic("yellow_gate","graphics/gates/lock_gold_sparkle_strip32.png");
  addGraphic("purple_gate","graphics/gates/lock_magic.png");
  addGraphic("black_gate","graphics/gates/lock_black.png");
  addGraphic("white_gate","graphics/gates/lock_silver_sparkle_strip32.png");
  addGraphic("Ep_gate","graphics/gates/supreme_strip7.png");
  addGraphic("coin_gate","graphics/gates/padlock_gold_sparkle_strip32.png");

  addGraphic("coin_gem","graphics/gimmicks/coins_strip32.png");
  addGraphic("magic_ring","graphics/gimmicks/super diamond_strip32.png");
  addGraphic("checkpoint","graphics/gimmicks/checkpoint.png");
  addGraphic("checkpoint_hit","graphics/gimmicks/checkpoint_active.png");
  addGraphic("life","graphics/gimmicks/life.png");
  addGraphic("web","graphics/gimmicks/web.png");
  addGraphic("trigger_off","graphics/gimmicks/detonator_off.png");
  addGraphic("trigger_on","graphics/gimmicks/detonator_on.png");
  addGraphic("exit","graphics/gimmicks/exitsign.png");
  addGraphic("dynamite","graphics/gimmicks/dynamite_pack.png");
  addGraphic("rock","graphics/gimmicks/rock.png");
  addGraphic("fireboot","graphics/gimmicks/fire boots_strip8.png");

  addGraphic("Hspider","graphics/hazards/spider_down_strip8.png");
  addGraphic("Vspider","graphics/hazards/ud spider_strip8.png");
  addGraphic("fireball_up","graphics/hazards/fireball_up_strip8.png");
  addGraphic("fireball_down","graphics/hazards/fireball_down_strip8.png");
  addGraphic("fireball_left","graphics/hazards/fireball_left_strip8.png");
  addGraphic("fireball_right","graphics/hazards/fireball_right_strip8.png");
  addGraphic("ghost","graphics/hazards/ghost_floating_strip8.png");
  addGraphic("weak_ghost","graphics/hazards/vulnerable ghost_strip8.png");
  addGraphic("fire","graphics/hazards/fire_strip5.png");

  
  addGraphic("bob_up", "graphics/Bob/explorer_up_strip8.png");
  addGraphic("bob_right", "graphics/Bob/explorer_right_strip8.png");
  addGraphic("bob_down", "graphics/Bob/explorer_down_strip8.png");
  addGraphic("bob_left", "graphics/Bob/explorer_left_strip8.png");
  addGraphic("super_bob_up", "graphics/Bob/super bob up_strip8.png");
  addGraphic("super_bob_right", "graphics/Bob/suoer bob right_strip8.png");
  addGraphic("super_bob_down", "graphics/Bob/super bob down_strip8.png");
  addGraphic("super_bob_left", "graphics/Bob/super bob left_strip8.png");


  addGraphic("cave_mid","graphics/walls/cave_cent.png");
  addGraphic("cave_horiz","graphics/walls/cave_horiz.png");
  addGraphic("cave_vert","graphics/walls/cave_vert.png");
  addGraphic("crystal_mid","graphics/walls/crystal_cent_strip13.png");
  addGraphic("crystal_horiz","graphics/walls/crystal_horiz_strip13.png");
  addGraphic("crystal_vert","graphics/walls/crystal_vert_strip13.png");
  addGraphic("lava_mid","graphics/walls/lava cent_strip9.png");
  addGraphic("lava_horiz","graphics/walls/lava horiz_strip9.png");
  addGraphic("lava_vert","graphics/walls/lava vert_strip9.png");
  addGraphic("pyramid_mid","graphics/walls/pyramid cent.png");
  addGraphic("pyramid_horiz","graphics/walls/pyramid horiz.png");
  addGraphic("pyramid_vert","graphics/walls/pyramid vert.png");
}
