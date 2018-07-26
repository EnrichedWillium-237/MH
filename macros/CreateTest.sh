#!/bin/sh
root -l -q -b 'GetVN.C+("../MH.root","N1HFcSUB3",0.8,1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH_loose.root","N1HFcSUB3",0.8,1.2,true,-1)'
root -l -q -b 'GetVN.C+("../MH_tight2.root","N1HFcSUB3",0.8,1.2,true,-1)'
