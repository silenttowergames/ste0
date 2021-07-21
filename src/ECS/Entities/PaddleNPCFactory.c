#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>

#include "../../ecs_declarations.h"
#include "PaddleNPCFactory.h"
#include "../Components/AIPaddle.h"

ecs_entity_t PaddleNPCFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ECS_TAG(world, AIPaddleNPC);
    
    ecs_set(world, e, AIPaddle, {
        .direction = false,
        .speed = 2.0f,
    });
    ecs_add(world, e, AIPaddleNPC);
    ecs_set(world, e, Animate, {
        "paddle",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable, RenderableSprite(
        getTexture("16x16"),
        int2dInit(0, 0),
        layer,
        0.5f,
        1,
        0xFFFFFFFF,
        0
    ));
    
    Renderable* sprite = ecs_get_mut(world, e, Renderable, 0);
    sprite->flipX = true;
    
    return e;
}
