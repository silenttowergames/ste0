$files = Get-ChildItem -Recurse src/*.c

foreach($file in $files)
{
    $fileO = $file.ToString() + ".o"
    
    gcc -g -c $file -o $fileO -IC:\C\libs\gcc\64\stonetowerengine\src -IC:\C\libs\gcc\64\flecs-master\include -IC:\C\libs\gcc\64\FNA3D-master\include -IC:\C\libs\gcc\64\FNA3D-master\MojoShader -IC:\C\libs\gcc\64\json-c-master -IC:\C\libs\gcc\64\lua-5.4.0\include -IC:\C\libs\gcc\64\soloud-custom\include -IC:\C\libs\gcc\64\SDL2-2.0.14\x86_64-w64-mingw32\include
}

$files = Get-ChildItem -Recurse src/*.o
$filesSoloud = Get-ChildItem -Recurse C:\C\libs\gcc\64\soloud-custom\src\*.o

g++ -pthread -g $files C:\C\libs\gcc\64\stonetowerengine\StoneTower.o $filesSoloud -IC:\C\libs\gcc\64\stonetowerengine\src -IC:\C\libs\gcc\64\flecs-master\include -IC:\C\libs\gcc\64\FNA3D-master\include -IC:\C\libs\gcc\64\FNA3D-master\MojoShader -IC:\C\libs\gcc\64\json-c-master -IC:\C\libs\gcc\64\lua-5.4.0\include -IC:\C\libs\gcc\64\soloud-custom\include -IC:\C\libs\gcc\64\SDL2-2.0.14\x86_64-w64-mingw32\include -LC:\C\libs\gcc\64\flecs-master -LC:\C\libs\gcc\64\FNA3D-master -LC:\C\libs\gcc\64\json-c-master -LC:\C\libs\gcc\64\lua-5.4.0 -LC:\C\libs\gcc\64\SDL2-2.0.14\x86_64-w64-mingw32\lib -lflecs -lSDL2 -lFNA3D -ljson-c -llua54 -lm -mwindows -o ./bin/win64/gcc/main
