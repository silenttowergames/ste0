#include <STE/Application/ApplicationState.h>
#include <STE/Audio/SoundFunctions.h>
#include <STE/Input/KeyboardStateFunctions.h>
#include "MenuItemFunctions.h"
#define TESTMENUFACTORY_EXTERN
#include "ECS/Entities/TestMenuFactoryExtern.h"

void MenuItem_Select_Exit(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu)
{
    app->quit = true;
}

void MenuItem_Select_PaddleScene(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu)
{
    app->flecsScene = "Paddle";
}

void MenuItem_Select_PlayMusic(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu)
{
    soundPlayFull("calm-example.ogg", 1.0f, 0.0f, 0.0f, 1.0f, false);
}

void MenuItem_Select_PlaySFX(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu)
{
    soundPlayFull("hit.ogg", 1.0f, 0.0f, 0.0f, 1.0f, false);
}

void MenuItem_Update_SetVolumeSFX(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu)
{
    if(keys(Pressed, RIGHT))
    {
        app->config.volumeSFX += 0.1f;
    }
    
    if(keys(Pressed, LEFT))
    {
        app->config.volumeSFX -= 0.1f;
    }
    
    sprintf(TestMenuFactory_String_Volume_SFX, "SFX Volume: %1.1f", app->config.volumeSFX);
}
