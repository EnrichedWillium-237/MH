#!/bin/sh

root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1MCm22SUB2",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1MCp22SUB2",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1MCm22SUB3",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1MCp22SUB3",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1SUB2",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N1SUB3",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N112SUB2",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N112SUB3",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N2SUB2",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../PbPb_AMPT.root","N2SUB3",-1.6,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
