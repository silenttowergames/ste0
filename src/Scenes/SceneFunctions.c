#include <STE/Application/ApplicationStateFunctions.h>
#include "SceneFunctions.h"

void initializeScene(ecs_world_t* world)
{
    ctx();
    
    factoryRun(app, "Player", -32, 0, 0, NULL);
    
    factoryRun(app, "NPC", 32, 0, 0, NULL);
    factoryRun(app, "NPC", 0, 32, 0, NULL);
    factoryRun(app, "NPC", 32, 32, 0, NULL);
    
    factoryRun(app, "NPC", 32, -96, 0, NULL);
    factoryRun(app, "NPC", 32, -80, 0, NULL);
    factoryRun(app, "NPC", 32, -64, 0, NULL);
    factoryRun(app, "NPC", 32, -48, 0, NULL);
    
    factoryRun(app, "NPC", 16, -56, 0, NULL);
    factoryRun(app, "NPC", 16, -72, 0, NULL);
    factoryRun(app, "NPC", 16, -88, 0, NULL);
    
    factoryRun(app, "TextBox", -20, -85, 2, NULL);
    factoryRun(app, "TextBox", 0, 0, 2, NULL);
}

void TitleScene(ecs_world_t* world)
{
    ctx();
    
    factoryRun(app, "TestMenu", -128, -32, 0, NULL);
}

void PaddleScene(ecs_world_t* world)
{
    ctx();
    
    app->renderState.targets[0].camera.position.X = app->renderState.targets[0].camera.resolution.X / 2;
    app->renderState.targets[0].camera.position.Y = app->renderState.targets[0].camera.resolution.Y / 2;
    
    factoryRun(app, "PaddleBall", app->renderState.resolution.X / 2, app->renderState.resolution.Y / 2, 0, NULL);
    
    factoryRun(app, "Paddle", 8, app->renderState.resolution.Y / 2, 0, NULL);
    
    factoryRun(app, "PaddleNPC", app->renderState.resolution.X - 8, app->renderState.resolution.Y / 2, 0, NULL);
}
