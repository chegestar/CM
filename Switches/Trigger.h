#include <Switch.h>
#include <Codes.h>
#ifndef __TRIGGER_H__
#define __TRIGGER_H__

class Dynamite;

class Trigger : public Switch {
 private:
  std::vector<Dynamite*> sticks;
  C_CODE c;
 public:
  Trigger(Level* l, float x_, float y_,C_CODE col);

  int activate();

  void add(Dynamite* d) {sticks.push_back(d);}
};

#endif
