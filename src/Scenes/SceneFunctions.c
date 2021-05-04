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

void init2Scene(ecs_world_t* world)
{
    ctx();
    
    factoryRun(app, "TextBox", -20, -20, 2, NULL);
    
    for(int x = 0; x < 28; x++)
    {
        for(int y = 0; y < 18; y++)
        {
            factoryRun(app, "NPC", 80 + (x * 12), 80 + (y * 12), 2, NULL);
        }
    }
    
    factoryRun(app, "TestMenu", -120, -40, 5, NULL);
}
