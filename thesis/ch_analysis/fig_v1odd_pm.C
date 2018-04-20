# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGaxis.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include <iostream>

using namespace std;

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

TFile * fin;
TFile * finA;
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFgSUB2;
TGraphErrors * N1HFm1gSUB2;
TGraphErrors * N1HFp1gSUB2;
TGraphErrors * N1HFgSUB2A;
TGraphErrors * N1HFm1gSUB2A;
TGraphErrors * N1HFp1gSUB2A;

void fig_v1odd_pm() {

    fin = new TFile("../../data/MH_hists_master.root");

    N1HFgSUB2 = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gint");
    N1HFgSUB2->SetMarkerStyle(24);
    N1HFgSUB2->SetMarkerSize(1.3);
    N1HFgSUB2->SetMarkerColor(kBlack);
    N1HFgSUB2->SetLineColor(kBlack);
    N1HFgSUB2->RemovePoint(0);
    N1HFgSUB2->RemovePoint(N1HFgSUB2->GetN() - 1);

    N1HFm1gSUB2 = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gintB");
    N1HFm1gSUB2->SetMarkerStyle(25);
    N1HFm1gSUB2->SetMarkerSize(1.2);
    N1HFm1gSUB2->SetMarkerColor(kRed);
    N1HFm1gSUB2->SetLineColor(kRed);
    N1HFm1gSUB2->RemovePoint(0);
    N1HFm1gSUB2->RemovePoint(N1HFm1gSUB2->GetN() - 1);

    N1HFp1gSUB2 = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gintA");
    N1HFp1gSUB2->SetMarkerStyle(24);
    N1HFp1gSUB2->SetMarkerSize(1.3);
    N1HFp1gSUB2->SetMarkerColor(kBlue);
    N1HFp1gSUB2->SetLineColor(kBlue);
    N1HFp1gSUB2->RemovePoint(0);
    N1HFp1gSUB2->RemovePoint(N1HFp1gSUB2->GetN() - 1);


    TCanvas * c = new TCanvas("c", "c", 1200, 600);
    c->Divide(2, 1);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.6, 2.6);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}");
    h1->GetYaxis()->SetDecimals();
    h1->GetYaxis()->SetNdivisions(509);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.70);
    h1->GetYaxis()->SetRangeUser(-0.08, 0.01);
    h1->Draw();
    N1HFm1gSUB2->Draw("same p");
    N1HFp1gSUB2->Draw("same p");

    TPaveText * tx0_1 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0_1, 22);
    tx0_1->AddText("#bf{CMS},  #eta_{C} = 0");
    tx0_1->Draw();

    TLegend * leg1_1 = new TLegend(0.22, 0.20, 0.53, 0.37);
    SetLegend(leg1_1, 22);
    leg1_1->SetHeader("20 - 60%");
    leg1_1->AddEntry(N1HFp1gSUB2,"v_{1} {HF+}","p");
    leg1_1->AddEntry(N1HFm1gSUB2,"v_{1} {HF-}","p");
    leg1_1->Draw();

    TPad * pad2 = (TPad *) c->cd(2);
    pad2->SetTopMargin(0.08);
    pad2->SetRightMargin(0.03);
    h2 = (TH1D *) h1->Clone("h2");
    h2->GetYaxis()->SetRangeUser(-0.02, 0.02);
    h2->Draw();
    N1HFgSUB2->Draw("same p");

    TPaveText * tx0_2 = new TPaveText(0.166, 0.927, 0.407, 0.971, "NDC");
    SetTPaveTxt(tx0_2, 22);
    tx0_2->AddText("PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0_2->Draw();

    TPaveText * tx1_2 = new TPaveText(0.23, 0.23, 0.51, 0.34, "NDC");
    SetTPaveTxt(tx1_2, 26);
    tx1_2->AddText("#frac{1}{2} (v_{1}{HF+} - v_{1}{HF-})");
    tx1_2->Draw();

    c->Print("../fig_v1odd_pm.pdf","pdf");

}
