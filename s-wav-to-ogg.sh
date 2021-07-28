cd assets/sounds/
echo Converting $1.wav...
ffmpeg -i $1.wav -acodec libvorbis $1.ogg 2> /dev/null
echo Done
