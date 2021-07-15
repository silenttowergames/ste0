START=`date +%s%N`

PIDS=()

function doShader {
    filename=$1
    
    if wine /C/shader/efb/efb.exe /I ./assets/shaders/ $filename $filename'b' > shader_output.txt 2>&1 ; then
        echo YES: $filename
    else
        echo NO: $filename
    fi
}

rm -f shader_output.txt

for filename in ./assets/shaders/*.fx; do
    if [ "$filename" -nt "$filename""b" ]; then
        doShader $filename &
        
        PIDS+=$!' '
    fi
done

for pid in ${PIDS[*]}; do
    wait $pid
done

let END=`date +%s%N`-$START
let ENDMS=$END/1000000
let ENDS=$ENDMS/1000

echo ${ENDS}s / ${ENDMS}ms / ${END}ns
