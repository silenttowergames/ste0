DIR=`pwd`
cd /C/libs/gcc/64/stonetowerengine/
./build-linux64-gcc.sh
cd $DIR

function checkDir {
    local DIR=$1'/*'
    
    for filename in $DIR; do
        if [[ $filename == *.o ]]; then
            rm $filename
            
            continue
        fi
        
        if [ -d "$filename" ]; then
            checkDir $filename
        fi
    done
}

checkDir ./src
