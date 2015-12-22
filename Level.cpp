#include "Level.h"
#include <Bob.h>
#include <Spider.h>
#include <GemDoor.h>
#include <Rock.h>
#include <Exit.h>
#include <Coin.h>
#include <EpCrystal.h>
#include <Crystal.h>
#include <Life.h>
#include <Web.h>
#include <Lava.h>
#include <Pit.h>
#include <FireBoot.h>
#include <utilities.h>
#include <cassert>
#include <algorithm>
#include <cmath>
Level::Level() {
  bob=NULL;
}

Actor* Level::getStationary(std::string key, int x, int y) {
    if (key=="b"||key=="block") {
      return new Block(this,x*width,y*height);
    }
    else if (key=="c"||key=="check") {
      return new CheckPoint(this,x*width,y*height);
    }
    else if (key=="coin") {
      return new Coin(this,x*width,y*height);
    }
    else if (key=="ecrystal" || key=="ec") {
      return new EpCrystal(this,x*width,y*height);
    }
    else if (key=="life" || key=="l") {
      return new Life(this,x*width,y*height);
    } 
    else if (key=="web"||key=="w") {
      return new Web(this,x*width,y*height);
    }
    else if (key=="lava") {
      return new Lava(this,x*width,y*height);
    }
    else if (key=="lavapath") {
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
    else if (key=="exit") {
      return new Exit(this,x*width,y*height);
    }
    else if (key=="fireboot") {
      return new FireBoot(this,x*width,y*height);
    }
    return NULL;
}
Level::Level(std::string filename,sf::RenderWindow& window) {
  std::ifstream in_str(filename.c_str());
  if (!in_str) {
    throw 1;
  }
  x_=y_=0;
  level_type=0;
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
    level_type=0;
  }
  else if (key=="GRID_LEVEL") {
    level_type=1;
    in_str>>y>>x;
    grows=y;
    gcols=x;
  }
  else if (key=="CONTINUOUS_LEVEL") {
    level_type=3;
  }
  else if (key=="AUTOSCROLL_LEVEL") {
    level_type=4;
    char c;
    in_str>>c>>dir;
    isVertical= (c=='V');
  }


  max_depth=0;
  max_rows = rows*grows-grows+1;
  max_cols= cols*gcols-gcols+1;
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
        addStationary(getStationary(key,i,y),y,i);
      }
    }
    else if (key=="col") {
      in_str>>x>>y>>end>>key;
      assert(end>=y);
      for (int i =y;i<=end;i++) {
        addStationary(getStationary(key,x,i),i,x);
      }
  
    }
    else if (key=="rect") {
      in_str>>y>>x>>end>>end2>>key;
      assert(end>=y&&end2>=x);
      for (int i = y;i<=end;i++)
        for (int j=x;j<=end2;j++)
          addStationary(getStationary(key,j,i),i,j);
    }

    //Bob Option
    else if (key=="start"||key=="s") {
      in_str>>y>>x;
      bob = new Bob(this,x*height,y*width);
      insert(bob);
    }

    //Moving Options
    else if (key=="spider"||key=="sp") {
      char c;
      in_str>>y>>x>>c;
      insert(new Spider(this,(x)*width,(y)*height,c=='V'));
    }
    else if (key=="rock") {
      in_str>>y>>x;
      Rock* r = new Rock(this,x*width,y*height);
      insert(r);
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
    else if (key=="gemdoor"||key=="gd") {
      int num;
      in_str>>num;
      GemDoor** doors = new GemDoor*[num];
      for (int i=0;i<num;i++) {
        int x,y;
        in_str>>y>>x;
        doors[i] = new GemDoor(this,x*width,y*height);
        addStationary(doors[i],y,x);
      }
      std::string c;
      while ((in_str>>c)&&(c!=";")) {
        if (c=="crow") {
          in_str>>y>>x>>end;
          for (int i=x;i<=end;i++)
            addGem(new Crystal(this,i*width,y*height,width,height),y,i,doors,num);
        }
        else if (c=="ccol") {
          in_str>>x>>y>>end;
          for (int i=y;i<=end;i++)
            addGem(new Crystal(this,x*width,i*height,width,height),i,x,doors,num);
        }
        else if (c=="crect") {
          in_str>>y>>x>>end>>end2;
          for (int i=y;i<=end;i++)
            for (int j=x;j<=end2;j++)
              addGem(new Crystal(this,j*width,i*height,width,height),i,j,doors,num);
        }
        else {
          in_str>>y>>x;
          addGem(new Crystal(this,x*width,y*height,width,height),y,x,doors,num);
        }
      }
      delete[] doors;
    }
    //Let's do all the stationary by calling the getStationary function
    else {
      in_str>>y>>x;
      Actor* actor = getStationary(key,x,y); 
      if (actor)
        addStationary(actor,y,x);
    }
  }
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

void Level::act() {
  ACTORS::iterator itr=actors.begin(); 
  while(itr!=actors.end()) {
    itr->second->act();
    if (itr->second->getDead()) {
      std::list<Rock*>::iterator* rock_itr = itr->second->removePosition();
      if (rock_itr) rocks.erase(*rock_itr);
      delete itr->second;
      
      ACTORS::iterator temp_itr = itr;
      itr--;
      actors.erase(temp_itr);
    }
    itr++;
  }
  if (level_type==1) {
    if (getRow()<grows-1&&bob->getY1()>window_height)
      y_ +=height*(rows-1);
    if (getRow()>0&&bob->getY2()<0)
      y_-=height*(rows-1);
    if (getCol()<gcols-1&&bob->getX1()>window_width)
      x_+=width*(cols-1);
    if (getCol()>0&&bob->getX2()<0)
      x_-=width*(cols-1);
  }
  else if (level_type==3&&!isHalted) {
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
  else if (level_type==4&&!isHalted) {
    const int speed=1.5;
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
  if (isWrapped) {
    if (bob->getY1()>window_height) {
      bob->shiftY(-max_rows*height);
      y_=0;
    }
    if (bob->getY2()<0) {
      bob->shiftY(max_rows*height); 
      y_ = height*max_rows-window_height;
    }
    if (bob->getX1()>window_width) {
      bob->shiftX(-max_cols*width);
      x_=0;
    }
    if (bob->getX2()<0) {
      bob->shiftX(window_width);
      x_ = width*max_cols-window_width;
    }
  }

}

void Level::testHitStationary(Actor* actor, std::vector<Actor*>& hits) {
  int c = (actor->getX1())/width+x_/width;
  int r = (actor->getY1())/height+y_/height;
  for (int ri = r;ri<=r+1;ri++)
    for (int ci = c;ci<=c+1;ci++)
      if (ri>=0&&ci>=0&&ri<max_rows&&ci<max_cols&&
          stationary[ri][ci] && isRectangularHit(actor,stationary[ri][ci]))
        hits.push_back(stationary[ri][ci]);
  std::list<Rock*>::iterator itr;
  for (itr=rocks.begin();itr!=rocks.end();itr++) {
    if (isRectangularHit(actor,*itr)) {
      hits.push_back(*itr);
    }
  }
}

void Level::testHitCollectable(Actor* actor,std::vector<Collectable*>& hits) {
  int c = (actor->getX1()+x_)/width;
  int r = (actor->getY1()+y_)/height;
  if (r>=0&&c>=0&&r<rows&&c<cols&&
      gems[r][c] && isRectangularHit(actor,gems[r][c]))
    hits.push_back(gems[r][c]);
  if (r+1>=0&&c>=0&&r+1<rows&&c<cols&&
      gems[r+1][c]&&isRectangularHit(actor,gems[r+1][c]))
    hits.push_back(gems[r+1][c]);
  if (r>=0&&c+1>=0&&r<rows&&c+1<cols&&
      gems[r][c+1]&&isRectangularHit(actor,gems[r][c+1]))
    hits.push_back(gems[r][c+1]);
  if (r+1>=0&&c+1>=0&&r+1<rows&&c+1<cols&&
      gems[r+1][c+1]&&isRectangularHit(actor,gems[r+1][c+1]))
    hits.push_back(gems[r+1][c+1]);
}
void Level::addStationary(Actor* actor,int r, int c) {
  if (!stationary[r][c]) {
    stationary[r][c] = actor;
    actor->linkPosition(&stationary[r][c]);
    insert(stationary[r][c]);
  }
  else
    delete actor;
}

void Level::addGem(Crystal* g, int r, int c, GemDoor* doors[], int num) {
  g->linkPosition(&gems[r][c]);
  gems[r][c] = g;
  insert(g);
  for (int i=0;i<num;i++) {
    doors[i]->addCrystal();
    g->addDoor(doors[i]);
  }
}

void Level::insert(Actor* actor,int depth) {
  if (depth==-1) {depth = max_depth; max_depth++;}
  actors.insert(std::make_pair(depth,actor));

}
