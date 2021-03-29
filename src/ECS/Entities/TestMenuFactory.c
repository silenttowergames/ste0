#include <flecs.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/Menu.h>
#include <STE/ECS/Components/MenuItem.h>
#include <STE/ECS/Components/PauseMenu.h>
#include <STE/ECS/Components/RenderableFunctions.h>

#include "../../ecs_declarations.h"
#include <STE/ECS/Components/MenuFunctions.h>
#include <STE/ECS/Components/MenuItemFunctions.h>
#include "TestMenuFactory.h"

ecs_entity_t TestMenuFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable,
        RenderableText(
            "Bloodyslime/Bloodyslime.ttf",
            32,
            layer,
            1,
            0,
            colorU(255, 0, 0, 255),
            0,
            "This Is A Menu!",
            false
        )
    );
    menuEasy(items, currentItem, e, 5, Menu_ItemUpdate_Basic, Menu_MenuUpdate_Basic, false);
    ecs_set(world, e, PauseMenu, { true, });
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            layer,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 0",
            false
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            layer,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 1",
            false
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            layer,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Disable",
            false
        ),
        MenuItem_Select_Disable,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            layer,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 3",
            false
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            layer,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 4",
            false
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    return e;
}
