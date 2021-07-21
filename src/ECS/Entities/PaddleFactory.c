#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>

#include "../../ecs_declarations.h"
#include "PaddleFactory.h"
#include "../Components/AIPaddle.h"

ecs_entity_t PaddleFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ECS_TAG(world, AIPaddlePlayer);
    
    ecs_set(world, e, AIPaddle, {
        .direction = true,
        .speed = 2.0f,
    });
    ecs_add(world, e, AIPaddlePlayer);
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
    
    return e;
}
