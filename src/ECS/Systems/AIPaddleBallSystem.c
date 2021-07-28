#include <math.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Audio/SoundFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/Body.h>
#include <STE/GameData/GameDataFunctions.h>
#include "AIPaddleBallSystem.h"
#define AIPADDLEBALLSYSTEMDEFINES_FINAL
#include "AIPaddleBallSystemDefines.h"
#include "../Components/AIPaddle.h"
#include "../Components/AIPaddleBall.h"
#include "../../ecs_declarations.h"

void AIPaddleBallSystem(ecs_iter_t* it)
{
    fctx();
    
	AIPaddleBall* a = ecs_column(it, AIPaddleBall, 1);
    Body* b = ecs_column(it, Body, 2);
    
    bool touchingX;
    bool touchingY;
    
    for(int i = 0; i < it->count; i++)
    {
        a[i].velocity.Y = fmin(fabs(a[i].velocity.Y), 7.0f) * (a[i].velocity.Y > 0 ? 1 : -1);
        
        b[i].position.X += a[i].velocity.X * fdelta();
        b[i].position.Y += a[i].velocity.Y * fdelta();
        
        if(
            (a[i].velocity.X < 0 && b[i].position.X < 0)
            ||
            (a[i].velocity.X > 0 && b[i].position.X >= app->renderState.resolution.X)
        )
        {
            app->flecsScene = "Paddle";
            
            GameDataAttribute* scoreLeft = GameData_Get(&app->gameData, "Scores", "left");
            GameDataAttribute* scoreRight = GameData_Get(&app->gameData, "Scores", "right");
            
            // Lol magic number
            if(b[i].position.X < 30)
            {
                scoreRight->valueInt++;
            }
            else
            {
                scoreLeft->valueInt++;
            }
            
            if(scoreLeft->valueInt >= 10 || scoreRight->valueInt >= 10)
            {
                scoreLeft->valueInt = 0;
                scoreRight->valueInt = 0;
                
                soundPlay("paddle-win.ogg");
            }
            else
            {
                soundPlay("paddle-fail.ogg");
            }
            
            return;
        }
        
        if(
            (a[i].velocity.Y < 0 && b[i].position.Y < 0)
            ||
            (a[i].velocity.Y > 0 && b[i].position.Y >= app->renderState.resolution.Y)
        )
        {
            touchingY = true;
        }
        
        // If we haven't touched on X, run the query
        if(!touchingX)
        {
            ecs_iter_t iter = ecs_query_iter(AIPaddleBallSystem_Query_Paddles);
            while(ecs_query_next(&iter))
            {
                AIPaddle* jp = ecs_column(&iter, AIPaddle, 1);
                Body* jb = ecs_column(&iter, Body, 2);
                
                for(int j = 0; j < iter.count; j++)
                {
                    // If Y doesn't match, quit
                    if(
                        b[i].position.Y > jb[i].position.Y + 10
                        ||
                        b[i].position.Y < jb[i].position.Y - 10
                    )
                    {
                        continue;
                    }
                    
                    // Collide with paddle
                    if(
                        // Left
                        (jp[i].direction && a[i].velocity.X < 0 && fabs(b[i].position.X - 8 - jb[i].position.X) < 2)
                        ||
                        // Right
                        (!jp[i].direction && a[i].velocity.X > 0 && fabs(b[i].position.X + 8 - jb[i].position.X) < 2)
                    )
                    {
                        touchingX = true;
                        
                        a[i].velocity.Y += (b[i].position.Y - jb[i].position.Y) / 4.0f;
                        
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
            
            soundPlay("paddle-blip-high.ogg");
        }
        
        if(touchingY)
        {
            a[i].velocity.Y *= -1;
            
            soundPlay("paddle-blip-low.ogg");
        }
    }
}
