#!/bin/sh

mv vnPlots.root vnPlots_previous_run.root

source ./CreateAll_default.sh
source ./CreateAll_epos.sh
source ./CreateAll_loose.sh
source ./CreateAll_narrow.sh
source ./CreateAll_tight.sh
source ./CreateAll_wide.sh
source ./CreateAll_ampt.sh
