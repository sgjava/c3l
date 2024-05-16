#!/bin/sh
# Concatnate sprite files extraxted with action replay 6

# Save current dir
cwd=$(pwd)

cd ../resources/sprites

for file in bw01.prg bw02.prg bw03.prg bw04.prg bw05.prg bw06.prg bw07.prg bw08.prg bw09.prg bw10.prg bw11.prg bw12.prg; do
    dd if="$file" bs=1 skip=2 >> burwor.spr
done

cd "$cwd"

# Populate disk image with sprite file.
ctools ../disks/demo.d71 p ../resources/burwor.spr
