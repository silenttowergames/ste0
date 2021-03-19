#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>
#include <STE/ECS/Components/RenderOffsetFunctions.h>
#include <STE/Assets/Font.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Utilities/colorFunctions.h>

#include "../../ecs_declarations.h"
#include "TextBoxFactory.h"

ecs_entity_t TextBoxFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            5,
            1,
            1,
            colorU(0, 0, 255, 255),
            0,
            "Retro"
        )
    );
    
    return e;
}
