#!/bin/sh
# Download and convert phonemes to 8 bit snd 8000 Hz

# Save current dir
cwd=$(pwd)

# Temp dir for downloads, etc.
tmpdir="$HOME/temp"

# Remove temp dir
rm -rf "$tmpdir"

mkdir "$tmpdir"
cd "$tmpdir"

# See https://github.com/radiohound/TeensyTalk
url="https://github.com/radiohound/TeensyTalk/raw/main/phonemes_v3.zip"

# Download zip file
wget -q --directory-prefix=$tmpdir "$url"

# Unzip files
unzip phonemes_v3.zip

# Clean up to make 39 ARPAbet phonemes
rm -f V-old.wav 
rm -f AX.wav
rm -f DX.wav
mv _H.wav HH.wav
rm -f IX.wav
rm -f LX.wav
mv J.wav JH.wav
mv  NX.wav NG.wav
rm -f OH.wav
rm -f RX.wav
rm -f UL.wav
rm -f UM.wav
rm -f UN.wav
rm -f UX.wav
rm -f WH.wav
rm -f YX.wav

# Convert 16 bit 22050 Hz wav files to 4 bit 8000 Hz snd (raw PCM) files.
for filename in *.wav; do
    [ -e "$filename" ] || continue
    name=$(basename "$filename" .wav)
    ffmpeg -hide_banner -loglevel error -i "$filename" -f u8 -ac 1 -ar 8000 -acodec pcm_u8 "$name.SND"
    # Get snd file size
    filesize=$(stat --format=%s "$name.SND")
    # Calculate 4 bit raw file size   
    echo "$name.RAW $((filesize/2))\r" >> fileinfo.txt    
done

# Add script to erase all snd files once converted
echo "era *.SND\r" >> convert.sub
echo "<Y" >> convert.sub

# Project root (assumes starting in scripts dir)
cd "$cwd/../"

# Remove existing disk image
rm -f ./disks/talk.d71

# Build D71 disk image for COM files
cformat -2 ./disks/talk.d71

# Populate disk image with sound files.
ctools ./disks/talk.d71 p "$tmpdir/"*.SND
ctools ./disks/talk.d71 p ./build/app/convpcm.com
ctools ./disks/talk.d71 p ./build/app/playpcm.com
ctools ./disks/talk.d71 p ./build/app/compile.com
ctools ./disks/talk.d71 p ./build/app/voice.com
ctools ./disks/talk.d71 p "$tmpdir/fileinfo.txt"
# Copy resource files to app disk
ctools ./disks/talk.d71 p ./resources/*.pho
