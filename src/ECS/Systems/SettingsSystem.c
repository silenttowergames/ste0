#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/Input/KeyboardStateFunctions.h>
#include <STE/Audio/SoundFunctions.h>

#include "SettingsSystem.h"


void SettingsSystem(ecs_iter_t* it)
{
    fctx();
	
	// FIXME: Timescale is broken!
	
	if(keys(Pressed, v))
	{
        printf("Playing `hit.ogg`\n");
		soundPlayFull("hit.ogg", 1.0f, 0.0f, 0.0f, 1.0f, false);
	}
	
	if(keys(Pressed, x))
	{
        printf("Setting world timescale to 1.0\n");
		ecs_set_time_scale(app->world, 1);
	}
	
	if(keys(Pressed, u))
	{
        printf("Setting world timescale to 2.0\n");
		ecs_set_time_scale(app->world, 2);
	}
	
	if(keys(Pressed, i))
	{
        printf("Setting world timescale to 0.5\n");
		ecs_set_time_scale(app->world, 0.5f);
	}
	
	if(keys(Pressed, o))
	{
        printf("Setting world timescale to 5.0\n");
		ecs_set_time_scale(app->world, 5);
	}
	
	if(keys(Pressed, p))
	{
        printf("Setting world timescale to 0.0\n");
		ecs_set_time_scale(app->world, 0.0f);
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
