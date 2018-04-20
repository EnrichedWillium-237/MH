#!/bin/sh

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFcSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFdSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFeSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFfSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB2",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFcSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFdSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFeSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFfSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB3",-2.0,2.0,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB2",-1.6,-1.2,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB2",1.2,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB3",-1.6,-1.2,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB3",1.2,1.6,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB2",0.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB2",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB3",0.4,2.4,false,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB3",-2.4,-0.4,false,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFcSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFdSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFeSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFfSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB3",1.2,1.6,true,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFcSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFdSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFeSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFfSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1HFgSUB3",-1.6,-1.2,true,-1,3,-0.05,0.05,-0.02,0.02)'

root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB3",0.4,2.4,true,-1,3,-0.05,0.05,-0.02,0.02)'
root -l -b -q 'GetVN.C+("../MH_tight2.root","N1EVENSUB3",-2.4,-0.4,true,-1,3,-0.05,0.05,-0.02,0.02)'

cp vnPlots.root MH_hists_tight.root
