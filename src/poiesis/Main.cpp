#include <iostream>
#include <memory.h>

#include "bandit/Engine.h"

#include "poiesis/systems/RenderingSystem.h"
#include "poiesis/levels/Level1.h"

int main()
{
    LOG_SET_DEBUG();
    BANDIT_ENGINE_INIT();
    Engine::GetInstance().CreateWindow("Poiesis", 1280, 720);

    // Necessary to display the window.
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());

    Engine::GetInstance().SetCurrentLevel(std::make_shared<Level1>());
    Engine::GetInstance().Run();
    BANDIT_ENGINE_SHUTDOWN();
    
    return 0;
}