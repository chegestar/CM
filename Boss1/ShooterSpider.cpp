#include "SpiderBoss.h"
#include <Spider.h>
#include <Level.h>
#include <Exit.h>
#include <EpCrystal.h>
#include <utilities.h>
#include <Codes.h>
ShooterSpider::ShooterSpider(Level* l, float level_width,float screen_width):
  Actor(l,level_width-screen_width/2-50+32,-32*3,100,32*3-2), Boss(l,x,y,width,height) {
  x=level_width-screen_width/2-width/2;
  startx=x;
  y = -32*3;
  isMove = 0;
  timer=0;
  hp=60*30; //1800

  char key[20];
  std::vector<std::string> keys;
  for (int i=0;i<8;i++) {
    sprintf(key,"Vspider_%d",i);
    keys.push_back(key);
  }
  texture_keys.push_back(keys);
  

  bottom_bar.setSize(sf::Vector2f(100,24));
  bottom_bar.setFillColor(sf::Color(255,0,0));
  bottom_bar.setPosition(screen_width-150,13*32+4);

  top_bar.setSize(sf::Vector2f(100,24));
  top_bar.setFillColor(sf::Color(0,255,0));
  top_bar.setPosition(screen_width-150,13*32+4);

}

void ShooterSpider::reset() {
  hp=60*30;
  isMove=1;
  timer=0;
  x=startx;
  y = -32*3;
  bullets.clear();
  spiders.clear();
}

void ShooterSpider::start() {
  isMove=1;
}

void ShooterSpider::act() {
  if (isMove==1) {
    y+=2;
    if (y>32)
      isMove=2;
  }
  else if (isMove==2) {
    timer++;
    hp--;
    if (timer>45) {
      FireBullet* bullet=new FireBullet(level,x+width/2-7.5,y+height);
      bullet->setAngle(getAngleTo(bullet,level->getBob()));
      bullets.push_back(bullet);
      timer=0;
    }
    std::list<FireBullet*>::iterator itr;
    for (itr=bullets.begin();itr!=bullets.end();itr++)
      (*itr)->act();
    std::list<Spider*>::iterator itr2;
    for (itr2=spiders.begin();itr2!=spiders.end();itr2++)
      (*itr2)->act();

    if (hp==0) {
      Exit* exit = new Exit(level,int(x/32)*32,32*13);
      EpCrystal* special = new EpCrystal(level,int(x/32+2)*32,32*13);
      level->addStationary(exit,13,int(x/32));
      level->addStationary(special,13,int(x/32)+2);
      level->setLevelType(CONTINUOUS);
      level->unhalt();
    }
    else if (hp%600==0) {
      //Make 2 vertical spiders
      Spider* spider1 = new Spider(level,level->getX()+32*(8-4*(hp/1200)),32,true);
      Spider* spider2 = new Spider(level,level->getX()+32*(11+4*(hp/1200)),32,true);
      spiders.push_back(spider1);
      spiders.push_back(spider2);
    }
    else if (hp%300==0) {
      //Make horizontal spider
      Spider* spider = new Spider(level,level->getX()+32,32*(9+2*(hp/600)),false);
      spiders.push_back(spider);
    }

  }
  Boss::act();
  texture_step++;
}

void ShooterSpider::render(sf::RenderWindow& window) {
  
  std::list<FireBullet*>::iterator itr;
  for (itr=bullets.begin();itr!=bullets.end();itr++)
    (*itr)->render(window);
  std::list<Spider*>::iterator itr2;
  for (itr2=spiders.begin();itr2!=spiders.end();itr2++)
    (*itr2)->render(window);
  
  Boss::render(window);
  if (isMove>0) {
    //render Health bar
    top_bar.setSize(sf::Vector2f(100*hp*1.0/(30*60),24));
    window.draw(bottom_bar);
    window.draw(top_bar);
  }
}
