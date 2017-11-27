#!/bin/sh
#
# calculate integrated vn over a given pT and eta range
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
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-2.4,2.4,true)'
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
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB3","useLoose",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useLoose",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N3SUB2","useLoose",-2.4,2.4,true)'
#
cd results/results_useTight_-2.4_2.4/
rm VNInt_useTight.root
hadd VNInt_useTight.root N1*.root N2*.root N3*.root
rm N1*.root N2*.root N3*.root
#
cd ../results_useLoose_-2.4_2.4/
rm VNInt_useLoose.root
hadd VNInt_useLoose.root N1*.root N2*.root N3*.root
rm N1*.root N2*.root N3*.root
#
cd ../../
rm *_C.so
rm *.d
rm *.pcm
rm *~
rm \#*\#
