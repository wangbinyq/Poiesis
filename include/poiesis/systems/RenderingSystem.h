// Process entities with renderable components and render sprites.

#ifndef RENDERING_SYSTEM_H_
#define RENDERING_SYSTEM_H_

#include <memory>
#include <string>

#include "bandit/Engine.h"
#include "bandit/core/entity/System.h"

#include "poiesis/components/PositionComponent.h"
#include "poiesis/components/SpriteComponent.h"

class RenderingSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
};

#endif // RENDERING_SYSTEM_H_