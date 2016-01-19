#include "Level.h"
#include <Bob.h>
#include <Fireball.h>
#include <Ghost.h>
#include <SpiderBoss.h>
#include <EpDoor.h>
#include <Rock.h>
#include <SpecialDoor.h>
#include <Coin.h>
#include <HourGlass.h>
#include <MagicRing.h>
#include <EpCrystal.h>
#include <Crystal.h>
#include <Life.h>
#include <Web.h>
#include <FakeExit.h>
#include <Trigger.h>
#include <Hint.h>
#include <Lava.h>
#include <Pit.h>
#include <FireBoot.h>
#include <Dynamite.h>
#include <utilities.h>
#include <cassert>
#include <algorithm>
#include <cmath>
Level::Level() {
  bob=NULL;
}

Actor* Level::getStationary(std::string key, int x, int y,std::ifstream& in_str) {
    if (key=="b"||key=="block") {
      return new Block(this,x*width,y*height);
    }
    else if (key=="coin"||key=="co") {
      return new Coin(this,x*width,y*height);
    }
    else if (key=="ecrystal" || key=="ec") {
      return new EpCrystal(this,x*width,y*height);
    }
    else if (key=="epdoor" || key=="ep") {
      return new EpDoor(this,x*width,y*height,num_levels);
    }
    else if (key=="life" || key=="l") {
      return new Life(this,x*width,y*height);
    }
    else if (key=="hourglass"|| key=="h") {
      char c;
      in_str>>c;
      return new HourGlass(this,x*width,y*height,c=='R');
    }
    else if (key=="magicring"|| key=="mr") {
      return new MagicRing(this,x*width,y*height);
    }
    else if (key=="web"||key=="w") {
      return new Web(this,x*width,y*height);
    }
    else if (key=="fakeexit"||key=="fe") {
      int newy,newx;
      in_str>>newy>>newx;
      return new FakeExit(this,x*width,y*height,newx*width,newy*height);
    }
    else if (key=="hint") {
      std::string m;
      getline(in_str,m);
      return new Hint(this,x*width,y*height,m);
    }
    else if (key=="lava"||key=="la") {
      return new Lava(this,x*width,y*height);
    }
    else if (key=="lavapath"||key=="lap") {
      if (stationary[y][x]) {
        if (dynamic_cast<Lava*>(stationary[y][x]))
          dynamic_cast<Lava*>(stationary[y][x])->setPath();
        else
          std::cerr<<"[WARNING] Location: ("<<y<<','<<x<<") is not lava";
        return NULL;
      }
      else {
        Lava* l = new Lava(this,x*width,y*height);
        l->setPath();
        return l;
      }
    }
    else if (key=="pit") {
      return new Pit(this,x*width,y*height);
    }
    else if (key=="fireboot"||key=="fib") {
      return new FireBoot(this,x*width,y*height);
    }
    else if (key=="dynamite"||key=="dm") {
      return new Dynamite(this,x*width,y*height,COIN);
    }
    return NULL;
}
Level::Level(std::string filename,sf::RenderWindow& window, int tot_levels,bool isS) {
  std::ifstream in_str(filename.c_str());
  if (!in_str) {
    throw 1;
  }
  isSong=false;
  num_levels=tot_levels;
  x_=y_=0;
  level_type=NORMAL;
  isSpecial=isS;
  isWrapped=false; isHalted=false;
  width=32;
  height=32;
  window_width = window.getSize().x;
  window_height = window.getSize().y;
  in_str>>rows>>cols;
  grows=gcols=1;
  std::string key;

  //Level Options
  int x,y;
  in_str>>key;
  if (key=="NORMAL_LEVEL") {
    assert(!actors.size());
    level_type=NORMAL;
  }
  else if (key=="GRID_LEVEL") {
    level_type=GRID;
    in_str>>y>>x;
    grows=y;
    gcols=x;
  }
  else if (key=="CONTINUOUS_LEVEL") {
    level_type=CONTINUOUS;
  }
  else if (key=="AUTOSCROLL_LEVEL") {
    level_type=AUTOSCROLL;
    char c;
    in_str>>c>>dir;
    isVertical= (c=='V');
  }

  in_str>>key;
  background.setPosition(0,0);
  zone = getZoneType(key);
  if (zone==CAVE)  {
    background.setTexture(getGraphic("cave"));
  }
  else if (zone==CRYSTAL) {
    background.setTexture(getGraphic("crystal"));
  }
  else if (zone==LAVA) {
    background.setTexture(getGraphic("lava"));
  }
  else if (zone==PYRAMID) {
    background.setTexture(getGraphic("sand"));
  }
  else if (zone==ICE) {
    background.setTexture(getGraphic("crystal"));
  }
  else if (zone==DARK) {
    background.setTexture(getGraphic("cave"));
  }
  else if (zone==FACTORY) {
    background.setTexture(getGraphic("cave"));
  }
  else if (zone==SPECIAL) {
    background.setTexture(getGraphic("cave"));
  }
  else {
    background.setTexture(getGraphic("cave"));
    for (int i=0;i<grows*gcols;i++) {
      in_str>>key;
      hub_grid.push_back(getZoneType(key));
    }
  }
  background.setTextureRect(sf::IntRect(0,0,32*20,32*15));

  min_depth=-1000;
  stationary_depth=0;
  gem_depth=10000;
  door_depth=20000;
  monster_depth=30000;
  wall_depth=40000;

  max_rows = rows*grows;
  max_cols= cols*gcols;
  stationary = new Actor**[max_rows];
  for (int i=0;i<max_rows;i++)  {
    stationary[i] = new Actor*[max_cols];
    for (int j=0;j<max_cols;j++)
      stationary[i][j] = NULL;
  }
  gems = new Collectable**[max_rows];
  for (int i=0;i<max_rows;i++)  {
    gems[i] = new Collectable*[max_cols];
    for (int j=0;j<max_cols;j++)
      gems[i][j] = NULL;
  }

  while (in_str>>key) {
    int end=0;
    int end2=0;
    //Level options
    if (key=="WRAPPED") {
      isWrapped=true;
    }
    else if (key=="HALTED") {
      isHalted=true;
    }
    //Prefix Options
    else if (key=="row") {
      in_str>>y>>x>>end>>key;
      assert(end>=x);
      for (int i=x;i<=end;i++) {
        addStationary(getStationary(key,i,y,in_str),y,i);
      }
    }
    else if (key=="col") {
      in_str>>x>>y>>end>>key;
      assert(end>=y);
      for (int i =y;i<=end;i++) {
        addStationary(getStationary(key,x,i,in_str),i,x);
      }

    }
    else if (key=="rect") {
      in_str>>y>>x>>end>>end2>>key;
      assert(end>=y&&end2>=x);
      for (int i = y;i<=end;i++)
        for (int j=x;j<=end2;j++)
          addStationary(getStationary(key,j,i,in_str),i,j);
    }

    //Bob Option
    else if (key=="start"||key=="s") {
      in_str>>y>>x;
      bob = new Bob(this,x*height,y*width);
      insert(bob,min_depth);
    }
    else if (key=="c"||key=="check") {
      in_str>>y>>x;
      insert(new CheckPoint(this,x*width,y*height),stationary_depth);
    }
    else if (key=="exit") {
      in_str>>y>>x;
      insert(new Exit(this,x*width,y*height),stationary_depth);
    }
    else if (key=="specialexit"||key=="se") {
      in_str>>y>>x;
      insert(new SpecialDoor(this,x*width,y*height),stationary_depth);
    }

    //Moving Options
    else if (key=="spider"||key=="sp") {
      char c;
      in_str>>y>>x>>c;
      insert(new Spider(this,(x)*width,(y)*height,c=='V'),monster_depth);
    }
    else if (key=="spiders"||key=="ss") {
      char c;
      in_str>>y>>x>>c>>dir;
      insert(new Spider(this,(x)*width,(y)*height,c=='V',dir),monster_depth);
    }

    else if (key=="fireball"||key=="fb") {
      char c;
      in_str>>y>>x>>c;
      insert(new Fireball(this,(x)*width,(y)*height,c=='V'),monster_depth);
    }
    else if (key=="ghost"||key=="gh") {
      in_str>>y>>x;
      insert(new Ghost(this,(x)*width,(y)*height),monster_depth);
    }
    else if (key=="rock") {
      in_str>>y>>x;
      Rock* r = new Rock(this,x*width,y*height);
      insert(r,wall_depth);
      rocks.push_back(r);
      std::list<Rock*>::iterator temp = rocks.end();
      temp--;
      r->linkPosition(temp);
    }

    //Syntactic Sugar
    else if (key=="brow") {
      in_str>>y;
      for (int i=0;i<max_cols;i++)
        if (!stationary[y][i]) {
          addStationary(new Block(this,i*width,y*height),y,i);
        }
    }
    else if (key=="bcol") {
      in_str>>x;
      for (int i=0;i<max_rows;i++)
        if (!stationary[i][x]) {
          addStationary( new Block(this,x*width,i*height),i,x);
        }
    }

    //Block Options
    else if (key=="read_board") {
      for (int i=0;i<max_rows;i++) {
        for (int j=0;j<max_cols;j++) {
          in_str>>key;
          Actor* actor = getStationary(key,j,i,in_str);
          if (actor) {
            addStationary(actor,i,j);
          }
        }
      }
    }
    else if (key=="read_gems") {
      std::vector<std::vector<GemDoor*>* > doorss;
      std::vector<C_CODE> colors;
      int num_colors;
      in_str>>num_colors;
      for (int i=0;i<num_colors;i++) {
        std::vector<GemDoor*>* doors = new std::vector<GemDoor*>();
        std::string color;

        int num;
        in_str>>color>>num;
        C_CODE col = getColor(color);
        colors.push_back(col);
        for (int j=0;j<num;j++) {
          in_str>>y>>x;
          GemDoor* door = new GemDoor(this,x*width,y*height,col);
          if (j==0)
            door->own(doors);
          doors->push_back(door);
          addStationary((*doors)[j],y,x);
        }
        doorss.push_back(doors);
      }

      for (int i=0;i<max_rows;i++) {
        for (int j=0;j<max_cols;j++) {
          int index;
          in_str>>index;
          if (index==0) continue;
          addGem(new Crystal(this,j*width,i*height,colors[index-1],doorss[index-1]),i,j);
        }
      }
    }
    else if (key=="gemdoor"||key=="g") {
      std::string color;
      int num;
      in_str>>color>>num;
      C_CODE col = getColor(color);
      std::vector<GemDoor*>* doors = new std::vector<GemDoor*>();
      for (int i=0;i<num;i++) {
        in_str>>y>>x;
        doors->push_back(new GemDoor(this,x*width,y*height,col));
        if (i==0)
          (*doors)[0]->own(doors);
        addStationary((*doors)[i],y,x);
        
      }
      std::string c;
      while ((in_str>>c)&&(c!=";")) {
        if (c=="row") {
          in_str>>y>>x>>end;
          for (int i=x;i<=end;i++)
            addGem(new Crystal(this,i*width,y*height,col,doors),y,i);
        }
        else if (c=="col") {
          in_str>>x>>y>>end;
          for (int i=y;i<=end;i++)
            addGem(new Crystal(this,x*width,i*height,col,doors),i,x);
        }
        else if (c=="rect") {
          in_str>>y>>x>>end>>end2;
          for (int i=y;i<=end;i++)
            for (int j=x;j<=end2;j++)
              addGem(new Crystal(this,j*width,i*height,col,doors),i,j);
        }
        else {
          in_str>>y>>x;
          addGem(new Crystal(this,x*width,y*height,col,doors),y,x);
        }
      }
    }
    else if (key=="trigger"||key=="t") {
      std::string color;
      in_str>>color>>y>>x;
      C_CODE col = getColor(color);
      int storey =y; int storex = x;
      Trigger* trigger = new Trigger(this,x*width,y*height,col);
      std::string c;
      while ((in_str>>c)&&(c!=";")) {
        if (c=="row") {
          in_str>>y>>x>>end;
          for (int i=x;i<=end;i++) {
            Dynamite* d = new Dynamite(this,i*width,y*height,col);
            trigger->add(d);
            addStationary(d,y,i);
          }
        }
        else if (c=="col") {
          in_str>>x>>y>>end;
          for (int i=y;i<=end;i++) {
            Dynamite* d = new Dynamite(this,x*width,i*height,col);
            trigger->add(d);
            addStationary(d,i,x);
          }
        }
        else if (c=="rect") {
          in_str>>y>>x>>end>>end2;
          for (int i=y;i<=end;i++)
            for (int j=x;j<=end2;j++) {
              Dynamite* d = new Dynamite(this,j*width,i*height,col);
              trigger->add(d);
              addStationary(d,i,j);
            }
        }
        else {
          in_str>>y>>x;
          Dynamite* d = new Dynamite(this,x*width,y*height,col);
          trigger->add(d);
          addStationary(d,y,x);
        }
      }
      addStationary(trigger,storey,storex);
    }

    //Bosses
    else if (key=="spiderboss") {
      for (int i=0;i<5;i++)
        insert(new ChaseSpider(this,i),monster_depth);
      ShooterSpider* boss = new ShooterSpider(this,(max_cols)*width,window_width);
      insert(boss,monster_depth);
      SpiderExit* exit = new SpiderExit(this,boss,(max_cols-10)*width);
      addStationary(exit,13,(max_cols-10));
    }

    //Let's do all the stationary by calling the getStationary function
    else {
      in_str>>y>>x;
      Actor* actor = getStationary(key,x,y,in_str);
      if (actor)
        addStationary(actor,y,x);
    }
  }

  setBlocks();
}

Level::~Level() {
  ACTORS::iterator itr;
  for (itr=actors.begin();itr!=actors.end();itr++) {
    delete itr->second;
  }
  for (int i=0;i<rows;i++)
    delete [] gems[i];
  delete [] gems;

  for (int i=0;i<rows;i++)
    delete [] stationary[i];
  delete [] stationary;
}

Z_TYPE Level::getHubZone(int x,int y) const {
  int r = y/window_height;
  int c = x/window_width;
  return hub_grid[r*gcols+c];
}
void Level::act() {
  //Spider Boss reset
  if (chase_indices.size()) {
    int index=0;
    for (int i=0;i<5;i++) {
      if (chase_indices[index]!=i) {
        insert(new ChaseSpider(this,i),monster_depth);
      }
      else
        index++;
    }
    bob->resetPosition();
    chase_indices.clear();
  }


  if (zone==HUB) {
    std::string key = getZoneString(getHubZone(x_,y_));
    background.setTexture(getGraphic(key));
    background.setTextureRect(sf::IntRect(0,0,32*20,32*15));


  }
  bob->act();
  ACTORS::iterator itr=actors.begin();
  bool is_block_gone=false;
  while(itr!=actors.end()) {
    if (itr->second!=bob)
      itr->second->act();
    if (itr->second->getDead()) {
      std::list<Rock*>::iterator* rock_itr = itr->second->removePosition();
      if (rock_itr) rocks.erase(*rock_itr);
      if (dynamic_cast<Block*>(itr->second))
        is_block_gone=true;
      delete itr->second;
      ACTORS::iterator temp_itr = itr;
      itr--;
      actors.erase(temp_itr);
    }
    itr++;
  }
  if (is_block_gone)
    setBlocks();
  if (level_type==GRID) {
    if (getRow()<grows-1&&bob->getY1()>window_height)
      y_ +=height*(rows);
    if (getRow()>0&&bob->getY2()<0)
      y_-=height*(rows);
    if (getCol()<gcols-1&&bob->getX1()>window_width)
      x_+=width*(cols);
    if (getCol()>0&&bob->getX2()<0)
      x_-=width*(cols);
  }
  else if (level_type==CONTINUOUS&&!isHalted) {
    const float max_num = 5;
    if (bob->getY2()>window_height*2/3) {
      float diff = fabs(bob->getY2()-window_height*2/3);
      diff = std::min(diff,max_num);
      y_+=diff;
      if (y_>32*rows-window_height)
        y_ = 32*rows-window_height;
    }
    if (bob->getY1()<window_height*1/3) {
      float diff = fabs(bob->getY1()-window_height*1/3);
      diff = std::min(diff,max_num);
      y_-=diff;
      if (y_<0)
        y_ = 0;
    }
    if (bob->getX2()>window_width) {
      float diff = fabs(bob->getX2()-window_width*2/3);
      diff = std::min(diff,max_num);
      x_+=diff;
      if (x_>32*cols-window_width)
        x_ = 32*cols-window_width;
    }
    if (bob->getX1()<0) {
      float diff = fabs(bob->getX1()-window_width*1/3);
      diff = std::min(diff,max_num);
      x_-=diff;
      if (x_<0)
        x_ = 0;
    }
  }
  else if (level_type==AUTOSCROLL) {
    if (!isHalted) {
      const float speed=1.8;
      if (isVertical) {
        y_ += dir*speed;
        if (y_>32*rows-window_height)
          y_ = 32*rows-window_height;
        if (y_<0)
          y_ = 0;
      }
      else {
        x_ += dir*speed;
        if (x_>32*cols-window_width)
          x_ = 32*cols-window_width;
        if (x_<0)
          x_ = 0;

      }
    }
    if (bob->getY1()<0)
      bob->setY(y_);
    else if (bob->getY2()>window_height)
      bob->setY(y_+window_height-bob->getHeight());
    if (bob->getX1()<0)
      bob->setX(x_);
    else if (bob->getX2()>window_width)
      bob->setX(x_+window_width-bob->getWidth());
  }
  if (isWrapped) {
    if (bob->getY1()>=window_height*.99) {
      bob->shiftY(-max_rows*height);
      bob->preX();
      y_=0;
    }
    if (bob->getY2()<=.01) {
      bob->shiftY(max_rows*height);
      bob->preX();
      y_ = height*max_rows-window_height;
    }
    if (bob->getX1()>=window_width*.99) {
      bob->shiftX(-max_cols*width);
      bob->preY();
      x_=0;
    }
    if (bob->getX2()<=.01) {
      bob->shiftX(window_width);
      bob->preY();
      x_ = width*max_cols-window_width;
    }
  }
  else {
    if (bob->getY2()+y_>max_rows*height) {
      bob->shiftY(max_rows*height-bob->getY2()-y_);
    }
    if (bob->getY1()+y_<0) {
      bob->shiftY(-bob->getY1()-y_);
    }
    if (bob->getX2()+x_>max_cols*width) {
      bob->shiftX(window_width-bob->getX2()-x_);
    }
    if (bob->getX1()+x_<0) {
      bob->shiftX(-bob->getX1()-x_);
    }
  }

}

void Level::render(sf::RenderWindow& window) {
  window.draw(background);
#ifdef COMPILE_DEBUG
  //render row lines
  for (int i=1;i<15;i++) {
    sf::Vertex line[] = {
      sf::Vertex(sf::Vector2f(0, 32*i),sf::Color(0,0,0)),
      sf::Vertex(sf::Vector2f(window_width, 32*i),sf::Color(0,0,0))
    };
    window.draw(line, 2, sf::Lines);
  }
  //render column lines
  for (int i=1;i<20;i++) {
    sf::Vertex line[] = {
      sf::Vertex(sf::Vector2f(32*i, 0),sf::Color(0,0,0)),
      sf::Vertex(sf::Vector2f(32*i, window_height),sf::Color(0,0,0))
    };
    window.draw(line, 2, sf::Lines);

  }
#endif
  sf::RenderTexture dark;
  if (zone==DARK)
    if (!dark.create(window_width,window_height)) throw 1;
    dark.clear(sf::Color(0,0,0,225));
  ACTORS::iterator itr;
  for (itr=actors.begin();itr!=actors.end();itr++) {
    if (bob!=itr->second&&!isOutOfBounds(itr->second)) {
      itr->second->render(window);
      if (zone==DARK) {
        itr->second->addLights(dark);
      }
    }
  }
  bob->render(window);
  if (zone==DARK) {
    dark.setRepeated(true);
    sf::Sprite darkness;
    darkness.setTexture(dark.getTexture());
    window.draw(darkness);
  }
  
}

void Level::testHitStationary(Actor* actor, std::vector<Actor*>& hits) {
  int c = (actor->getX1())/width+x_/width;
  int r = (actor->getY1())/height+y_/height;
  int nc = ceil(actor->getWidth()/width);
  int nr = ceil(actor->getHeight()/height);
  for (int ri = r;ri<=r+nr;ri++)
    for (int ci = c;ci<=c+nc;ci++) {
      if (ri>=0&&ci>=0&&ri<max_rows&&ci<max_cols&&
          stationary[ri][ci] && hitTest(actor,stationary[ri][ci]))
        hits.push_back(stationary[ri][ci]);
    }
  std::list<Rock*>::iterator itr;
  for (itr=rocks.begin();itr!=rocks.end();itr++) {
    if (hitTest(actor,*itr)) {
      hits.push_back(*itr);
    }
  }
}

void Level::testHitCollectable(Actor* actor,std::vector<Collectable*>& hits) {

  int c = (actor->getX1())/width+x_/width;
  int r = (actor->getY1())/height+y_/height;
  int nc = ceil(actor->getWidth()/width);
  int nr = ceil(actor->getHeight()/height);
  for (int ri = r;ri<=r+nr;ri++)
    for (int ci = c;ci<=c+nc;ci++)
      if (ri>=0&&ci>=0&&ri<max_rows&&ci<max_cols&&
          gems[ri][ci] && hitTest(actor,gems[ri][ci]))
        hits.push_back(gems[ri][ci]);
}

void Level::findOpenPosition(int& r,int& c) const {
  int orr,orc,layer,offset,iter;
  orr=r; orc=c; layer=1;offset=0;iter=0;
  while (r>=0&&c>=0&&r<max_rows&&c<max_cols&&stationary[r][c]) {
    int dr = orr-r;
    int dc = orc-c;
    if (dr==0&&dc==0) {
      dr=-1;
    }
    else if (iter==3) {
      iter=0;
      offset++;
      if (offset>layer)
        offset-=2*layer;
      if (offset==0)
        layer++;
      dr=-layer;
      dc=offset;
    }
    else {
      int tr = dr;
      dr=dc;
      dc=-tr;
      iter++;
    }
    r= orr+dr;
    c = orc+dc;
  }

}

void Level::setSpiders(bool isR) {
  ACTORS::iterator itr;
  for (itr=beginActor();itr!=endActor();iterateActor(itr)) {
    if (dynamic_cast<Spider*>(itr->second)) {
      dynamic_cast<Spider*>(itr->second)->flip(isR);
    }
  }
}

void Level::resetSpiderBoss(int index) {
  halt();
  x_=0;
  chase_indices.push_back(index);
}
void Level::addStationary(Actor* actor,int r, int c,bool needs_adding) {
  if (!stationary[r][c]) {
    stationary[r][c] = actor;
    actor->linkPosition(&stationary[r][c]);
    if (needs_adding) {
      if (dynamic_cast<GemDoor*>(actor))
        insert(stationary[r][c],door_depth);
      else if (dynamic_cast<Die*>(actor))
        insert(stationary[r][c],monster_depth);
      else if (dynamic_cast<Coin*>(actor))
        insert(stationary[r][c],gem_depth);
      else if (dynamic_cast<Switch*>(actor))
        insert(stationary[r][c],stationary_depth);
      else if (dynamic_cast<Block*>(actor))
        insert(stationary[r][c],wall_depth);
      else
        insert(stationary[r][c],min_depth);
    }
  }
  else
    delete actor;
}

void Level::addGem(Crystal* g, int r, int c) {
  g->linkPosition(&gems[r][c]);
  gems[r][c] = g;
  insert(g,gem_depth);
}

void Level::insert(Actor* actor,int& depth) {
  actors.insert(std::make_pair(depth,actor));
  depth++;

}

bool Level::isOutOfBounds(Actor* actor) const {
  if (actor->getX2()<0)
    return true;
  if (actor->getY2()<0)
    return true;
  if (actor->getX1()>getLevelWidth())
    return true;
  if (actor->getY1()>getLevelHeight())
    return true;
  return false;
}

bool Level::isBlock(int i,int j) {

  return dynamic_cast<Block*>(stationary[i][j]);//&& !dynamic_cast<GemDoor*>(stationary[i][j]);
}
void Level::setBlocks() {

  for (int i=0;i<max_rows;i++) {
    for (int j=0;j<max_cols;j++) {
      Block* b;
      if (stationary[i][j]&&(b=dynamic_cast<Block*>(stationary[i][j]))) {
        b->setDirs(i-1>=0&&isBlock(i-1,j),
                   i-1>=0&&dynamic_cast<GemDoor*>(stationary[i-1][j])!=NULL,
                   j+1<max_cols&&isBlock(i,j+1),
                   j+1<max_cols&&dynamic_cast<GemDoor*>(stationary[i][j+1])!=NULL,
                   i+1<max_rows&&isBlock(i+1,j),
                   i+1<max_rows&&dynamic_cast<GemDoor*>(stationary[i+1][j])!=NULL,
                   j-1>=0&&isBlock(i,j-1),
                   j-1>=0&&dynamic_cast<GemDoor*>(stationary[i][j-1])!=NULL);

      }
    }
  }
}
