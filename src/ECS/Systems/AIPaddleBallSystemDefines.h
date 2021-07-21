#pragma once

#include <flecs.h>

#define AIPaddleBallSystem_Init()\
    AIPaddleBallSystem_Query_Paddles = ecs_query_init(world, &(ecs_query_desc_t){\
        .filter.terms = {\
            { ecs_id(AIPaddle), },\
            { ecs_id(Body), },\
        },\
    });\
    ECS_SYSTEM(world, AIPaddleBallSystem, EcsOnUpdate, AIPaddleBall, Body);

#ifdef AIPADDLEBALLSYSTEMDEFINES_FINAL
ecs_query_t* AIPaddleBallSystem_Query_Paddles = NULL;
#else
extern ecs_query_t* AIPaddleBallSystem_Query_Paddles;
#endif
