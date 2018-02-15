#!/bin/sh

root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB2",-2.0,0.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB2",0.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-2.0,0.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",0.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root data_fig1.root
