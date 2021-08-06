#pragma once

#include <flecs.h>
#include <STE/Application/ApplicationState.h>
#include <STE/ECS/Components/Menu.h>

void MenuItem_Select_Exit(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
void MenuItem_Select_PaddleScene(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
void MenuItem_Select_PlayMusic(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
void MenuItem_Select_PlaySFX(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
static void MenuItem_Update_SetVolumeGeneric(float* volume, char* string, char* prefix, bool isActive, bool inputAdd, bool inputSubtract);
void MenuItem_Update_SetVolumeMaster(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive);
void MenuItem_Update_SetVolumeMusic(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive);
void MenuItem_Update_SetVolumeSFX(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu, bool isActive);
