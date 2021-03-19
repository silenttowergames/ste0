#pragma once

#include <STE/ECS/Entities/Factory.h>

ecs_entity_t NPCFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object);
