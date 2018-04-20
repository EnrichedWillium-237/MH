# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include <iostream>

#include "HiEvtPlaneList.h"

using namespace std;
using namespace hi;

static const int ncbins = 11;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const double centbins[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};

void SetTPaveTxt( TPaveText * txtemplate, int txtsize ) {
  txtemplate->SetFillColor(0);
  txtemplate->SetBorderSize(0);
  txtemplate->SetTextFont(43);
  txtemplate->SetTextAlign(12);
  txtemplate->SetTextSize(txtsize);
}

void SetLegend( TLegend * legtemplate, int legsize ) {
  legtemplate->SetFillColor(0);
  legtemplate->SetBorderSize(0);
  legtemplate->SetTextFont(43);
  legtemplate->SetTextSize(legsize);
}

TFile * finRes;
TH1D * h;

TH2D * resep1[ncbins];
TH2D * rescnt1[ncbins];
TH2D * resep12[ncbins];
TH2D * rescnt12[ncbins];
TH2D * resep2[ncbins];
TH2D * rescnt2[ncbins];

TH1D * resHF1gSUB2;
TH1D * resHF1gSUB3;
TH1D * restrack122SUB2;
TH1D * resHF2SUB2;
TH1D * resHF2SUB3;

void fig_ResEP() {

    finRes = new TFile("../../data/Resolutions.root");

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    resHF1gSUB2 = new TH1D("resHF1gSUB2", "", ncbins, centbins);
    resHF1gSUB3 = (TH1D *) resHF1gSUB2->Clone("resHF1gSUB3");
    restrack122SUB2 = (TH1D *) resHF1gSUB2->Clone("restrack122SUB2");
    resHF2SUB2 = (TH1D *) resHF1gSUB2->Clone("resHF2SUB2");
    resHF2SUB3 = (TH1D *) resHF1gSUB2->Clone("resHF2SUB3");

    resHF1gSUB2->SetMarkerStyle(21);
    resHF1gSUB2->SetMarkerSize(1.2);
    resHF1gSUB2->SetMarkerColor(kBlue);
    resHF1gSUB2->SetLineColor(kBlue);

    resHF1gSUB3->SetMarkerStyle(25);
    resHF1gSUB3->SetMarkerSize(1.2);
    resHF1gSUB3->SetMarkerColor(kBlack);
    resHF1gSUB3->SetLineColor(kBlack);

    resHF2SUB2->SetMarkerStyle(20);
    resHF2SUB2->SetMarkerSize(1.3);
    resHF2SUB2->SetMarkerColor(kRed);
    resHF2SUB2->SetLineColor(kRed);

    resHF2SUB3->SetMarkerStyle(24);
    resHF2SUB3->SetMarkerSize(1.2);
    resHF2SUB3->SetMarkerColor(kBlack);
    resHF2SUB3->SetLineColor(kBlack);

    double QAB = 0;
    double QAC = 0;
    double QBC = 0;
    double val = 0;
    double err = 0;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        resep1[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/resep1",cmin[cbin],cmax[cbin]));
        rescnt1[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/rescnt1",cmin[cbin],cmax[cbin]));
        resep12[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/resep12",cmin[cbin],cmax[cbin]));
        rescnt12[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/rescnt12",cmin[cbin],cmax[cbin]));
        resep2[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/resep2",cmin[cbin],cmax[cbin]));
        rescnt2[cbin] = (TH2D *) finRes->Get(Form("default/%d_%d/rescnt2",cmin[cbin],cmax[cbin]));

        resep1[cbin]->Divide(rescnt1[cbin]);
        resep12[cbin]->Divide(rescnt12[cbin]);
        resep2[cbin]->Divide(rescnt2[cbin]);

        QAB = resep1[cbin]->GetBinContent(HFm1g+1, HFp1g+1);
        val = sqrt( fabs(QAB) );
        err = resep1[cbin]->GetBinError(HFm1g+1, HFp1g+1);
        err = val * 0.5*err/fabs(QAB);
        err = 0.0005;
        resHF1gSUB2->SetBinContent(cbin+1, val);
        resHF1gSUB2->SetBinError(cbin+1, err);

        QAB = resep1[cbin]->GetBinContent(HFm1g+1, HFp1g+1);
        QAC = resep1[cbin]->GetBinContent(trackmid1+1, HFm1g+1);
        QBC = resep1[cbin]->GetBinContent(trackmid1+1, HFp1g+1);
        val = sqrt( fabs(QAB*QAC/QBC) );
        resHF1gSUB3->SetBinContent(cbin+1, val);
        resHF1gSUB3->SetBinError(cbin+1, err);

        QAB = resep2[cbin]->GetBinContent(HFm2-HFm2+1, HFp2-HFm2+1);
        val = sqrt( fabs(QAB) );
        resHF2SUB2->SetBinContent(cbin+1, val);
        resHF2SUB2->SetBinError(cbin+1, err);

        QAB = resep2[cbin]->GetBinContent(HFm2-HFm2+1, HFp2-HFm2+1);
        QAC = resep2[cbin]->GetBinContent(HFm2-HFm2+1, trackmid2-HFm2+1);
        QBC = resep2[cbin]->GetBinContent(HFp2-HFm2+1, trackmid2-HFm2+1);
        val = sqrt( fabs(QAB*QAC/QBC) );
        resHF2SUB3->SetBinContent(cbin+1, val);
        resHF2SUB3->SetBinError(cbin+1, err);
    }

    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad = (TPad *) c->cd();
    pad->SetTopMargin(0.08);
    pad->SetLeftMargin(0.18);
    h = new TH1D("h", "", 100, 0, 70);
    h->SetXTitle("Centrality (%)");
    // h->SetYTitle("<cos[n(#Psi_{n} - #Psi_{RP})]>");
    h->SetYTitle("Resolution Correction");
    h->GetYaxis()->SetDecimals();
    h->GetXaxis()->CenterTitle();
    h->GetYaxis()->CenterTitle();
    h->GetXaxis()->SetTitleOffset(1.15);
    h->GetYaxis()->SetTitleOffset(1.50);
    h->GetYaxis()->SetRangeUser(0, 1);
    h->Draw();
    resHF1gSUB2->Draw("same");
    resHF1gSUB3->Draw("same");
    resHF2SUB2->Draw("same");
    resHF2SUB3->Draw("same");

    TPaveText * tx0 = new TPaveText(0.178, 0.933, 0.420, 0.978, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TLegend * leg = new TLegend(0.35, 0.39, 0.59, 0.61);
    SetLegend(leg, 22);
    leg->AddEntry(resHF1gSUB2," Res{#Psi_{1}} 2-subevent","p");
    leg->AddEntry(resHF1gSUB3," Res{#Psi_{1}} 3-subevent","p");
    leg->AddEntry(resHF2SUB2," Res{#Psi_{2}} 2-subevent","p");
    leg->AddEntry(resHF2SUB3," Res{#Psi_{2}} 3-subevent","p");
    leg->Draw();

    c->Print("../fig_ResEP.pdf","pdf");
    // c->Print("../fig_ResEP.png","png");


}
