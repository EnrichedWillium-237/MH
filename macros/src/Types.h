enum AnalTypes{
         N1SUB2,       N1SUB3,   N1EVENSUB2,  N1EVENSUB3,      N1ASUB2,
        N1ASUB3,      N1BSUB2,      N1BSUB3,      N2SUB2,       N2SUB3,
         N3SUB2,       N3SUB3,       N4SUB2,      N4SUB3,       N5SUB2,
         N5SUB3,       N6SUB2,       N6SUB3,      N7SUB2,       N7SUB3,
       N112SUB2,     N112SUB3,    N112ASUB2,   N112ASUB3,    N112BSUB2,
      N112BSUB3,     N523SUB2,     N523SUB3,   N523ASUB2,    N523ASUB3,
    N1MCm22SUB3,  N1MCm18SUB3,  N1MCm14SUB3, N1MCm10SUB3,  N1MCm06SUB3,
    N1MCm02SUB3,  N1MCp22SUB3,  N1MCp18SUB3, N1MCp14SUB3,  N1MCp10SUB3,
    N1MCp06SUB3,  N1MCp02SUB3,  N1MCm22SUB2, N1MCm18SUB2,  N1MCm14SUB2,
    N1MCm10SUB2,  N1MCm06SUB2,  N1MCm02SUB2, N1MCp22SUB2,  N1MCp18SUB2,
    N1MCp14SUB2,  N1MCp10SUB2,  N1MCp06SUB2, N1MCp02SUB2,      N42SUB2,
	N42SUB3,     N42ASUB2,     N42ASUB3,    N42BSUB3,     N42CSUB3,
	N62SUB2,      N62SUB3,     N62ASUB3,     N63SUB2,      N63SUB3,
       N63ASUB2,     N63ASUB3,     N63BSUB3,    N63CSUB3,         Chi4,
	  Chi4A,      D24SUB2,     D24ASUB2,        Chi5,        Chi5A,
      D2232SUB2,   D2232ASUB2,        Chi62,      Chi62A,      D26SUB2,   
       D26ASUB2,        Chi63,       Chi63A,     D34SUB2,     D34ASUB2,
	   Chi7,        Chi7A,    D2432SUB2,  D2432ASUB2,     N723SUB2,
       N723SUB3,   N723ASUB2,    N723ASUB3,
	 N1HFm1cSUB2, N1HFm1dSUB2, N1HFm1eSUB2,N1HFm1fSUB2,
	 N1HFm1cSUB3, N1HFm1dSUB3, N1HFm1eSUB3,N1HFm1fSUB3,
	 N1HFp1cSUB2, N1HFp1dSUB2, N1HFp1eSUB2,N1HFp1fSUB2,
	 N1HFp1cSUB3, N1HFp1dSUB3, N1HFp1eSUB3,N1HFp1fSUB3,
	 N1HFcSUB2, N1HFdSUB2, N1HFeSUB2,N1HFfSUB2,
	 N1HFcSUB3, N1HFdSUB3, N1HFeSUB3,N1HFfSUB3,
       EP112SUB2,     EP112SUB3,    EP112ASUB2,   EP112ASUB3,    EP112BSUB2,
      EP112BSUB3,  
	N112cSUB2, N112cSUB3, N112AcSUB2, N112AcSUB3,N112BcSUB2, N112BcSUB3,
	N112dSUB2, N112dSUB3, N112AdSUB2, N112AdSUB3,N112BdSUB2, N112BdSUB3,
	N112eSUB2, N112eSUB3, N112AeSUB2, N112AeSUB3,N112BeSUB2, N112BeSUB3,
	N112fSUB2, N112fSUB3, N112AfSUB2, N112AfSUB3,N112BfSUB2, N112BfSUB3,
    LAST
};

static const string ANALS[250][3] {
    "N1SUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1SUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
"N1EVENSUB2",      "v_{1}^{even}\{#Psi_{1}}",    "",
"N1EVENSUB3",      "v_{1}^{even}\{#Psi_{1}}",                                 "",
   "N1ASUB2",             "v_{1}\{#Psi_{1}}",     "2 sub-event resolution - need to add to N1B",

   "N1ASUB3",  "v_{1}\{#Psi_{1}}", "3 sub-event resolution - HFp1-HFm1-trackp114",
   "N1BSUB2",  "v_{1}\{#Psi_{1}}", "2 sub-event resolution - need to add to N1A",
   "N1BSUB3",  "v_{1}\{#Psi_{1}}", "3 sub-event resolution - HFm1-HFp1-trackm114",
    "N2SUB2",  "v_{2}\{#Psi_{2}}", "2 sub-event resolution",
    "N2SUB3",  "v_{2}\{#Psi_{2}}", "3 sub-event resolution",
      
    "N3SUB2",  "v_{3}\{#Psi_{3}}", "2 sub-event resolution",
    "N3SUB3",  "v_{3}\{#Psi_{3}}", "3 sub-event resolution",      
    "N4SUB2",  "v_{4}\{#Psi_{4}}", "2 sub-event resolution",
    "N4SUB3",  "v_{4}\{#Psi_{4}}", "3 sub-event resolution",
    "N5SUB2",  "v_{5}\{#Psi_{5}}", "2 sub-event resolution",
      
    "N5SUB3",  "v_{5}\{#Psi_{5}}", "3 sub-event resolution",
    "N6SUB2",  "v_{6}\{#Psi_{6}}", "2 sub-event resolution",      
    "N6SUB3",  "v_{6}\{#Psi_{6}}", "3 sub-event resolution",
    "N7SUB2",  "v_{7}\{#Psi_{7}}", "2 sub-event resolution",
    "N7SUB3",  "v_{7}\{#Psi_{7}}", "3 sub-event resolution",
      
  "N112SUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Correctly combines 112A and 112B",
  "N112SUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Correctly combines 112A and 112B",
  "N112ASUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "qA is the correct version, n=1 in HF+",
  "N112ASUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "qA is the correct version, n=1 in HF+",
  "N112BSUB2",  "v_{1}\{#Psi_{1B},#Psi_{2B}}",  "qA is the correct version, n=1 in HF-",
    
  "N112BSUB3",  "v_{1}\{#Psi_{1B},#Psi_{2B}}",  "qA is the correct version, n=1 in HF-",
   "N523SUB2",  "v_{5}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",
   "N523SUB3",  "v_{5}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",
   "N523ASUB2", "v_{5}\{#Psi_{2A},#Psi_{3B}}",  "A side is HF+",
   "N523ASUB3",  "v_{5}\{#Psi_{2A},#Psi_{3B}}", "A side if HF+",

 "N1MCm22SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm18SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm14SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm10SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm06SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
      
 "N1MCm02SUB3",  "v_{1}\{#Psi{1mc}}",  "",
 "N1MCp22SUB3",  "v_{1}\{#Psi{1mc}}",  "",
 "N1MCp18SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp14SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp10SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
      
 "N1MCp06SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp02SUB3",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm22SUB2",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCm18SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm14SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
      
 "N1MCm10SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm06SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCm02SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp22SUB2",  "v_{1}\{#Psi_{1mc}}",  "",
 "N1MCp18SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
      
 "N1MCp14SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp10SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp06SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
 "N1MCp02SUB2",  "v_{1}\{#Psi_{1mc}}",  "DO NOT USE, A and B EP cover different #eta ranges",
     "N42SUB2", "v_{4}\{#Psi_{2A}^{2}}",  "2 sub-event resolution ",

     "N42SUB3", "v_{4}\{#Psi_{2A}^{2}}",  "3 sub-event resolution ",
    "N42ASUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "2 sub-event resolution; note: resolution from same side ",
    "N42ASUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "3 sub-event resolution; note: resolution from same side ",
    "N42BSUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "5 sub-event resolution; res calc uses symmetric event planes 0.8 to 1.2 ",
    "N42CSUB3", "v_{4}\{#Psi_{2A},#Psi_{2B}}",  "5 sub-event resolution; res calc used symmetric event planes 1.6 to 2.0 ",

     "N62SUB2", "v_{6}\{#Psi_{2A}^{3}}",  "2 sub-event resolution ",
     "N62SUB3", "v_{6}\{#Psi_{2A}^{3}}",  "3 sub-event resolution ",
    "N62ASUB3", "v_{6}\{#Psi_{2A}^{2},#Psi_{2B}}",  "3 sub-event, A/B sides not symmetric ",
     "N63SUB2", "v_{6}\{#Psi_{3A}^{2}}",  "2 sub-event resolution ",
     "N63SUB3", "v_{6}\{#Psi_{3A}^{2}}",  "3 sub-event resolution ",

    "N63ASUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "2 sub-event resolution; note: resolution from same side ",
    "N63ASUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "3 sub-event resolution; note: resolution from same side ",
    "N63BSUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "5 sub-event resolution; res calc uses symmetric event planes 0.8 to 1.2 ",
    "N63CSUB3", "v_{6}\{#Psi_{3A},#Psi_{3B}}",  "5 sub-event resolution; res calc used symmetric event planes 1.6 to 2.0 ",
        "Chi4",                    "#chi_{4}",  "#chi_{4} based on N42SUB2",

       "Chi4A",                    "#chi_{4}",  "#chi_{4} based on N42ASUB2",
     "D24SUB2",                     "D24SUB2",  "",
    "D24ASUB2",                    "D24ASUB2",  "",
        "Chi5",                    "#chi_{5}",  "#chi_{5} based on N523SUB2",
       "Chi5A",                    "#chi_{5}",  "#chi_{5} based on N523ASUB2",
 
   "D2232SUB2",                   "D2232SUB2",  "",
  "D2232ASUB2",                  "D2232ASUB2",  "",
       "Chi62",                   "#chi_{62}",  "#chi_{62} based on N62SUB2",
      "Chi62A",                   "#chi_{62}",  "#chi_{62} based on N62ASUB2", 
     "D26SUB2",                     "D26SUB2",  "",
      
    "D26ASUB2",                    "D26ASUB2",  "",
       "Chi63",                   "#chi_{63}",  "#chi_{63} based on N63SUB2",
      "Chi63A",                   "#chi_{63}",  "#chi_{63} based on N63ASUB2", 
     "D34SUB2",                     "D34SUB2",  "",
    "D34ASUB2",                    "D34ASUB2",  "",

        "Chi7",                    "#chi_{7}",  "#chi_{7} based on N723SUB2",
       "Chi7A",                    "#chi_{7}",  "#chi_{7} based on N723ASUB2",
   "D2432SUB2",                   "D2432SUB2",  "",
  "D2432ASUB2",                  "D2432ASUB2",  "",
    "N723SUB2",  "v_{7}\{#Psi_{2A},#Psi_{3A}}",  "A side is HF+",

    "N723SUB3",  "v_{7}\{#Psi_{7A}^{2},#Psi_{3A}}",  "A side is HF+",
   "N723ASUB2",  "v_{7}\{#Psi_{2A}^{2},#Psi_{3B}}",  "2 sub-event; A side is HF+",
   "N723ASUB3",  "v_{7}\{#Psi_{2A}^{2},#Psi_{3B}}",  "3 sub-event; A side if HF+",
    "N1HFm1cSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFm1dSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFm1eSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFm1fSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFm1cSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFm1dSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFm1eSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFm1fSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",

    "N1HFp1cSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFp1dSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFp1eSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFp1fSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFp1cSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFp1dSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFp1eSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",
    "N1HFp1fSUB3",             "v_{1}\{#Psi_{1}}",    "3 sub-event resolution - HF+ summed with HF-",

    "N1HFcSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFdSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFeSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFfSUB2",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",

    "N1HFcSUB3",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFdSUB3",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFeSUB3",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
    "N1HFfSUB3",             "v_{1}\{#Psi_{1}}",    "2 sub-event resolution - HF+ summed with HF-",
  "EP112SUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Correctly combines 112A and 112B",
  "EP112SUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "Correctly combines 112A and 112B",
  "EP112ASUB2",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "qA is the correct version, n=1 in HF+",
  "EP112ASUB3",  "v_{1}\{#Psi_{1A},#Psi_{2A}}",  "qA is the correct version, n=1 in HF+",
  "EP112BSUB2",  "v_{1}\{#Psi_{1B},#Psi_{2B}}",  "qA is the correct version, n=1 in HF-",
    
  "EP112BSUB3",  "v_{1}\{#Psi_{1B},#Psi_{2B}}",  "qA is the correct version, n=1 in HF-",

  "N112cSUB2",  "v_{1}\{#Psi_{1Ac},#Psi_{2Ac}}",  "Correctly combines 112A and 112B",
  "N112cSUB3",  "v_{1}\{#Psi_{1Ac},#Psi_{2Ac}}",  "Correctly combines 112A and 112B",
  "N112AcSUB2",  "v_{1}\{#Psi_{1Ac},#Psi_{2Ac}}",  "qA is the correct version, n=1 in HF+",
  "N112AcSUB3",  "v_{1}\{#Psi_{1Ac},#Psi_{2Ac}}",  "qA is the correct version, n=1 in HF+",
  "N112BcSUB2",  "v_{1}\{#Psi_{1Bc},#Psi_{2Bc}}",  "qA is the correct version, n=1 in HF-",    
  "N112BcSUB3",  "v_{1}\{#Psi_{1Bc},#Psi_{2Bc}}",  "qA is the correct version, n=1 in HF-",

  "N112dSUB2",  "v_{1}\{#Psi_{1Ad},#Psi_{2Ad}}",  "Correctly combines 112A and 112B",
  "N112dSUB3",  "v_{1}\{#Psi_{1Ad},#Psi_{2Ad}}",  "Correctly combines 112A and 112B",
  "N112AdSUB2",  "v_{1}\{#Psi_{1Ad},#Psi_{2Ad}}",  "qA is the correct version, n=1 in HF+",
  "N112AdSUB3",  "v_{1}\{#Psi_{1Ad},#Psi_{2Ad}}",  "qA is the correct version, n=1 in HF+",
  "N112BdSUB2",  "v_{1}\{#Psi_{1Bd},#Psi_{2Bd}}",  "qA is the correct version, n=1 in HF-",    
  "N112BdSUB3",  "v_{1}\{#Psi_{1Bd},#Psi_{2Bd}}",  "qA is the correct version, n=1 in HF-",

  "N112eSUB2",  "v_{1}\{#Psi_{1Ae},#Psi_{2Ae}}",  "Correctly combines 112A and 112B",
  "N112eSUB3",  "v_{1}\{#Psi_{1Ae},#Psi_{2Ae}}",  "Correctly combines 112A and 112B",
  "N112AeSUB2",  "v_{1}\{#Psi_{1Ae},#Psi_{2Ae}}",  "qA is the correct version, n=1 in HF+",
  "N112AeSUB3",  "v_{1}\{#Psi_{1Ae},#Psi_{2Ae}}",  "qA is the correct version, n=1 in HF+",
  "N112BeSUB2",  "v_{1}\{#Psi_{1Be},#Psi_{2Be}}",  "qA is the correct version, n=1 in HF-",    
  "N112BeSUB3",  "v_{1}\{#Psi_{1Be},#Psi_{2Be}}",  "qA is the correct version, n=1 in HF-",

  "N112fSUB2",  "v_{1}\{#Psi_{1Af},#Psi_{2Af}}",  "Correctly combines 112A and 112B",
  "N112fSUB3",  "v_{1}\{#Psi_{1Af},#Psi_{2Af}}",  "Correctly combines 112A and 112B",
  "N112AfSUB2",  "v_{1}\{#Psi_{1Af},#Psi_{2Af}}",  "qA is the correct version, n=1 in HF+",
  "N112AfSUB3",  "v_{1}\{#Psi_{1Af},#Psi_{2Af}}",  "qA is the correct version, n=1 in HF+",
  "N112BfSUB2",  "v_{1}\{#Psi_{1Bf},#Psi_{2Bf}}",  "qA is the correct version, n=1 in HF-",    
  "N112BfSUB3",  "v_{1}\{#Psi_{1Bf},#Psi_{2Bf}}",  "qA is the correct version, n=1 in HF-"

      };

/* enum AnalType { */
/*     N1MCm22SUB3,       N1MCm18SUB3,        N1MCm14SUB3,      N1MCm10SUB3,  */
/*     N1MCm06SUB3,       N1MCm02SUB3,        N1MCp22SUB3,      N1MCp18SUB3,  */
/*     N1MCp14SUB3,       N1MCp10SUB3,        N1MCp06SUB3,      N1MCp02SUB3, */
/*          N1SUB2,            N1SUB3,            N1ASUB2,          N1ASUB3, */
/*         N1BSUB2,           N1BSUB3,           N112SUB2,         N112SUB3, */
/*       N112ASUB2,         N112ASUB3,          N112BSUB2,        N112BSUB3, */
/*       N123SUB2,           N123SUB3, */
/*       N123ASUB2,         N123ASUB3, */
/*       N123BSUB2,         N123BSUB3, */
/*     N2SUB2,           N2SUB3, */
/*          N3SUB2,            N3SUB3,             N4SUB2,           N4SUB3, */
/*         N42SUB2,           N42SUB3,           N42ASUB2,         N42ASUB3, */
/*        N42BSUB3,          N42CSUB3,             N5SUB2,           N5SUB3,              */
/*          N6SUB2,            N6SUB3,             N7SUB2,           N7SUB3,           */
/*        N523SUB2,          N523SUB3,          N523ASUB2,        N523ASUB3, */
/*        N723SUB2,          N723SUB3,          N723ASUB2,        N723ASUB3,    */
/*         N62SUB2,           N62SUB3,           N62ASUB3,          N63SUB2, */
/*         N63SUB3,          N63ASUB2,           N63ASUB3,         N63BSUB3, */
/*        N63CSUB3, */
/*         D24SUB2,           D24SUB3,           D24ASUB2,         D24ASUB3,           */
/* 	D34SUB2,           D34SUB3,           D34ASUB2,         D34ASUB3,           */
/*       D2232SUB2,        D2232SUB3,         */
/*       D2432SUB2,         D2432SUB3,         D2232ASUB2,       D2232ASUB3,         */
/*      D2432ASUB2,        D2432ASUB3,            D26SUB2,          D26SUB3,   */
/*        D26ASUB2,          D26ASUB3,             */
/* 	   CHI4,             CHI4A,               CHI5,            CHI5A,   */
/* 	  CHI62,            CHI62A,              CHI63,           CHI63A,  */
/* 	   CHI7,             CHI7A, */
/*           N2EFF,           N2NOEFF,            N723EFF,        N723NOEFF,          */
/*        D2432EFF,        D2432NOEFF,            CHI7EFF,        CHI7NOEFF,             */
/*          N42EFF,              LAST */
/* }; */
/* static const string AnalNames[]={ */
/*   "N1MCm22SUB3",     "N1MCm18SUB3",      "N1MCm14SUB3",    "N1MCm10SUB3", */
/*   "N1MCm06SUB3",     "N1MCm02SUB3",      "N1MCp22SUB3",    "N1MCp18SUB3",  */
/*   "N1MCp14SUB3",     "N1MCp10SUB3",      "N1MCp06SUB3",    "N1MCp02SUB3", */
/*        "N1SUB2",          "N1SUB3",          "N1ASUB2",        "N1ASUB3", */
/*       "N1BSUB2",         "N1BSUB3",         "N112SUB2",       "N112SUB3", */
/*     "N112ASUB2",       "N112ASUB3",        "N112BSUB2",      "N112BSUB3", */
/*     "N123SUB2",       "N123SUB3", */
/*     "N123ASUB2",       "N123ASUB3", */
/*     "N123BSUB2",       "N123BSUB3", */
/*   "N2SUB2",         "N2SUB3", */
/*        "N3SUB2",          "N3SUB3",           "N4SUB2",         "N4SUB3", */
/*       "N42SUB2",         "N42SUB3",         "N42ASUB2",       "N42ASUB3", */
/*      "N42BSUB3",        "N42CSUB3",           "N5SUB2",         "N5SUB3",           */
/*        "N6SUB2",          "N6SUB3",           "N7SUB2",         "N7SUB3",       */
/*      "N523SUB2",        "N523SUB3",        "N523ASUB2",      "N523ASUB3",       */
/*      "N723SUB2",        "N723SUB3",        "N723ASUB2",      "N723ASUB3",        */
/*       "N62SUB2",         "N62SUB3",         "N62ASUB3",        "N63SUB2", */
/*       "N63SUB3",        "N63ASUB2",         "N63ASUB3",       "N63BSUB3", */
/*      "N63CSUB3", */
/*       "D24SUB2",         "D24SUB3",         "D24ASUB2",       "D24ASUB3",         */
/*       "D34SUB2",         "D34SUB3",         "D34ASUB2",       "D34ASUB3",         */
/*      "D2232SUB2",      "D2232SUB3",       */
/*     "D2432SUB2",       "D2432SUB3",       "D2232ASUB2",     "D2232ASUB3",     */
/*    "D2432ASUB2",      "D2432ASUB3",          "D26SUB2",        "D26SUB3",   */
/*      "D26ASUB2",        "D26ASUB3",      */
/*          "CHI4",           "CHI4A",             "CHI5",          "CHI5A",         */
/*         "CHI62",          "CHI62A",            "CHI63",         "CHI63A",            */
/*          "CHI7",           "CHI7A",  */
/*         "N2EFF",         "N2NOEFF",          "N723EFF",      "N723NOEFF",         */
/*      "D2432EFF",      "D2432NOEFF",          "CHI7EFF",      "CHI7NOEFF",          */
/*        "N42EFF",             "LAST" */
/* }; */
/* static const string ytitle[]={ */
/*    "v_{1}\{#Psi_{1,MC} (-2.4<#eta<-2.0)}",   "v_{1}\{#Psi_{1,MC} (-2.0<#eta<-1.6)}",   "v_{1}\{#Psi_{1,MC} (-1.6<#eta<-1.2)}",   "v_{1}\{#Psi_{1,MC} (-1.2<#eta<-0.8)}", */
/*    "v_{1}\{#Psi_{1,MC} (-0.8<#eta<-0.4)}",    "v_{1}\{#Psi_{1,MC} (-0.4<#eta<0.0)}",     "v_{1}\{#Psi_{1,MC} (2.0<#eta<2.4)}",     "v_{1}\{#Psi_{1,MC} (1.6<#eta<2.0)}", */
/*      "v_{1}\{#Psi_{1,MC} (1.2<#eta<1.6)}",     "v_{1}\{#Psi_{1,MC} (0.8<#eta<1.2)}",     "v_{1}\{#Psi_{1,MC} (0.4<#eta<0.8)}",     "v_{1}\{#Psi_{1,MC} (0.0<#eta<0.4)}", */
/*                        "v_{1}\{#Psi_{1}}",                       "v_{1}\{#Psi_{1}}",                       "v_{1}\{#Psi_{1}}",                       "v_{1}\{#Psi_{1}}", */
/*                        "v_{1}\{#Psi_{1}}",                       "v_{1}\{#Psi_{1}}",              "v_{1}\{#Psi{1A},#Psi{2B}}",              "v_{1}\{#Psi{1A},#Psi{2B}}", */
/*               "v_{1}\{#Psi{1A},#Psi{2A}}",              "v_{1}\{#Psi{1A},#Psi{2A}}",              "v_{1}\{#Psi{1A},#Psi{2A}}",              "v_{1}\{#Psi{1A},#Psi{2A}}", */
/*               "v_{1}\{#Psi{2A},#Psi{3B}}",              "v_{1}\{#Psi{2A},#Psi{3B}}", */
/*               "v_{1}\{#Psi{2A},#Psi{3B}}",              "v_{1}\{#Psi{2A},#Psi{3B}}", */
/*               "v_{1}\{#Psi{2A},#Psi{3B}}",              "v_{1}\{#Psi{2A},#Psi{3B}}", */
/*    "v_{2}",                                  "v_{2}", */
/*                                   "v_{3}",                                  "v_{3}",                                  "v_{4}",                                  "v_{4}", */
/*                        "v_{4}\{#Psi_{2}}",                       "v_{4}\{#Psi_{2}}",            "v_{4}\{#Psi_{2A},#Psi_{2B}}",            "v_{4}\{#Psi_{2A},#Psi_{2B}}", */
/*   "v_{4}\{#Psi_{2A},#Psi_{2B}}(5 sub-ep)",  "v_{4}\{#Psi_{2A},#Psi_{2B}}(5 sub-ep)",                                  "v_{5}",                                  "v_{5}",                        */
/*                                   "v_{6}",                                  "v_{6}",                                  "v_{7}",                                  "v_{7}",        */
/*             "v_{5}\{ #Psi_{2}, #Psi_{3}}",            "v_{5}\{ #Psi_{2}, #Psi_{3}}",            "v_{5}\{#Psi_{2A},#Psi_{3B}}",            "v_{5}\{#Psi_{2A},#Psi_{3B}}",     */
/*               "v_{7}\{#Psi_{2},#Psi_{3}}",              "v_{7}\{#Psi_{2},#Psi_{3}}",            "v_{7}\{#Psi_{2A},#Psi_{3B}}",            "v_{7}\{#Psi_{2A},#Psi_{3B}}",           */
/*                        "v_{6}\{#Psi_{2}}",                       "v_{6}\{#Psi_{2}}",        "v_{6}\{#Psi_{2A}^{2},#Psi_{2B}}",                       "v_{6}\{#Psi_{3}}", */
/*                        "v_{6}\{#Psi_{3}}",            "v_{6}\{#Psi_{3A},#Psi_{3B}}",            "v_{6}\{#Psi_{3A},#Psi_{3B}}",            "v_{6}\{#Psi_{3A},#Psi_{3B}}", */
/*             "v_{6}\{#Psi_{3A},#Psi_{3B}}", */
/* 	              "D24SUB2",                      "D24SUB3",                        "D24ASUB2",                          "D24ASUB3",       */
/*                       "D34SUB2",                      "D34SUB3",                        "D34ASUB2",                          "D34ASUB3",             */
/*                     "D2232SUB2",                         "D2232SUB3",             */
/*                     "D2432SUB2",                    "D2432SUB3",                      "D2232ASUB2",                        "D2232ASUB3",   */
/*                    "D2432ASUB2",                   "D2432ASUB3",                         "D26SUB2",                           "D26SUB3",            */
/*                      "D26ASUB2",                     "D26ASUB3",      */
/*                      "#chi_{4}",                    "#chi_{4A}",                        "#chi_{5}",                         "#chi_{5A}",             */
/*                     "#chi_{62}",                   "#chi_{62A}",                       "#chi_{63}",                        "#chi_{63A}",                      */
/*                      "#chi_{7}",                    "#chi_{7A}",            */
/*                    "v_{2}(eff)",                 "v_{2}(noeff)",                    "v_{723}(eff)",                    "v_{723}(noeff)",                */
/*                      "D2432EFF",                   "D2432NOEFF",                   "#chi_{7}(eff)",                   "#chi_{7}(moeff)",        */
/*                   "v_{42}(eff)",                     "LAST" */
/* }; */
