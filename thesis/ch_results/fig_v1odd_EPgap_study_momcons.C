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

TFile * fin = new TFile("../../data/vnPlots.root","read");
TH1D * h0;
TGraphErrors * gHFc;
TGraphErrors * gHFd;
TGraphErrors * gHFe;
TGraphErrors * gHFf;
TGraphErrors * gHFc_decor;
TGraphErrors * gHFd_decor;
TGraphErrors * gHFe_decor;
TGraphErrors * gHFf_decor;
TGraphErrors * gHFc_mix;
TGraphErrors * gHFd_mix;
TGraphErrors * gHFe_mix;
TGraphErrors * gHFf_mix;

void fig_v1odd_EPgap_study_momcons() {

    gHFc = (TGraphErrors *) fin->Get("default/N1HFcSUB3/1.2_1.6/20_60/gintA");
    gHFd = (TGraphErrors *) fin->Get("default/N1HFdSUB3/1.2_1.6/20_60/gintA");
    gHFe = (TGraphErrors *) fin->Get("default/N1HFeSUB3/1.2_1.6/20_60/gintA");
    gHFf = (TGraphErrors *) fin->Get("default/N1HFfSUB3/1.2_1.6/20_60/gintA");

    gHFc_decor = (TGraphErrors *) fin->Get("default/N1HFcSUB3_decor/1.2_1.6/20_60/gintA");
    gHFd_decor = (TGraphErrors *) fin->Get("default/N1HFdSUB3_decor/1.2_1.6/20_60/gintA");
    gHFe_decor = (TGraphErrors *) fin->Get("default/N1HFeSUB3_decor/1.2_1.6/20_60/gintA");
    gHFf_decor = (TGraphErrors *) fin->Get("default/N1HFfSUB3_decor/1.2_1.6/20_60/gintA");

    gHFc_mix = (TGraphErrors *) fin->Get("default/N112CSUB3/1.2_1.6/20_60/gintA");
    gHFd_mix = (TGraphErrors *) fin->Get("default/N112DSUB3/1.2_1.6/20_60/gintA");
    gHFe_mix = (TGraphErrors *) fin->Get("default/N112ESUB3/1.2_1.6/20_60/gintA");
    gHFf_mix = (TGraphErrors *) fin->Get("default/N112FSUB3/1.2_1.6/20_60/gintA");

    gHFc->SetMarkerStyle(24);
    gHFc->SetMarkerSize(1.3);
    gHFc->SetMarkerColor(kMagenta);
    gHFc->SetLineColor(kMagenta);

    gHFd->SetMarkerStyle(20);
    gHFd->SetMarkerSize(1.3);
    gHFd->SetMarkerColor(kGreen+2);
    gHFd->SetLineColor(kGreen+2);

    gHFe->SetMarkerStyle(25);
    gHFe->SetMarkerSize(1.2);
    gHFe->SetMarkerColor(kRed);
    gHFe->SetLineColor(kRed);

    gHFf->SetMarkerStyle(21);
    gHFf->SetMarkerSize(1.2);
    gHFf->SetMarkerColor(kBlue);
    gHFf->SetLineColor(kBlue);


    //--  --//

    TCanvas * c0 = new TCanvas("c0", "c0", 620, 600);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetTopMargin(0.08);
    pad0->SetLeftMargin(0.18);
    h0 = new TH1D("h0", "", 100, -2.8, 2.8);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}");
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleOffset(1.15);
    h0->GetYaxis()->SetTitleOffset(1.70);
    h0->GetXaxis()->SetLabelSize(0.04);
    h0->GetYaxis()->SetLabelSize(0.04);
    h0->GetYaxis()->SetRangeUser(-0.05, 0.00);
    h0->Draw();
    gHFc->Draw("same p");
    gHFd->Draw("same p");
    gHFe->Draw("same p");
    gHFf->Draw("same p");
    TLegend * leg0 = new TLegend(0.22, 0.21, 0.42, 0.41);
    SetLegend(leg0, 20);
    leg0->AddEntry(gHFf,"4.5 < #eta_{HF+} < 5.0","p");
    leg0->AddEntry(gHFe,"4.0 < #eta_{HF+} < 4.5","p");
    leg0->AddEntry(gHFd,"3.5 < #eta_{HF+} < 4.0","p");
    leg0->AddEntry(gHFc,"3.0 < #eta_{HF+} < 3.5","p");
    leg0->Draw();
    TPaveText * tx0_0 = new TPaveText(0.17, 0.93, 0.37, 0.98, "NDC");
    SetTPaveTxt(tx0_0, 20);
    tx0_0->AddText("#bf{CMS}   20 - 60%");
    tx0_0->Draw();
    c0->Print("../figures/fig_v1odd_EPgap_study_momcons.pdf","pdf");

}
