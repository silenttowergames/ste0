<?php

$components = [
    'Animate',
    'BasicAABB',
    'Body',
    'CameraFollow',
    'Menu',
    'MenuItem',
    'PauseMenu',
    'Renderable',
    'TiledMap',
    'TiledObject',
    'TileLayerCollides',
];

foreach(scandir('./src/ECS/Components/') as $cFile)
{
    if(in_array($cFile, [ '.', '..', ]))
    {
        continue;
    }
    
    $cFile = explode('.', $cFile);
    $cFile = array_shift($cFile);
    
    $components[] = $cFile;
}

ob_start();

?>
#pragma once

#include <flecs.h>

#define STE_ECS_COMPONENT_DECLARE(w, T) ECS_COMPONENT_DECLARE(T)
#define STE_ECS_COMPONENT_DEFINE(w, T) ECS_COMPONENT_DEFINE(w, T)
#define STE_ECS_COMPONENT_EXTERN(w, T) ECS_COMPONENT_EXTERN(T)

#define ECS_Setup(de, w) \
<?php foreach($components as $key => $component): ?>
    STE_ECS_COMPONENT_ ## de(w, <?=$component?>)<?php if($key < count($components) - 1): ?>;\<?php endif; ?>

<?php endforeach; ?>

ECS_Setup(EXTERN, );
<?php

$contents = ob_get_clean();

file_put_contents('./src/ecs_declarations.h', $contents);

?>