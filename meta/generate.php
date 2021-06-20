<?php

// TODO: Auto-generating factories
// TODO: Finish asset load generation
// TODO: generate.php assets
// TODO: Automate ecs_declarations
// TODO: Make asset & others loading part of build script
// TODO: Ctrl+. task or something for pulling in .h for missing struct usage?

// Get rid of filename
array_shift($argv);

if(empty($argv))
{
    die("No command!\n");
}

// Command
$cmd = array_shift($argv);

// Work based off of the command
switch($cmd)
{
    case 'factory':
    {
        if(empty($argv))
        {
            die("Factory: no name!\n");
        }
        
        $template = file_get_contents('./meta/template__factory.h');
        $template = str_replace('_____NAME_____', $argv[0], $template);
        file_put_contents('./src/ECS/Entities/' . $argv[0] . 'Factory.h', $template);
        
        $template = file_get_contents('./meta/template__factory.c');
        $template = str_replace('_____NAME_____', $argv[0], $template);
        file_put_contents('./src/ECS/Entities/' . $argv[0] . 'Factory.c', $template);
    } break;
}

?>