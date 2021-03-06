#ifndef TIMELINE_H
#define TIMELINE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Timeline : public Behaviour
{
public:
  static Timeline* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  Texture2d* test;


};

#endif

