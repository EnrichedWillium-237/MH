#!/bin/sh

#root -l -b -q 'GetVN.C+("../MH.root","N1HFcSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
#root -l -b -q 'GetVN.C+("../MH.root","N1HFdSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
#root -l -b -q 'GetVN.C+("../MH.root","N1HFeSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
#root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH.root","N1HFcSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFdSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFeSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root data_fig3.root
