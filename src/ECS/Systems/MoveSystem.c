#include <flecs.h>
#include "MoveSystem.h"
#include <STE/ECS/FlecsMapFunctions.h>
#include <STE/Application/ApplicationState.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/Audio/SoundFunctions.h>
#include <STE/Application/ConfigFunctions.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Input/GamepadStateFunctions.h>
#include <STE/Input/KeyboardStateFunctions.h>
#include <STE/Input/MouseStateFunctions.h>
#include <STE/Utilities/wallsFunctions.h>
#include <STE/GameData/GameDataAttribute.h>
#include <STE/GameData/GameDataFunctions.h>

#include "../Components/AIPlayer.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	if(keys(Pressed, v))
	{
		//soundPlayFull("hit.ogg", 1.0f, 0.0f, 0.0f, 1.0f, false);
	}
	
	if(keys(Pressed, x))
	{
		//ecs_set_time_scale(it->world, 1);
		//app->flecsScene = "map1";
	}
	
	if(keys(Pressed, u))
	{
		//ecs_set_time_scale(it->world, 2);
	}
	
	if(keys(Pressed, i))
	{
		//ecs_set_time_scale(it->world, 0.5f);
	}
	
	if(keys(Pressed, o))
	{
		//ecs_set_time_scale(it->world, 5);
	}
	
	if(keys(Pressed, p))
	{
		//ecs_set_time_scale(it->world, 0.125f);
	}
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		memset(&b[i].velocity, 0, sizeof(float2d));
		
		if(keys(Down, RIGHT) || button(Down, 0, DPAD_RIGHT) || button(Down, 0, STICK_LEFT_RIGHT))
		{
			b[i].velocity.X += a[i].speed * fdelta();
		}
		
		if(keys(Down, LEFT) || button(Down, 0, DPAD_LEFT) || button(Down, 0, STICK_LEFT_LEFT))
		{
			b[i].velocity.X -= a[i].speed * fdelta();
		}
		
		if(keys(Down, DOWN) || button(Down, 0, DPAD_DOWN) || button(Down, 0, STICK_LEFT_DOWN))
		{
			b[i].velocity.Y += a[i].speed * fdelta();
		}
		
		if(keys(Down, UP) || button(Down, 0, DPAD_UP) || button(Down, 0, STICK_LEFT_UP))
		{
			b[i].velocity.Y -= a[i].speed * fdelta() * (keys(Down, LSHIFT) ? 0.0375f : 1);
		}
		
		if(button(Pressed, 0, X))
		{
			printf("Runble 0\n");
			//rumble(0, 1.0f, 500);
			rumble(0, 0xFFFF, 0xFFFF, 500);
		}
		
		if(button(Released, 1, X))
		{
			printf("Runble 1\n");
			rumble(1, 0xFFFF, 0xFFFF, 500);
		}
	}
	
	if(keys(Pressed, x))
	{
		//soundPlay("calm-example.ogg");
	}
	
	if(keys(Pressed, z))
	{
		//soundPlay("speech0");
	}
	
	if(keys(Pressed, c))
	{
		//soundPlay("hit.ogg");
	}
	
	if(keys(Pressed, v))
	{
		//app->flecsScene = "map1";
	}
	
	if(keys(Pressed, g))
	{
		//RenderState_VSync(app, true);
	}
	
	if(keys(Pressed, h))
	{
		//RenderState_VSync(app, false);
	}
}
