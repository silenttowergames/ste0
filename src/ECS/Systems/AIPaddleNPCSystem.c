#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include "AIPaddleNPCSystem.h"
#include "../Components/AIPaddle.h"

static ecs_query_t* AIPaddleNPCSystem_BallQuery = NULL;

void AIPaddleNPCSystem_Init(ecs_world_t* world)
{
    AIPaddleNPCSystem_BallQuery = ecs_query_new(world, "AIPaddleBall,Body");
}

void AIPaddleNPCSystem(ecs_iter_t* it)
{
    fctx();
    
    // Get the ball position
    float2d ballPos = {
        .X = 0,
        .Y = 0,
    };
    ecs_iter_t iter = ecs_query_iter(AIPaddleNPCSystem_BallQuery);
    while(ecs_query_next(&iter))
    {
        Body* bb = ecs_column(&iter, Body, 2);
        
        for(int i = 0; i < 1; i++)
        {
            ballPos.X = bb[i].position.X;
            ballPos.Y = bb[i].position.Y;
        }
    }
    
	AIPaddle* a = ecs_column(it, AIPaddle, 1);
    Body* b = ecs_column(it, Body, 3);
    
    for(int i = 0; i < it->count; i++)
    {
        b[i].position.Y += ((ballPos.Y - b[i].position.Y) / 5.0f) * fdelta();
    }
}
