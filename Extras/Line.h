#ifndef __LINE__H__
#define __LINE__H__

#include <map>

class Line {
public:
  Line() {};
  Line(float x1, float x2, float y1, float y2);
  std::pair<float,float> p1;
  std::pair<float,float> p2;
  float m();
  bool isOn(float x,float y);
};

#endif
