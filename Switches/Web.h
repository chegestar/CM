#include <Switch.h>

#ifndef __WEB__H__
#define __WEB__H__

class Web : public Switch {
 public:
  Web(Level* l, float x_, float y_);

  float getBoundX1() const {return getX1()+1.5;}
  float getBoundX2() const {return getX2()-1.5;}
  float getBoundY1() const {return getY1()+1.5;}
  float getBoundY2() const {return getY2()-1.5;}
  std::vector<Line> getLines() const;
  std::vector<Circle> getCircles() const;

  virtual int activate();

};

#endif
