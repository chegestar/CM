#include <Boss.h>
#include <Switch.h>
#include <Bullet.h>
#include <Spider.h>

class ChaseSpider : public Boss{
 private:
  bool isMove;
 public:
  ChaseSpider(Level* l,int index);

  void reset();

  void act();
};


class FireBullet : public Bullet {
 public:
  FireBullet(Level* l, float x, float y);

};

class ShooterSpider : public Boss {
 private:
  int isMove;
  int timer;
  std::list<FireBullet*> bullets;
  std::list<Spider*> spiders;
  sf::RectangleShape bottom_bar;
  sf::RectangleShape top_bar;
  float startx;
 public:
  ShooterSpider(Level* l, float level_width, float screen_width);

  void start();
  void reset();

  void act();
  void render(sf::RenderWindow& window);
};


class SpiderExit : public Switch {
 private:
  ShooterSpider* boss;
 public:
  SpiderExit(Level* l,ShooterSpider* b,float x);
  
  void reset();

  int activate();
};
