#!/bin/bash

START=`date +%s%N`

function doFile {
    objf=$1'.'$COMPILER'.o'
    
    if [ "$1" -nt "$objf" ]; then
        echo "Compiling $objf..."
        $COMPILER -g -c $1 -o $objf ${INCS[*]} &
        PIDS+=$!' '
    fi
    
    OBJS+=($objf)
}

function doDir {
    local DIR=$1'/*'
    
    for filename in $DIR; do
        if [[ $filename == "./src/main.c" ]]; then
            continue
        fi
        
        if [ -d $filename ]; then
            doDir $filename OBJS
            
            continue
        fi
        
        if [[ $filename == *.c ]]; then
            doFile $filename
        fi
    done
}

PIDS=()
OBJS=()
INCS=(
    'stonetowerengine/src'
    'flecs-master/include'
    'FNA3D-master/include'
    'FNA3D-master/MojoShader'
    'json-c-master'
    'lua-5.4.0/include'
    'soloud-custom/include'
)
LIBS=(
    'flecs-master'
    'FNA3D-master'
    'json-c-master'
    'lua-5.4.0'
)
LFLAGS=(
    'flecs'
    'FNA3D'
    'json-c'
    'lua54'
    'SDL2'
    'm' # math.h
)
DIR=`pwd`

COMPILER='gcc'
if [ $1 ]; then
    COMPILER=$1
fi

PLATFORM='64'
if [ $2 ]; then
    PLATFORM=$2
fi

COMPILERPP='g++'
if [ $3 ]; then
    COMPILERPP=$3
fi

for i in $(seq 1 ${#INCS[*]})
do
    INCS[$i - 1]='-I/C/libs/'$COMPILER'/'$PLATFORM'/'${INCS[$i - 1]}
done

for i in $(seq 1 ${#LIBS[*]})
do
    LIBS[$i - 1]='-L/C/libs/'$COMPILER'/'$PLATFORM'/'${LIBS[$i - 1]}
done

for i in $(seq 1 ${#LFLAGS[*]})
do
    LFLAGS[$i - 1]='-l'${LFLAGS[$i - 1]}
done

doDir ./src
doFile ./src/main.c

for pid in ${PIDS[*]}; do
    wait $pid
done

if test -f ./bin/linux${PLATFORM}/${COMPILER}/main; then
    rm ./bin/linux${PLATFORM}/${COMPILER}/main
fi

echo Final compilation...

$COMPILERPP -m${PLATFORM} -pthread -g ${OBJS[*]} /C/libs/gcc/64/stonetowerengine/StoneTower.o /C/libs/gcc/64/soloud-custom/built/*.o `sdl2-config --libs` ${INCS[*]} ${LIBS[*]} ${LFLAGS[*]} -Wl,-rpath=\$ORIGIN/libs -o ./bin/linux${PLATFORM}/${COMPILER}/main

let END=`date +%s%N`-$START
let ENDMS=$END/1000000

echo That took ${ENDMS}ms, or ${END} nanoseconds
