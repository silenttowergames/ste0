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
