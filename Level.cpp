#include "Level.h"
#include <Bob.h>
#include <Spider.h>
#include <GemDoor.h>
#include <CheckPoint.h>
#include <Collectable.h>
#include <utilities.h>
#include <cassert>

Level::Level() {
  bob=NULL;
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
  window_width = window.getSize().y;
  window_height = window.getSize().x;
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
    int isPrefix=0;
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
      isPrefix=1;
      in_str>>y>>x>>end>>key;
      assert(end>=x);
    }
    else if (key=="col") {
      isPrefix=2;
      in_str>>x>>y>>end>>key;
      assert(end>=y);
    }
    else if (key=="rect") {
      isPrefix=3;
      in_str>>y>>x>>end>>end2>>key;
      assert(end>=y&&end2>=x);
    }

    //Bob Option
    if (key=="start"||key=="s") {
      assert(!isPrefix);
      in_str>>y>>x;
      bob = new Bob(this,x*height,y*width);
      insert(bob);
    }

    //Stationary Options
    else if (key=="b"||key=="block") {
      if (isPrefix==1) {
	for (int i =x;i<=end;i++) {
	  addStationary(new Block(this,i*width,y*height),y,i);
	}
      }
      else if (isPrefix==2) {
	for (int i =y;i<=end;i++) {
	  addStationary(new Block(this,x*width,i*height),i,x);
	}
      }
      else if (isPrefix==3) {
	for (int i = y;i<=end;i++)
	  for (int j=x;j<=end2;j++)
	    addStationary(new Block(this,j*width,i*height),i,j);
      }
      else {
	in_str>>y>>x;
	addStationary(new Block(this,x*width,y*height),y,x);
      }
    }
    else if (key=="c"||key=="check") {
      if (isPrefix==1) {
	for (int i =x;i<=end;i++) {
	  addStationary(new CheckPoint(this,i*width,y*height),y,i);
	}
      }
      else if (isPrefix==2) {
	for (int i =y;i<=end;i++) {
	  addStationary(new CheckPoint(this,x*width,i*height),i,x);
	}
      }
      else if (isPrefix==3) {
	for (int i = y;i<=end;i++)
	  for (int j=x;j<=end2;j++)
	    addStationary(new CheckPoint(this,j*width,i*height),i,j);
      }
      else {
	in_str>>y>>x;
	addStationary(new CheckPoint(this,x*width,y*height),y,x);
      }
    }

    //Moving Options
    else if (key=="spider"||key=="sp") {
      assert(!isPrefix);
      char c;
      in_str>>c>>y>>x;
      insert(new Spider(this,(x+.1)*width,(y+.1)*height,width*4/5,height*4/5,c=='V'));
    }

    //Syntactic Sugar
    else if (key=="brow") {
      assert(!isPrefix);
      in_str>>y;
      for (int i=0;i<cols;i++) 
	if (!stationary[y][i]) {
	  stationary[y][i] = new Block(this,i*width,y*height);
	  insert(stationary[y][i]);
	}
    }
    else if (key=="bcol") {
      assert(!isPrefix);
      in_str>>x;
      for (int i=0;i<rows;i++) 
	if (!stationary[i][x]) {
	  stationary[i][x] = new Block(this,x*width,i*height);
	  insert(stationary[i][x]);
	}
    }

    //Block Options
    else if (key=="gemdoor"||key=="gd") {
      assert(!isPrefix);
      int num;
      in_str>>num;
      GemDoor** doors = new GemDoor*[num];
      for (int i=0;i<num;i++) {
	int x,y;
	in_str>>y>>x;
	doors[i] = new GemDoor(this,x*width,y*height);
	stationary[y][x] = doors[i];
	insert(doors[i]);
      }
      std::string c;
      while ((in_str>>c)&&(c!=";")) {
	if (c=="crow") {
	  in_str>>y>>x>>end;
	  for (int i=x;i<=end;i++)
	    addGem(new Collectable(this,i*width,y*height,width,height),y,i,doors,num);
	}
	else if (c=="ccol") {
	  in_str>>x>>y>>end;
	  for (int i=y;i<=end;i++)
	    addGem(new Collectable(this,x*width,i*height,width,height),i,x,doors,num);
	}
	else if (c=="crect") {
	  in_str>>y>>x>>end>>end2;
	  for (int i=y;i<=end;i++)
	    for (int j=x;j<=end2;j++)
	    addGem(new Collectable(this,j*width,i*height,width,height),i,j,doors,num);
	}
	else {
	  in_str>>y>>x;
	  addGem(new Collectable(this,x*width,y*height,width,height),y,x,doors,num);
	}
      }
	  delete[] doors;
    }
  }
}

Level::~Level() {
  ACTORS::iterator itr;
  for (itr=actors.begin();itr!=actors.end();itr++) {
    delete itr->second;
  }
  for (int i=0;i<rows;i++)
    delete [] stationary[i];
  delete [] stationary;
}

void Level::act() {
  ACTORS::iterator itr=actors.begin(); 
  std::vector<ACTORS::iterator> to_delete;
  while(itr!=actors.end()) {
    itr->second->act();
    if (itr->second->getDead()) {
      if (dynamic_cast<Collectable*>(itr->second)) {
	      int r = (getY()+itr->second->getY1())/height;
	int c = (getX()+itr->second->getX1())/width;
	gems[r][c] = NULL;
      }
      else if (itr->second->isStationary()) {
	int r = (getY()+itr->second->getY1())/height;
	int c = (getX()+itr->second->getX1())/width;
	stationary[r][c] = NULL;
      }
      delete itr->second;
      to_delete.push_back(itr);
    }
    itr++;
  }
  for (size_t i=0;i<to_delete.size();i++) {
    actors.erase(to_delete[i]);
  }
  to_delete.clear();
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

Actor** Level::testHitStationary(Actor* actor) {
  int c = (actor->getX1()+x_)/width;
  int r = (actor->getY1()+y_)/height;
  Actor** bs = new Actor*[4];
  bs[0]=NULL;bs[1]=NULL;bs[2]=NULL;bs[3]=NULL;
  if (r>=0&&c>=0&&r<rows&&c<cols&&
      stationary[r][c] && isRectangularHit(actor,stationary[r][c]))
    bs[0]=stationary[r][c];
  if (r+1>=0&&c>=0&&r+1<rows&&c<cols&&
      stationary[r+1][c]&&isRectangularHit(actor,stationary[r+1][c]))
    bs[1] =stationary[r+1][c];
  if (r>=0&&c+1>=0&&r<rows&&c+1<cols&&
      stationary[r][c+1]&&isRectangularHit(actor,stationary[r][c+1]))
    bs[2] =stationary[r][c+1];
  if (r+1>=0&&c+1>=0&&r+1<rows&&c+1<cols&&
      stationary[r+1][c+1]&&isRectangularHit(actor,stationary[r+1][c+1]))
    bs[3] =stationary[r+1][c+1];
  return bs;
}

Collectable** Level::testHitCollectable(Actor* actor) {
  int c = (actor->getX1()+x_)/width;
  int r = (actor->getY1()+y_)/height;
  Collectable** bs = new Collectable*[4];
  bs[0]=NULL;bs[1]=NULL;bs[2]=NULL;bs[3]=NULL;
  if (r>=0&&c>=0&&r<rows&&c<cols&&
      gems[r][c] && isRectangularHit(actor,gems[r][c]))
    bs[0]=gems[r][c];
  if (r+1>=0&&c>=0&&r+1<rows&&c<cols&&
      gems[r+1][c]&&isRectangularHit(actor,gems[r+1][c]))
    bs[1] =gems[r+1][c];
  if (r>=0&&c+1>=0&&r<rows&&c+1<cols&&
      gems[r][c+1]&&isRectangularHit(actor,gems[r][c+1]))
    bs[2] =gems[r][c+1];
  if (r+1>=0&&c+1>=0&&r+1<rows&&c+1<cols&&
      gems[r+1][c+1]&&isRectangularHit(actor,gems[r+1][c+1]))
    bs[3] =gems[r+1][c+1];
  return bs;
}
void Level::addStationary(Actor* actor,int r, int c) {
  if (!stationary[r][c]) {
    stationary[r][c] = actor;
    insert(stationary[r][c]);
  }
}

void Level::addGem(Collectable* g, int r, int c, GemDoor* doors[], int num) {
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
