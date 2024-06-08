#!/bin/sh
# Concatnate sprite files extraxted with action replay 6.
#
# Since fonts are saved off with first two byte as load address we trim that off.
#

# Save current dir
cwd=$(pwd)

cd ../resources/fonts

# Build multicolor font in proper sequence

# Space thru ?
dd if=conflict_in_vietnam_multi.64c bs=1 skip=2 count=256 > mc.chr
# @ thru _
dd if=conflict_in_vietnam_multi.64c bs=1 skip=258 count=256 >> mc.chr
# ` thru DEL
dd if=conflict_in_vietnam_multi.64c bs=1 skip=770 count=256 >> mc.chr

# Copy sprite libraries to resources
cp *.chr ../../resources/.

cd "$cwd"