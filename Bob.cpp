#include "Bob.h"
#include <Rock.h>
#include <Level.h>
#include <Exit.h>
#include <utilities.h>

#include <FireBoot.h>
#include <Dynamite.h>

#include <cassert>

Bob::Bob(Level* l,float x_,float y_) : 
  Actor(l,x_,y_,l->getWidth()*5/8,l->getHeight()*5/8), 
  Mover(l,x,y,width,height),
  startx(x), starty(y){
  isExit=isSpecial=false;
  num_lives=0;
  old_lives=3;
  score=specials=num_coins=0;
  old_score=old_specials=old_coins=0;
  hp=100;
#ifdef COMPILE_DEBUG
  glitch_everythang=false;
#endif 
  justDied=isInvincible=0;

  has_item = new unsigned int[MAX_INVENTORY];
  for (unsigned int i=0;i<MAX_INVENTORY;i++)
    has_item[i]=0;
  has_dropped=false;

  warmth=100;
  top_warmth.setFillColor(sf::Color(0,255,0));
  bottom_bar.setFillColor(sf::Color(255,0,0));
  bottom_bar.setSize(sf::Vector2f(width,5));
  std::vector<std::string> keys;
  char key[30];
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","bob_up",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","bob_right",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","bob_down",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","bob_left",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","super_bob_up",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","super_bob_right",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","super_bob_down",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  for (int i=0;i<8;i++) {
    sprintf(key,"%s_%d","super_bob_left",i);
    keys.push_back(std::string(key));
  }
  texture_keys.push_back(keys);
  keys.clear();
  

}

Bob::~Bob() {
  delete [] has_item;
}

void Bob::web() {
  if (!isWeb) {
    shiftX(-(x-lastx)*3.5/5);
    shiftY(-(y-lasty)*3.5/5);
  }
  isWeb=true;
}

void Bob::drain() {
  if (!isDrain) {
    hp-=.25;
  }
  if (hp<=0)
    die();
  isDrain=true;
}

void Bob::drainWarmth() {
  warmth-=.125;
  if (warmth<=0)
    die();

}

void Bob::warmup() {
  warmth+=.5;
  if (warmth>100)
    warmth=100;
}

bool Bob::die() {
#ifdef COMPILE_DEBUG
  if (glitch_everythang)
    return true;
#endif
  if (isInvincible>0)
    return false;
  if (justDied>0)
    return true;
  x = startx; 
  y = starty; 
  if (old_lives>0)
    old_lives--; 
  else
    num_lives--;
  hp=100;
  warmth=100;
  justDied=60*1.5;
  return true;
}

std::vector<Line> Bob::getLines() const {
  return lines;
}

void Bob::act() {
  Mover::act();
  isWeb=false;
  if (!isDrain) hp+=1;
  if (hp>100)
    hp=100;
  isDrain=false;
  if (isInvincible>0)
    isInvincible--;
  if (justDied>0)
    justDied--;
  if (level->getZone()==ICE) {
    drainWarmth();
    if (!has_item[JACKET])
      drainWarmth();
  }
  float speed = 2.5;
  if (has_item[FIRE_BOOT]) {
    speed*=3.5/5;
  }
  if (has_item[DYNAMITE]) {
    speed*=pow(.99,has_item[DYNAMITE]);
  }
  bool didMove=false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    didMove=true;
    texture_set=0;
    y-=getMovementCorrectionY(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    didMove=true;
    texture_set=2;
    y+=getMovementCorrectionY(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    didMove=true;
    texture_set=3;
    x-=getMovementCorrectionX(speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    didMove=true;
    texture_set=1;
    x+=getMovementCorrectionX(speed);
  }
  if (didMove) {
    texture_step++;
  }
  else
    texture_step=0;
  texture_set=(texture_set%4)+(isInvincible>0)*4;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (!has_dropped) {
      int r = y/level->getHeight();
      int c = x/level->getWidth();
      Item* item = popInventory();
      if (item) {
        level->findOpenPosition(r,c);
        item->setPosition(c*level->getWidth(),r*level->getHeight());
        level->addStationary(item,r,c,false);
        recent_drops.insert(item);
        has_dropped=true;
      }
    }

  }
  else {
    has_dropped=false;
  }

  lines.clear();
  lines.push_back(Line(getBoundX1(),getBoundY1(),getBoundX2(),getBoundY1()));
  lines.push_back(Line(getBoundX2(),getBoundY1(),getBoundX2(),getBoundY2()));
  lines.push_back(Line(getBoundX1(),getBoundY2(),getBoundX2(),getBoundY2()));
  lines.push_back(Line(getBoundX1(),getBoundY1(),getBoundX1(),getBoundY2()));
    
  std::set<Item*> new_drops;
#ifdef COMPILE_DEBUG
  if (!glitch_everythang) {
#endif
  std::vector<Actor*> stationary;
  level->testHitStationary(this,stationary);
  for (unsigned int i=0;i<stationary.size();i++) {
    Actor* actor = stationary[i];
    if (!actor) continue;
    int dir = getApproachDir(this,actor);
    if (dynamic_cast<Rock*>(actor)) {
      if (dir%2) 
        actor->shiftY(getY1()-actor->getY2());
      if ((dir>>1)%2)
        actor->shiftX(getX2()-actor->getX1());
      if ((dir>>2)%2)
        actor->shiftY(getY2()-actor->getY1());
      if ((dir>>3)%2)
        actor->shiftX(getX1()-actor->getX2());
    }
    else if (dynamic_cast<Block*>(actor)) {
      Block* b = dynamic_cast<Block*>(actor);
      b->push_back(this,dir);
    }
    else if (dynamic_cast<Item*>(actor)) {
      Item* item = static_cast<Item*>(actor);
      if (recent_drops.find(item)!=recent_drops.end()) {
        new_drops.insert(item);
      }
      else  {
        if (pushInventory(item)) {
          
          actor->removePosition();
        }
      }
    }
    else if (dynamic_cast<Collectable*>(actor)) {
      int s =actor->activate();
      score+=s;
    }
    else if (dynamic_cast<Switch*>(actor)) {
      actor->activate();
    }
  }
  recent_drops=new_drops;
#ifdef COMPILE_DEBUG
  }
#endif
  std::vector<Collectable*> collects;
  level->testHitCollectable(this,collects);
  
  for (unsigned int i=0;i<collects.size();i++) {
    Collectable* collect = collects[i];
    if (!collect) continue;
    int s = collect->activate();
    score+=s;
  }

}

void Bob::render(sf::RenderWindow& window) {
  if (level->getZone()==ICE&&warmth!=100) {
    top_warmth.setSize(sf::Vector2f(bottom_bar.getSize().x*warmth/100,bottom_bar.getSize().y));
    top_warmth.setPosition(getX1(),getY1()+height+2);
    bottom_bar.setPosition(getX1(),getY1()+height+2);
    window.draw(bottom_bar);
    window.draw(top_warmth);
  }
  sprite.setColor(sf::Color(255,255,255,(1-(justDied/4)%2)*255));
  Actor::render(window);
}

I_CODE Bob::convertItemToIndex(Item* item) {
  if (dynamic_cast<FireBoot*>(item)) 
    return FIRE_BOOT;
  else if (dynamic_cast<Dynamite*>(item))
    return DYNAMITE;
  else
    return NO_ITEM;
}

bool Bob::pushInventory(Item* item) {

  I_CODE index = convertItemToIndex(item);
  assert(index!=NO_ITEM);
  inventory.push_back(item);
  has_item[index]++;
  return true;
}

Item* Bob::popInventory() {
  if (inventory.size()==0)
    return NULL;
  Item* item = *(inventory.begin());
  I_CODE index = convertItemToIndex(item);
  assert(index!=NO_ITEM);
  inventory.pop_front();
  has_item[index]--;
  return item;
}

bool Bob::hasItem(I_CODE index) {
  assert(index!=NO_ITEM);
  assert(index<MAX_INVENTORY);
  return has_item[index];
}

void Bob::removeDynamite(C_CODE color) {
  std::list<Item*>::iterator itr;
  for (itr=inventory.begin();itr!=inventory.end();itr++) {
    Dynamite* d;
    if ((d=dynamic_cast<Dynamite*>(*itr))) {
      if (d->getColor()==color)  {
        std::list<Item*>::iterator temp = itr;
        itr--;
        inventory.erase(temp);
      }
    }
  }
}
