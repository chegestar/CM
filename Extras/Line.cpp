#include "stdafx.h"
#include "Line.h"

Line::Line(float x1, float x2, float y1, float y2) {
  p1 = std::make_pair(x1,y1);
  p2 = std::make_pair(x2,y2);
}

float Line::m() {
  if (p2.first==p1.first)
    throw 1;
  return (p2.second-p1.second)/(p2.first-p1.first);
}
float min(float n1, float n2) {
  if (n1<n2)
    return n1;
  return n2;
}
bool Line::isOn(float x,float y) {
  float minx = min(p1.first,p2.first);
  float miny = min(p1.second,p2.second);
  float maxx = p1.first+p2.first-minx;
  float maxy = p1.second+p2.second-miny;
  return x>=minx && x<=maxx && y>=miny&& y<=maxy;
}
