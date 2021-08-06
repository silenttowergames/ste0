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

static void MenuItem_Update_SetVolumeGeneric(float* volume, char* string, char* prefix, bool isActive, bool inputAdd, bool inputSubtract)
{
    if(isActive)
    {
        if(inputAdd)
        {
            *volume += 0.1f;
        }
        
        if(inputSubtract)
        {
            *volume -= 0.1f;
        }
    }
    
    sprintf(string, "%s Volume: %1.1f", prefix, *volume);
}

void MenuItem_Update_SetVolumeMaster(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive)
{
    MenuItem_Update_SetVolumeGeneric(
        &app->config.volumeMaster,
        TestMenuFactory_String_Volume_Master,
        "Master",
        isActive,
        keys(Held, RIGHT),
        keys(Held, LEFT)
    );
}

void MenuItem_Update_SetVolumeMusic(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive)
{
    MenuItem_Update_SetVolumeGeneric(
        &app->config.volumeMusic,
        TestMenuFactory_String_Volume_Music,
        "Music",
        isActive,
        keys(Held, RIGHT),
        keys(Held, LEFT)
    );
}

void MenuItem_Update_SetVolumeSFX(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive)
{
    MenuItem_Update_SetVolumeGeneric(
        &app->config.volumeSFX,
        TestMenuFactory_String_Volume_SFX,
        "SFX",
        isActive,
        keys(Held, RIGHT),
        keys(Held, LEFT)
    );
}
