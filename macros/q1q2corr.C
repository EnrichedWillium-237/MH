# include "TCanvas.h"
# include "TFile.h"
# include "TGraph.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TPaveText.h"
# include <iostream>

#include "src/HiEvtPlaneList.h"

TFile * tf = new TFile("../MH.root","read");
// TFile * tf = new TFile("../PbPb_AMPT.root","read");
// TBrowser br;
using namespace hi;

void q1q2corr( string cent="25_30" ) {
    TH2D * res12ep = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/resep12",cent.data()));
    TH2D * res12cnt = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/rescnt12",cent.data()));
    res12ep->Divide(res12cnt);
    //res12ep->Draw();
    // TH1D * prjp = res12ep->ProjectionX("prjp",HFp2g-HFm2+1,HFp2g-HFm2+1);
    // TH1D * prjm = res12ep->ProjectionX("prjm",HFm2g-HFm2+1,HFm2g-HFm2+1);
    TH1D * prjp = res12ep->ProjectionX("prjp",trackp222-HFm2+1,trackp222-HFm2+1);
    TH1D * prjm = res12ep->ProjectionX("prjm",trackm222-HFm2+1,trackm222-HFm2+1);
    TCanvas * c = new TCanvas(Form("c_%s",cent.data()), Form("c_%s",cent.data()), 620, 600);
    c->cd();
    //prj->Draw();
    double xp[12];
    double yp[12];
    double xm[12];
    double ym[12];
    for (int i = 0; i<12; i++) {
        xp[i] = -2.2+i*0.4;
        yp[i] = prjp->GetBinContent(trackm122+i+1);
        xm[i] = -2.2+i*0.4;
        ym[i] = prjm->GetBinContent(trackm122+i+1);
    }
    TGraph * gp = new TGraph(12,xp,yp);
    gp->SetMarkerStyle(20);
    gp->SetMarkerSize(1.2);
    gp->SetMarkerColor(kBlue);
    gp->RemovePoint(0);
    gp->RemovePoint(gp->GetN()-1);
    TGraph * gm = new TGraph(12, xm, ym);
    gm->SetMarkerStyle(20);
    gm->SetMarkerSize(1.2);
    gm->SetMarkerColor(kRed);
    gm->RemovePoint(0);
    gm->RemovePoint(gm->GetN()-1);
    TH1D * h = new TH1D("h", "h", 100, -2.5, 2.5);
    h->SetMinimum(0);
    h->SetMaximum(0.06);
    h->SetXTitle("#eta");
    h->SetYTitle("Q_{1}^{2}Q_{2}^{*}");
    h->Draw();
    gp->Draw("p");
    gm->Draw("p");
    TLegend * leg = new TLegend(0.2, 0.2, 0.4, 0.4);
    leg->SetBorderSize(0);
    leg->SetHeader(Form("%s",cent.data()));
    // leg->AddEntry(gp,"Q_{2} (4<#eta<5)","lp");
    // leg->AddEntry(gm,"Q_{2} (-5<#eta<-4)","lp");
    leg->AddEntry(gp,"Q_{2} (2<#eta<2.4)","lp");
    leg->AddEntry(gm,"Q_{2} (-2.4<#eta<-2)","lp");
    leg->Draw();
    c->Print(Form("q1q2/q1q2corr_%s.pdf",cent.data()),"pdf");
    c->Print(Form("q1q2/q1q2corr_%s.png",cent.data()),"png");
    //    c->Print(Form("q1q2/q1q2corr_AMPT_%s.pdf",cent.data()),"pdf");
    //    c->Print(Form("q1q2/q1q2corr_AMPT_%s.png",cent.data()),"png");
}
