#!/bin/sh
# Run compile job
dosbox
# Remove existing disk image
rm -f ~/eclipse-workspace/c3l/disks/c3l.d71
# Build D71 disk image
cformat -2 ~/eclipse-workspace/c3l/disks/c3l.d71
# Populate disk image with COM files.
ctools ~/eclipse-workspace/c3l/disks/c3l.d71 p ~/myz80/tmp/*.COM

