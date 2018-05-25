#include "src/HiEvtPlaneList.h"
using namespace hi;
TFile * fin = new TFile("../MH.root");
bool exists = false;
TH2D * resep1;
TH2D * rescnt1;
TH2D * resep2;
TH2D * rescnt2;
TH2D * resep12;
TH2D * rescnt12;

double GetCorrelation(string cent="25_30", int ep1 = HFp1, int ep2 = HFp1){
  if(!exists) {
    resep1  = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resep1",cent.data()));
    rescnt1 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/rescnt1",cent.data()));
    resep1->Divide(rescnt1);
    resep2  = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resep2",cent.data()));				  
    rescnt2 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/rescnt2",cent.data()));
    resep2->Divide(rescnt2);
    resep12  = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resep12",cent.data()));				  
    rescnt12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/rescnt12",cent.data()));
    resep12->Divide(rescnt12);
    exists=true;
  }
  int iorder1 = EPOrder[ep1];
  int iorder2 = EPOrder[ep2];
  int xind = -1;
  int yind = -1;

  if(iorder1==1) {
    xind = ep1-HFm1+1;
  }else if(iorder1==2) {
    xind = ep1-HFm2+1;
  }
  if(iorder2==1) {
    yind = ep2-HFm1+1;
  }else if(iorder2==2) {
    yind = ep2-HFm2+1;
  }
  double corr = 0;
  double err = 0;
  if(iorder1==1 && iorder2==1) {
    int x = min(xind,yind);
    int y = max(xind,yind);
    corr = resep1->GetBinContent(x,y);
    err = resep1->GetBinError(x,y);
  }
  if(iorder1==2 && iorder2==2) {
    int x = min(xind,yind);
    int y = max(xind,yind);
    corr = resep12->GetBinContent(x,y);
    err = resep12->GetBinError(x,y);
  }
  if(iorder1==1 && iorder2==2) {
    corr = resep12->GetBinContent(xind,yind);
    err = resep12->GetBinError(xind,yind);
  }
  cout<<EPNames[ep1]<<"\t"<<EPNames[ep2]<<"\t"<<corr<<"\t"<<err<<endl;
  return corr;
}
