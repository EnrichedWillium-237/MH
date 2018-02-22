TGraphErrors * N1(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB, double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe ){
  fin = new TFile(rootFile.data(),"r");
  TGraphErrors * g2 ;
  TGraphErrors * gA2 ;
  TGraphErrors * gB2 ;
  TGraphErrors * gSpec2 ;
  TGraphErrors * gint2 ;
  TGraphErrors * gintA2 ;
  TGraphErrors * gintB2 ;
  TGraphErrors * gtmp;
  double x[12];
  double y[12];
  double ey[12];
  gint2 = new TGraphErrors(12,x,y,0,ey);
  gintA2 = new TGraphErrors(12,x,y,0,ey);
  gintB2 = new TGraphErrors(12,x,y,0,ey);
  double vint2=0;
  double vinte2=0;
  double vintA2=0;
  double vintAe2=0;
  double vintB2=0;
  double vintBe2=0;
  int epindxA = -1;
  int epindxB = -1;
  cout<<"N1 replay with replay = "<<replay<<"\t"<<ANALS[replay][0]<<endl;
  int A = N1ASUB2;
  int B = N1BSUB2;

  if(replay==N1ASUB2) {
    A = N1ASUB2;
    B = N1BSUB2;
    Decor = false;
  } else if (replay == N1ASUB3) {
    A = N1ASUB3;
    B = N1BSUB3;
    epindxA = HFp1;
    epindxB = HFm1;
  }
  if(replay==N1BSUB2) {
    A = N1BSUB2;
    B = N1ASUB2;
    Decor = false;
  } else if (replay == N1BSUB3) {
    A = N1BSUB3;
    B = N1ASUB3;
    epindxA = HFp1;
    epindxB = HFm1;
  }

  if(replay==N1SUB2) {
    A = N1ASUB2;
    B = N1BSUB2;
    Decor = false;
  } else if (replay == N1SUB3) {
    A = N1ASUB3;
    B = N1BSUB3;
    epindxA = HFp1;
    epindxB = HFm1;
  }

  if(replay==N1HFcSUB2) {
    A = N1HFp1cSUB2;
    B = N1HFm1cSUB2;
    Decor = false;
  } else if (replay == N1HFcSUB3) {
    A = N1HFp1cSUB3;
    B = N1HFm1cSUB3;
    epindxA = HFp1c;
    epindxB = HFm1c;
  }

  if(replay==N1HFdSUB2) {
    A = N1HFp1dSUB2;
    B = N1HFm1dSUB2;
    Decor = false;
  } else if (replay == N1HFdSUB3) {
    A = N1HFp1dSUB3;
    B = N1HFm1dSUB3;
    epindxA = HFp1d;
    epindxB = HFm1d;
  }

  if(replay==N1HFeSUB2) {
    A = N1HFp1eSUB2;
    B = N1HFm1eSUB2;
    Decor = false;
  } else if (replay == N1HFeSUB3) {
    A = N1HFp1eSUB3;
    B = N1HFm1eSUB3;
    epindxA = HFp1e;
    epindxB = HFm1e;
  }

  if(replay==N1HFfSUB2) {
    A = N1HFp1fSUB2;
    B = N1HFm1fSUB2;
    Decor = false;
  } else if (replay == N1HFfSUB3) {
    A = N1HFp1fSUB3;
    B = N1HFm1fSUB3;
    epindxA = HFp1f;
    epindxB = HFm1f;
  }
  if(epindxA>=0) {
    cout<<"A: "<<A<<"\t"<<ANALS[A][0]<<"\t"<<EPNames[epindxA]<<"\t"<<EPNames[RCMate1[epindxA]]<<"\t"<<EPNames[RCMate2[epindxA]]<<endl;
    cout<<"B: "<<B<<"\t"<<ANALS[B][0]<<"\t"<<EPNames[epindxB]<<"\t"<<EPNames[RCMate1[epindxB]]<<"\t"<<EPNames[RCMate2[epindxB]]<<endl;
  }
  //
  // Start with eta distribution
  //
  if(epindxA<0){
    for(int i = 0; i<12; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      gtmp = GetVNPt(replay,bin,epindxA,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
      gint->GetY()[i] = vint;
      gint->GetEY()[i] = vinte;
      gintA->GetY()[i]=vintA;
      gintA->GetEY()[i]=vintAe;
      gintB->GetY()[i]=vintB;
      gintB->GetEY()[i]=vintBe;
    }
  } else {
    for(int i = 0; i<12; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      g = GetVNPt(A,bin,epindxA,EtaMin,EtaMax,gA, gB, gSpec, vint, vinte,vintA, vintAe, vintB, vintBe, false);
      fin->Close();
      fin = new TFile(rootFile.data(),"r");
      g2 = GetVNPt(B,bin,epindxB,EtaMin,EtaMax,gA2, gB2, gSpec2, vint2, vinte2,vintA2, vintAe2, vintB2, vintBe2, false);
      fin->Close();
      gint->GetY()[i] = (vintA+vintA2+vintB+vintB2)/4.;
      gint->GetEY()[i] = (vintAe+vintAe2+vintBe+vintBe2)/4.;
      gintA->GetY()[i]=(vintA+vintA2)/2.;
      gintA->GetEY()[i]=(vintAe+vintAe2)/2.;
      gintB->GetY()[i]=(vintB+vintB2)/2.;
      gintB->GetEY()[i]=(vintBe+vintBe2)/2.;
    }
  }
  gint->SetName("gint");
  gintA->SetName("gintA");
  gintB->SetName("gintB");
  //
  // Now do requested calculation
  //
  if(epindxA<0){
    g = GetVNPt(replay,bin,epindxA,eMin,eMax,gA, gB, gSpec, vint, vinte,vintA, vintAe, vintB, vintBe, false);
    ymin = setYmin(g,gA,gB);
    ymax = setYmax(g,gA,gB);
    fin->Close();
    outint = fopen(soutint.data(),"a+");
    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
    fclose(outint);
    g->SetName("g");
    gA->SetName("gA");
    gB->SetName("gB");
    return g;
  }
  g = GetVNPt(A,bin,epindxA,eMin,eMax,gA, gB, gSpec, vint, vinte, vintA, vintAe, vintB, vintBe,false);
  fin->Close();
  fin = new TFile(rootFile.data(),"r");
  g2 = GetVNPt(B,bin,epindxB,eMin,eMax,gA2, gB2, gSpec2, vint2, vinte2, vintA2, vintAe2, vintB2, vintBe2,false);
  fin->Close();
  for(int i = 0; i<g->GetN(); i++) {
    g->GetY()[i] = (g->GetY()[i]+g2->GetY()[i])/2.;
    gA->GetY()[i] = (gA->GetY()[i]+gA2->GetY()[i])/2.;
    gB->GetY()[i] = (gB->GetY()[i]+gB2->GetY()[i])/2.;
  }
  ymin = setYmin(g,gA,gB);
  ymax = setYmax(g,gA,gB);
  g->SetName("g");
  gA->SetName("gA");
  gB->SetName("gB");
  return g;
}
