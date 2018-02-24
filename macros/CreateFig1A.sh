#!/bin/sh

root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-2.0,0.0,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",0.0,2.0,true,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root data_fig1A.root
