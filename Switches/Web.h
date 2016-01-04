#include <Switch.h>

#ifndef __WEB__H__
#define __WEB__H__

class Web : public Switch {
 public:
  Web(Level* l, float x_, float y_);

  virtual int activate();

};

#endif
