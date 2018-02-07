TGraphErrors * N1EVEN(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB , double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe){
  fin = new TFile(rootFile.data(),"r");
  int epindx = -1;
  TGraphErrors * gtmp;
  TGraphErrors * g2;
  TGraphErrors * gA2;
  TGraphErrors * gB2;
  TGraphErrors * gSpec2;
  int pRef2 = N1MCp22SUB2;
  int pRef3 = N1MCp22SUB3;
  int mRef2 = N1MCm22SUB2;
  int mRef3 = N1MCm22SUB3;
  int ioff = 1;

  string lepA = "";
  string lepB = "";
  string pref = "trk ";
  if(sTrackOrientation==Type_pPb && ANALS[replay][0].find("MCp")!=std::string::npos) pref = "p-side ";
  if(sTrackOrientation==Type_pPb && ANALS[replay][0].find("MCm")!=std::string::npos) pref = "Pb-side ";
  int nrep = replay;
  if(replay==N1EVENSUB2 || replay==N1EVENSUB3) nrep = pRef2;

  if(ANALS[nrep][0].find("MCm22")!=std::string::npos) {
    lepA = pref+"(-2.4<#eta<-2.0)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCm18")!=std::string::npos) {
    lepA = pref+"(-2.0<#eta<-1.6)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCm14")!=std::string::npos) {
    lepA = pref+"(-1.6<#eta<-1.2)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCm10")!=std::string::npos) {
    lepA = pref+"(-1.2<#eta<-0.8)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCm06")!=std::string::npos) {
    lepA = pref+"(-0.8<#eta<-0.4)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCm02")!=std::string::npos) {
    lepA = pref+"(-0.4<#eta<0.0)";
    lepB = pref+"(2.0<#eta<2.4)";
  }
if(ANALS[nrep][0].find("MCp22")!=std::string::npos) {
    lepA = pref+"(2.0<#eta<2.4)";
    lepB = pref+"(-2.4<#eta<-2.0)";
  }
if(ANALS[nrep][0].find("MCp18")!=std::string::npos) {
    lepA = pref+"(1.6<#eta<2.0)";
    lepB = pref+"(-2.4<#eta<-2.0)";
    if(ANALS[nrep][0].find("SUB2")!=std::string::npos) lepA+=" NG - Use SUB3";
  }
if(ANALS[nrep][0].find("MCp14")!=std::string::npos) {
    lepA = pref+"(1.2<#eta<1.6)";
    lepB = pref+"(-2.4<#eta<-2.0)";
    if(ANALS[nrep][0].find("SUB2")!=std::string::npos) lepA+=" NG - Use SUB3";
  }
if(ANALS[nrep][0].find("MCp10")!=std::string::npos) {
    lepA = pref+"(0.8<#eta<1.2)";
    lepB = pref+"(-2.4<#eta<-2.0)";
    if(ANALS[nrep][0].find("SUB2")!=std::string::npos) lepA+=" NG - Use SUB3";
  }
if(ANALS[nrep][0].find("MCp06")!=std::string::npos) {
    lepA = pref+"(0.4<#eta<0.8)";
    lepB = pref+"(-2.4<#eta<-2.0)";
    if(ANALS[nrep][0].find("SUB2")!=std::string::npos) lepA+=" NG - Use SUB3";
  }
if(ANALS[nrep][0].find("MCp02")!=std::string::npos) {
    lepA = pref+"(0.0<#eta<0.4)";
    lepB = pref+"(-2.4<#eta<-2.0)";
    if(ANALS[nrep][0].find("SUB2")!=std::string::npos) lepA+=" NG - Use SUB3";
  }
  
  Decor = false;
  //
  // Start with eta distribution
  //
  if(replay==N1EVENSUB2 || replay==N1EVENSUB3) {
    for(int i = 0+ioff; i<12-ioff; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      if(i<6) {
	int rep = pRef2;
	if(replay==N1EVENSUB3) rep = pRef3;
	gtmp = GetVNPt(rep,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
	gint->GetY()[i-ioff] = vintA;
	gint->GetEY()[i-ioff] = vintAe;
	gintA->GetY()[i-ioff] = vintA;
	gintA->GetEY()[i-ioff] = vintAe;
	gintB->GetY()[i-ioff] = vintB;
	gintB->GetEY()[i-ioff] = vintBe;
	gint->SetTitle("Selected");
	gintA->SetTitle(lepA.data());
	gintB->SetTitle(lepB.data());
      } else {
	int rep = mRef2;
	if(replay==N1EVENSUB3) rep = mRef3;
	gtmp = GetVNPt(rep,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
	gint->GetY()[i-ioff] = vintA;
	gint->GetEY()[i-ioff] = vintAe;
	gintA->GetY()[i-ioff] = vintB;
	gintA->GetEY()[i-ioff] = vintBe;
	gintB->GetY()[i-ioff] = vintA;
	gintB->GetEY()[i-ioff] = vintAe;
      }
    }
    gint->Set(12-2*ioff);
    gintA->Set(12-2*ioff);
    gintB->Set(12-2*ioff);
  } else {
    for(int i = 0; i<12; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      gtmp = GetVNPt(replay,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
      gint->GetY()[i] = vint;
      gint->GetEY()[i] = vinte;
      gintA->GetY()[i]=vintA;
      gintA->GetEY()[i]=vintAe;
      gintB->GetY()[i]=vintB;
      gintB->GetEY()[i]=vintBe;
    }
    gint->SetTitle("NOGOOD");
    gintA->SetTitle(lepA.data());
    gintB->SetTitle(lepB.data());
  }
  gint->SetName("gint");
  gintA->SetName("gintA");
  gintB->SetName("gintB");
  //
  // Now do requested calculation
  //
  if(replay != N1EVENSUB3  && replay !=N1EVENSUB2){
    g = GetVNPt(replay,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte, vintA,vintAe,vintB,vintBe,false);
    g->SetTitle("NOGOOD");
    gB->SetTitle(lepB.data());
    if(replay!=N1MCm22SUB2 && replay!=N1MCp22SUB2) gB->SetTitle("NOGOOD");
    gA->SetTitle(lepA.data());
    g->SetName("g");
    gA->SetName("gA");
    gB->SetName("gB");
    ymin = setYmin(gA);
    ymax = setYmax(gA);
    fin->Close();
    outint = fopen(soutint.data(),"a+");
    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
    fclose(outint);
  } else {
    int settype = 0;
    if(eMin*eMax>0) {
      if(eMin < 0 ) {
	settype = pRef2;
	if(replay==N1EVENSUB3) settype=pRef3;
      } else {
	settype = mRef2;
	if(replay==N1EVENSUB3) settype=mRef3;
      }
      g = GetVNPt(settype,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
      g->SetTitle("NOGOOD");
      gB->SetTitle("NOGOOD");
      gA->SetTitle(lepA.data());
      ymin = setYmin(gA);
      ymax = setYmax(gA);
    } else {
      settype = pRef2;
      if(replay==N1EVENSUB3) settype=pRef3;
      g = GetVNPt(settype,bin,epindx,eMin,0.,gA, gB, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
      settype = mRef2;
      if(replay==N1EVENSUB3) settype=mRef3;
      g2 = GetVNPt(settype,bin,epindx,0.,eMax,gA2, gB2, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
      for(int i = 0; i<g->GetN(); i++) {
	g->GetY()[i] = (g->GetY()[i]+g2->GetY()[i])/2.;
	g->GetEY()[i] = (g->GetEY()[i]+g2->GetEY()[i])/2.;
	gA->GetY()[i] = (gA->GetY()[i]+gA2->GetY()[i])/2.;
	gA->GetEY()[i] = (gA->GetEY()[i]+gA2->GetEY()[i])/2.;
	gB->GetY()[i] = (gB->GetY()[i]+gB2->GetY()[i])/2.;
	gB->GetEY()[i] = (gB->GetEY()[i]+gB2->GetEY()[i])/2.;
      }
      g->SetTitle("Adopted");
      gA->SetTitle(lepA.data());
      gB->SetTitle(lepB.data());
      ymin = setYmin(g,gA,gB);
      ymax = setYmax(g,gA,gB);
    }
  }
  if(VNMIN>-10) ymin=VNMIN;
  if(VNMAX>-10) ymax=VNMAX;
  g->SetName("g");
  gA->SetName("gA");
  gB->SetName("gB");
  return g;
}
