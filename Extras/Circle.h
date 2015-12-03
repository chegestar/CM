#ifndef __CIRCLE__H__
#define __CIRCLE__H__

#include <map>

class Circle {
public:
  Circle() {};
  Circle(float x, float y, float r);
  std::pair<float,float> p;
  float rad;
};

#endif
