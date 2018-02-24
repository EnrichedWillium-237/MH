#!/bin/sh

# corrected for decorrelation
# root -l -b -q 'GetVN.C+("../MH.root","N1HFcSUB2",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
# root -l -b -q 'GetVN.C+("../MH.root","N1HFdSUB2",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
# root -l -b -q 'GetVN.C+("../MH.root","N1HFeSUB2",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
# root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB2",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'

# root -l -b -q 'GetVN.C+("../MH.root","N1HFcSUB3",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
# root -l -b -q 'GetVN.C+("../MH.root","N1HFdSUB3",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
# root -l -b -q 'GetVN.C+("../MH.root","N1HFeSUB3",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-2.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH.root","N1EVENSUB3",0.4,2.4,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1EVENSUB3",-2.4,-0.4,true,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root MH_hists_master.root
