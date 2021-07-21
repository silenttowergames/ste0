#include <STE/StoneTower.h>
#include <STE/includes_libs.h>
#include <STE/includes_vendor.h>
#include "ecs_declarations.h"
#include <STE/includes.h>
#include "includes.h"

ECS_Setup(DECLARE, );

void initWorld(ecs_world_t* world)
{
    printf("Initializing world...\n");
    
    ECS_Setup(DEFINE, world);
    printf("Defines\n");
    
    // Some early preliminary stuff
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, FullscreenShortcutSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, PauseMenuSystem, EcsOnUpdate, Menu, PauseMenu);
    
    printf("3 systems\n");
    
    // Paddle Systems
    ECS_TAG(world, AIPaddlePlayer);
    ECS_TAG(world, AIPaddleNPC);
    ECS_SYSTEM(world, AIPaddlePlayerSystem, EcsOnUpdate, AIPaddle, AIPaddlePlayer, Body);
    ECS_SYSTEM(world, AIPaddleNPCSystem, EcsOnUpdate, AIPaddle, AIPaddleNPC, Body);
    ECS_SYSTEM(world, AIPaddleYSystem, EcsOnUpdate, AIPaddle, Body);
    
    // FAILS TO INIT
    //AIPaddleBallSystem_Init();
    AIPaddleBallSystem_Query_Paddles = NULL;
    ECS_SYSTEM(world, AIPaddleBallSystem, EcsOnUpdate, AIPaddleBall, Body);
    
    printf("4 more systems\n");
    
    BasicAABBSystem_Init();
    printf("1 more systems\n");
    
    MenuSystem_Init();
    printf("1 more systems\n");
    
    DebugMovableSystem_Init();
    printf("1 more systems\n");
    
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow, Renderable);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    printf("3 more systems\n");
    
    // FAILS TO INIT
    //DrawSystem_Init();
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, FinalizeScreenSystem, EcsOnUpdate, 0);
    const EcsQuery* sort = ecs_get(world, DrawSystem, EcsQuery);
    //ecs_query_order_by(world, sort->query, ecs_entity(Renderable), SortByLayerThenY);
    //ecs_query_order_by(world, sort->query, ecs_entity(Renderable), NULL);
    printf("1 more systems\n");
    
    printf("World initialized!\n");
}

int main(int arcg, char* argv[])
{
    configDefault(config, 1280, 720, "en", true);
    
    printf("Init\n");
    
    init(
        "Engine Test",
        "v1.0.0",
        "OpenGL",
        60,
        config,
        320, 180,
        1024, 1024,
        initWorld,
        "Paddle",
        RSZ_Floor
    );
    
    scenes(
        2,
        scene(Title),
        scene(Paddle)
    );
    
    printf("Resources:\n");
    
    /* RESOURCES */
    
    textures(
        2,
        Texture_Create(&app, "16x16", 16, 16, 0, 0, 0, 0),
        Texture_Create(&app, "8x8", 8, 8, 0, 0, 0, 0)
    );
    
    maps(
        2,
        TiledJSON_Load(&app, "map0"),
        TiledJSON_Load(&app, "map1")
    );
    
    shaders(
        2,
        Shader_Create(&app, "CRTShader", ShaderUpdate_Disable),
        Shader_Create(&app, "YellowShader", NULL)
    );
    
    scripts(
        2,
        LuaScript_Load(&app, "test"),
        LuaScript_Load(&app, "test2")
    );
    
    fonts(
        2,
        Font_Create(&app, "Bloodyslime/Bloodyslime.ttf"),
        Font_Create(&app, "PressStart2P/PressStart2P.ttf")
    );
    
    sounds(
        4,
        Sound_create_load("calm-example.ogg", Play_StopAll, SoundCategory_Music),
        Sound_create_load("hit.ogg", Play_StopOne, SoundCategory_SFX),
        Sound_create_speech("speech0", "Uncompromised", Play_Default, SoundCategory_SFX),
        Sound_create_sfxr("sfxr", Play_Default, SoundCategory_SFX)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(&app, (int2d){ 320, 180, }, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 0, 0, 0, 1, })
    );
    
    gameDataInit(
        8,
        gdAttr("Bools", "isThisTrue", true, Bool),
        gdAttr("Bools", "isThisFalse", false, Bool),
        gdAttr("Floats", "piApprox", 3.141592, Float),
        gdAttr("Floats", "piHello", 3.14, Float),
        gdAttr("Integers", "hello", 27, Int),
        gdAttr("Integers", "hiThere", 8, Int),
        gdAttr("Strings", "alrighty", "Well! Hello.", String),
        gdAttr("Strings", "helloWorld", "Hello, World!", String)
    );
    
    ConsoleCommand_AddAll(
        &app,
        9,
        ConsoleCommand_Create("exit", cmdExit),
        ConsoleCommand_Create("play", cmdPlaySound),
        ConsoleCommand_Create("volume", cmdVolume),
        ConsoleCommand_Create("scene", cmdChangeScene),
        ConsoleCommand_Create("pause", cmdPause),
        ConsoleCommand_Create("unpause", cmdUnpause),
        ConsoleCommand_Create("website", cmdWebsite),
        ConsoleCommand_Create("reload-map", cmdReloadMap),
        ConsoleCommand_Create("movable", cmdMovable)
    );
    
    /* RESOURCES */
    
    printf("Resources done!\n");
    
    printf("Factories:\n");
    
    /* FACTORIES */
    factories(
        5,
        factory(PaddleBall),
        factory(Paddle),
        factory(PaddleNPC),
        factory(TestMenu),
        factory(TextBox)
    );
    /* FACTORIES */
    
    printf("Factorties done!\n");
    
    //*
    app.renderState.targets[0].shadersCount = 1;
    app.renderState.targets[0].shaders = malloc(sizeof(Shader*) * app.renderState.targets[0].shadersCount);
    app.renderState.targets[0].shaders[0] = *mapGet(app.assetManager.mapShader, "YellowShader", Shader*);
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //app.renderState.mainRenderTarget.shaders[1] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //*/
    
    printf("Loop:\n");
    
    loop();
    
    GameData_Save(&app.gameData);
    
    quit();
}
