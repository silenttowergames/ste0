#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>
#include <STE/GameData/GameDataFunctions.h>
#include <STE/Utilities/colorFunctions.h>

#include "../../ecs_declarations.h"
#include "PaddleScoresFactory.h"

static char PaddleScoresFactory_ScoreLeft[3];
static char PaddleScoresFactory_ScoreRight[3];

ecs_entity_t PaddleScoresFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e;
    int score;
    
    score = gdValue("Scores", "left", Int);
    sprintf(PaddleScoresFactory_ScoreLeft, "%d", score);
    e = ecs_new(world, 0);
    ecs_set(world, e, Body, bodyEasy(
        -16,
        -(app->renderState.resolution.Y / 2) + 10
    ));
    ecs_set(world, e, Renderable, RenderableText(
        "PressStart2P/PressStart2P.ttf",
        8,
        layer,
        1,
        0,
        colorU(255, 0, 0, 255),
        0,
        PaddleScoresFactory_ScoreLeft,
        true
    ));
    
    score = gdValue("Scores", "right", Int);
    sprintf(PaddleScoresFactory_ScoreRight, "%d", score);
    e = ecs_new(world, 0);
    ecs_set(world, e, Body, bodyEasy(
        +16,
        -(app->renderState.resolution.Y / 2) + 10
    ));
    ecs_set(world, e, Renderable, RenderableText(
        "PressStart2P/PressStart2P.ttf",
        8,
        layer,
        1,
        0,
        colorU(255, 0, 0, 255),
        0,
        PaddleScoresFactory_ScoreRight,
        true
    ));
    
    return e;
}
