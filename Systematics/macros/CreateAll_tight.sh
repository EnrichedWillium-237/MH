#!/bin/sh

root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB2",-2.0,0.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB3",-2.0,0.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB2",0.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB3",0.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB2",-2.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -q -b 'GetVN.C+("../MH_tight.root","N1SUB3",-2.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -q -b 'GetVN.C+("../MH_tight.root","N1MCm22SUB2",0.4,2.4,false,-1,3,-0.05,0.05,-0.1,0.03)'
root -l -q -b 'GetVN.C+("../MH_tight.root","N1MCp22SUB2",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.1,0.03)'

root -l -q -b 'GetVN.C+("../MH_tight.root","N1MCm22SUB3",0.4,2.4,false,-1,3,-0.05,0.05,-0.1,0.03)'
root -l -q -b 'GetVN.C+("../MH_tight.root","N1MCp22SUB3",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.1,0.03)'
