#include "utilities.h"
#include <fstream>
#include <cmath>
#include "MersenneTwister.h"
#include <Spider.h>

float getPi() {return 3.141592653589793238;}

bool isRectangularHit(Actor* a1,Actor* a2) {
  return (a1->getX1()<=a2->getX2() && 
          a1->getX2()>=a2->getX1() &&
          a1->getY1()<=a2->getY2() && 
          a1->getY2()>=a2->getY1());
}

float getAngleTo(Actor* a1,Actor* a2) {
  float c1x,c1y,c2x,c2y;
  getObjectCenter(a1,c1x,c1y);
  getObjectCenter(a2,c2x,c2y);
  float diffy = c2y-c1y;
  float diffx = c2x-c1x;
  float angle = atan(diffy/diffx);
  if (diffx<0) {
    angle+=getPi();
  }
  return angle;
}

bool isLineHit(Line l1, Line l2) {
  float x1 = l1.p1.first;
  float x2 = l2.p1.first;
  float y1 = l1.p1.second;
  float y2 = l2.p1.second;
  bool isUp1 = x1==l1.p2.first;
  bool isUp2 = x2==l2.p2.first;
  float x;
  float m2;
  float y;
  float m1;
  if (isUp1&&isUp2)
    if (x1==x2) {
      x=x1;
      m1=0;
      m2=0;
      y1=y2;
    }
    else
      return false;
  else if (isUp1) {
    x=x1;
    m1=0;
    y1=y2;
    m2 = l2.m();
  }
  else if (isUp2) {
    x=x2;
    m2=0;
    y2=y1;
    m1=l1.m();
  }
  else {
    m1 = l1.m();
    m2 = l2.m();
    if (m1==m2)
      return false;
    x = (y2-y1+m1*x1-m2*x2)/(m1-m2);
  }
  if (m2==0)
    y = m1*(x-x1)+y1;
  else
    y = m2*(x-x2)+y2;
  return l1.isOn(x,y)&&l2.isOn(x,y);
}

bool isCircleLineHit(Circle c1, Line l) {
  float x1 = l.p1.first;
  float x2 = l.p2.first;
  float y1 = l.p1.second;
  float y2 = l.p2.second;
  float cx = c1.p.first;
  float cy = c1.p.second;
  float cr = c1.rad;
 
  float a = pow(x2-x1,2)+pow(y2-y1,2);
  float b = 2*((x2-x1)*(x1-cx) + (y2-y1)*(y1-cy));
  float c = pow(x1-cx,2)+pow(y1-cy,2)-pow(cr,2);

  float disc = b*b-4*a*c;

  if (disc<0)
    return false;
  disc = sqrt(disc);
  float t1 = (-b-disc)/(2*a);
  float t2 = (-b+disc)/(2*a);
  
  return (t1>=0&&t1<=1)||(t2>=0&&t2<=1);
}

int isCircleHit(Circle c1, Circle c2)
{
  float dx = c2.p.first - c1.p.first;
  float  dy = c2.p.second - c1.p.second;
  float radii = c2.rad + c1.rad;
  if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
      return true;
  return false;
}

bool hitTest(Actor* a1,Actor* a2) {
  std::vector<Line> l1 = a1->getLines();
  std::vector<Line> l2 = a2->getLines();
  std::vector<Circle> c1 = a1->getCircles();
  std::vector<Circle> c2 = a2->getCircles();
  if ((l1.size()==c1.size()&&l1.size()==0)||(l2.size()==c2.size()&&c2.size()==0))
    return isRectangularHit(a1,a2);
  for (unsigned int i=0;i<l1.size();i++)
    for (unsigned int j=0;j<l2.size();j++)
      if (isLineHit(l1[i],l2[j]))
        return true;
  for (unsigned int i=0;i<c1.size();i++)
    for (unsigned int j=0;j<l2.size();j++)
      if (isCircleLineHit(c1[i],l2[j]))
        return true;
  for (unsigned int i=0;i<c2.size();i++)
    for (unsigned int j=0;j<l1.size();j++)
      if (isCircleLineHit(c2[i],l1[j]))
        return true;
  for (unsigned int i=0;i<c1.size();i++)
    for (unsigned int j=0;j<c2.size();j++)
      if (isCircleHit(c1[i],c2[j]))
        return true;
  return false;
}

int getApproachDir(Actor* a1, Actor* a2) {
  int dir=0;
  if (a1->getLastY2()<=a2->getLastY1() && a1->getBoundY2()>=a2->getBoundY1()&&a1->getBoundY1()>a1->getLastY1()) //Landing
    dir+=4;
  if (a1->getLastY1()>=a2->getLastY2() && a1->getBoundY1()<=a2->getBoundY2()&&a1->getBoundY1()<a1->getLastY1()) //Ceiling
    dir+=1;
  if (a1->getLastX2() <= a2->getLastX1() && a1->getBoundX2()>=a2->getBoundX1()&&a1->getBoundX1()>a1->getLastX1()) //Right wall
    dir+=2;
  if (a1->getLastX1() >= a2->getLastX2() && a1->getBoundX1()<=a2->getBoundX2()&&a1->getBoundX1()<a1->getLastX1()) //Left wall
    dir+=8;
  return dir;
}

void getObjectCenter(Actor* a,float& cx,float& cy) {
  cx = a->getX1()+a->getWidth()/2;
  cy = a->getY1()+a->getHeight()/2;
}


MTRand mtr;

int getRandInt(int low, int high) {
  return mtr.randInt(high-low)+low;
}

float getRand(float low, float high) {
  return (float)(mtr.rand(high-low)+low);
}


Reader reader;

void addGraphic(std::string name,std::string file_name,bool isRepeated) {
  reader.registerGraphics(name,file_name,isRepeated);
}
void addFont(std::string name,std::string file_name) {
  reader.registerFont(name,file_name);
}
void addSong(std::string name,std::string file_name, bool repeat) {
  reader.registerSong(name,file_name,repeat);
}

const sf::Texture& getGraphic(std::string name) {
  return reader.getGraphics(name);
}
const sf::Font& getFont(std::string name) {
  return reader.getFont(name);
}
sf::Music* getSong(std::string name) {
  return reader.getSong(name);
}

void destroySongs() {
  reader.destroy();
}
