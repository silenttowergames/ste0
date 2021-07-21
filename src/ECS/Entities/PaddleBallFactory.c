#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>

#include "../../ecs_declarations.h"
#include "PaddleBallFactory.h"
#include "../Components/AIPaddleBall.h"

ecs_entity_t PaddleBallFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, AIPaddleBall, {
        .velocity = {
            .X = -5.0f,
            .Y = 0.0f,
        },
    });
    ecs_set(world, e, Animate, {
        "ball",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable, RenderableSprite(
        getTexture("8x8"),
        int2dInit(0, 0),
        layer,
        0.5f,
        1,
        0xFFFFFFFF,
        0
    ));
    
    return e;
}
