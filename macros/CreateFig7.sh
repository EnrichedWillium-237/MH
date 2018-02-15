#!/bin/sh

root -l -b -q 'GetVN.C+("../MH.root","N1MCm22SUB2",0.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1MCp22SUB2",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH.root","N1MCm22SUB3",0.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH.root","N1MCp22SUB3",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.02,0.02)'

mv MH_hists.root data_fig7.root
