#!/bin/sh
#
# calculate integrated vn over a given pT and eta range
# pT-dependence
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-2.4,-2.0,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-2.4,-2.0,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-2.4,-2.0,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-2.4,-2.0,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-2.0,-1.6,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-2.0,-1.6,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-2.0,-1.6,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-2.0,-1.6,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-1.6,-1.2,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-1.6,-1.2,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-1.6,-1.2,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-1.6,-1.2,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-1.2,-0.8,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-1.2,-0.8,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-1.2,-0.8,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-1.2,-0.8,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-0.8,-0.4,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-0.8,-0.4,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-0.8,-0.4,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-0.8,-0.4,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",-0.4,0.0,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",-0.4,0.0,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",-0.4,0.0,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",-0.4,0.0,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",0.0,0.4,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",0.0,0.4,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",0.0,0.4,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",0.0,0.4,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",0.4,0.8,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",0.4,0.8,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",0.4,0.8,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",0.4,0.8,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",0.8,1.2,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",0.8,1.2,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",0.8,1.2,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",0.8,1.2,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",1.2,1.6,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",1.2,1.6,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",1.2,1.6,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",1.2,1.6,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",1.6,2.0,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",1.6,2.0,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",1.6,2.0,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",1.6,2.0,true)'
#
root -l -q -b 'GetVN.C+("N1SUB3","useTightB",2.0,2.4,true)'
root -l -q -b 'GetVN.C+("N2SUB3","useTightB",2.0,2.4,true)'
root -l -q -b 'GetVN.C+("N1SUB2","useTightB",2.0,2.4,true)'
root -l -q -b 'GetVN.C+("N2SUB2","useTightB",2.0,2.4,true)'
#
#
#
rm *_C.so
rm *.d
rm *.pcm
rm *~
rm \#*\#
