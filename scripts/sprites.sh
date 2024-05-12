#!/bin/sh
# Concatnate sprite files extraxted with action replay 6

# Save current dir
cwd=$(pwd)

cd ../resources

for file in BW1 BW2 BW3 BW4 BW5 BW6 BW7 BW8 BW9 BW10 BW11 BW12; do
    dd if="$file" bs=1 skip=2 >> burwor.spr
done

cd "$cwd"

# Populate disk image with sprite file.
ctools ../disks/demo.d71 p ../resources/burwor.spr
