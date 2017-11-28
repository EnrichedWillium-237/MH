#!/bin/sh
#
# calculate integrated vn over a given pT and eta range
# pT-dependence
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-2.4,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-2.4,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-2.4,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-2.4,2.4,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-0.8,0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-0.8,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-0.8,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-0.8,0.8,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-2.4,-2.0,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-2.4,-2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-2.4,-2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-2.4,-2.0,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-2.0,-1.6,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-2.0,-1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-2.0,-1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-2.0,-1.6,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-1.6,-1.2,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-1.6,-1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-1.6,-1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-1.6,-1.2,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-1.2,-0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-1.2,-0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-1.2,-0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-1.2,-0.8,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-0.8,-0.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-0.8,-0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-0.8,-0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-0.8,-0.4,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",-0.4,0.0,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",-0.4,0.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",-0.4,0.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",-0.4,0.0,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",0.0,0.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",0.0,0.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",0.0,0.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",0.0,0.4,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",0.4,0.8,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",0.4,0.8,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",0.4,0.8,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",0.4,0.8,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",0.8,1.2,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",0.8,1.2,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",0.8,1.2,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",0.8,1.2,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",1.2,1.6,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",1.2,1.6,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",1.2,1.6,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",1.2,1.6,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",1.6,2.0,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",1.6,2.0,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",1.6,2.0,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",1.6,2.0,true)'
#
#
#
root -l -q -b 'GetVNIntPt.C+("N1MCm22SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm18SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm14SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm10SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm06SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCm02SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp22SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp18SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp14SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp10SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp06SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N1MCp02SUB3","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N112ASUB3","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB3","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB3","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB3","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB3","useTight",2.0,2.4,true)'
#
root -l -q -b 'GetVNIntPt.C+("N112ASUB2","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N123ASUB2","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N1SUB2","useTight",2.0,2.4,true)'
root -l -q -b 'GetVNIntPt.C+("N2SUB2","useTight",2.0,2.4,true)'
# root -l -q -b 'GetVNIntPt.C+("N3SUB2","useTight",2.0,2.4,true)'
#
rm *_C.so
rm *.d
rm *.pcm
rm *~
rm \#*\#
