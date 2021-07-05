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

// Filter recursive for headers
function filterRecursiveHeaders($dir) : array
{
    $files = scandir($dir);
    
    $arr = [];
    
    foreach($files as $_file)
    {
        if(in_array($_file, [ '.', '..', ]))
        {
            continue;
        }
        
        $file = $dir . '/' . $_file;
        
        if(is_dir($file))
        {
            $arr = array_merge($arr, filterRecursiveHeaders($file));
            
            continue;
        }
        
        // Faster than substr & strcmp maybe?
        if(
            // Isn't .h
            (
                $file[strlen($file) - 1] != 'h'
                ||
                $file[strlen($file) - 2] != '.'
            )
            ||
            // Is a .h, but should be manually required
            (
                $file[strlen($file) - 3] == 'm'
                &&
                $file[strlen($file) - 4] == '.'
            )
        )
        {
            continue;
        }
        
        $arr[] = $file;
    }
    
    return $arr;
}

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
    
    case 'assets':
    {
        include 'assets.php';
    }
    
    case 'ecs-dec':
    {
        include 'ecs_declarations.php';
    }
    
    case 'includes':
    {
        $files = filterRecursiveHeaders('./src');
        
        $src = file_get_contents('./src/includes.h');
        
        $splitter = '/* GENERATE */';
        
        $src = explode($splitter, $src);
        
        if(count($src) != 3)
        {
            die("More than two splitters found!\n");
        }
        
        $includes = "\n";
        foreach($files as $file)
        {
            $includes .= '#include "' . str_replace('./src/', './', $file) . '"' . "\n";
        }
        $src[1] = $includes;
        
        $src = implode($splitter, $src);
        
        file_put_contents('./src/includes.h', $src);
    }
    
    default:
    {
        die("Invalid parameter!\n");
    }
}

?>