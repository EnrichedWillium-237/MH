#!/bin/sh

sh CreateMaster.sh
sh CreateNarrow.sh
sh CreateWide.sh
sh CreateTight.sh
sh CreateLoose.sh

cp vnPlots.root data_master.root

rm *_C.so *.d *.pcm *~ \#*\#
