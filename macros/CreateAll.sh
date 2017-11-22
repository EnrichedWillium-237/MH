#!/bin/sh
#
# calculate integrated vn over a given pT and eta range
# pT-dependence
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-0.8,0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-0.8,0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB3","useLoose",-0.8,0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useLoose",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB2","useLoose",-0.8,0.8,true)'
#
# eta-dependence
#
root -l -q -b 'GetVNIntEta.C+("N1MCm22SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm18SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm14SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm10SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm06SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm02SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp22SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp18SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp14SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp10SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp06SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp02SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N112ASUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N2SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N3SUB3","useTight",-0.8,0.8,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N112ASUB2","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB2","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB2","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N2SUB2","useTight",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N3SUB2","useTight",-0.8,0.8,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N1MCm22SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm18SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm14SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm10SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm06SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCm02SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp22SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp18SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp14SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp10SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp06SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1MCp02SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N112ASUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N2SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N3SUB3","useLoose",-0.8,0.8,0.3,3.0,false)'
#
root -l -q -b 'GetVNIntEta.C+("N112ASUB2","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N123ASUB2","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N1SUB2","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N2SUB2","useLoose",-0.8,0.8,0.3,3.0,false)'
root -l -q -b 'GetVNIntEta.C+("N3SUB2","useLoose",-0.8,0.8,0.3,3.0,false)'
#
cd results/results_useTight_-0.8_0.8/
rm VNInt_useTight.root
hadd VNInt_useTight.root N1*.root N2*.root N3*.root
rm N1*.root N2*.root N3*.root
#
cd ../results_useLoose_-0.8_0.8/
rm VNInt_useLoose.root
hadd VNInt_useLoose.root N1*.root N2*.root N3*.root
rm N1*.root N2*.root N3*.root
#
rm *_C.so
rm *.d
rm *.pcm
rm *~
rm \#*\#
