#!/bin/sh
#
# Created on February 27, 2024
#
# @author: sgoldsmith
#
# Make library source, create c3l.lib, compile apps and create disk images.
#
# Steven P. Goldsmith
# sgjava@gmail.com
#

# Need to explicitly set these
export PATH="${PATH}:${HOME}/z88dk/bin:${HOME}/ctools/bin"
export ZCCCFG="${HOME}/z88dk/lib/config"
eval $(perl -I ~/perl5/lib/perl5/ -Mlocal::lib)

# Project root (assumes starting in scripts dir)
cd ../
# Clean project
make clean
# Compile library source
make -j$(nproc)
# Create c3l.lib
make lib
# Create demo.lib
make demo

# Add app dir
mkdir ./build/app

# Build demo apps
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/baseline.com ./src/app/baseline.c -L./build/lib -lc3l
zcc +cpm -vn -I"$HOME/z88dk/include" -I./include -o ./build/app/ciaapp.com ./src/app/ciademo.c -L./build/lib -lc3l
zcc +cpm -vn -I"$HOME/z88dk/include" -I./include -o ./build/app/rtcapp.com ./src/app/rtcdemo.c -L./build/lib -lc3l
zcc +cpm -vn -I"$HOME/z88dk/include" -I./include -o ./build/app/sidapp.com ./src/app/siddemo.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/convpcm.com ./src/app/convpcm.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/cpmdir.com ./src/app/cpmdir.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/playpcm.com ./src/app/playpcm.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/compile.com ./src/app/compile.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/voice.com ./src/app/voice.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vdcfile.com ./src/app/vdcfile.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vdccon.com ./src/app/vdccon.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/viccon.com ./src/app/viccon.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vdcgraph.com ./src/app/vdcgraph.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vicgraph.com ./src/app/vicgraph.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/dualcon.com ./src/app/dualcon.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vicsplit.com ./src/app/vicsplit.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vicdev.com ./src/app/vicdev.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vdcdev.com ./src/app/vdcdev.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/vicspr.com ./src/app/vicspr.c -L./build/lib -lc3l
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/textperf.com ./src/app/textperf.c -L./build/lib -lc3l -ldemo
zcc +cpm -vn -DAMALLOC -I"$HOME/z88dk/include" -I./include -o ./build/app/observer.com ./src/app/observer.c -L./build/lib -lc3l

# Remove curent demo disk image
rm -f ./disks/demo.d71
# Create new demo disk image
cformat -2 ./disks/demo.d71
# Copy all com files to demo disk
ctools ./disks/demo.d71 p ./build/app/*.com
# Copy resource files to demo disk
ctools ./disks/demo.d71 p ./resources/test.sub
ctools ./disks/demo.d71 p ./resources/default.chr
ctools ./disks/demo.d71 p ./resources/*.spr

# Remove curent playpcm disk image
rm -f ./disks/playpcm.d71
# Create new app disk image
cformat -2 ./disks/playpcm.d71
# Copy resource files to app disk
ctools ./disks/playpcm.d71 p ./resources/*.snd
ctools ./disks/playpcm.d71 p ./resources/*.raw
# Copy com files to playpcm disk
ctools ./disks/playpcm.d71 p ./build/app/convpcm.com
ctools ./disks/playpcm.d71 p ./build/app/playpcm.com
