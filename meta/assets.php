<?php

// FIXME: Commas within quotation marks are broken

function getVec2($v)
{
    $v = explode('x', $v);
    
    return [
        'X' => $v[0],
        'Y' => $v[1],
    ];
}

function getVec2Obj($v, $type)
{
    return '(' . $type . '){ ' . $v['X'] . ', ' . $v['Y'] . ', }';
}

function getValType($val)
{
    $patterns = [
        'bool' => '^(true|false)$',
        'float' => '^([0-9]+\.[0-9]+)$',
        'int' => '^([0-9]+)$',
        'string' => '^"([^\n]+)"$',
    ];
    
    foreach($patterns as $type => $pattern)
    {
        if(preg_match('/' . $pattern . '/', $val, $matches))
        {
            return $type;
        }
    }
}

function getLine__fonts($val)
{
    return [ 'title' => $val, ];
}

function getLine__maps($val)
{
    return [ 'title' => $val, ];
}

function getLine__scripts($val)
{
    return [ 'title' => $val, ];
}

function getLine__shaders($val)
{
    $val = explode(',', $val);
    
    if(count($val) == 1)
    {
        return [ 'title' => $val[0], 'callable' => 'NULL', ];
    }
    
    return [ 'title' => $val[0], 'callable' => $val[1], ];
}

function getLine__sounds($val)
{
    $val = explode(',', $val);
    
    if(!in_array(count($val), [ 4, 5, ]))
    {
        die('Sound line has too may components: `' . implode(',', $val) . '`');
    }
    
    $ret = [
        'type' => array_shift($val),
        'name' => array_shift($val),
        'playType' => array_pop($val),
        'soundType' => array_pop($val),
    ];
    
    if(count($val))
    {
        $ret['soundData'] = array_shift($val);
    }
    
    return $ret;
}

function writeSound($val)
{
    $val['playType'] = 'SoundCategory_' . $val['playType'];
    $val['soundType'] = 'Play_' . $val['soundType'];
    
    return 'Sound_create_' . array_shift($val) . '(' . array_shift($val) . ', ' . implode(', ', array_reverse($val)) . ')';
}

function getLine__textures($val)
{
    $val = explode(',', $val);
    
    $title = $val[0];
    
    if(count($val) == 1)
    {
        $size = getVec2($title);
        
        return [
            'title' => $title,
            'width' => $size['X'],
            'height' => $size['Y'],
            'paddingWidth' => 0,
            'paddingHeight' => 0,
            'borderWidth' => 0,
            'borderHeight' => 0,
        ];
    }
    
    $size = getVec2($val[1]);
    $padding = getVec2($val[2]);
    $border = getVec2($val[3]);
    
    return [
        'title' => $title,
        'width' => $size['X'],
        'height' => $size['Y'],
        'paddingWidth' => $padding['X'],
        'paddingHeight' => $padding['Y'],
        'borderWidth' => $border['X'],
        'borderHeight' => $border['Y'],
    ];
}

function getLine__renderTargets($val)
{
    //resolution,destResolution,position,upscale,hexColor,alpha[,shaders...]
    
    $val = explode(',', $val);
    
    $resolution = getVec2Obj(getVec2(array_shift($val)), 'int2d');
    $size = getVec2Obj(getVec2(array_shift($val)), 'int2d');
    $position = getVec2Obj(getVec2(array_shift($val)), 'int2d');
    $upscale = array_shift($val);
    $colorHex = array_shift($val);
    $alpha = array_shift($val);
    
    $colorHex = explode('0x', $colorHex);
    $colorHex = array_pop($colorHex);
    $colorHex = [
        hexdec(substr($colorHex, 0, 2)),
        hexdec(substr($colorHex, 2, 2)),
        hexdec(substr($colorHex, 4, 2)),
        $alpha,
    ];
    
    for($i = 0; $i < 3; $i++)
    {
        if($colorHex[$i] == 0)
        {
            continue;
        }
        
        $colorHex[$i] = 1.0 / (255 / $colorHex[$i]);
    }
    
    $color = '(FNA3D_Vec4){ ' . implode(', ', $colorHex) . ', }';
    
    $shaders = [];
    while($shader = array_shift($val))
    {
        $shaders[] = $shader;
    }
    
    return [
        'resolution' => $resolution,
        'size' => $size,
        'position' => $position,
        'upscale' => $upscale,
        'color' => $color,
        'shaders' => $shaders,
    ];
}

function getLine__consoleCommands($val)
{
    $val = explode(',', $val);
    
    return [
        'title' => $val[0],
        'callable' => $val[1],
    ];
}

// Setup

define('SECTION_NONE', 0);
define('SECTION_GAMEDATA', 1);
define('SECTION_ASSETS', 2);

$section = SECTION_NONE;
$header = NULL;

$gamedataCount = 0;
$gamedata = [];
$assets = [];

// Load app

$appFile = './app.ini';

if(!file_exists($appFile))
{
    die("No app.ini found!\n");
}

$app = file_get_contents($appFile);

// Parse app

// Remove blank lines
// This replaces two or more linebreaks with a single linebreak
$app = preg_replace('/(\n){2,}/', "\n", $app);

// Split it into lines
$app = explode("\n", $app);

// If the last line is blank, get rid of it
if(empty($app[count($app) - 1]))
{
    array_pop($app);
}

// Go line-by-line to parse
foreach($app as $line)
{
    // If we're changing sections
    
    if($line[0] === '#')
    {
        $piece = substr($line, 2);
        
        switch($piece)
        {
            case 'gamedata':
            {
                $section = SECTION_GAMEDATA;
            } break;
            
            case 'assets':
            {
                $section = SECTION_ASSETS;
            } break;
        }
        
        continue;
    }
    
    // Get header, if this is a header line
    
    if(preg_match('/\[([a-zA-Z]+)\]/', $line, $matches))
    {
        $header = $matches[1];
        
        continue;
    }
    
    // If not, parse by section
    
    switch($section)
    {
        case SECTION_GAMEDATA:
        {
            $p = explode('=', $line);
            
            $varDec = array_shift($p);
            
            $val = implode('=', $p);
            
            $var = explode(':', $varDec);
            
            $type = NULL;
            
            if(count($var) > 2)
            {
                die($varDec . ' has too many :' . "\n");
            }
            
            if(count($var) == 2)
            {
                $type = $var[1];
            }
            else
            {
                $type = getValType($val);
            }
            
            $var = $var[0];
            
            $gamedata[$header][] = [
                'name' => $var,
                'type' => $type,
                'value' => $val,
            ];
            
            $gamedataCount++;
        } break;
        
        case SECTION_ASSETS:
        {
            if(empty($assets[$header]))
            {
                $assets[$header] = [];
            }
            
            $assets[$header][] = call_user_func_array('getLine__' . $header, [ $line, ]);
        } break;
    }
}

// Save the data

// Unpack the file
$file = './src/main.c';
$div = '/* RESOURCES */';
$data = file_get_contents($file);
$data = explode($div, $data);

if(count($data) != 3)
{
    die("WOOPS\n");
}

$data[1] = "\n    \n    ";

// Build the asset calls
// Textures
$data[1] .= "textures(\n        " . count($assets['textures']) . ",\n        ";
foreach($assets['textures'] as $key => $texture)
{
    $texture['title'] = '"' . $texture['title'] . '"';
    
    $data[1] .= 'Texture_Create(&app, ' . implode(', ', $texture) . ')';
    
    if($key >= count($assets['textures']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Maps
$data[1] .= "maps(\n        " . count($assets['maps']) . ",\n        ";
foreach($assets['maps'] as $key => $map)
{
    $data[1] .= 'TiledJSON_Load(&app, "' . $map['title'] . '")';
    
    if($key >= count($assets['maps']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Shaders
$data[1] .= "shaders(\n        " . count($assets['shaders']) . ",\n        ";
foreach($assets['shaders'] as $key => $shader)
{
    $data[1] .= 'Shader_Create(&app, "' . $shader['title'] . '", ' . $shader['callable'] . ')';
    
    if($key >= count($assets['shaders']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Scripts
$data[1] .= "scripts(\n        " . count($assets['scripts']) . ",\n        ";
foreach($assets['scripts'] as $key => $script)
{
    $data[1] .= 'LuaScript_Load(&app, "' . $script['title'] . '")';
    
    if($key >= count($assets['scripts']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Fonts
$data[1] .= "fonts(\n        " . count($assets['fonts']) . ",\n        ";
foreach($assets['fonts'] as $key => $font)
{
    $data[1] .= 'Font_Create(&app, "' . $font['title'] . '")';
    
    if($key >= count($assets['fonts']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Sounds
$data[1] .= "sounds(\n        " . count($assets['sounds']) . ",\n        ";
foreach($assets['sounds'] as $key => $sound)
{
    $data[1] .= writeSound($sound);
    
    if($key >= count($assets['sounds']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// Render Targets
$data[1] .= "renderTargets(\n        " . count($assets['renderTargets']) . ",\n        ";
foreach($assets['renderTargets'] as $key => $renderTarget)
{
    $shaders = $renderTarget['shaders'];
    
    unset($renderTarget['shaders']);
    
    $data[1] .= 'RenderTarget_Create(&app, ' . implode(', ', $renderTarget) . ')';
    
    if($key >= count($assets['renderTargets']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";
// GameData
$data[1] .= "gameDataInit(\n        " . $gamedataCount . ",\n        ";
foreach($gamedata as $key => $list)
{
    static $i = 0;
    foreach($list as $val)
    {
        $data[1] .= 'gdAttr("' . $key . '", "' . $val['name'] . '", ' . $val['value'] . ', ' . ucfirst($val['type']) . ')';
        
        if($i >= $gamedataCount - 1)
        {
            $data[1] .= "\n";
        }
        else
        {
            $data[1] .= ",\n        ";
        }
        
        $i++;
    }
}
$data[1] .= "    );\n    \n    ";
// Console Commands
$data[1] .= "ConsoleCommand_AddAll(\n        &app,\n        " . count($assets['consoleCommands']) . ",\n        ";
foreach($assets['consoleCommands'] as $key => $cmd)
{
    $data[1] .= 'ConsoleCommand_Create("' . $cmd['title'] . '", ' . $cmd['callable'] . ')';
    
    if($key >= count($assets['consoleCommands']) - 1)
    {
        $data[1] .= "\n";
    }
    else
    {
        $data[1] .= ",\n        ";
    }
}
$data[1] .= "    );\n    \n    ";

// Put the file back
$data = implode($div, $data);
file_put_contents($file, $data);

?>