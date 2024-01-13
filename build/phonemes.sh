#!/bin/sh
# Download and convert phonemes to 8 bit snd 8000 Hz

# Temp dir for downloads, etc.
tmpdir="$HOME/temp"

mkdir "$tmpdir"
cd "$tmpdir"

# See https://github.com/radiohound/TeensyTalk
url="https://github.com/radiohound/TeensyTalk/raw/main/phonemes_v3.zip"

# Download zip file
wget -q --directory-prefix=$tmpdir "$url"

# Unzip files
unzip phonemes_v3.zip

# Remove old version
rm -f V-old.wav 

# Convert 16 bit 22050 Hz wav files to 8 bit 8000 Hz snd (raw PCM) files.
for filename in *.wav; do
    [ -e "$filename" ] || continue
    name=$(basename "$filename" .wav)
    ffmpeg -hide_banner -loglevel error -i "$filename" -f u8 -ac 1 -ar 8000 -acodec pcm_u8 "$name.SND"
    # Create submit file that converts 8 bit snd file to 1 bit raw file 
    echo "convpcm $name.SND $name.RAW 1\r" >> convert.sub
    # Get snd file size
    filesize=$(stat --format=%s "$name.SND")
    # Calculate 1 bit raw file size   
    echo "$name.RAW,$((filesize/8))\r" >> fileinfo.txt    
done

# Add script to erase all snd files once converted
echo "b:\r" >> convert.sub
echo "era b:*.SND\r" >> convert.sub
echo "<Y" >> convert.sub

# Remove existing disk image
rm -f ~/eclipse-workspace/c3l/disks/talk.d71

# Build D71 disk image for COM files
cformat -2 ~/eclipse-workspace/c3l/disks/talk.d71

# Populate disk image with sound files.
ctools ~/eclipse-workspace/c3l/disks/talk.d71 p *.SND
ctools ~/eclipse-workspace/c3l/disks/talk.d71 p ~/myz80/tmp/PLAYPCM.COM
ctools ~/eclipse-workspace/c3l/disks/talk.d71 p ~/myz80/tmp/CONVPCM.COM
ctools ~/eclipse-workspace/c3l/disks/talk.d71 p convert.sub
ctools ~/eclipse-workspace/c3l/disks/talk.d71 p fileinfo.txt

# Remove temp dir
rm -rf "$tmpdir"
