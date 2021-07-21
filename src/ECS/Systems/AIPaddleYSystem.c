#include <math.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include "AIPaddleYSystem.h"
#include "../Components/AIPaddle.h"

void AIPaddleYSystem(ecs_iter_t* it)
{
    fctx();
	
	AIPaddle* a = ecs_column(it, AIPaddle, 1);
    Body* b = ecs_column(it, Body, 2);
    
    app->renderState.targets[0].camera.position.X = app->renderState.resolution.X / 2;
    app->renderState.targets[0].camera.position.Y = app->renderState.resolution.Y / 2;
    
    for(int i = 0; i < it->count; i++)
    {
        b[i].position.Y = fmax(8, fmin((app->renderState.resolution.Y - 8), b[i].position.Y));
    }
}
