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

function factoryGen()
{
    $main = file_get_contents('./src/main.c');
    
    $splitter = '/* FACTORIES */';
    
    $main = explode($splitter, $main);
    
    if(count($main) != 3)
    {
        die("More than two splitters found!\n");
    }
    
    $main[1] = '';
    
    $factoryFiles = scandir('./src/ECS/Entities/');
    $factories = [];
    $count = 0;
    foreach($factoryFiles as $factoryFile)
    {
        if(in_array($factoryFile, [ '.', '..', ]))
        {
            continue;
        }
        
        if(
            $factoryFile[strlen($factoryFile) - 1] != 'c'
            ||
            $factoryFile[strlen($factoryFile) - 2] != '.'
        )
        {
            continue;
        }
        
        $factoryName = explode('Factory.', $factoryFile);
        $factoryName = array_shift($factoryName);
        
        $factories[] = 'factory(' . $factoryName . ')';
        
        $count++;
    }
    
    $main[1] =
        "\n    factories(\n        $count,\n        "
        .
        implode(",\n        ", $factories)
        .
        "\n    );\n    "
    ;
    
    file_put_contents('./src/main.c', implode($splitter, $main));
}

function includesGen()
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
        if($file == './src/includes.h')
        {
            continue;
        }
        
        $includes .= '#include "' . str_replace('./src/', './', $file) . '"' . "\n";
    }
    $src[1] = $includes;
    
    $src = implode($splitter, $src);
    
    file_put_contents('./src/includes.h', $src);
}

// Work based off of the command
switch($cmd)
{
    case 'shaders':
    {
        echo exec('`pwd`/shaders.sh') . "\n";
    } break;
    
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
        
        factoryGen();
    } break;
    
    case 'factory-gen':
    {
        factoryGen();
    } break;
    
    case 'system':
    {
        if(empty($argv))
        {
            die("Factory: no name!\n");
        }
        
        $name = array_shift($argv);
        
        $components = $argv;
        
        $componentsDec = [];
        $componentsSet = [ 'i', ];
        $includes = [
            'ste' => [],
            'local' => [],
        ];
        foreach($components as $key => $component)
        {
            // Create a list of component includes
            if(file_exists('./src/ECS/Components/' . $component . '.h'))
            {
                $includes['local'][] = '#include "../Components/' . $component . '.h"';
            }
            else
            {
                $includes['ste'][] = '#include <STE/ECS/Components/' . $component . '.h>';
            }
            
            // Come up with a variable name & add it to the list of declarations in the system
            $varName = '';
            $j = 0;
            do {
                $j++;
                
                $varName = strtolower(substr($component, 0, $j));
                
                if($j == strlen($component))
                {
                    echo "WARNING: Manually adjust variable names!\n";
                    
                    break;
                }
            }
            while(in_array($varName, $componentsSet));
            
            $componentsSet[] = $varName;
            
            $componentsDec[] = $component . '* ' . $varName . ' = ecs_column(it, ' . $component . ', ' . ($key + 1) . ');';
        }
        $componentsDec = implode("\n    ", $componentsDec);
        
        $cfile = file_get_contents('./meta/template__system.c');
        $cfile = str_replace('/* SYSTEM NAME */', $name, $cfile);
        $cfile = str_replace('/* COMPONENT DECLARATIONS */', $componentsDec, $cfile);
        $cfile = str_replace('/* STE COMPONENT INCLUDES */', implode("\n", $includes['ste']), $cfile);
        $cfile = str_replace('/* COMPONENT INCLUDES */', implode("\n", $includes['local']), $cfile);
        file_put_contents('./src/ECS/Systems/' . $name . 'System.c', $cfile);
        
        $cfile = file_get_contents('./meta/template__system.h');
        $cfile = str_replace('/* SYSTEM NAME */', $name, $cfile);
        file_put_contents('./src/ECS/Systems/' . $name . 'System.h', $cfile);
    }
    
    case 'assets':
    {
        include 'assets.php';
    } break;
    
    case 'ecs-dec':
    {
        include 'ecs_declarations.php';
    } break;
    
    case 'includes':
    {
        includesGen();
    } break;
    
    default:
    {
        die("Invalid parameter!\n");
    }
}

?>