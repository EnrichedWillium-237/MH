#!/bin/sh

root -l -b -q 'GetVN.C+("../MH.root","N1HFfSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFm1fSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1HFp1fSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root data_HFtest.root
