#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include <STE/Input/KeyboardStateFunctions.h>
#include "AIPaddlePlayerSystem.h"
#include "../Components/AIPaddle.h"

void AIPaddlePlayerSystem(ecs_iter_t* it)
{
    fctx();
    
	AIPaddle* a = ecs_column(it, AIPaddle, 1);
    Body* b = ecs_column(it, Body, 3);
    
    for(int i = 0; i < it->count; i++)
    {
        if(keys(Down, DOWN))
        {
            b[i].position.Y += a[i].speed * fdelta();
        }
        
        if(keys(Down, UP))
        {
            b[i].position.Y -= a[i].speed * fdelta();
        }
    }
}
