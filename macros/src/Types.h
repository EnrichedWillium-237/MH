enum AnalTypes{
         N1SUB2,       N1SUB3,   N1EVENSUB2,  N1EVENSUB3,      N1ASUB2,  //1
        N1ASUB3,      N1BSUB2,      N1BSUB3,      N2SUB2,       N2SUB3,  //2
         N3SUB2,       N3SUB3,       N4SUB2,      N4SUB3,       N5SUB2,  //3
         N5SUB3,       N6SUB2,       N6SUB3,      N7SUB2,       N7SUB3,  //4
       N112SUB2,     N112SUB3,    N112ASUB2,   N112ASUB3,    N112BSUB2,  //5
      N112BSUB3,     N523SUB2,     N523SUB3,   N523ASUB2,    N523ASUB3,  //6
    N1MCm22SUB3,  N1MCm18SUB3,  N1MCm14SUB3, N1MCm10SUB3,  N1MCm06SUB3,  //7
    N1MCm02SUB3,  N1MCp22SUB3,  N1MCp18SUB3, N1MCp14SUB3,  N1MCp10SUB3,  //8
    N1MCp06SUB3,  N1MCp02SUB3,  N1MCm22SUB2, N1MCm18SUB2,  N1MCm14SUB2,  //9
    N1MCm10SUB2,  N1MCm06SUB2,  N1MCm02SUB2, N1MCp22SUB2,  N1MCp18SUB2,  //10
    N1MCp14SUB2,  N1MCp10SUB2,  N1MCp06SUB2, N1MCp02SUB2,      N42SUB2,  //11
	N42SUB3,     N42ASUB2,     N42ASUB3,    N42BSUB3,     N42CSUB3,  //12
	N62SUB2,      N62SUB3,     N62ASUB3,     N63SUB2,      N63SUB3,  //13
       N63ASUB2,     N63ASUB3,     N63BSUB3,    N63CSUB3,         Chi4,  //14
	  Chi4A,      D24SUB2,     D24ASUB2,        Chi5,        Chi5A,  //15
      D2232SUB2,   D2232ASUB2,        Chi62,      Chi62A,      D26SUB2,  //16  
       D26ASUB2,        Chi63,       Chi63A,     D34SUB2,     D34ASUB2,  //17
	   Chi7,        Chi7A,    D2432SUB2,  D2432ASUB2,     N723SUB2,  //18
       N723SUB3,    N723ASUB2,    N723ASUB3, N1HFm1cSUB2,  N1HFm1dSUB2,  //19 
    N1HFm1eSUB2,  N1HFm1fSUB2,  N1HFm1gSUB2, N1HFm1cSUB3,  N1HFm1dSUB3,  //20
    N1HFm1eSUB3,  N1HFm1fSUB3,  N1HFm1gSUB3, N1HFp1cSUB2,  N1HFp1dSUB2,  //21  
    N1HFp1eSUB2,  N1HFp1fSUB2,  N1HFp1gSUB2, N1HFp1cSUB3,  N1HFp1dSUB3,  //22  
    N1HFp1eSUB3,  N1HFp1fSUB3,  N1HFp1gSUB3,   N1HFcSUB2,    N1HFdSUB2,  //23    
      N1HFeSUB2,    N1HFfSUB2,    N1HFgSUB2,   N1HFcSUB3,    N1HFdSUB3,  //24    
      N1HFeSUB3,    N1HFfSUB3,    N1HFgSUB3,   N112CSUB2,    N112CSUB3,  //25
      N112DSUB2,    N112DSUB3,    N112CombinedSUB2,   N112CombinedSUB3,  // 26
	 N112ESUB2,    N112ESUB3,    N112FSUB2,   N112FSUB3,   N112GSUB2,   //27
	 N112GSUB3,    N112HSUB2,    N112HSUB3,N112MCASUB2, N112MCASUB3,     LAST  //28
};

static const string ANALS[250][3] {
//1
    "N1SUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1SUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
"N1EVENSUB2",      "v_{1}^{even}\{#Psi_{1}}",    "2 sub-event with mom. cons. weights",
"N1EVENSUB3",      "v_{1}^{even}\{#Psi_{1}}",                                 "3 sub-event with mom. cons. weights",
   "N1ASUB2",             "v_{1}\{#Psi_{1}}",     "2 sub-event resolution - need to add to N1B",
//2
   "N1ASUB3",  "v_{1}\{#Psi_{1}}", "3 sub-event resolution - HFp1-HFm1-trackp114",
   "N1BSUB2",  "v_{1}\{#Psi_{1}}", "2 sub-event resolution - need to add to N1A",
   "N1BSUB3",  "v_{1}\{#Psi_{1}}", "3 sub-event resolution - HFm1-HFp1-trackm114",
    "N2SUB2",  "v_{2}\{#Psi_{2}}", "2 sub-event resolution",
    "N2SUB3",  "v_{2}\{#Psi_{2}}", "3 sub-event resolution",
//3      
    "N3SUB2",  "v_{3}\{#Psi_{3}}", "2 sub-event resolution",
    "N3SUB3",  "v_{3}\{#Psi_{3}}", "3 sub-event resolution",      
    "N4SUB2",  "v_{4}\{#Psi_{4}}", "2 sub-event resolution",
    "N4SUB3",  "v_{4}\{#Psi_{4}}", "3 sub-event resolution",
    "N5SUB2",  "v_{5}\{#Psi_{5}}", "2 sub-event resolution",
//4      
    "N5SUB3",  "v_{5}\{#Psi_{5}}", "3 sub-event resolution",
    "N6SUB2",  "v_{6}\{#Psi_{6}}", "2 sub-event resolution",      
    "N6SUB3",  "v_{6}\{#Psi_{6}}", "3 sub-event resolution",
    "N7SUB2",  "v_{7}\{#Psi_{7}}", "2 sub-event resolution",
    "N7SUB3",  "v_{7}\{#Psi_{7}}", "3 sub-event resolution",
//5      
  "N112SUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Based on STAR analysis",
  "N112SUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Based on STAR analysis",
  "N112ASUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 2A (-0.8<#eta<0.8)",
  "N112ASUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 1C (-1.6<#eta<-1.2) 2A (-0.8<#eta<0.8)",
  "N112BSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (-5<#eta<-4) 2A (-0.8<<#eta<0.8)",
//6    
  "N112BSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (-5<#eta<-4) 1C (1.2<#eta<1.6) 2A (-0.8<<#eta<0.8)",
   "N523SUB2",  "v_{5}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",
   "N523SUB3",  "v_{5}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",
   "N523ASUB2", "v_{5}\{#Psi_{2A},#Psi_{3B}}",  "A side is HF+",
   "N523ASUB3",  "v_{5}\{#Psi_{2A},#Psi_{3B}}", "A side if HF+",
//7
 "N1MCm22SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm18SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm14SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm10SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm06SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
//8      
 "N1MCm02SUB3",  "v_{1}\{#Psi{1mc}}",  "",
 "N1MCp22SUB3",  "v_{1}\{#Psi{1mc}}",  "",
 "N1MCp18SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp14SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp10SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
//9      
 "N1MCp06SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp02SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm22SUB2",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm18SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm14SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
//10      
 "N1MCm10SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm06SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm02SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp22SUB2",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp18SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
//11      
 "N1MCp14SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp10SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp06SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp02SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
     "N42SUB2", "v_{4}\{#Psi_{2A}^{2}}",  "2 sub-event resolution ",
//12
     "N42SUB3", "v_{4}\{#Psi_{2A}^{2}}",  "3 sub-event resolution ",
    "N42ASUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "2 sub-event resolution; note: resolution from same side ",
    "N42ASUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "3 sub-event resolution; note: resolution from same side ",
    "N42BSUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "5 sub-event resolution; res calc uses symmetric event planes 0.8 to 1.2 ",
    "N42CSUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "5 sub-event resolution; res calc used symmetric event planes 1.6 to 2.0 ",
//13
     "N62SUB2", "v_{6}\{#Psi_{2A}^{3}}",  "2 sub-event resolution ",
     "N62SUB3", "v_{6}\{#Psi_{2A}^{3}}",  "3 sub-event resolution ",
    "N62ASUB3", "v_{6}\{#Psi_{2A}^{2},#Psi_{2B}}",  "3 sub-event, A/B sides not symmetric ",
     "N63SUB2", "v_{6}\{#Psi_{3A}^{2}}",  "2 sub-event resolution ",
     "N63SUB3", "v_{6}\{#Psi_{3A}^{2}}",  "3 sub-event resolution ",
//14
    "N63ASUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "2 sub-event resolution; note: resolution from same side ",
    "N63ASUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "3 sub-event resolution; note: resolution from same side ",
    "N63BSUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "5 sub-event resolution; res calc uses symmetric event planes 0.8 to 1.2 ",
    "N63CSUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "5 sub-event resolution; res calc used symmetric event planes 1.6 to 2.0 ",
        "Chi4",                    "#chi_{4}",  "#chi_{4} based on N42SUB2",
//15
       "Chi4A",                    "#chi_{4}",  "#chi_{4} based on N42ASUB2",
     "D24SUB2",                     "D24SUB2",  "",
    "D24ASUB2",                    "D24ASUB2",  "",
        "Chi5",                    "#chi_{5}",  "#chi_{5} based on N523SUB2",
       "Chi5A",                    "#chi_{5}",  "#chi_{5} based on N523ASUB2",
//16 
   "D2232SUB2",                   "D2232SUB2",  "",
  "D2232ASUB2",                  "D2232ASUB2",  "",
       "Chi62",                   "#chi_{62}",  "#chi_{62} based on N62SUB2",
      "Chi62A",                   "#chi_{62}",  "#chi_{62} based on N62ASUB2", 
     "D26SUB2",                     "D26SUB2",  "",
//17      
    "D26ASUB2",                    "D26ASUB2",  "",
       "Chi63",                   "#chi_{63}",  "#chi_{63} based on N63SUB2",
      "Chi63A",                   "#chi_{63}",  "#chi_{63} based on N63ASUB2", 
     "D34SUB2",                     "D34SUB2",  "",
    "D34ASUB2",                    "D34ASUB2",  "",
//18
        "Chi7",                    "#chi_{7}",  "#chi_{7} based on N723SUB2",
       "Chi7A",                    "#chi_{7}",  "#chi_{7} based on N723ASUB2",
   "D2432SUB2",                   "D2432SUB2",  "",
  "D2432ASUB2",                  "D2432ASUB2",  "",
    "N723SUB2",  "v_{7}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",
//19
    "N723SUB3",  "v_{7}\{#Psi_{7A}^{2},#Psi_{3A}}",  "A side is HF+",
   "N723ASUB2",  "v_{7}\{#Psi_{2A}^{2},#Psi_{3B}}",  "2 sub-event; A side is HF+",
   "N723ASUB3",  "v_{7}\{#Psi_{2A}^{2},#Psi_{3B}}",  "3 sub-event; A side if HF+",
    "N1HFm1cSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFm1dSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
//20
    "N1HFm1eSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFm1fSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFm1gSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFm1cSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFm1dSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
//21
    "N1HFm1eSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFm1fSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFm1gSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFp1cSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFp1dSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
//22
    "N1HFp1eSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution",
    "N1HFp1fSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution ",
    "N1HFp1gSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution ",
    "N1HFp1cSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFp1dSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
//23
    "N1HFp1eSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFp1fSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
    "N1HFp1gSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution",
      "N1HFcSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFdSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
//24
    "N1HFeSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFfSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFgSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFcSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFdSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
//25
    "N1HFeSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFfSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFgSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N112CSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 2A (-0.8<#eta<0.8)",
    "N112CSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 1C (-0.5<#eta<0.0) 2A (-3.5<#eta<-3.0)",
      //26
    "N112DSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",   "1A (-5<#eta<-4) 2A (-0.8<#eta<0.8)",
    "N112DSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",   "1A (-5<#eta<-4) 1C(0.0<#eta<0.5) 2A (-0.8<#eta<0.8)",
    "N112CombinedSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2Cmid}}",  "1A (4<#eta<5) 1B (-5<#eta<-4) 2Cmid (-0.8<#eta<0.8)",
    "N112CombinedSUB3",  "NG",  "NG",
      //27
    "N112ESUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 2A (3.0<#eta<3.5)",
    "N112ESUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 1C (-1.6<#eta<-1.2) 2A (3.0<#eta<3.5)",
    "N112FSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A -5<#eta<-4) 2A (-3.5<#eta<-3.0)",
    "N112FSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (-5<#eta<-4) 1C (1.2<#eta<1.6) 2A (-3.5<#eta<-3.0)",
    "N112GSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 2A (-3.5<#eta<-3.0)",
    "N112GSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (4<#eta<5) 1C (-1.6<#eta<-1.2) 2A (-3.5<#eta<-3.0)",
    "N112HSUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (-5<#eta<-4) 2A (3.0<#eta<3.5)",
    "N112HSUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "1A (-5<#eta<-4) 1C (1.2<#eta<1.6) 2A (3.0<#eta<3.5)",
    "N112MCASUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}^{even}",  "1A (-2.4<#eta<-2.0) 2A (3.0<#eta<5.0)",
    "N112MCASUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}^{even}",  "1A (-2.4<#eta<-2.0) 1C (-0.8<#eta<0.8) 2A (3.0<#eta<5.0)"
      };
