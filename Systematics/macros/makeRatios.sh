#!/bin/sh

root -l -b -q 'figRatiosTight.C+'
root -l -b -q 'figRatiosWide.C+'
root -l -b -q 'figRatiosNarrow.C+'

rm *_C.so *.d *.pcm *~ \#*\#
