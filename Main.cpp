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
    level = new Level(worlds[world_index][level_index],window,worlds[world_index].size()-1);
  }
  else
    level = new Level(argv[1],window,1);

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
      if (event.type==sf::Event::KeyPressed&&
          event.key.code == sf::Keyboard::N)
        level->getBob()->setExit();
      if (event.type==sf::Event::KeyPressed&&
          event.key.code == sf::Keyboard::R) {
        Bob* b = level->getBob();
        score = b->getOldScore();
        lives = b->getLives();
        num_spe = b->getOldSpecials();
        num_coins = b->getOldCoins();

        delete level;
        level = new Level(worlds[world_index][level_index],window,worlds[world_index].size()-1);
        Bob* b2 = level->getBob();
        b2->setStats(score,lives,num_spe,num_coins);
      }
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
    if (b->getLives()<=0) {
      window.close();
    }
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
        if (world_index>=worlds.size()) {
          window.close();
        }
        else {
          delete level;
          level = new Level(worlds[world_index][level_index],window,worlds[world_index].size()-1);
          Bob* b2 = level->getBob();
          b2->setStats(score,lives,num_spe,num_coins);
        }
      }
    }
    else if (b->getSpecialExit()) {
      if (worlds.size()==0) {
        window.close();
      }
      else {
        score = b->getScore();
        lives = b->getLives();
        num_spe = b->getSpecials();
        num_coins = b->getCoins();
        delete level;
        level = new Level(worlds[world_index][worlds[world_index].size()-1],
                          window,worlds[world_index].size()-1,true);
        Bob* b2 = level->getBob();
        b2->setStats(score,lives,num_spe,num_coins);
      }
        
    }


  }
  delete level;
  return 0;
}

void addStrip(std::string key,std::string prefix,int num) {
  char c_key[30];
  char path[100];
  for (int i=0;i<num;i++) {
    sprintf(c_key,"%s_%d",key.c_str(),i);
    sprintf(path,"%s_%d.png",prefix.c_str(),i);
    addGraphic(c_key,path);
  }
}

void loadInFiles() {
  addGraphic("cave","graphics/backgrounds/cave.png",true);
  addGraphic("crystal","graphics/backgrounds/crystal.png",true);
  addGraphic("lava","graphics/backgrounds/lava.png",true);
  addGraphic("sand","graphics/backgrounds/sand.png",true);

  addStrip("blue_gem","graphics/Crystals/blue_gem",32);
  addStrip("red_gem","graphics/Crystals/red_gem",32);
  addStrip("green_gem","graphics/Crystals/green_gem",32);
  addStrip("yellow_gem","graphics/Crystals/yello_gem",32);
  addStrip("purple_gem","graphics/Crystals/purple_gem",32);
  addStrip("black_gem","graphics/Crystals/dark_gem",32);
  addStrip("white_gem","graphics/Crystals/light_gem",32);

  addGraphic("blue_gate","graphics/gates/crystal.png");
  addGraphic("red_gate","graphics/gates/lock_copper.png");
  addGraphic("green_gate","graphics/gates/emerald.png");
  addGraphic("yellow_gate","graphics/gates/yellow_gate_1.png");
  addStrip("yellow_gate","graphics/gates/yellow_gate",32);
  addGraphic("purple_gate","graphics/gates/lock_magic.png");
  addGraphic("black_gate","graphics/gates/lock_black.png");
  addGraphic("white_gate","graphics/gates/white_gate_1.png");
  addStrip("white_gate","graphics/gates/white_gate",32);
  addStrip("coin_gate","graphics/gates/coin_gate",32);


  
  addStrip("coin_gem","graphics/gimmicks/coin",32);
  addStrip("hourglass_red","graphics/gimmicks/red_hg",12);
  addStrip("hourglass_black","graphics/gimmicks/black_hg",12);
  addStrip("magic_ring","graphics/gimmicks/super_diamond",32);
  addGraphic("checkpoint","graphics/gimmicks/checkpoint.png");
  addGraphic("checkpoint_hit","graphics/gimmicks/checkpoint_active.png");
  addGraphic("life","graphics/gimmicks/life.png");
  addGraphic("web","graphics/gimmicks/web.png");
  addGraphic("trigger_off","graphics/gimmicks/detonator_off.png");
  addGraphic("trigger_on","graphics/gimmicks/detonator_on.png");
  addGraphic("exit","graphics/gimmicks/exitsign.png");
  addStrip("special_door","graphics/gimmicks/special_door",6);
  addGraphic("door","graphics/gimmicks/doors.png");
  addGraphic("dynamite","graphics/gimmicks/dynamite_pack.png");
  addGraphic("rock","graphics/gimmicks/rock.png");
  addStrip("fireboot","graphics/gimmicks/fire_boot",8);

  addStrip("Hspider","graphics/hazards/hspider",8);
  addStrip("Vspider","graphics/hazards/vspider",8);
  addStrip("fireball_up","graphics/hazards/fireball_up",8);
  addStrip("fireball_down","graphics/hazards/fireball_down",8);
  addStrip("fireball_left","graphics/hazards/fireball_left",8);
  addStrip("fireball_right","graphics/hazards/fireball_right",8);
  addStrip("ghost","graphics/hazards/ghost",8);
  addStrip("weak_ghost","graphics/hazards/weak_ghost",8);
  addStrip("fire","graphics/hazards/fire",5);
  addStrip("explosion","graphics/hazards/explosion",7);
  
  addStrip("bob_up","graphics/Bob/bob_up",8);
  addStrip("bob_left","graphics/Bob/bob_left",8);
  addStrip("bob_down","graphics/Bob/bob_down",8);
  addStrip("bob_right","graphics/Bob/bob_right",8);
  addStrip("super_bob_up","graphics/Bob/super_bob_up",8);
  addStrip("super_bob_left","graphics/Bob/super_bob_left",8);
  addStrip("super_bob_down","graphics/Bob/super_bob_down",8);
  addStrip("super_bob_right","graphics/Bob/super_bob_right",8);





  addGraphic("cave_mid","graphics/walls/cave_cent.png");
  addGraphic("cave_horiz","graphics/walls/cave_horiz.png");
  addGraphic("cave_vert","graphics/walls/cave_vert.png");
  addStrip("crystal_mid","graphics/walls/crystal_cent",13);
  addStrip("crystal_horiz","graphics/walls/crystal_horiz",13);
  addStrip("crystal_vert","graphics/walls/crystal_vert",13);
  addStrip("lava_mid","graphics/walls/lava_cent",9);
  addStrip("lava_horiz","graphics/walls/lava_horiz",9);
  addStrip("lava_vert","graphics/walls/lava_vert",9);
  addGraphic("pyramid_mid","graphics/walls/pyramid cent.png");
  addGraphic("pyramid_horiz","graphics/walls/pyramid horiz.png");
  addGraphic("pyramid_vert","graphics/walls/pyramid vert.png");
}
