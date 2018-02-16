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

using namespace std;

static const int ncbins = 11;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};

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

TH1D * rat_tight_N1SUB2_pt[ncbins];
TH1D * rat_tight_N1SUB3_pt[ncbins];
TH1D * rat_tight_N1MCm22SUB2_pt[ncbins];
TH1D * rat_tight_N1MCp22SUB2_pt[ncbins];
TH1D * rat_tight_N1MCm22SUB3_pt[ncbins];
TH1D * rat_tight_N1MCp22SUB3_pt[ncbins];

TH1D * rat_tight_N1SUB2_eta[ncbins];
TH1D * rat_tight_N1SUB3_eta[ncbins];
TH1D * rat_tight_N1MCm22SUB2_eta[ncbins];
TH1D * rat_tight_N1MCp22SUB2_eta[ncbins];
TH1D * rat_tight_N1MCm22SUB3_eta[ncbins];
TH1D * rat_tight_N1MCp22SUB3_eta[ncbins];


TH1D * rat_wide_N1SUB2_pt[ncbins];
TH1D * rat_wide_N1SUB3_pt[ncbins];
TH1D * rat_wide_N1MCm22SUB2_pt[ncbins];
TH1D * rat_wide_N1MCp22SUB2_pt[ncbins];
TH1D * rat_wide_N1MCm22SUB3_pt[ncbins];
TH1D * rat_wide_N1MCp22SUB3_pt[ncbins];

TH1D * rat_wide_N1SUB2_eta[ncbins];
TH1D * rat_wide_N1SUB3_eta[ncbins];
TH1D * rat_wide_N1MCm22SUB2_eta[ncbins];
TH1D * rat_wide_N1MCp22SUB2_eta[ncbins];
TH1D * rat_wide_N1MCm22SUB3_eta[ncbins];
TH1D * rat_wide_N1MCp22SUB3_eta[ncbins];


TH1D * rat_narrow_N1SUB2_pt[ncbins];
TH1D * rat_narrow_N1SUB3_pt[ncbins];
TH1D * rat_narrow_N1MCm22SUB2_pt[ncbins];
TH1D * rat_narrow_N1MCp22SUB2_pt[ncbins];
TH1D * rat_narrow_N1MCm22SUB3_pt[ncbins];
TH1D * rat_narrow_N1MCp22SUB3_pt[ncbins];

TH1D * rat_narrow_N1SUB2_eta[ncbins];
TH1D * rat_narrow_N1SUB3_eta[ncbins];
TH1D * rat_narrow_N1MCm22SUB2_eta[ncbins];
TH1D * rat_narrow_N1MCp22SUB2_eta[ncbins];
TH1D * rat_narrow_N1MCm22SUB3_eta[ncbins];
TH1D * rat_narrow_N1MCp22SUB3_eta[ncbins];

TFile * fin;

void figRatiosTight() {

    fin = new TFile("hists/MH_ratios.root","read");

    for (int i = 0; i<ncbins; i++) {
        TString ctag = Form("%d_%d",cmin[i],cmax[i]);

        rat_tight_N1SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCm22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1MCm22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCp22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1MCp22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCm22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1MCm22SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCp22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_tight_N1MCp22SUB3_pt_%s",ctag.Data(),ctag.Data()));

        rat_tight_N1SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCm22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1MCm22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCp22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1MCp22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCm22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1MCm22SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_tight_N1MCp22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_tight_N1MCp22SUB3_eta_%s",ctag.Data(),ctag.Data()));


        rat_wide_N1SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCm22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1MCm22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCp22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1MCp22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCm22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1MCm22SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCp22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_wide_N1MCp22SUB3_pt_%s",ctag.Data(),ctag.Data()));

        rat_wide_N1SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCm22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1MCm22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCp22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1MCp22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCm22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1MCm22SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_wide_N1MCp22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_wide_N1MCp22SUB3_eta_%s",ctag.Data(),ctag.Data()));


        rat_narrow_N1SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCm22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1MCm22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCp22SUB2_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1MCp22SUB2_pt_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCm22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1MCm22SUB3_pt_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCp22SUB3_pt[i] = (TH1D *) fin->Get(Form("%s/vn_pt/rat_narrow_N1MCp22SUB3_pt_%s",ctag.Data(),ctag.Data()));

        rat_narrow_N1SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCm22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1MCm22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCp22SUB2_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1MCp22SUB2_eta_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCm22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1MCm22SUB3_eta_%s",ctag.Data(),ctag.Data()));
        rat_narrow_N1MCp22SUB3_eta[i] = (TH1D *) fin->Get(Form("%s/vn_eta/rat_narrow_N1MCp22SUB3_eta_%s",ctag.Data(),ctag.Data()));
    }

    if (!fopen("figures","r")) system("mkdir figures");

    TCanvas * c0 = new TCanvas("c0", "c0", 700, 950);
    c0->Divide(3,4,0,0);
    TH1D * h0 = new TH1D("h0", "", 100, -2.15, 2.15);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->SetRangeUser(0.76, 1.24);
    h0->GetXaxis()->SetTitleSize(0.07);
    h0->GetXaxis()->SetTitleOffset(0.90);
    h0->GetXaxis()->SetLabelSize(0.06);
    h0->GetYaxis()->SetTitleSize(0.08);
    h0->GetYaxis()->SetTitleOffset(1.10);
    h0->GetYaxis()->SetLabelSize(0.06);
    TLine * ln0 = new TLine(-2.15, 1.0, 2.15, 1.0);
    for (int i = 0; i<ncbins; i++) {
        TPad * pad0 = (TPad *) c0->cd(i+1);
        if (i == 2 || i == 5 || i == 8) pad0->SetRightMargin(0.03);
        if (i == 8) pad0->SetBottomMargin(0.01);
        if (i == 10) pad0->SetRightMargin(0.01);
        h0->Draw();
        ln0->Draw();
        rat_tight_N1SUB2_eta[i]->SetMarkerStyle(20);
        rat_tight_N1SUB2_eta[i]->SetMarkerSize(1.0);
        rat_tight_N1SUB2_eta[i]->SetMarkerColor(kBlack);
        rat_tight_N1SUB2_eta[i]->SetLineColor(kBlack);
        rat_tight_N1SUB2_eta[i]->Draw("same");
        TPaveText * tx0 = new TPaveText(0.27, 0.8, 0.45, 0.93, "NDC");
        SetTPaveTxt(tx0, 18);
        tx0->AddText(Form("%d-%d%%",cmin[i],cmax[i]));
        tx0->Draw();
    }
    c0->cd(12);
    TLegend * leg0 = new TLegend(0.20, 0.46, 0.62, 0.66);
    SetLegend(leg0, 18);
    leg0->AddEntry(rat_tight_N1SUB2_eta[0], "tight/nominal", "lp");
    leg0->Draw();
    c0->Print("figures/ratio_tight_N1SUB_eta.pdf","pdf");


    TCanvas * c1 = new TCanvas("c1", "c1", 700, 950);
    c1->Divide(3,4,0,0);
    TH1D * h1 = new TH1D("h0", "", 100, 0, 8.5);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(0.78, 1.22);
    h1->GetXaxis()->SetTitleSize(0.07);
    h1->GetXaxis()->SetTitleOffset(0.90);
    h1->GetXaxis()->SetLabelSize(0.06);
    h1->GetYaxis()->SetTitleSize(0.08);
    h1->GetYaxis()->SetTitleOffset(1.10);
    h1->GetYaxis()->SetLabelSize(0.06);
    TLine * ln1 = new TLine(0.0, 1.0, 8.5, 1.0);
    for (int i = 0; i<ncbins; i++) {
        TPad * pad1 = (TPad *) c1->cd(i+1);
        if (i == 2 || i == 5 || i == 8) pad1->SetRightMargin(0.03);
        if (i == 8) pad1->SetBottomMargin(0.01);
        if (i == 10) pad1->SetRightMargin(0.01);
        h1->Draw();
        ln1->Draw();
        rat_tight_N1SUB2_pt[i]->SetMarkerStyle(20);
        rat_tight_N1SUB2_pt[i]->SetMarkerSize(1.0);
        rat_tight_N1SUB2_pt[i]->SetMarkerColor(kBlack);
        rat_tight_N1SUB2_pt[i]->SetLineColor(kBlack);
        rat_tight_N1SUB2_pt[i]->Draw("same");
        TPaveText * tx1 = new TPaveText(0.27, 0.8, 0.45, 0.93, "NDC");
        SetTPaveTxt(tx1, 18);
        tx1->AddText(Form("%d-%d%%",cmin[i],cmax[i]));
        tx1->Draw();
    }
    c1->cd(12);
    TLegend * leg1 = new TLegend(0.20, 0.46, 0.62, 0.66);
    SetLegend(leg1, 18);
    leg1->AddEntry(rat_tight_N1SUB2_eta[0], "tight/nominal", "lp");
    leg1->Draw();
    c1->Print("figures/ratio_tight_N1SUB_pt.pdf","pdf");


    TCanvas * c2 = new TCanvas("c2", "c2", 700, 950);
    c2->Divide(3,4,0,0);
    TH1D * h2 = new TH1D("h0", "", 100, 0, 8.5);
    h2->SetStats(0);
    h2->SetXTitle("p_{T} (GeV/c)");
    h2->SetYTitle("v_{1}^{even}");
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->SetRangeUser(0.50, 1.5);
    h2->GetXaxis()->SetTitleSize(0.07);
    h2->GetXaxis()->SetTitleOffset(0.90);
    h2->GetXaxis()->SetLabelSize(0.06);
    h2->GetYaxis()->SetTitleSize(0.08);
    h2->GetYaxis()->SetTitleOffset(1.10);
    h2->GetYaxis()->SetLabelSize(0.06);
    TLine * ln2 = new TLine(0.0, 1.0, 8.5, 1.0);
    for (int i = 0; i<ncbins; i++) {
        TPad * pad1 = (TPad *) c2->cd(i+1);
        if (i == 2 || i == 5 || i == 8) pad1->SetRightMargin(0.03);
        if (i == 8) pad1->SetBottomMargin(0.01);
        if (i == 10) pad1->SetRightMargin(0.01);
        h2->Draw();
        ln2->Draw();
        rat_tight_N1MCp22SUB2_pt[i]->SetMarkerStyle(20);
        rat_tight_N1MCp22SUB2_pt[i]->SetMarkerSize(1.0);
        rat_tight_N1MCp22SUB2_pt[i]->SetMarkerColor(kBlack);
        rat_tight_N1MCp22SUB2_pt[i]->SetLineColor(kBlack);
        rat_tight_N1MCp22SUB2_pt[i]->Draw("same");
        TPaveText * tx2 = new TPaveText(0.50, 0.06, 0.69, 0.19, "NDC");
        SetTPaveTxt(tx2, 18);
        tx2->AddText(Form("%d-%d%%",cmin[i],cmax[i]));
        tx2->Draw();
    }
    c2->cd(12);
    TLegend * leg2 = new TLegend(0.20, 0.46, 0.62, 0.66);
    SetLegend(leg2, 18);
    leg2->AddEntry(rat_tight_N1MCp22SUB2_pt[0], "tight/nominal", "lp");
    leg2->Draw();
    c2->Print("figures/ratio_tight_N1MCpSUB_pt.pdf","pdf");


}
