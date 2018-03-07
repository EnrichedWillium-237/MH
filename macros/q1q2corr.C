#include "src/HiEvtPlaneList.h"
TFile * tf = new TFile("../MH_tight2.root","read");
TBrowser br;
using namespace hi;
void q1q2corr(string cent="25_30"){
  TH2D * res12ep = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/resep12",cent.data()));
  TH2D * res12cnt = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/rescnt12",cent.data()));
  res12ep->Divide(res12cnt);
  //res12ep->Draw();
  TH1D * prjp = res12ep->ProjectionX("prjp",HFp2g-HFm2+1,HFp2g-HFm2+1);
  TH1D * prjm = res12ep->ProjectionX("prjm",HFm2g-HFm2+1,HFm2g-HFm2+1);
  TCanvas * c = new TCanvas(Form("c_%s",cent.data()),Form("c_%s",cent.data()),1000,800);
  c->cd();
  //prj->Draw();
  double xp[12];
  double yp[12];
  double xm[12];
  double ym[12];
  for(int i = 0; i<12; i++) {
    xp[i] = -2.2+i*0.4;
    yp[i] = prjp->GetBinContent(trackm122+i+1);
    xm[i] = -2.2+i*0.4;
    ym[i] = prjm->GetBinContent(trackm122+i+1);
  }
  TGraph * gp = new TGraph(12,xp,yp);
  gp->SetMarkerStyle(20);
  gp->SetMarkerColor(kBlue);
  TGraph * gm = new TGraph(12,xm,ym);
  gm->SetMarkerStyle(20);
  gm->SetMarkerColor(kRed);
  TH1D * h = new TH1D("h","h",100,-3,3);
  h->SetMinimum(0);
  h->SetMaximum(0.06);
  h->SetXTitle("#eta");
  h->SetYTitle("Q_{1}^{2}Q_{2}^{*}");
  h->Draw();
  gp->Draw("p");
  gm->Draw("p");
  TLegend * leg = new TLegend(0.2,0.2,0.4,0.4);
  leg->SetBorderSize(0);
  leg->AddEntry(gp,"Q_{2} (4<#eta<5)","lp");
  leg->AddEntry(gm,"Q_{2} (-5<#eta<-4)","lp");
  leg->Draw();
  c->Print(Form("q1q2/q1q2corr_%s.pdf",cent.data()),"pdf");
}
