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

static const int ncbins = 6;
static const int cmin[] = {0, 5, 10, 20, 30, 40};
static const int cmax[] = {5, 10, 20, 30, 40, 50};
static const double pmin[] = {0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};
static const double pmax[] = {0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0};

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

void SetTPaveTxt2( TPaveText * txtemplate, int txtsize ) {
    txtemplate->SetFillColor(0);
    txtemplate->SetBorderSize(0);
    txtemplate->SetTextFont(43);
    txtemplate->SetTextSize(txtsize);
}

TFile * fin = new TFile("../../data/vnPlots.root","read");
TFile * fdata = new TFile("../../data/published_results.root","read");

TH1D * h0;
TH1D * h1;
TGraphErrors * ATLAS_v1even_pT_00_05;
TGraphErrors * ATLAS_v1even_pT_05_10;
TGraphErrors * ATLAS_v1even_pT_10_20;
TGraphErrors * ATLAS_v1even_pT_20_30;
TGraphErrors * ATLAS_v1even_pT_30_40;
TGraphErrors * ATLAS_v1even_pT_40_50;
TGraphErrors * ALICE_v1even_pT_c5_80;
TGraphErrors * STAR_v1even_62GeV_0_10;
TGraphErrors * STAR_v1even_200GeV_0_10;
TGraphErrors * N1AEVENSUB3[ncbins];
TGraphErrors * N1BEVENSUB3[ncbins];
TGraphErrors * N1EVENSUB3[ncbins];
TGraphErrors * N1EVENSUB3_syst[ncbins];

TGraphErrors * N1AEVENSUB3_0_10;
TGraphErrors * N1BEVENSUB3_0_10;
TGraphErrors * N1EVENSUB3_0_10;
TGraphErrors * N1EVENSUB3_0_10_syst;

TGraphErrors * N1AEVENSUB3_5_80;
TGraphErrors * N1BEVENSUB3_5_80;
TGraphErrors * N1EVENSUB3_5_80;
TGraphErrors * N1EVENSUB3_5_80_syst;

const double syst_v1even_pt[ncbins] = {2.4e-4, 2.4e-4, 2.4e-4, 2.4e-4, 2.4e-4, 2.4e-4};
# include "../../data/systematics.h"

double getSyst( TGraphErrors * g, string dep, int centbin ) {
    double syst = 0;
    int x = 0;
    if (cmin[centbin]>31) x = 1;
    if (cmin[centbin]>61) x = 2;
    TString name = g->GetName();
    if (name.Contains("N1HFg") && !name.Contains("decor")) {
        if (dep == "eta") syst = syst_N1HFgSUB3_eta[x];
        if (dep == "pt0") syst = syst_N1HFgSUB3_pt0[x];
        if (dep == "pt1") syst = syst_N1HFgSUB3_pt1[x];
    }
    if (name.Contains("N1HFg") && name.Contains("decor")) {
        if (dep == "eta") syst = syst_N1HFgSUB3_decor_eta[x];
        if (dep == "pt0") syst = syst_N1HFgSUB3_decor_pt0[x];
        if (dep == "pt1") syst = syst_N1HFgSUB3_decor_pt1[x];
    }
    if (name.Contains("N112A") ) {
        if (dep == "eta") syst = syst_N112ASUB3_eta[x];
        if (dep == "pt0") syst = syst_N112ASUB3_pt0[x];
        if (dep == "pt1") syst = syst_N112ASUB3_pt1[x];
    }
    if (name.Contains("N1EVEN") && !name.Contains("decor")) {
        if (dep == "eta") syst = syst_N1EVENSUB3_eta[x];
        if (dep == "pt0") syst = syst_N1EVENSUB3_pt0[x];
        if (dep == "pt1") syst = syst_N1EVENSUB3_pt1[x];
    }
    if (name.Contains("N1EVEN") && name.Contains("decor")) {
        if (dep == "eta") syst = syst_N1EVENSUB3_decor_eta[x];
        if (dep == "pt0") syst = syst_N1EVENSUB3_decor_pt0[x];
        if (dep == "pt1") syst = syst_N1EVENSUB3_decor_pt1[x];
    }
    return syst;
}

void fig_comp_v1even_pT() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        // Average negative and positive side v1even
        N1AEVENSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3/-2.4_-0.4/%d_%d/gA",cmin[cbin],cmax[cbin]));
        N1BEVENSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3/0.4_2.4/%d_%d/gA",cmin[cbin],cmax[cbin]));
        int num =  N1AEVENSUB3[cbin]->GetN();
        double xvalA[50], xvalB[50], yvalA[50], yvalB[50], yerrA[50], yerrB[50];
        for (int j = 0; j<num; j++) {
            N1AEVENSUB3[cbin]->GetPoint(j, xvalA[j], yvalA[j]);
            yerrA[j] = N1AEVENSUB3[cbin]->GetErrorY(j);
            N1BEVENSUB3[cbin]->GetPoint(j, xvalB[j], yvalB[j]);
            yerrB[j] = N1BEVENSUB3[cbin]->GetErrorY(j);

            yvalA[j] = 0.5*(yvalA[j] + yvalB[j]);
            yerrA[j] = 0.5*sqrt( pow(yerrA[j],2) + pow(yerrB[j],2) );
        }

        N1EVENSUB3[cbin] = new TGraphErrors(num, xvalA, yvalA, 0, yerrA);
        N1EVENSUB3[cbin]->SetName(Form("N1EVENSUB3_0.4_2.4_%d_%d",cmin[cbin],cmax[cbin]));

        N1EVENSUB3[cbin]->SetMarkerStyle(21);
        N1EVENSUB3[cbin]->SetMarkerSize(1.3);
        N1EVENSUB3[cbin]->SetMarkerColor(kBlue);
        N1EVENSUB3[cbin]->SetLineColor(kBlue);
        N1EVENSUB3[cbin]->SetFillColor(kBlue-9);

        //-- systematics
        Double_t x[50], y[50], xerr[50], ysyst[50];
        num = N1EVENSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1EVENSUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.18;
            if (x[j]<3) ysyst[j] = getSyst( N1EVENSUB3[cbin], "pt0", cbin );
            if (x[j]>3) ysyst[j] = getSyst( N1EVENSUB3[cbin], "pt1", cbin );
        }
        N1EVENSUB3_syst[cbin] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1EVENSUB3_syst[cbin]->SetLineColor(kBlue-9);
        N1EVENSUB3_syst[cbin]->SetFillColor(kBlue-9);
        //--

    }


    //---- results for 0 to 10% centrality
    N1AEVENSUB3_0_10 = (TGraphErrors *) fin->Get("default/N1EVENSUB3/-2.4_-0.4/0_10/gA");
    N1BEVENSUB3_0_10 = (TGraphErrors *) fin->Get("default/N1EVENSUB3/0.4_2.4/0_10/gA");
    int num =  N1AEVENSUB3_0_10->GetN();
    double xvalA[50], xvalB[50], yvalA[50], yvalB[50], yerrA[50], yerrB[50];
    for (int j = 0; j<num; j++) {
        N1AEVENSUB3_0_10->GetPoint(j, xvalA[j], yvalA[j]);
        yerrA[j] = N1AEVENSUB3_0_10->GetErrorY(j);
        N1BEVENSUB3_0_10->GetPoint(j, xvalB[j], yvalB[j]);
        yerrB[j] = N1BEVENSUB3_0_10->GetErrorY(j);

        yvalA[j] = 0.5*(yvalA[j] + yvalB[j]);
        yerrA[j] = 0.5*sqrt( pow(yerrA[j],2) + pow(yerrB[j],2) );
    }
    N1EVENSUB3_0_10 = new TGraphErrors(num, xvalA, yvalA, 0, yerrA);

    N1EVENSUB3_0_10->SetMarkerStyle(21);
    N1EVENSUB3_0_10->SetMarkerSize(1.3);
    N1EVENSUB3_0_10->SetMarkerColor(kBlue);
    N1EVENSUB3_0_10->SetLineColor(kBlue);
    N1EVENSUB3_0_10->SetFillColor(kBlue-9);

    Double_t x[50], y[50], xerr[50], ysyst[50];
    num = N1EVENSUB3_0_10->GetN();
    for (int j = 0; j<num; j++) {
        N1EVENSUB3_0_10->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.09;
        if (x[j]<3) ysyst[j] = getSyst( N1EVENSUB3[1], "pt0", 1 );
        if (x[j]>3) ysyst[j] = getSyst( N1EVENSUB3[1], "pt1", 1 );
    }
    N1EVENSUB3_0_10_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3_0_10_syst->SetLineColor(kBlue-9);
    N1EVENSUB3_0_10_syst->SetFillColor(kBlue-9);


    //---- results for 5 to 80% centrality
    N1AEVENSUB3_5_80 = (TGraphErrors *) fin->Get("default/N1EVENSUB3/-2.4_-0.4/5_80/gA");
    N1BEVENSUB3_5_80 = (TGraphErrors *) fin->Get("default/N1EVENSUB3/0.4_2.4/5_80/gA");
    num =  N1AEVENSUB3_5_80->GetN();
    for (int j = 0; j<num; j++) {
        N1AEVENSUB3_5_80->GetPoint(j, xvalA[j], yvalA[j]);
        yerrA[j] = N1AEVENSUB3_5_80->GetErrorY(j);
        N1BEVENSUB3_5_80->GetPoint(j, xvalB[j], yvalB[j]);
        yerrB[j] = N1BEVENSUB3_5_80->GetErrorY(j);

        yvalA[j] = 0.5*(yvalA[j] + yvalB[j]);
        yerrA[j] = 0.5*sqrt( pow(yerrA[j],2) + pow(yerrB[j],2) );
    }

    N1EVENSUB3_5_80 = new TGraphErrors(num, xvalA, yvalA, 0, yerrA);

    N1EVENSUB3_5_80->SetMarkerStyle(21);
    N1EVENSUB3_5_80->SetMarkerSize(1.3);
    N1EVENSUB3_5_80->SetMarkerColor(kBlue);
    N1EVENSUB3_5_80->SetLineColor(kBlue);
    N1EVENSUB3_5_80->SetFillColor(kBlue-9);

    num = N1EVENSUB3_5_80->GetN();
    for (int j = 0; j<num; j++) {
        N1EVENSUB3_5_80->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.12;
        if (x[j]<3) ysyst[j] = syst_N1EVENSUB3_pt0[3];
        else ysyst[j] = syst_N1EVENSUB3_pt0[4];
    }
    N1EVENSUB3_5_80_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3_5_80_syst->SetLineColor(kBlue-9);
    N1EVENSUB3_5_80_syst->SetFillColor(kBlue-9);
    //----


    ATLAS_v1even_pT_00_05 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_0_5");
    ATLAS_v1even_pT_05_10 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_5_10");
    ATLAS_v1even_pT_10_20 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_10_20");
    ATLAS_v1even_pT_20_30 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_20_30");
    ATLAS_v1even_pT_30_40 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_30_40");
    ATLAS_v1even_pT_40_50 = (TGraphErrors *) fdata->Get("v1even/ATLAS_v1even_pT_2TeV_40_50");
    ATLAS_v1even_pT_00_05->SetMarkerStyle(20);
    ATLAS_v1even_pT_05_10->SetMarkerStyle(20);
    ATLAS_v1even_pT_10_20->SetMarkerStyle(20);
    ATLAS_v1even_pT_20_30->SetMarkerStyle(20);
    ATLAS_v1even_pT_30_40->SetMarkerStyle(20);
    ATLAS_v1even_pT_40_50->SetMarkerStyle(20);
    ATLAS_v1even_pT_00_05->SetMarkerSize(0.06);
    ATLAS_v1even_pT_05_10->SetMarkerSize(0.06);
    ATLAS_v1even_pT_10_20->SetMarkerSize(0.06);
    ATLAS_v1even_pT_20_30->SetMarkerSize(0.06);
    ATLAS_v1even_pT_30_40->SetMarkerSize(0.06);
    ATLAS_v1even_pT_40_50->SetMarkerSize(0.06);
    ATLAS_v1even_pT_00_05->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_05_10->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_10_20->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_20_30->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_30_40->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_40_50->SetMarkerColor(kBlack);
    ATLAS_v1even_pT_00_05->SetLineColor(kGray+1);
    ATLAS_v1even_pT_05_10->SetLineColor(kGray+1);
    ATLAS_v1even_pT_10_20->SetLineColor(kGray+1);
    ATLAS_v1even_pT_20_30->SetLineColor(kGray+1);
    ATLAS_v1even_pT_30_40->SetLineColor(kGray+1);
    ATLAS_v1even_pT_40_50->SetLineColor(kGray+1);
    ATLAS_v1even_pT_00_05->SetFillColor(kGray+1);
    ATLAS_v1even_pT_05_10->SetFillColor(kGray+1);
    ATLAS_v1even_pT_10_20->SetFillColor(kGray+1);
    ATLAS_v1even_pT_20_30->SetFillColor(kGray+1);
    ATLAS_v1even_pT_30_40->SetFillColor(kGray+1);
    ATLAS_v1even_pT_40_50->SetFillColor(kGray+1);

    ALICE_v1even_pT_c5_80 = (TGraphErrors *) fdata->Get("v1even/ALICE_v1even_pT_2TeV_5_80");
    ALICE_v1even_pT_c5_80->SetMarkerStyle(20);
    ALICE_v1even_pT_c5_80->SetMarkerSize(1.3);
    ALICE_v1even_pT_c5_80->SetMarkerColor(kMagenta);
    ALICE_v1even_pT_c5_80->SetLineColor(kMagenta);

    STAR_v1even_62GeV_0_10 = (TGraphErrors *) fdata->Get("v1even/STAR_v1even_62GeV_0_10");
    STAR_v1even_62GeV_0_10->SetMarkerStyle(30);
    STAR_v1even_62GeV_0_10->SetMarkerSize(1.9);
    STAR_v1even_62GeV_0_10->SetMarkerColor(kBlack);
    STAR_v1even_62GeV_0_10->SetLineColor(kBlack);

    STAR_v1even_200GeV_0_10 = (TGraphErrors *) fdata->Get("v1even/STAR_v1even_200GeV_0_10");
    STAR_v1even_200GeV_0_10->SetMarkerStyle(29);
    STAR_v1even_200GeV_0_10->SetMarkerSize(1.9);
    STAR_v1even_200GeV_0_10->SetMarkerColor(kRed);
    STAR_v1even_200GeV_0_10->SetLineColor(kRed);


    TCanvas * c0 = new TCanvas("c0", "c0", 1100, 730);
    TPad * pad0[6];
    c0->cd();
    pad0[0] = new TPad("pad0_0", "pad0_0", 0.0, 0.53, 0.37, 1.0);
    pad0[0]->SetTopMargin(0.095);
    pad0[0]->SetLeftMargin(0.23);
    pad0[0]->SetBottomMargin(0);
    pad0[0]->SetRightMargin(0);
    pad0[0]->Draw();

    c0->cd();
    pad0[1] = new TPad("pad0_1", "pad0_1", 0.37, 0.53, 0.67, 1.0);
    pad0[1]->SetTopMargin(0.095);
    pad0[1]->SetLeftMargin(0);
    pad0[1]->SetRightMargin(0);
    pad0[1]->SetBottomMargin(0);
    pad0[1]->Draw();

    c0->cd();
    pad0[2] = new TPad("pad0_2", "pad0_2", 0.67, 0.53, 1.0, 1.0);
    pad0[2]->SetTopMargin(0.095);
    pad0[2]->SetLeftMargin(0);
    pad0[2]->SetRightMargin(0.10);
    pad0[2]->SetBottomMargin(0);
    pad0[2]->Draw();

    c0->cd();
    pad0[3] = new TPad("pad0_3", "pad0_3", 0.0, 0.0, 0.37, 0.53);
    pad0[3]->SetLeftMargin(0.23);
    pad0[3]->SetRightMargin(0);
    pad0[3]->SetTopMargin(0);
    pad0[3]->SetBottomMargin(0.18);
    pad0[3]->Draw();

    c0->cd();
    pad0[4] = new TPad("pad0_4", "pad0_4", 0.37, 0.0, 0.67, 0.53);
    pad0[4]->SetLeftMargin(0);
    pad0[4]->SetRightMargin(0);
    pad0[4]->SetTopMargin(0);
    pad0[4]->SetBottomMargin(0.18);
    pad0[4]->Draw();

    c0->cd();
    pad0[5] = new TPad("pad0_5", "pad0_5", 0.67, 0.0, 1.0, 0.53);
    pad0[5]->SetLeftMargin(0);
    pad0[5]->SetRightMargin(0.10);
    pad0[5]->SetTopMargin(0);
    pad0[5]->SetBottomMargin(0.18);
    pad0[5]->Draw();

    h0 = new TH1D("h0", "h0", 100, 0.001, 7.9);
    h0->SetStats(0);
    h0->SetXTitle("p_{T} (GeV/c)");
    h0->SetYTitle("v_{1}^{even}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(21);
    h0->GetXaxis()->SetTitleOffset(2.35);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(18);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(25);
    h0->GetYaxis()->SetTitleOffset(2.8);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(18);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.04, 0.18);

    for (int cbin = 0; cbin<6; cbin++) {
        pad0[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->Draw();
        if (cbin == 0) {
            ATLAS_v1even_pT_00_05->Draw("same 3");
            ATLAS_v1even_pT_00_05->Draw("same p");
            N1EVENSUB3_syst[0]->Draw("same 2");
            N1EVENSUB3[0]->Draw("same p");
            TPaveText * txt0_CMS0 = new TPaveText(0.22, 0.93, 0.42, 0.98, "NDC");
            SetTPaveTxt(txt0_CMS0, 21);
            txt0_CMS0->AddText("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV");
            txt0_CMS0->Draw();
            TPaveText * txt0_0 = new TPaveText(0.27, 0.66, 0.44, 0.75, "NDC");
            SetTPaveTxt(txt0_0, 22);
            txt0_0->AddText("0 - 5%");
            txt0_0->Draw();
            TLegend * leg0_1 = new TLegend(0.27, 0.76, 0.45, 0.87);
            SetLegend(leg0_1, 20);
            leg0_1->AddEntry(ATLAS_v1even_pT_05_10,"  ATLAS PbPb 2.76 TeV","pf");
            leg0_1->Draw();
        }
        if (cbin == 1) {
            ATLAS_v1even_pT_05_10->Draw("same 3");
            ATLAS_v1even_pT_05_10->Draw("same p");
            N1EVENSUB3_syst[1]->Draw("same 2");
            N1EVENSUB3[1]->Draw("same p");
            TPaveText * txt0_CMS1 = new TPaveText(0.01, 0.93, 0.21, 0.98, "NDC");
            SetTPaveTxt(txt0_CMS1, 21);
            txt0_CMS1->AddText("0.4 < |#eta| < 2.4");
            txt0_CMS1->Draw();
            TPaveText * txt0_1 = new TPaveText(0.08, 0.77, 0.25, 0.86, "NDC");
            SetTPaveTxt(txt0_1, 22);
            txt0_1->AddText("5 - 10%");
            txt0_1->Draw();
        }
        if (cbin == 2) {
            ATLAS_v1even_pT_10_20->Draw("same 3");
            ATLAS_v1even_pT_10_20->Draw("same p");
            N1EVENSUB3_syst[2]->Draw("same 2");
            N1EVENSUB3[2]->Draw("same p");
            TPaveText * txt0_CMS2 = new TPaveText(0.01, 0.93, 0.21, 0.98, "NDC");
            SetTPaveTxt(txt0_CMS2, 21);
            txt0_CMS2->AddText("#eta_{C} = 0");
            txt0_CMS2->Draw();
            TPaveText * txt0_2 = new TPaveText(0.06, 0.77, 0.24, 0.86, "NDC");
            SetTPaveTxt(txt0_2, 22);
            txt0_2->AddText("10 - 20%");
            txt0_2->Draw();
        }
        if (cbin == 3) {
            ATLAS_v1even_pT_20_30->Draw("same 3");
            ATLAS_v1even_pT_20_30->Draw("same p");
            N1EVENSUB3_syst[3]->Draw("same 2");
            N1EVENSUB3[3]->Draw("same p");
            TPaveText * txt0_3 = new TPaveText(0.27, 0.86, 0.44, 0.95, "NDC");
            SetTPaveTxt(txt0_3, 22);
            txt0_3->AddText("20 - 30%");
            txt0_3->Draw();
        }
        if (cbin == 4) {
            ATLAS_v1even_pT_30_40->Draw("same 3");
            ATLAS_v1even_pT_30_40->Draw("same p");
            N1EVENSUB3_syst[4]->Draw("same 2");
            N1EVENSUB3[4]->Draw("same p");
            TPaveText * txt0_4 = new TPaveText(0.08, 0.86, 0.25, 0.95, "NDC");
            SetTPaveTxt(txt0_4, 22);
            txt0_4->AddText("30 - 40%");
            txt0_4->Draw();
        }
        if (cbin == 5) {
            ATLAS_v1even_pT_40_50->Draw("same 3");
            ATLAS_v1even_pT_40_50->Draw("same p");
            N1EVENSUB3_syst[5]->Draw("same 2");
            N1EVENSUB3[5]->Draw("same p");
            TPaveText * txt0_5 = new TPaveText(0.06, 0.86, 0.24, 0.95, "NDC");
            SetTPaveTxt(txt0_5, 22);
            txt0_5->AddText("40 - 50%");
            txt0_5->Draw();
        }
    }
    c0->Print("../figures/fig_v1even_compare_ATLAS_SP.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 600, 550);
    TPad * pad1 = (TPad *) c1->cd();
    pad1->SetTopMargin(0.05);
    pad1->SetBottomMargin(0.15);
    pad1->SetLeftMargin(0.15);
    pad1->SetRightMargin(0.08);
    h1 = new TH1D("h1", "h1", 1000, 0.0, 6.0);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{even}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->SetNdivisions(510);
    h1->GetYaxis()->SetNdivisions(507);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleFont(43);
    h1->GetXaxis()->SetTitleSize(22);
    h1->GetXaxis()->SetTitleOffset(1.5);
    h1->GetXaxis()->SetLabelFont(43);
    h1->GetXaxis()->SetLabelSize(20);
    h1->GetXaxis()->SetLabelOffset(0.018);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleSize(26);
    h1->GetYaxis()->SetTitleOffset(1.4);
    h1->GetYaxis()->SetLabelFont(43);
    h1->GetYaxis()->SetLabelSize(20);
    h1->GetYaxis()->SetLabelOffset(0.010);
    h1->GetYaxis()->SetRangeUser(-0.03, 0.20);
    h1->Draw();
    N1EVENSUB3_5_80_syst->Draw("same 2");
    ALICE_v1even_pT_c5_80->Draw("same p");
    N1EVENSUB3_5_80->Draw("same p");

    TLegend * leg1_0 = new TLegend(0.19, 0.81, 0.39, 0.93);
    SetLegend(leg1_0, 18);
    leg1_0->SetHeader("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV  0.4<|#eta|<2.4");
    leg1_0->AddEntry(N1EVENSUB3_5_80," 5-80%  #eta_{C} = 0","lpf");
    leg1_0->Draw();

    TLegend * leg1_1 = new TLegend(0.19, 0.69, 0.39, 0.79);
    SetLegend(leg1_1, 18);
    leg1_1->SetHeader("ALICE PbPb #sqrt{s_{NN}} = 2.76 TeV  |#eta|<0.8");
    leg1_1->AddEntry(ALICE_v1even_pT_c5_80," 5-80%","p");
    leg1_1->Draw();

    c1->Print("../figures/fig_v1even_compare_ALICE_SP.pdf","pdf");



    //-- scaled ALICE results
    double scaleVal = 35.;
    double xval_alice[50], yval_alice[50], yvalerr_alice[50];
    int numscale = 0;
    for (int i = 0; i<ALICE_v1even_pT_c5_80->GetN(); i++) {
        ALICE_v1even_pT_c5_80->GetPoint(i, xval_alice[i], yval_alice[i]);
        yval_alice[i] = yval_alice[i] * scaleVal;
        yvalerr_alice[i] = ALICE_v1even_pT_c5_80->GetErrorY(i);
        yvalerr_alice[i] = yvalerr_alice[i] * scaleVal;
        numscale++;
    }
    TGraphErrors * ALICE_v1even_pT_c5_80_scaled = new TGraphErrors(numscale, xval_alice, yval_alice, 0, yvalerr_alice);
    ALICE_v1even_pT_c5_80_scaled->SetMarkerStyle(20);
    ALICE_v1even_pT_c5_80_scaled->SetMarkerSize(1.3);
    ALICE_v1even_pT_c5_80_scaled->SetMarkerColor(kMagenta);
    ALICE_v1even_pT_c5_80_scaled->SetLineColor(kMagenta);

    TCanvas * c2 = new TCanvas("c2", "c2", 600, 550);
    TPad * pad2 = (TPad *) c2->cd();
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.15);
    pad2->SetLeftMargin(0.15);
    pad2->SetRightMargin(0.08);
    TH1D * h2 = (TH1D *) h1->Clone("h2");
    h2->Draw();
    N1EVENSUB3_5_80_syst->Draw("same 2");
    ALICE_v1even_pT_c5_80_scaled->Draw("same p");
    N1EVENSUB3_5_80->Draw("same p");

    TLegend * leg2_0 = new TLegend(0.19, 0.81, 0.39, 0.93);
    SetLegend(leg2_0, 18);
    leg2_0->SetHeader("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV  0.4<|#eta|<2.4");
    leg2_0->AddEntry(N1EVENSUB3_5_80," 5-80%  #eta_{C} = 0","lpf");
    leg2_0->Draw();

    TLegend * leg2_1 = new TLegend(0.19, 0.69, 0.39, 0.79);
    SetLegend(leg2_1, 18);
    leg2_1->SetHeader("ALICE (scaled) PbPb #sqrt{s_{NN}} = 2.76 TeV  |#eta|<0.8");
    leg2_1->AddEntry(ALICE_v1even_pT_c5_80," 5-80%  (#times 35)","p");
    leg2_1->Draw();

    c2->Print("../figures/fig_v1even_compare_ALICE_SP_scaled.pdf","pdf");



    TCanvas * c3 = new TCanvas("c3", "c3", 600, 550);
    TPad * pad3 = (TPad *) c3->cd();
    pad3->SetTopMargin(0.05);
    pad3->SetBottomMargin(0.15);
    pad3->SetLeftMargin(0.15);
    pad3->SetRightMargin(0.08);
    pad3->Draw();
    TH1D * h3 = (TH1D *) h1->Clone("h3");
    h3->GetXaxis()->SetRangeUser(0.0, 3.5);
    h3->GetYaxis()->SetRangeUser(-0.03, 0.15);
    h3->Draw();
    N1EVENSUB3_0_10_syst->Draw("same 2");
    // STAR_v1even_62GeV_0_10->Draw("same p");
    STAR_v1even_200GeV_0_10->Draw("same p");
    N1EVENSUB3_0_10->Draw("same p");

    TLegend * leg3_0 = new TLegend(0.19, 0.81, 0.39, 0.93);
    SetLegend(leg3_0, 18);
    leg3_0->SetHeader("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV  0.4<|#eta|<2.4");
    leg3_0->AddEntry(N1EVENSUB3_5_80," 0-10%  #eta_{C} = 0","lpf");
    leg3_0->Draw();

    TLegend * leg3_1 = new TLegend(0.19, 0.69, 0.39, 0.79);
    SetLegend(leg3_1, 18);
    STAR_v1even_200GeV_0_10->SetMarkerColor(kBlack);
    STAR_v1even_200GeV_0_10->SetLineColor(kBlack);
    leg3_1->SetHeader("STAR  AuAu #sqrt{s_{NN}} = 200 GeV");
    leg3_1->AddEntry(STAR_v1even_200GeV_0_10," 0-10%","p");
    leg3_1->Draw();

    c3->Print("../figures/fig_v1even_compare_STAR_SP.pdf","pdf");


}
