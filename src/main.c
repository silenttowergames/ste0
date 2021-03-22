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
    
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, FullscreenShortcutSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, PauseMenuSystem, EcsOnUpdate, Menu, PauseMenu);
    ECS_SYSTEM(world, AINPCSystem, EcsOnUpdate, AINPC, Body);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    
    BasicAABBSystem_Init();
    
    MenuSystem_Init();
    
    ECS_SYSTEM(world, DebugMovableSystem, EcsOnUpdate, Renderable, Body);
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow, Renderable);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    
    DrawSystem_Init();
}

void initializeScene(ecs_world_t* world)
{
    ctx();
    
    factoryRun(app, "Player", -32, 0, 0, NULL);
    
    factoryRun(app, "NPC", 32, 0, 0, NULL);
    factoryRun(app, "NPC", 0, 32, 0, NULL);
    factoryRun(app, "NPC", 32, 32, 0, NULL);
    
    factoryRun(app, "NPC", 32, -96, 0, NULL);
    factoryRun(app, "NPC", 32, -80, 0, NULL);
    factoryRun(app, "NPC", 32, -64, 0, NULL);
    factoryRun(app, "NPC", 32, -48, 0, NULL);
    
    factoryRun(app, "NPC", 16, -56, 0, NULL);
    factoryRun(app, "NPC", 16, -72, 0, NULL);
    factoryRun(app, "NPC", 16, -88, 0, NULL);
    
    factoryRun(app, "TextBox", -20, -85, 2, NULL);
    factoryRun(app, "TextBox", 0, 0, 2, NULL);
}

void init2Scene(ecs_world_t* world)
{
    ctx();
    
    //factoryRun(app, "TextBox", -20, -20, 2, NULL);
    
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            //factoryRun(app, "NPC", 80 + (x * 12), 80 + (y * 12), 2, NULL);
        }
    }
    
    factoryRun(app, "TestMenu", -120, -40, 5, NULL);
}

int Time = 0;

void ShaderUpdate_Disable(void* _app, void* _renderTarget, void* _shader)
{
    sctx();
    
    if(keys(Pressed, s))
    {
        shader->disabled = !shader->disabled;
    }
    
    Time += rand() % 5;
    
    Shader_ParamCopy(shader, "Width", &renderTarget->size.X, sizeof(int));
    Shader_ParamCopy(shader, "Height", &renderTarget->size.Y, sizeof(int));
    
    float tmod = (sinf(Time * 64.0f) * 0.01f) + 0.99f;
    tmod = 1;
    
    Shader_ParamCopy(shader, "tmod", &tmod, sizeof(float));
}

int main(int arcg, char* argv[])
{
    configDefault(config, 1280, 720, "en", false);
    
    printf("M: %f\nS: %f\nM: %f\n", config.volumeMaster, config.volumeSFX, config.volumeMusic);
    
    init(
        "Engine Test",
        "v1.0.5 alpha",
        "OpenGL",
        60,
        config,
        320, 180,
        1024, 1024,
        initWorld,
        "map0",
        RSZ_Floor
    );
    
    gameDataInit(
        3,
        gdAttr("Integers", "hello", 27, Int),
        gdAttr("Integers", "hiThere", 8, Int),
        gdAttr("Strings", "alrighty", "Well! Hello.", String)
    );
    
    scenes(
        4,
        scene(initialize),
        sceneTiled("map1", NULL),
        sceneTiled("map0", init2Scene),
        scene(init2)
    );
    
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
        1,
        Shader_Create(&app, "CRTShader", ShaderUpdate_Disable)
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
    
    factories(
        4,
        factory(Player),
        factory(NPC),
        factory(TextBox),
        factory(TestMenu)
    );
    
    renderTargets(
        2,
        RenderTarget_Create(&app, (int2d){ 200, 180, }, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 1, 0, 1, 1, }),
        RenderTarget_Create(&app, (int2d){ 80, 80, }, (int2d){ 80, 80, }, (int2d){ 40, 40, }, false, (FNA3D_Vec4){ 1, 1, 1, 0.5f, })
    );
    
    /*
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //*/
    
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
    
    loop();
    
    GameData_Save(&app.gameData);
    
    quit();
}