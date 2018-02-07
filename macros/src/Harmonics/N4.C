TGraphErrors * N4(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB, double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe){
  int epindx = HFp4;
  TGraphErrors * gtmp;
  //
  // Start with eta distribution
  //
  for(int i = 0; i<12; i++) {
    double EtaMin = -2.4 + 0.4*i;
    double EtaMax = EtaMin+0.4;
    if(fabs(EtaMin)<0.001) EtaMin = 0.;
    if(fabs(EtaMax)<0.001) EtaMax = 0.;
    gtmp = GetVNPt(replay,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
    gint->GetY()[i] = (vintA+vintB)/2.;
    gint->GetEY()[i] = (vintAe+vintBe)/2.;
    gintA->GetY()[i]=vintA;
    gintA->GetEY()[i]=vintAe;
    gintB->GetY()[i]=vintB;
    gintB->GetEY()[i]=vintBe;
  }
  gint->SetTitle("HF^{+} + HF^{-}");
  gintA->SetTitle("HF^{+}");
  gintB->SetTitle("HF^{-}");
  if(sTrackReaction == pPb) {
    gint->SetTitle("p-side + Pb-side");
    gintA->SetTitle("p-side");
    gintB->SetTitle("Pb-side");
    if(sTrackOrientation==Type_pPb) {
      gintA->SetTitle("Pb-side");
      gintB->SetTitle("p-side");
    }
  }
  gint->SetName("gint");
  gintA->SetName("gintA");
  gintB->SetName("gintB");
  //
  // Now do requested calculation
  
  g = GetVNPt(replay,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte, vintA, vintAe, vintB, vintBe, false);
  ymin = setYmin(g,gA,gB);
  ymax = setYmax(g,gA,gB);
  outint = fopen(soutint.data(),"a+");
  fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
  fclose(outint);
  cout<<"Integral: "<<eMin<<"\t"<<eMax<<"\t"<<vint<<endl;
  g->SetTitle("HF^{+} + HF^{-}");
  gA->SetTitle("HF^{+}");
  gB->SetTitle("HF^{-}");
  if(sTrackReaction == pPb) {
    g->SetTitle("p-side + Pb-side");
    gA->SetTitle("p-side");
    gB->SetTitle("Pb-side");
    if(sTrackOrientation==Type_pPb) {
      gA->SetTitle("Pb-side");
      gB->SetTitle("p-side");
    }
  }
  g->SetName("g");
  gA->SetName("gA");
  gB->SetName("gB");
  return g;
}
