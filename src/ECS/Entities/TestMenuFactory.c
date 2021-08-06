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
#include "../../MenuItemFunctions.h"
#include "TestMenuFactoryExtern.h"

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
            "Engine Test",
            true
        )
    );
    menuEasy(
        // Sets this var
        items,
        // Sets this var
        currentItem,
        // Menu entity ID
        e,
        // Number of items
        7,
        // Run this for each item
        Menu_ItemUpdate_Basic,
        // Run this for the menu
        Menu_MenuUpdate_Basic,
        // Active?
        true
    );
    
    menuItemSetup(e, "PressStart2P/PressStart2P.ttf", 8, items);
    
    menuItemSuperEasy("Play `Paddle`", MenuItem_Select_PaddleScene, NULL);
    menuItemSuperEasy(TestMenuFactory_String_Volume_Master, NULL, MenuItem_Update_SetVolumeMaster);
    menuItemSuperEasy(TestMenuFactory_String_Volume_Music, NULL, MenuItem_Update_SetVolumeMusic);
    menuItemSuperEasy(TestMenuFactory_String_Volume_SFX, NULL, MenuItem_Update_SetVolumeSFX);
    menuItemSuperEasy("Play SFX", MenuItem_Select_PlaySFX, NULL);
    menuItemSuperEasy("Play Song", MenuItem_Select_PlayMusic, NULL);
    menuItemSuperEasy("Exit", MenuItem_Select_Exit, NULL);
    
    return e;
}
