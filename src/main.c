#include <STE/StoneTower.h>
#include <STE/includes_libs.h>
#include <STE/includes_vendor.h>
#include "ecs_declarations.h"
#include <STE/includes.h>
#include "includes.h"

ECS_Setup(DECLARE, );

void initWorld(ecs_world_t* world)
{
    ECS_Setup(DEFINE, world);
    
    // Init
    AIPaddleNPCSystem_Init(world);
    
    // Some early preliminary stuff
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, FullscreenShortcutSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, PauseMenuSystem, EcsOnUpdate, Menu, PauseMenu);
    
    // Paddle Systems
    ECS_TAG(world, AIPaddlePlayer);
    ECS_TAG(world, AIPaddleNPC);
    ECS_SYSTEM(world, AIPaddlePlayerSystem, EcsOnUpdate, AIPaddle, AIPaddlePlayer, Body);
    ECS_SYSTEM(world, AIPaddleNPCSystem, EcsOnUpdate, AIPaddle, AIPaddleNPC, Body);
    ECS_SYSTEM(world, AIPaddleYSystem, EcsOnUpdate, AIPaddle, Body);
    AIPaddleBallSystem_Init();
    
    BasicAABBSystem_Init();
    
    MenuSystem_Init();
    
    DebugMovableSystem_Init();
    
    ECS_SYSTEM(world, SettingsSystem, EcsOnUpdate, 0);
    
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow, Renderable);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    
    DrawSystem_Init();
}

int main(int argc, char* argv[])
{
    configDefault(config, 1280, 720, "en", true);
    
    init(
        "Engine Test",
        "v1.0.0",
        "OpenGL",
        60,
        config,
        320, 180,
        1024, 1024,
        initWorld,
        "Title",
        RSZ_Floor
    );
    
    if(argc > 1 && strcmp("getpath", argv[1]) == 0)
    {
        printf("%s", app.savePath);
        
        return 0;
    }
    
    scenes(
        2,
        scene(Title),
        scene(Paddle)
    );
    
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
        8,
        Sound_create_load("calm-example.ogg", Play_StopAll, SoundCategory_Music),
        Sound_create_load("hit.ogg", Play_StopOne, SoundCategory_SFX),
        Sound_create_load("paddle-blip-high.ogg", Play_StopAll, SoundCategory_SFX),
        Sound_create_load("paddle-blip-low.ogg", Play_StopAll, SoundCategory_SFX),
        Sound_create_load("paddle-fail.ogg", Play_StopAll, SoundCategory_SFX),
        Sound_create_load("paddle-win.ogg", Play_StopAll, SoundCategory_SFX),
        Sound_create_speech("speech0", "Uncompromised", Play_Default, SoundCategory_SFX),
        Sound_create_sfxr("sfxr", Play_Default, SoundCategory_SFX)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(&app, (int2d){ 320, 180, }, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 0, 0, 0, 1, })
    );
    
    gameDataInit(
        10,
        gdAttr("Scores", "left", 3, Int),
        gdAttr("Scores", "right", 0, Int),
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
        10,
        ConsoleCommand_Create("exit", cmdExit),
        ConsoleCommand_Create("play", cmdPlaySound),
        ConsoleCommand_Create("volume", cmdVolume),
        ConsoleCommand_Create("scene", cmdChangeScene),
        ConsoleCommand_Create("pause", cmdPause),
        ConsoleCommand_Create("unpause", cmdUnpause),
        ConsoleCommand_Create("website", cmdWebsite),
        ConsoleCommand_Create("reload-map", cmdReloadMap),
        ConsoleCommand_Create("movable", cmdMovable),
        ConsoleCommand_Create("fps", cmdShowFPS)
    );
    
    /* RESOURCES */
    
    /* FACTORIES */
    factories(
        6,
        factory(PaddleBall),
        factory(Paddle),
        factory(PaddleNPC),
        factory(PaddleScores),
        factory(TestMenu),
        factory(TextBox)
    );
    /* FACTORIES */
    
    //*
    app.renderState.targets[0].shadersCount = 1;
    app.renderState.targets[0].shaders = malloc(sizeof(Shader*) * app.renderState.targets[0].shadersCount);
    app.renderState.targets[0].shaders[0] = *mapGet(app.assetManager.mapShader, "YellowShader", Shader*);
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //app.renderState.mainRenderTarget.shaders[1] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //*/
    
    loop();
    
    GameData_Save(&app.gameData);
    
    quit();
}
