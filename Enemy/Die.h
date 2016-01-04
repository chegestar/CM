#include <Actor.h>

#ifndef __DIE__H__
#define __DIE__H__

class Bob;

class Die : public virtual Actor {
 private:

 public:
  Die(Level* l, float x, float y, float w, float h);
  
  virtual bool hitBob(Bob* b);
  
  virtual void act();

};

#endif
