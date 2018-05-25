TGraphErrors * N112( int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors * &gintA, TGraphErrors * &gintB, double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe ) {
    fin = new TFile(rootFile.data(),"r");
    TGraphErrors * g2;
    TGraphErrors * gA2;
    TGraphErrors * gB2;
    TGraphErrors * gtmp;
    double vint2 = 0;
    double vinte2 = 0;
    double vintA2 = 0;
    double vintAe2 = 0;
    double vintB2 = 0;
    double vintBe2 = 0;
    int epindx = -1;
    Decor = false;
    //
    // Start with eta distribution
    //
    int ioff = 0;
    for (int i = ioff; i<12-ioff; i++) {
        double EtaMin = -2.4 + 0.4*i;
        double EtaMax = EtaMin+0.4;
        if (fabs(EtaMin)<0.001) EtaMin = 0.;
        if (fabs(EtaMax)<0.001) EtaMax = 0.;
        gtmp = GetVNPt( replay, bin, epindx, EtaMin, EtaMax, gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false );
        gint->GetY()[i-ioff] = vint;
        gint->GetEY()[i-ioff] = vinte;

        gint->GetX()[i-ioff] = (EtaMin+EtaMax)/2.;
        gintA->GetX()[i-ioff] = (EtaMin+EtaMax)/2.;
        gintB->GetX()[i-ioff] = (EtaMin+EtaMax)/2.;

        if (replay==N112ASUB2||replay==N112CSUB2||replay==N112ESUB2||replay==N112GSUB2||replay==N112HSUB2||replay==N112ASUB3||replay==N112CSUB3||replay==N112ESUB3||replay==N112GSUB3||replay==N112HSUB3) {
            if (EtaMin<0) {
	            gint->GetY()[i-ioff] = vintA;
	            gint->GetEY()[i-ioff] = vintAe;
            } else {
	            gint->GetY()[i-ioff] = vintB;
	            gint->GetEY()[i-ioff] = vintBe;
            }
        } else {
            if (EtaMin<0) {
	            gint->GetY()[i-ioff] = vintB;
	            gint->GetEY()[i-ioff] = vintBe;
            } else {
	            gint->GetY()[i-ioff] = vintA;
	            gint->GetEY()[i-ioff] = vintAe;
            }
        }
        gintA->GetY()[i-ioff] = vintA;
        gintA->GetEY()[i-ioff] = vintAe;
        gintB->GetY()[i-ioff] = vintB;
        gintB->GetEY()[i-ioff] = vintBe;
    }
    if (ioff>0) for (int i = 11-ioff; i<12; i++) {gint->GetX()[i]=10.;gintA->GetX()[i]=10; gintB->GetX()[i]=10;}
    gint->SetName("gint");
    gintA->SetName("gintA");
    gintB->SetName("gintB");
    gint->SetTitle("Adopted");
    if (replay==N112ASUB2 || replay==N112ASUB3) {
        gintA->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-0.8<#eta<0.8) ");
        gintB->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-0.8<#eta<0.8)");
    }
    if (replay==N112BSUB2 || replay==N112BSUB3) {
        gintB->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-0.8<#eta<0.8) ");
        gintA->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-0.8<#eta<0.8)");
    }
    if (replay==N112CSUB2 || replay==N112CSUB3) {
        gintA->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-0.8<#eta<0.8) ");
        gintB->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-0.8<#eta<0.8)");
    }
    if (replay==N112DSUB2 || replay==N112DSUB3) {
        gintB->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-0.8<#eta<0.8) ");
        gintA->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-0.8<#eta<0.8)");
    }
    if (replay==N112ESUB2 || replay==N112ESUB3) {
        gintA->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (3.0<#eta<3.5) ");
        gintB->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (3.0<#eta<3.5)");
    }
    if (replay==N112FSUB2 || replay==N112FSUB3) {
        gintB->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-3.5<#eta<-3.0) ");
        gintA->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-3.5<#eta<-3.0)");
    }
    if (replay==N112GSUB2 || replay==N112GSUB3) {
        gintA->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-3.5<#eta<-3.0) ");
        gintB->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-3.5<#eta<-3.0)");
    }
    if (replay==N112HSUB2 || replay==N112HSUB3) {
        gintB->SetTitle("#Psi_{1} (4.0<#eta<5.0)  #Psi_{2} (-3.5<#eta<-3.0) ");
        gintA->SetTitle("#Psi_{1} (-5.0<#eta<-4.0)  #Psi_{2} (-3.5<#eta<-3.0)");
    }
    //
    // Now do requested calculation
    //
    g = GetVNPt( replay, bin, epindx, eMin, eMax, gA, gB, gSpec, vint, vinte, vintA2, vintAe2, vintB2, vintBe2, false );
    fin->Close();
    ymin = setYmin(g,gA,gB);
    ymax = setYmax(g,gA,gB);
    g->SetName("g");
    gA->SetName("gA");
    gB->SetName("gB");
    return g;
}
