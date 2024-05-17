#!/bin/sh
# Concatnate sprite files extraxted with action replay 6.
#
# Since sprites are save off with first two byte as load address we trim that off.
#

# Save current dir
cwd=$(pwd)

cd ../resources/sprites

# Burwor library
rm -f burwor.spr
for file in bw12.prg bw11.prg bw10.prg bw09.prg bw08.prg bw07.prg bw06.prg bw05.prg bw04.prg bw03.prg bw02.prg bw01.prg; do
 	dd if="$file" bs=1 skip=2 >> burwor.spr
done

# Garwor library
rm -f garwor.spr
for file in gw12.prg gw11.prg gw10.prg gw09.prg gw08.prg gw07.prg gw06.prg gw05.prg gw04.prg gw03.prg gw02.prg gw01.prg; do
    dd if="$file" bs=1 skip=2 >> garwor.spr
done

# Thorwor library
rm -f thorwor.spr
for file in tw12.prg tw11.prg tw10.prg tw09.prg tw08.prg tw07.prg tw06.prg tw05.prg tw04.prg tw03.prg tw02.prg tw01.prg; do
    dd if="$file" bs=1 skip=2 >> thorwor.spr
done

# Copy sprite libraries to resources
cp *.spr ../../resources/.

cd "$cwd"