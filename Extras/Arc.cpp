#include "Arc.h"
#include <cmath>
#include <utility>
Arc::Arc() {
  x=y=0;
  for (int i=0;i<4;i++) {
    quadrants[i].setOrigin(0,0);
    quadrants[i].setPosition(0,0);
  }
}
void Arc::setFillColor(sf::Color col) {
  for (int i=0;i<4;i++) {
    quadrants[i].setFillColor(col);
  }
}
void Arc::setPosition(float x_, float y_) {
  x=x_;
  y=y_;
  for (int i=0;i<4;i++)
    quadrants[i].setPosition(x,y);
}

void Arc::setRadius(float r) {
  rad=r;
}

void Arc::setRotation(float angle) {
  for (int i=0;i<4;i++)
    quadrants[i].setRotation(angle);
}

void Arc::setScale(float xs, float ys) {
  for (int i=0;i<4;i++)
    quadrants[i].setScale(xs,ys);
}

std::pair<float,float> getBounds(float l1,float u1, float l2, float u2) {
  std::pair<float,float> bds;
  bds.first = std::max(l1,l2);
  bds.second = std::min(u1,u2);
  return bds;
}

void Arc::setBounds(float lower,float upper) {
  float pts = 10;
  for (int i=0;i<4;i++) {
    quadrants[i].setPointCount(pts+1);
    quadrants[i].setPoint(0,sf::Vector2f(0,0));
    std::pair<float,float> bounds = getBounds(i*90,(i+1)*90,lower,upper);
    float diff = bounds.second-bounds.first;
    float angle = bounds.first;
    float pi=3.1415926535;
    for (int j=0;j<pts;j++) {
      if (diff<=0)
        quadrants[i].setPoint(j+1,sf::Vector2f(0,0));
      else
        quadrants[i].setPoint(j+1,sf::Vector2f(rad*cos(angle*pi/180),
                                               rad*sin(angle*pi/180)));
      angle+=diff/(pts-1);
    }
  }

}

void Arc::render(sf::RenderWindow& window) {
  for (int i=0;i<4;i++) 
    window.draw(quadrants[i]);
}
