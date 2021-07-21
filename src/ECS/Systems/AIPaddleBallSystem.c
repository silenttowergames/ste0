#include <math.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include "AIPaddleBallSystem.h"
#define AIPADDLEBALLSYSTEMDEFINES_FINAL
#include "AIPaddleBallSystemDefines.h"
#include "../Components/AIPaddle.h"
#include "../Components/AIPaddleBall.h"
#include "../../ecs_declarations.h"

void AIPaddleBallSystem(ecs_iter_t* it)
{
    fctx();
    
    printf("AIPaddleBallSystem:\n");
    
    if(AIPaddleBallSystem_Query_Paddles == NULL)
    {
        printf("AIPaddleBallSystem_Query_Paddles:\n");
        
        AIPaddleBallSystem_Query_Paddles = ecs_query_init(it->world, &(ecs_query_desc_t){
            .filter.terms = {
                { ecs_id(AIPaddle), },
                { ecs_id(Body), },
            },
        });
        
        printf("AIPaddleBallSystem_Query_Paddlesed!\n");
    }
	
	AIPaddleBall* a = ecs_column(it, AIPaddleBall, 1);
    Body* b = ecs_column(it, Body, 2);
    
    bool touchingX;
    bool touchingY;
    
    for(int i = 0; i < it->count; i++)
    {
        b[i].position.X += a[i].velocity.X;
        b[i].position.Y += a[i].velocity.Y;
        
        if(
            (a[i].velocity.X < 0 && b[i].position.X < 0)
            ||
            (a[i].velocity.X > 0 && b[i].position.X >= app->renderState.resolution.X)
        )
        {
            //a[i].velocity.X *= -1;
            touchingX = true;
        }
        
        if(
            (a[i].velocity.Y < 0 && b[i].position.Y < 0)
            ||
            (a[i].velocity.Y > 0 && b[i].position.Y >= app->renderState.resolution.Y)
        )
        {
            //a[i].velocity.Y *= -1;
            touchingY = true;
        }
        
        // If we haven't touched on X, run the query
        if(!touchingX)
        {
            printf("Starting internal query\n");
            
            ecs_iter_t iter = ecs_query_iter(AIPaddleBallSystem_Query_Paddles);
            while(ecs_query_next(&iter))
            {
                AIPaddle* jp = ecs_column(&iter, AIPaddle, 1);
                Body* jb = ecs_column(&iter, Body, 2);
                
                for(int j = 0; j < iter.count; j++)
                {
                    // If Y doesn't match, quit
                    if(
                        b[i].position.Y > jb[i].position.Y + 8
                        ||
                        b[i].position.Y < jb[i].position.Y - 8
                    )
                    {
                        continue;
                    }
                    
                    // Collide with paddle
                    if(
                        // Left
                        (jp[i].direction && a[i].velocity.X < 0 && fabs(b[i].position.X - jb[i].position.X) < 8)
                        ||
                        // Right
                        (!jp[i].direction && a[i].velocity.X > 0 && fabs(b[i].position.X - jb[i].position.X) < 8)
                    )
                    {
                        touchingX = true;
                        
                        a[i].velocity.Y += (b[i].position.Y - jb[i].position.Y) / 2.0f;
                        
                        break;
                    }
                }
                
                if(touchingX)
                {
                    break;
                }
            }
        }
        
        if(touchingX)
        {
            a[i].velocity.X *= -1;
        }
        
        if(touchingY)
        {
            a[i].velocity.Y *= -1;
        }
    }
}
