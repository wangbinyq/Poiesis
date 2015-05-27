// Gets input from the user.

#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/ParticleComponent.h"

class InputSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // INPUT_SYSTEM_H_