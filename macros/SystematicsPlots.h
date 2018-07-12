TGraphErrors * ErrorPlot(string name, bool pt, bool ratio,  int order, TGraphErrors * g1, TGraphErrors * g2,TGraph *& gshade, TGraph * &gmin, TGraph * &gmax, int marker, int color) {
  int n = g1->GetN();
  double minx = 0;
  double maxx = 10;
  //  cout<<name<<endl;
  if(!pt) {
    minx = -3;
    maxx = 3; 
  } 
  double x[100];
  double y[100];
  double ey[100];
  double ymin[100];
  double ymax[100];
  int npts = 0;
  double xerr[100],yerr[100];
  int nerr = 0;
  for(int i = 0; i<n; i++) {
    bool skip = false;
    double y1 = g1->GetY()[i];
    double ey1 = g1->GetEY()[i];
    double y2 = g2->GetY()[i];
    double ey2 = g2->GetEY()[i];
    double val,err;
    if(ratio ) {
      if(y2!=0) {
	val = y1/y2;
      } else {
	val = 0;
	skip = true;
      }
      err = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(min(ey1,ey2),2)/y1/y2;
      if(err<=0) err=pow(ey1/y1,2);
      err = sqrt(err)*val;
    } else {
      val = y1-y2;
      err = sqrt(fabs(pow(ey1,2)-pow(ey2,2)));
      val*=1000.;
      err*=1000.;
    }
    if(!skip) {
      x[npts] = g1->GetX()[i];
      y[npts] = val;
      ey[npts] = err;
      ++npts;
    }
  }
  TGraphErrors * g = new TGraphErrors(npts,x,y,0,ey);
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(color);
  g->SetName(name.data());
  g->SetTitle(name.data());
  string fits[3]={"pol0","pol1","pol2"};
  TF1 * f0 = 0;
  TF1 * f1 = 0; 
  TF1 * f2 = 0;
  double f0min;
  double f0max;
  double f1min;
  double f1max;
  double f2min;
  double f2max;
  if(pt) {
    f0min = 0.3;
    f0max = 0.61;
    f1min = 0.5;
    f1max = 3.1;
    f2min = 2.5;
    f2max = 8.0;
  } else {
    f0min = -2.4;
    f0max = -1.2;
    f1min = -1.6;
    f1max = 1.6;
    f2min = 1.2;
    f2max = 2.4;
  }
  f0 = new TF1("f0",fits[order].data(),f0min,f0max);
  f1 = new TF1("f1",fits[order].data(),f1min,f1max);
  f2 = new TF1("f2",fits[order].data(),f2min,f2max);
  f0->SetLineColor(color);
  f1->SetLineColor(color);
  f2->SetLineColor(color);
  g->Fit(f0,"qR");
  g->Fit(f1,"qR+");
  g->Fit(f2,"qR+");

  double xs[100],ymins[100],ymaxs[100];
  for(int i = 0; i<n; i++) {
    double xv = g1->GetX()[i];
    xs[i] = xv;
    double ymin,ymax,y0;
    if(xv<f1min) {
      y0 = f0->Eval(xv);
      ymin = f0->Eval(xv)-f0->GetParError(0);
      ymax = f0->Eval(xv)+f0->GetParError(0);
      //cout<<"1: "<<xv<<"\t"<<ymin<<"\t"<<ymax<<endl;
    } else if ( xv < f0max) {
      y0 = (f0->Eval(xv) + f1->Eval(xv) )/2.;
      ymin = (f0->Eval(xv) + f1->Eval(xv) - f0->GetParError(0) - f1->GetParError(0) )/2.;
      ymax = (f0->Eval(xv) + f1->Eval(xv) + f0->GetParError(0) + f1->GetParError(0) )/2.;
      //cout<<"2: "<<xv<<"\t"<<ymin<<"\t"<<ymax<<endl;
    } else if ( xv < f2min) {
      y0 = f1->Eval(xv) ;
      ymin = f1->Eval(xv)-f1->GetParError(0) ;
      ymax = f1->Eval(xv)+f1->GetParError(0) ;
      //cout<<"3: "<<xv<<"\t"<<ymin<<"\t"<<ymax<<endl;
    } else if ( xv < f1max) { 
      y0 = (f1->Eval(xv) + f2->Eval(xv) )/2.;
      ymin = (f1->Eval(xv) + f2->Eval(xv) - f1->GetParError(0) - f2->GetParError(0) )/2.;
      ymax = (f1->Eval(xv) + f2->Eval(xv) + f1->GetParError(0) + f2->GetParError(0) )/2.;
      //cout<<"4: "<<xv<<"\t"<<ymin<<"\t"<<ymax<<endl;
   } else if ( xv >= f1max) {
      y0 = f2->Eval(xv);
      ymin = f2->Eval(xv)-f1->GetParError(0) ;
      ymax = f2->Eval(xv)+f1->GetParError(0) ;
      //cout<<"5: "<<xv<<"\t"<<ymin<<"\t"<<ymax<<endl;
    }
      if(ratio) {
	y0=y0-1;
	ymin=ymin-1;
	ymax=ymax-1;
      }
    if(y0<0) {
      ymin = -ymin;
      ymax = -ymax;
    }
    if(ratio) {
      ymin*=100.;
      ymax*=100.;
    }
    ymins[i] = ymin;
    ymaxs[i] = ymax;
  }
  gmin = new TGraph(n,xs,ymins);
  gmax = new TGraph(n,xs,ymaxs);
  gshade = new TGraph(2*n);
  for(int i = 0; i<n; i++) {
    gshade->SetPoint(i,xs[i],ymaxs[i]);
    gshade->SetPoint(n+i,xs[n-i-1],ymins[n-i-1]); 
  }
  gshade->SetFillStyle(3013);
  gshade->SetFillColorAlpha(color,0.5);
  gmin->SetLineColorAlpha(color,0.5);
  gmax->SetLineColorAlpha(color,0.5);
  string gshadeN = name+"_gshade";
  string gminN = name+"_gmin";
  string gmaxN = name+"_gmax";
  gshade->SetName(gshadeN.data());
  gshade->SetTitle(gshadeN.data());
  gmin->SetName(gminN.data());
  gmin->SetTitle(gminN.data());
  gmax->SetName(gmaxN.data());
  gmax->SetTitle(gmaxN.data());
  return g;
}


