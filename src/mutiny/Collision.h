#ifndef MUTINY_ENGINE_COLLISION_H
#define MUTINY_ENGINE_COLLISION_H

#include "Vector3.h"
#include "ContactPoint.h"

#include <vector>

namespace mutiny
{

namespace engine
{

class Collision
{
public:
  Vector3 relativeVelocity;
  std::vector<ContactPoint> contacts;

};

}

}

#endif

