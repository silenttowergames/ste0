#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include "AIPaddleNPCSystem.h"
#include "../Components/AIPaddle.h"

void AIPaddleNPCSystem(ecs_iter_t* it)
{
    fctx();
	
	AIPaddle* a = ecs_column(it, AIPaddle, 1);
    Body* b = ecs_column(it, Body, 3);
    
    for(int i = 0; i < it->count; i++)
    {
        // Put your code here
    }
}
