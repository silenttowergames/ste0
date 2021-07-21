#include "MenuItemFunctions.h"

void MenuItem_Select_Exit(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    app->quit = true;
}

void MenuItem_Select_PaddleScene(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    app->flecsScene = "Paddle";
}
