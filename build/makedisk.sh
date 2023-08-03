#!/bin/sh
# Run compile job
dosbox
# Remove existing disk images
rm -f ~/eclipse-workspace/c3l/disks/demo.d71
rm -f ~/eclipse-workspace/c3l/disks/lib.d71
# Build D71 disk image for COM files
cformat -2 ~/eclipse-workspace/c3l/disks/demo.d71
# Populate disk image with demo files.
ctools ~/eclipse-workspace/c3l/disks/demo.d71 p ~/myz80/tmp/*.COM
ctools ~/eclipse-workspace/c3l/disks/demo.d71 p ~/myz80/tmp/*.RAW
# Build D71 disk image for LIB files
cformat -2 ~/eclipse-workspace/c3l/disks/lib.d71
# Populate disk image with LIB files.
ctools ~/eclipse-workspace/c3l/disks/lib.d71 p ~/myz80/tmp/*.LIB
