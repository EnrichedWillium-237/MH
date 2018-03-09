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
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFcASUB3_ampt;
TGraphErrors * N1HFdASUB3_ampt;
TGraphErrors * N1HFeASUB3_ampt;
TGraphErrors * N1HFfASUB3_ampt;
TGraphErrors * N1HFgASUB3_ampt;
TGraphErrors * N1HFcBSUB3_ampt;
TGraphErrors * N1HFdBSUB3_ampt;
TGraphErrors * N1HFeBSUB3_ampt;
TGraphErrors * N1HFfBSUB3_ampt;
TGraphErrors * N1HFgBSUB3_ampt;
TGraphErrors * N1HFcSUB3_ampt;
TGraphErrors * N1HFdSUB3_ampt;
TGraphErrors * N1HFeSUB3_ampt;
TGraphErrors * N1HFfSUB3_ampt;
TGraphErrors * N1HFgSUB3_ampt;

void plotAMPT() {

    fin = new TFile("data_AMPT.root");

    N1HFcASUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFcSUB3/-2.0_2.0/20_60/gintA");
    N1HFdASUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFdSUB3/-2.0_2.0/20_60/gintA");
    N1HFeASUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFeSUB3/-2.0_2.0/20_60/gintA");
    N1HFfASUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFfSUB3/-2.0_2.0/20_60/gintA");
    N1HFgASUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFgSUB3/-2.0_2.0/20_60/gintA");

    N1HFcBSUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFcSUB3/-2.0_2.0/20_60/gintB");
    N1HFdBSUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFdSUB3/-2.0_2.0/20_60/gintB");
    N1HFeBSUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFeSUB3/-2.0_2.0/20_60/gintB");
    N1HFfBSUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFfSUB3/-2.0_2.0/20_60/gintB");
    N1HFgBSUB3_ampt = (TGraphErrors *) fin->Get("PbPb_AMPT/N1HFgSUB3/-2.0_2.0/20_60/gintB");

    int num = N1HFcASUB3_ampt->GetN();
    double xA[30], yA[30], yAerr[30], xB[30], yB[30], yBerr[30], yAB[30], yABerr[30];
    for (int i = 0; i<num; i++) {
        N1HFcASUB3_ampt->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = N1HFcASUB3_ampt->GetErrorY(i);

        N1HFcBSUB3_ampt->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = N1HFcBSUB3_ampt->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] + yB[i]);
        yABerr[i] = 0.5*sqrt( yAerr[i]*yAerr[i] + yBerr[i]*yBerr[i] );
    }
    N1HFcSUB3_ampt = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        N1HFdASUB3_ampt->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = N1HFdASUB3_ampt->GetErrorY(i);

        N1HFdBSUB3_ampt->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = N1HFdBSUB3_ampt->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] + yB[i]);
        yABerr[i] = 0.5*sqrt( yAerr[i]*yAerr[i] + yBerr[i]*yBerr[i] );
    }
    N1HFdSUB3_ampt = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        N1HFeASUB3_ampt->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = N1HFeASUB3_ampt->GetErrorY(i);

        N1HFeBSUB3_ampt->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = N1HFeBSUB3_ampt->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] + yB[i]);
        yABerr[i] = 0.5*sqrt( yAerr[i]*yAerr[i] + yBerr[i]*yBerr[i] );
    }
    N1HFeSUB3_ampt = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        N1HFfASUB3_ampt->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = N1HFfASUB3_ampt->GetErrorY(i);

        N1HFfBSUB3_ampt->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = N1HFfBSUB3_ampt->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] + yB[i]);
        yABerr[i] = 0.5*sqrt( yAerr[i]*yAerr[i] + yBerr[i]*yBerr[i] );
    }
    N1HFfSUB3_ampt = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        N1HFgASUB3_ampt->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = N1HFgASUB3_ampt->GetErrorY(i);

        N1HFgBSUB3_ampt->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = N1HFgBSUB3_ampt->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] + yB[i]);
        yABerr[i] = 0.5*sqrt( yAerr[i]*yAerr[i] + yBerr[i]*yBerr[i] );
    }
    N1HFgSUB3_ampt = new TGraphErrors(num, xA, yAB, 0, yABerr);

    N1HFcSUB3_ampt->SetMarkerStyle(20);
    N1HFcSUB3_ampt->SetMarkerSize(1.3);
    N1HFcSUB3_ampt->SetMarkerColor(kBlack);
    N1HFcSUB3_ampt->SetLineColor(kBlack);
    N1HFcSUB3_ampt->Draw("same p");

    N1HFdSUB3_ampt->SetMarkerStyle(25);
    N1HFdSUB3_ampt->SetMarkerSize(1.2);
    N1HFdSUB3_ampt->SetMarkerColor(kRed);
    N1HFdSUB3_ampt->SetLineColor(kRed);
    N1HFdSUB3_ampt->Draw("same p");

    N1HFeSUB3_ampt->SetMarkerStyle(24);
    N1HFeSUB3_ampt->SetMarkerSize(1.3);
    N1HFeSUB3_ampt->SetMarkerColor(kGreen+2);
    N1HFeSUB3_ampt->SetLineColor(kGreen+2);
    N1HFeSUB3_ampt->Draw("same p");

    N1HFfSUB3_ampt->SetMarkerStyle(21);
    N1HFfSUB3_ampt->SetMarkerSize(1.2);
    N1HFfSUB3_ampt->SetMarkerColor(kBlue);
    N1HFfSUB3_ampt->SetLineColor(kBlue);
    N1HFfSUB3_ampt->Draw("same p");


    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.5, 2.5);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.018, 0.018);
    h1->Draw();
    N1HFcSUB3_ampt->Draw("same p");
    N1HFdSUB3_ampt->Draw("same p");
    N1HFeSUB3_ampt->Draw("same p");
    N1HFfSUB3_ampt->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.35, 0.83, 0.50, 0.87, "NDC");
    SetTPaveTxt(tx1, 26);
    tx1->AddText("#eta_{C} = 0");
    tx1->AddText("20 - 60%");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.55, 0.67, 0.86, 0.88);
    SetLegend(leg1, 22);
    leg1->AddEntry(N1HFcSUB3_ampt,"3.0 < |#eta_{EP}| < 3.5","p");
    leg1->AddEntry(N1HFdSUB3_ampt,"3.5 < |#eta_{EP}| < 4.0","p");
    leg1->AddEntry(N1HFeSUB3_ampt,"4.0 < |#eta_{EP}| < 4.5","p");
    leg1->AddEntry(N1HFfSUB3_ampt,"4.5 < |#eta_{EP}| < 5.0","p");
    leg1->Draw();

    c->Print("fig_AMPT_00.pdf","pdf");
    c->Print("fig_AMPT_00.png","png");

}
