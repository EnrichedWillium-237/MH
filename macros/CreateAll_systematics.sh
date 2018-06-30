#!/bin/sh

mv 'vnPlots.root' 'vnPlots_tmp.root'

root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",0.0,2.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",-1.6,-1.2,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",1.2,1.6,false,-1)'

###

root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",-2.0,0.0,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",0.0,2.0,false,-1)'

root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",-1.6,-1.2,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",1.2,1.6,false,-1)'

###

root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",-2.4,-0.4,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",0.4,2.4,false,-1)'

root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",-1.6,-1.2,false,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",1.2,1.6,false,-1)'

## repeat but with decorrelation correction

root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",-1.6,-1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1HFgSUB3",1.2,1.6,true,-1)'

###

root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",-1.6,-1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N112ASUB3",1.2,1.6,true,-1)'

###

root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",-1.6,-1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH.root","N1EVENSUB3",1.2,1.6,true,-1)'

mv 'vnPlots.root' 'systPlots.root'
mv 'vnPlots_tmp.root' 'vnPlots.root'
