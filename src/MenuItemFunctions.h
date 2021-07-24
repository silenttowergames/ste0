#pragma once

#include <flecs.h>
#include <STE/Application/ApplicationState.h>
#include <STE/ECS/Components/Menu.h>

void MenuItem_Select_Exit(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
void MenuItem_Select_PaddleScene(ApplicationState* app, ecs_world_t* world, ecs_entity_t entityID, Menu* menu);
