TGraphErrors * N112(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB, double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe ){
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
  int epindx = -1;
  Decor = false;
  //
  // Get needed resolution parameters for v2
  //
  double v2int,v2inte,v2intA,v2intAe,v2intB,v2intBe;
  double res2A = 0;
  double res2B = 0;
  double res2 = 0;
  cout<<"replay: "<<replay<<endl;
  cout<<ANALS[replay][0]<<endl;
  if(ANALS[replay][0].find("SUB2")!=std::string::npos) {
    gtmp = GetVNPt(N2SUB2,bin,-1,EtaMin,EtaMax,gtmp,gtmp,gtmp,v2int,v2inte,v2intA,v2intAe,v2intB,v2intBe,false);
  } else {
    gtmp = GetVNPt(N2SUB3,bin,-1,EtaMin,EtaMax,gtmp,gtmp,gtmp,v2int,v2inte,v2intA,v2intAe,v2intB,v2intBe,false);
  }
  res2A = resA[0];
  res2B = resB[0];
  res2 = (res2A+res2B)/2.;
  fin->Close();
  fin = new TFile(rootFile.data(),"r");
  cout<<"res2: "<<res2A<<"\t"<<res2B<<endl;
  int A = -1;
  int B = -1;
  if(replay==N112SUB2) {A=N112ASUB2; B=N112BSUB2;}
  if(replay==N112SUB3) {A=N112ASUB3; B=N112BSUB3;}
  if(replay==N112cSUB2) {A=N112AcSUB2; B=N112BcSUB2;}
  if(replay==N112cSUB3) {A=N112AcSUB3; B=N112BcSUB3;}
  if(replay==N112dSUB2) {A=N112AdSUB2; B=N112BdSUB2;}
  if(replay==N112dSUB3) {A=N112AdSUB3; B=N112BdSUB3;}
  if(replay==N112eSUB2) {A=N112AeSUB2; B=N112BeSUB2;}
  if(replay==N112eSUB3) {A=N112AeSUB3; B=N112BeSUB3;}
  if(replay==N112fSUB2) {A=N112AfSUB2; B=N112BfSUB2;}
  if(replay==N112fSUB3) {A=N112AfSUB3; B=N112BfSUB3;}
  if(replay==EP112SUB2) {A=EP112ASUB2; B=EP112BSUB2;}
  if(replay==EP112SUB3) {A=EP112ASUB3; B=EP112BSUB3;}
  if(A>=0) {
    cout<<"A: "<<A<<"\t"<<ANALS[A][0]<<endl;
    cout<<"B: "<<B<<"\t"<<ANALS[B][0]<<endl;
  }

  //
  // Start with eta distribution
  //
  if(A<0){
    for(int i = 0; i<12; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      gtmp = GetVNPt(replay,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
      vint/=res2;
      vinte/=res2;
      vintA/=res2;
      vintAe/=res2;
      vintB/=res2;
      vintBe/=res2;
      cout<<ANALS[replay][0]<<"\t"<<EtaMin<<"\t"<<EtaMax<<"\t"<<vintA<<endl;
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
      g = GetVNPt(A,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte,vintA, vintAe, vintB, vintBe, false);
      vint/=res2;
      vinte/=res2;
      vintA/=res2;
      vintAe/=res2;
      vintB/=res2;
      vintBe/=res2;
      fin->Close();
      fin = new TFile(rootFile.data(),"r");
      g2 = GetVNPt(B,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint2, vinte2,vintA2, vintAe2, vintB2, vintBe2, false);
      vint2/=res2;
      vinte2/=res2;
      vintA2/=res2;
      vintAe2/=res2;
      vintB2/=res2;
      vintBe2/=res2;
      fin->Close();
      cout<<ANALS[replay][0]<<"\t"<<EtaMin<<"\t"<<EtaMax<<"\t"<<vintA<<"\t"<<vintA2<<endl;
      gint->GetY()[i] = (vintA+vintA2)/2.;
      gint->GetEY()[i] = (vintAe+vintAe2)/2.;
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

  if(A<0){
    g = GetVNPt(replay,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte, vintA2, vintAe2, vintB2, vintBe2,false);
    ymin = setYmin(g,gA,gB);
    ymax = setYmax(g,gA,gB);
    fin->Close();
    outint = fopen(soutint.data(),"a+");
    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
    fclose(outint);
    return g;
  }
  g = GetVNPt(A,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte,vintA2, vintAe2, vintB2, vintBe2, false);
  fin->Close();
  fin = new TFile(rootFile.data(),"r");
    g2 = GetVNPt(B,bin,epindx,eMin,eMax,gA2, gB2, gSpec2, vint2, vinte2,vintA2, vintAe2, vintB2, vintBe2, false);
  fin->Close();
  //Only A has the correct symmetry...
  for(int i = 0; i<g->GetN(); i++) {
    gA->GetY()[i] = (gA->GetY()[i]+gA2->GetY()[i])/2.;
    gB->GetY()[i] = gA->GetY()[i];
    g->GetY()[i] = gA->GetY()[i];
    gA->GetEY()[i] = (gA->GetEY()[i]+gA2->GetEY()[i])/2.;
    gB->GetEY()[i] = gA->GetEY()[i];
    g->GetEY()[i] = gA->GetEY()[i];
  }
  ymin = setYmin(g,gA,gB);
  ymax = setYmax(g,gA,gB);
  g->SetName("g");
  gA->SetName("gA");
  gB->SetName("gB");
  return g;
}
