#!/bin/sh

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB2",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB2",0.0,2.0,false,-1)'

###

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1SUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFcSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFdSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFeSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFfSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",-2.0,0.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1SUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFcSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFdSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFeSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFfSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",0.0,2.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",-1.6,-1.2,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",1.2,1.6,false,-1)'

###

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112BSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112CSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112DSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ESUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112FSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112GSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112CombinedSUB3",-2.0,0.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112BSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112CSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112DSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ESUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112FSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112GSUB3",0.0,2.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112CombinedSUB3",0.0,2.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",-1.6,-1.2,false,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",1.2,1.6,false,-1)'

## repeat but with decorrelation correction

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",-1.6,-1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N1HFgSUB3",1.2,1.6,true,-1)'

###

root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",-1.6,-1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH_AMPT.root","N112ASUB3",1.2,1.6,true,-1)'
