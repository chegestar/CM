#include <CheckPoint.h>

#ifndef __EXIT__H__
#define __EXIT__H__

class Exit : public CheckPoint {
 public:
  Exit(Level* l, float x_,float y_);
  int activate() {texture_set=0;level->getBob()->setExit();return 0;}

 
};

#endif
