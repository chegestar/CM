#include <SFML/Graphics.hpp>
#ifndef __ARC_H__
#define __ARC_H__
/* Notes: The functions are similar to that of SFML but do not follow the same inner structure
   After running setRadius() or setPosition() setBounds should be run to recreate the quadrant arcs
 */
class Arc {
 public:
  Arc();
  
  void setFillColor(sf::Color col);
  void setPosition(float x_, float y_);
  void setScale(float xs, float ys);
  void setRotation(float angle);
  void setBounds(float lower,float upper);
  void render(sf::RenderWindow& window);
  void setRadius(float r);
 private:
  float rad;
  float x,y;
  sf::ConvexShape quadrants[4];
};

#endif
