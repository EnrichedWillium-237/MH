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
TH1D * h0;
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFm1gSUB2;
TGraphErrors * N1HFp1gSUB2;
TGraphErrors * N1HFm1gSUB3;
TGraphErrors * N1HFp1gSUB3;

TGraphErrors * N1HFcSUB2;
TGraphErrors * N1HFdSUB2;
TGraphErrors * N1HFeSUB2;
TGraphErrors * N1HFfSUB2;
TGraphErrors * N1HFgSUB2;

TGraphErrors * N1HFcSUB3;
TGraphErrors * N1HFdSUB3;
TGraphErrors * N1HFeSUB3;
TGraphErrors * N1HFfSUB3;
TGraphErrors * N1HFgSUB3;

void figHF23SUB() {

    fin = new TFile("data_figHF23SUB.root");

    N1HFm1gSUB2 = (TGraphErrors *) fin->Get("default/N1HFm1gSUB2/-2.0_2.0/20_60/gintA");
    N1HFm1gSUB2->SetMarkerStyle(24);
    N1HFm1gSUB2->SetMarkerSize(1.4);
    N1HFm1gSUB2->SetMarkerColor(kRed);
    N1HFm1gSUB2->SetLineColor(kRed);
    N1HFm1gSUB2->RemovePoint(0);
    N1HFm1gSUB2->RemovePoint(N1HFm1gSUB2->GetN()-1);

    N1HFp1gSUB2 = (TGraphErrors *) fin->Get("default/N1HFp1gSUB2/-2.0_2.0/20_60/gintA");
    N1HFp1gSUB2->SetMarkerStyle(25);
    N1HFp1gSUB2->SetMarkerSize(1.3);
    N1HFp1gSUB2->SetMarkerColor(kBlue);
    N1HFp1gSUB2->SetLineColor(kBlue);
    N1HFp1gSUB2->RemovePoint(0);
    N1HFp1gSUB2->RemovePoint(N1HFp1gSUB2->GetN()-1);

    N1HFm1gSUB3 = (TGraphErrors *) fin->Get("default/N1HFm1gSUB3/-2.0_2.0/20_60/gintA");
    N1HFm1gSUB3->SetMarkerStyle(20);
    N1HFm1gSUB3->SetMarkerSize(1.4);
    N1HFm1gSUB3->SetMarkerColor(kRed);
    N1HFm1gSUB3->SetLineColor(kRed);
    N1HFm1gSUB3->RemovePoint(0);
    N1HFm1gSUB3->RemovePoint(N1HFm1gSUB3->GetN()-1);

    N1HFp1gSUB3 = (TGraphErrors *) fin->Get("default/N1HFp1gSUB3/-2.0_2.0/20_60/gintA");
    N1HFp1gSUB3->SetMarkerStyle(21);
    N1HFp1gSUB3->SetMarkerSize(1.3);
    N1HFp1gSUB3->SetMarkerColor(kBlue);
    N1HFp1gSUB3->SetLineColor(kBlue);
    N1HFp1gSUB3->RemovePoint(0);
    N1HFp1gSUB3->RemovePoint(N1HFp1gSUB3->GetN()-1);

    TCanvas * c0 = new TCanvas("c0", "c0", 620, 600);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetTopMargin(0.08);
    pad0->SetLeftMargin(0.18);
    h0 = new TH1D("h0", "", 100, -2.5, 2.5);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}");
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(509);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleOffset(1.15);
    h0->GetYaxis()->SetTitleOffset(1.65);
    h0->GetYaxis()->SetRangeUser(-0.05, 0.00);
    h0->Draw();
    N1HFm1gSUB2->Draw("same p");
    N1HFp1gSUB2->Draw("same p");
    N1HFm1gSUB3->Draw("same p");
    N1HFp1gSUB3->Draw("same p");

    TPaveText * tx00 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx00, 20);
    tx00->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx00->Draw();

    TPaveText * tx01 = new TPaveText(0.22, 0.77, 0.37, 0.89, "NDC");
    SetTPaveTxt(tx01, 24);
    tx01->AddText("4.0 < |#eta_{EP}| < 5.0");
    tx01->AddText("20 - 60%");
    tx01->Draw();

    TLegend * leg0 = new TLegend(0.63, 0.76, 0.87, 0.89);
    SetLegend(leg0, 20);
    leg0->SetNColumns(2);
    leg0->SetHeader("2SUB   3SUB");
    leg0->AddEntry(N1HFm1gSUB2,"             ","p");
    leg0->AddEntry(N1HFm1gSUB3,"        HF-","p");
    leg0->AddEntry(N1HFp1gSUB2,"             ","p");
    leg0->AddEntry(N1HFp1gSUB3,"        HF+","p");
    leg0->Draw();

    c0->Print("fig0.pdf","pdf");
    // c0->Print("../figures/fig0.png","png");


    //--  --//
    N1HFcSUB2 = (TGraphErrors *) fin->Get("default/N1HFcSUB2/-2.0_2.0/20_60/gint");
    N1HFcSUB2->SetMarkerStyle(24);
    N1HFcSUB2->SetMarkerSize(1.4);
    N1HFcSUB2->SetMarkerColor(kBlack);
    N1HFcSUB2->SetLineColor(kBlack);

    N1HFdSUB2 = (TGraphErrors *) fin->Get("default/N1HFdSUB2/-2.0_2.0/20_60/gint");
    N1HFdSUB2->SetMarkerStyle(27);
    N1HFdSUB2->SetMarkerSize(2.0);
    N1HFdSUB2->SetMarkerColor(kRed);
    N1HFdSUB2->SetLineColor(kRed);

    N1HFeSUB2 = (TGraphErrors *) fin->Get("default/N1HFeSUB2/-2.0_2.0/20_60/gint");
    N1HFeSUB2->SetMarkerStyle(28);
    N1HFeSUB2->SetMarkerSize(1.8);
    N1HFeSUB2->SetMarkerColor(kGreen+2);
    N1HFeSUB2->SetLineColor(kGreen+2);

    N1HFfSUB2 = (TGraphErrors *) fin->Get("default/N1HFfSUB2/-2.0_2.0/20_60/gint");
    N1HFfSUB2->SetMarkerStyle(25);
    N1HFfSUB2->SetMarkerSize(1.3);
    N1HFfSUB2->SetMarkerColor(kBlue);
    N1HFfSUB2->SetLineColor(kBlue);

    N1HFcSUB3 = (TGraphErrors *) fin->Get("default/N1HFcSUB3/-2.0_2.0/20_60/gint");
    N1HFcSUB3->SetMarkerStyle(20);
    N1HFcSUB3->SetMarkerSize(1.4);
    N1HFcSUB3->SetMarkerColor(kBlack);
    N1HFcSUB3->SetLineColor(kBlack);

    N1HFdSUB3 = (TGraphErrors *) fin->Get("default/N1HFdSUB3/-2.0_2.0/20_60/gint");
    N1HFdSUB3->SetMarkerStyle(33);
    N1HFdSUB3->SetMarkerSize(2.0);
    N1HFdSUB3->SetMarkerColor(kRed);
    N1HFdSUB3->SetLineColor(kRed);

    N1HFeSUB3 = (TGraphErrors *) fin->Get("default/N1HFeSUB3/-2.0_2.0/20_60/gint");
    N1HFeSUB3->SetMarkerStyle(34);
    N1HFeSUB3->SetMarkerSize(1.8);
    N1HFeSUB3->SetMarkerColor(kGreen+2);
    N1HFeSUB3->SetLineColor(kGreen+2);

    N1HFfSUB3 = (TGraphErrors *) fin->Get("default/N1HFfSUB3/-2.0_2.0/20_60/gint");
    N1HFfSUB3->SetMarkerStyle(21);
    N1HFfSUB3->SetMarkerSize(1.3);
    N1HFfSUB3->SetMarkerColor(kBlue);
    N1HFfSUB3->SetLineColor(kBlue);

    TCanvas * c1 = new TCanvas("c1", "c1", 620, 600);
    TPad * pad1 = (TPad *) c1->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.5, 2.5);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}");
    h1->GetYaxis()->SetDecimals();
    h1->GetYaxis()->SetNdivisions(509);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.018, 0.018);
    h1->Draw();
    N1HFcSUB2->Draw("same p");
    N1HFdSUB2->Draw("same p");
    N1HFeSUB2->Draw("same p");
    N1HFfSUB2->Draw("same p");
    N1HFcSUB3->Draw("same p");
    N1HFdSUB3->Draw("same p");
    N1HFeSUB3->Draw("same p");
    N1HFfSUB3->Draw("same p");

    TPaveText * tx10 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx10, 20);
    tx10->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx10->Draw();

    TPaveText * tx11 = new TPaveText(0.49, 0.83, 0.65, 0.87, "NDC");
    SetTPaveTxt(tx11, 24);
    tx11->AddText("20 - 60%");
    tx11->Draw();

    TLegend * leg1 = new TLegend(0.31, 0.18, 0.61, 0.40);
    SetLegend(leg1, 18);
    leg1->SetNColumns(2);
    leg1->SetHeader("2SUB   3SUB");
    leg1->AddEntry(N1HFcSUB2,"             ","p");
    leg1->AddEntry(N1HFcSUB3,"      3.0 < |#eta_{EP}| < 3.5","p");
    leg1->AddEntry(N1HFdSUB2,"             ","p");
    leg1->AddEntry(N1HFdSUB3,"      3.5 < |#eta_{EP}| < 4.0","p");
    leg1->AddEntry(N1HFeSUB2,"             ","p");
    leg1->AddEntry(N1HFeSUB3,"      4.0 < |#eta_{EP}| < 4.5","p");
    leg1->AddEntry(N1HFfSUB2,"             ","p");
    leg1->AddEntry(N1HFfSUB3,"      4.0 < |#eta_{EP}| < 4.5","p");
    leg1->Draw();

    c1->Print("fig1.pdf","pdf");
    // c1->Print("fig1.png","png");


    //--  --//
    N1HFgSUB2 = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gint");
    N1HFgSUB2->SetMarkerStyle(25);
    N1HFgSUB2->SetMarkerSize(1.3);
    N1HFgSUB2->SetMarkerColor(kBlack);
    N1HFgSUB2->SetLineColor(kBlack);
    N1HFgSUB2->RemovePoint(0);
    N1HFgSUB2->RemovePoint(N1HFgSUB2->GetN()-1);

    N1HFgSUB3 = (TGraphErrors *) fin->Get("default/N1HFgSUB3/-2.0_2.0/20_60/gint");
    N1HFgSUB3->SetMarkerStyle(21);
    N1HFgSUB3->SetMarkerSize(1.3);
    N1HFgSUB3->SetMarkerColor(kBlack);
    N1HFgSUB3->SetLineColor(kBlack);
    N1HFgSUB3->RemovePoint(0);
    N1HFgSUB3->RemovePoint(N1HFgSUB3->GetN()-1);
    // Double_t xval[30], yval[30], yerr[30];
    // int num = N1HFgSUB3->GetN();
    // for (int j = 0; j<num; j++) {
    //     N1HFgSUB3->GetPoint(j, xval[j], yval[j]);
    //     cout<<yval[j]<<endl;
    // }

    TCanvas * c2 = new TCanvas("c2", "c2", 620, 600);
    TPad * pad2 = (TPad *) c2->cd();
    pad2->SetTopMargin(0.08);
    pad2->SetLeftMargin(0.18);
    h2 = new TH1D("h2", "", 100, -2.5, 2.5);
    h2->SetStats(0);
    h2->SetXTitle("#eta");
    h2->SetYTitle("v_{1}");
    h2->GetYaxis()->SetDecimals();
    h2->GetYaxis()->SetNdivisions(509);
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->CenterTitle();
    h2->GetXaxis()->SetTitleOffset(1.15);
    h2->GetYaxis()->SetTitleOffset(1.65);
    h2->GetYaxis()->SetRangeUser(-0.015, 0.015);
    h2->Draw();
    N1HFgSUB2->Draw("same p");
    N1HFgSUB3->Draw("same p");

    TPaveText * tx20 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx20, 20);
    tx20->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx20->Draw();

    TPaveText * tx21 = new TPaveText(0.65, 0.76, 0.80, 0.88, "NDC");
    SetTPaveTxt(tx21, 24);
    tx21->AddText("4.0 < |#eta_{EP}| < 5.0");
    tx21->AddText("20 - 60%");
    tx21->Draw();

    TLegend * leg2 = new TLegend(0.65, 0.62, 0.83, 0.74);
    SetLegend(leg2, 22);
    leg2->AddEntry(N1HFgSUB2,"   2SUB","p");
    leg2->AddEntry(N1HFgSUB3,"   3SUB","p");
    leg2->Draw();

    c2->Print("fig2.pdf","pdf");
    // c2->Print("fig2.png","png");

}
