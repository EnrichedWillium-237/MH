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

void symtest() {

    fin = new TFile("data_figHF23SUB.root");

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

    Double_t xval[30], yval[30], yerr[30];
    int num = N1HFgSUB2->GetN();
    for (int j = 0; j<num; j++) {
        N1HFgSUB2->GetPoint(j, xval[j], yval[j]);
        yerr[j] = N1HFgSUB2->GetErrorY(j);
    }
    Double_t xad[30], yad[30], yaderr[30];
    for (int j = 0; j<5; j++) {
        xad[j] = xval[j+5];
        double yneg = yval[j];
        double ynegErr = yerr[j];
        double ypos = yval[11-j];
        double yposErr = yerr[11-j];
        yad[j] = fabs(fabs(ypos) - fabs(yneg));
        yaderr[j] = sqrt( pow(yposErr,2) + pow(ynegErr,2) );
    }
    TGraphErrors * diffN1HFgSUB2 = new TGraphErrors(5, xad, yad, 0, yaderr);
    diffN1HFgSUB2->SetMarkerStyle(25);
    diffN1HFgSUB2->SetMarkerSize(1.3);
    diffN1HFgSUB2->SetMarkerColor(kBlack);
    diffN1HFgSUB2->SetLineColor(kBlack);

    for (int j = 0; j<num; j++) {
        N1HFgSUB3->GetPoint(j, xval[j], yval[j]);
        yerr[j] = N1HFgSUB3->GetErrorY(j);
    }
    for (int j = 0; j<5; j++) {
        xad[j] = xval[j+5];
        double yneg = yval[j];
        double ynegErr = yerr[j];
        double ypos = yval[11-j];
        double yposErr = yerr[11-j];
        yad[j] = fabs(fabs(ypos) - fabs(yneg));
        yaderr[j] = sqrt( pow(yposErr,2) + pow(ynegErr,2) );
    }
    TGraphErrors * diffN1HFgSUB3 = new TGraphErrors(5, xad, yad, 0, yaderr);
    diffN1HFgSUB3->SetMarkerStyle(21);
    diffN1HFgSUB3->SetMarkerSize(1.3);
    diffN1HFgSUB3->SetMarkerColor(kBlack);
    diffN1HFgSUB3->SetLineColor(kBlack);


    TCanvas * c0 = new TCanvas("c0", "c0", 620, 600);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetTopMargin(0.08);
    pad0->SetLeftMargin(0.18);
    h0 = new TH1D("h0", "", 100, 0, 2.5);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("|v_{1}^{HF+}| - |v_{1}^{HF-}|");
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(509);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleOffset(1.15);
    h0->GetYaxis()->SetTitleOffset(1.65);
    h0->GetYaxis()->SetRangeUser(0, 0.02);
    h0->Draw();
    diffN1HFgSUB2->Draw("same p");
    diffN1HFgSUB3->Draw("same p");

    TPaveText * tx00 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx00, 20);
    tx00->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx00->Draw();

    TPaveText * tx01 = new TPaveText(0.65, 0.76, 0.80, 0.88, "NDC");
    SetTPaveTxt(tx01, 24);
    tx01->AddText("4.0 < |#eta_{EP}| < 5.0");
    tx01->AddText("20 - 60%");
    tx01->Draw();

    TLegend * leg0 = new TLegend(0.65, 0.62, 0.83, 0.74);
    SetLegend(leg0, 22);
    leg0->AddEntry(diffN1HFgSUB2,"   2SUB","p");
    leg0->AddEntry(diffN1HFgSUB3,"   3SUB","p");
    leg0->Draw();

    c0->Print("figsym.pdf","pdf");
    // c0->Print("figsym.png","png");

}
