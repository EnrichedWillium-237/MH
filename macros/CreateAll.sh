#!/bin/sh
#
# pT-dependence
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useLoose",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useLoose",-2.4,2.4,true)'
#
# eta-dependence
#
root -l -q -b 'GetVNIntEta.C+("N1MCm22SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm18SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm14SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm10SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm06SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm02SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp22SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp18SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp14SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp10SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp06SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp02SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N112ASUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB3","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB3","useTight",-2.4,2.4,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N112ASUB2","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB2","useTight",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB2","useTight",-2.4,2.4,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N1MCm22SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm18SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm14SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm10SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm06SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm02SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp22SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp18SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp14SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp10SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp06SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp02SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N112ASUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB3","useLoose",-2.4,2.4,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N112ASUB2","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB2","useLoose",-2.4,2.4,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB2","useLoose",-2.4,2.4,0.3,3.0,false)'
#
cd results/results_useTight_-2.4_2.4/
hadd VNInt_useTight.root N1*.root
rm N1*.root
#
cd ../results_useLoose_-2.4_2.4/
hadd VNInt_useLoose.root N1*.root
rm N1*.root
