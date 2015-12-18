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
#include <utilities.h>
#include <cassert>

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
    else if (key=="exit") {
      return new Exit(this,x*width,y*height);
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
  std::string key;
  max_depth=0;
  stationary = new Actor**[rows];
  for (int i=0;i<rows;i++)  {
    stationary[i] = new Actor*[cols];
    for (int j=0;j<cols;j++)
      stationary[i][j] = NULL;
  }
  gems = new Collectable**[rows];
  for (int i=0;i<rows;i++)  {
    gems[i] = new Collectable*[cols];
    for (int j=0;j<cols;j++)
      gems[i][j] = NULL;
  }
  while (in_str>>key) {
    int x,y;
    int end=0;
    int end2=0;
    //Level Options
    if (key=="NORMAL_LEVEL") {
      assert(!actors.size());
    }
    if (key=="ZOOMED_LEVEL") {
      assert(!actors.size());
      level_type=1;
      width=window_width/cols;
      height=window_height/rows;
    }
    else if (key=="GRID_LEVEL") {
      level_type=2;
      in_str>>y>>x;
      grows=y;
      gcols=x;
      width = window.getSize().y/x;
      height = window.getSize().x/y;
      assert(rows/y==int(rows/y)&&cols/x==int(cols/x));
    }
    //Prefix Options
    if (key=="row") {
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
      in_str>>c>>y>>x;
      insert(new Spider(this,(x)*width,(y)*height,c=='V'));
    }
    else if (key=="rock") {
      in_str>>y>>x;
      Rock* r = new Rock(this,x*width,y*height);
      insert(r);
      rocks.push_back(r);
    }
    //Syntactic Sugar
    else if (key=="brow") {
      in_str>>y;
      for (int i=0;i<cols;i++) 
        if (!stationary[y][i]) {
          addStationary(new Block(this,i*width,y*height),y,i);
        }
    }
    else if (key=="bcol") {
      in_str>>x;
      for (int i=0;i<rows;i++) 
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
      std::cout<<key<<'\n';
      in_str>>x>>y;
      Actor* actor = getStationary(key,x,y); 
      if (actor)
        addStationary(actor,y,x);
      else
        throw 1;
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
      itr->second->removePosition();
      delete itr->second;
      
      ACTORS::iterator temp_itr = itr;
      itr--;
      actors.erase(temp_itr);
    }
    itr++;
  }
  if (level_type==2) {
    if (bob->getY1()>window_height)
      y_ +=height*(grows-1);
    if (bob->getY2()<0)
      y_-=height*(grows-1);
    if (bob->getX1()>window_width)
      x_+=width*(gcols-1);
    if (bob->getX2()<0)
      x_-=width*(gcols-1);
  } 
}

void Level::testHitStationary(Actor* actor, std::vector<Actor*>& hits) {
  int c = (actor->getX1()+x_)/width;
  int r = (actor->getY1()+y_)/height;
  if (r>=0&&c>=0&&r<rows&&c<cols&&
      stationary[r][c] && isRectangularHit(actor,stationary[r][c]))
    hits.push_back(stationary[r][c]);
  if (r+1>=0&&c>=0&&r+1<rows&&c<cols&&
      stationary[r+1][c]&&isRectangularHit(actor,stationary[r+1][c]))
    hits.push_back(stationary[r+1][c]);
  if (r>=0&&c+1>=0&&r<rows&&c+1<cols&&
      stationary[r][c+1]&&isRectangularHit(actor,stationary[r][c+1]))
    hits.push_back(stationary[r][c+1]);
  if (r+1>=0&&c+1>=0&&r+1<rows&&c+1<cols&&
      stationary[r+1][c+1]&&isRectangularHit(actor,stationary[r+1][c+1]))
    hits.push_back(stationary[r+1][c+1]);
  for (unsigned int i=0;i<rocks.size();i++) {
    if (isRectangularHit(actor,rocks[i])) {
      hits.push_back(rocks[i]);
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
