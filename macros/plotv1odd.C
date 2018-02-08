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
# include "Riostream.h"
# include <iostream>
# include <string>

# include "src/style.h"

TFile * fin = new TFile("MH_hists.root");
TGraphErrors * gint_10_70;
TGraphErrors * gdiff_5_80;
TGraphErrors * gdiff_5_40;
TGraphErrors * gdiff_40_80;
TGraphErrors * gdiff_5_80_N1;

TGraphErrors * gint_10_70_sub2;
TGraphErrors * gint_10_70_N1_sub2;
TGraphErrors * gint_10_70_N1_sub3;

using namespace std;

static const int ncentbins = 14;
static const int cminCENT[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20,  60};
static const int cmaxCENT[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60, 100};
static const int NCbins = 11;
static const double centbins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
    3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};

TH2D * ampt_v1true2D[NCbins];
TH2D * ampt_v1raw2D[NCbins];
TH2D * ampt_qcnt[NCbins];

TH1D * ampt_v1_pT[NCbins][netabins];
TH1D * ampt_v1true_eta[NCbins];

TH1D * ampt_v1_pT_eta_0_8_neg[NCbins];
TH1D * ampt_v1_pT_eta_0_8_pos[NCbins];
TH1D * ampt_v1_pT_eta_0_24_neg[NCbins];
TH1D * ampt_v1_pT_eta_0_24_pos[NCbins];
TH1D * ampt_v1_pT_eta_0_8_av[NCbins];
TH1D * ampt_v1_pT_eta_0_24_av[NCbins];
TH1D * ampt_v2_pT_eta_0_8_av[NCbins];
TH1D * ampt_v2_pT_eta_0_24_av[NCbins];

TGraphErrors * gAMPTint_10_70;
TGraphErrors * gAMPTdiff_5_80;
TGraphErrors * gAMPTdiff_5_40;
TGraphErrors * gAMPTdiff_40_80;
TGraphErrors * gAMPTdiff_5_80_N1;

TGraphErrors * gAMPTdiff_30_40_N1MCp22;
TGraphErrors * gAMPTdiff_5_80_N1MCp22;


TFile * finAMPT;
TFile * finAMPTtrue;

void plotv1odd() {
    gint_10_70 = (TGraphErrors *) fin->Get("N1HFfSUB3/-0.8_0.8/10_70/gint");
    gdiff_5_80 = (TGraphErrors *) fin->Get("N1HFfSUB3/-0.8_0.8/10_70/g");
    gdiff_5_40 = (TGraphErrors *) fin->Get("N1HFfSUB3/-0.8_0.8/5_40/g");
    gdiff_40_80 = (TGraphErrors *) fin->Get("N1HFfSUB3/-0.8_0.8/40_70/g");
    gdiff_5_80_N1 = (TGraphErrors *) fin->Get("N1SUB3/-0.8_0.8/10_70/gB");

    gint_10_70_sub2 = (TGraphErrors *) fin->Get("N1HFfSUB2/-0.8_0.8/10_70/gint");
    gint_10_70_N1_sub2 = (TGraphErrors *) fin->Get("N1SUB2/-0.8_0.8/10_70/gint");
    gint_10_70_N1_sub3 = (TGraphErrors *) fin->Get("N1SUB3/-0.8_0.8/10_70/gint");

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    finAMPT = new TFile("../../../AMPT/VNAnalysis/macros/hists/amptVN.root","read");
    for (int cbin = 0; cbin<NCbins; cbin++) {
        TString ctag = Form("%d_%d",(int)centbins[cbin],(int)centbins[cbin+1]);
        ampt_v1true2D[cbin] = (TH2D *) finAMPT->Get(Form("%s/v1true_%s",ctag.Data(),ctag.Data()));
        ampt_v1raw2D[cbin] = (TH2D *) finAMPT->Get(Form("%s/v1raw_%s",ctag.Data(),ctag.Data()));
        ampt_qcnt[cbin] = (TH2D *) finAMPT->Get(Form("%s/qcnt_%s",ctag.Data(),ctag.Data()));

        ampt_v1true_eta[cbin] = new TH1D(Form("v1true_eta_%s",ctag.Data()), "", netabins, etabins);

        ampt_v1_pT_eta_0_8_neg[cbin] = ampt_v1true2D[cbin]->ProjectionX(Form("v1_pT_eta_0_8_neg_%s",ctag.Data()), 5, 6);
        ampt_v1_pT_eta_0_8_pos[cbin] = ampt_v1true2D[cbin]->ProjectionX(Form("v1_pT_eta_0_8_pos_%s",ctag.Data()), 7, 8);
        ampt_v1_pT_eta_0_24_neg[cbin] = ampt_v1true2D[cbin]->ProjectionX(Form("v1_pT_eta_0_24_neg_%s",ctag.Data()), 1, 6);
        ampt_v1_pT_eta_0_24_pos[cbin] = ampt_v1true2D[cbin]->ProjectionX(Form("v1_pT_eta_0_24_pos_%s",ctag.Data()), 7, 12);

        ampt_v1_pT_eta_0_8_neg[cbin]->Scale(1/2.);
        ampt_v1_pT_eta_0_8_pos[cbin]->Scale(1/2.);
        ampt_v1_pT_eta_0_24_neg[cbin]->Scale(1/6.);
        ampt_v1_pT_eta_0_24_pos[cbin]->Scale(1/6.);

        ampt_v1_pT_eta_0_8_av[cbin] = (TH1D *) ampt_v1_pT_eta_0_8_pos[cbin]->Clone(Form("v1_pT_eta_0_8_av_%s",ctag.Data()));
        ampt_v1_pT_eta_0_8_av[cbin]->Add(ampt_v1_pT_eta_0_8_neg[cbin],-1);
        ampt_v1_pT_eta_0_8_av[cbin]->Scale(0.5);

        ampt_v1_pT_eta_0_24_av[cbin] = (TH1D *) ampt_v1_pT_eta_0_24_pos[cbin]->Clone(Form("v1_pT_eta_0_24_av_%s",ctag.Data()));
        ampt_v1_pT_eta_0_24_av[cbin]->Add(ampt_v1_pT_eta_0_24_neg[cbin],-1);
        ampt_v1_pT_eta_0_24_av[cbin]->Scale(0.5);

        for (int ebin = 0; ebin<netabins; ebin++) {
            ampt_v1_pT[cbin][ebin] = ampt_v1true2D[cbin]->ProjectionX(Form("v1_pT_eta_%1.1f_%1.1f_%s",etabins[ebin],etabins[ebin+1],ctag.Data()), ebin+1, ebin+1);

            // compute integral v1(eta)
            double v1int = 0;
            double v1inte = 0;
            TH1D * yld = (TH1D *) ampt_qcnt[cbin]->ProjectionX("yld", ebin+1, ebin+1);
            double y1[20];
            double ey1[20];
            for (int i = 0; i<20; i++) {
                y1[20] = 0;
                ey1[20] = 0;
            }
            int npt = 0;
            double wv1 = 0;
            double wv1e = 0;
            double w = 0;
            for (int i = 1; i<=10; i++) {
                y1[npt] = ampt_v1_pT[cbin][ebin]->GetBinContent(i);
                ey1[npt] = ampt_v1_pT[cbin][ebin]->GetBinError(i);
                wv1  += y1[npt]*yld->GetBinContent(i);
                wv1e += ey1[npt]*yld->GetBinContent(i);
                w    += yld->GetBinContent(i);
                ++npt;
            }
            yld->Delete();
            v1int = wv1/w;
            v1inte = wv1e/w;

            ampt_v1true_eta[cbin]->SetBinContent(ebin+1, v1int);
            ampt_v1true_eta[cbin]->SetBinError(ebin+1, v1inte);

            int amptcol = kOrange+1;
            ampt_v1true_eta[cbin]->SetMarkerColor(amptcol);
            ampt_v1true_eta[cbin]->SetLineColor(amptcol);
            ampt_v1true_eta[cbin]->SetMarkerSize(0.1);
            ampt_v1true_eta[cbin]->SetFillColor(amptcol);
            ampt_v1true_eta[cbin]->SetFillStyle(1001);

            ampt_v1_pT_eta_0_8_pos[cbin]->SetMarkerColor(amptcol);
            ampt_v1_pT_eta_0_8_pos[cbin]->SetLineColor(amptcol);
            ampt_v1_pT_eta_0_8_pos[cbin]->SetMarkerSize(0.1);
            ampt_v1_pT_eta_0_8_pos[cbin]->SetFillColor(amptcol);
            ampt_v1_pT_eta_0_8_pos[cbin]->SetFillStyle(1001);
        }
    }


    finAMPT = new TFile("PbPb_AMPT_hists.root","read");
    gAMPTint_10_70 = (TGraphErrors *) finAMPT->Get("N1SUB3/-1.6_1.6/10_70/gint");
    gAMPTdiff_5_80 = (TGraphErrors *) finAMPT->Get("N1SUB3/-1.6_1.6/10_70/gA");
    gAMPTdiff_5_40 = (TGraphErrors *) finAMPT->Get("N1SUB3/-1.6_1.6/5_40/gA");
    gAMPTdiff_40_80 = (TGraphErrors *) finAMPT->Get("N1SUB3/-1.6_1.6/40_70/gA");

    gAMPTdiff_30_40_N1MCp22 = (TGraphErrors *) finAMPT->Get("N1MCp22SUB2/-1.6_1.6/30_35/gA");
    gAMPTdiff_5_80_N1MCp22 = (TGraphErrors *) finAMPT->Get("N1MCp22SUB2/-1.6_1.6/10_70/gA");

    gAMPTint_10_70->SetMarkerColor(kTeal+2);
    gAMPTint_10_70->SetLineColor(kTeal+2);
    gAMPTint_10_70->SetMarkerSize(0.1);
    gAMPTint_10_70->SetFillColor(kTeal+2);
    gAMPTint_10_70->SetFillStyle(1001);

    gAMPTdiff_5_80->SetMarkerColor(kTeal+2);
    gAMPTdiff_5_80->SetLineColor(kTeal+2);
    gAMPTdiff_5_80->SetMarkerSize(0.1);
    gAMPTdiff_5_80->SetFillColor(kTeal+2);
    gAMPTdiff_5_80->SetFillStyle(1001);

    gAMPTdiff_5_40->SetMarkerColor(kTeal+2);
    gAMPTdiff_5_40->SetLineColor(kTeal+2);
    gAMPTdiff_5_40->SetMarkerSize(0.1);
    gAMPTdiff_5_40->SetFillColor(kTeal+2);
    gAMPTdiff_5_40->SetFillStyle(1001);

    gAMPTdiff_40_80->SetMarkerColor(kTeal+2);
    gAMPTdiff_40_80->SetLineColor(kTeal+2);
    gAMPTdiff_40_80->SetMarkerSize(0.1);
    gAMPTdiff_40_80->SetFillColor(kTeal+2);
    gAMPTdiff_40_80->SetFillStyle(1001);

    gAMPTdiff_30_40_N1MCp22->SetMarkerColor(kTeal+2);
    gAMPTdiff_30_40_N1MCp22->SetLineColor(kTeal+2);
    gAMPTdiff_30_40_N1MCp22->SetMarkerSize(0.1);
    gAMPTdiff_30_40_N1MCp22->SetFillColor(kTeal+2);
    gAMPTdiff_30_40_N1MCp22->SetFillStyle(1001);

    gAMPTdiff_5_80_N1MCp22->SetMarkerColor(kTeal+2);
    gAMPTdiff_5_80_N1MCp22->SetLineColor(kTeal+2);
    gAMPTdiff_5_80_N1MCp22->SetMarkerSize(0.1);
    gAMPTdiff_5_80_N1MCp22->SetFillColor(kTeal+2);
    gAMPTdiff_5_80_N1MCp22->SetFillStyle(1001);


    # include "../../published_results/PhysRevLett_92_062301.h" // participant v1

    TGraphErrors * STAR_v1_3PC_200GeV = new TGraphErrors(24, STAR_v1_3PC_200GeV_eta, STAR_v1_3PC_200GeV_val, 0, STAR_v1_3PC_200GeV_err);
    STAR_v1_3PC_200GeV->SetMarkerColor(kBlack);
    STAR_v1_3PC_200GeV->SetLineColor(kBlack);
    STAR_v1_3PC_200GeV->SetMarkerStyle(30);
    STAR_v1_3PC_200GeV->SetMarkerSize(1.7);


    # include "../../published_results/PhysRevC72_14904.h" // participant v1

    TGraphErrors * STAR_v1_mix_200GeV = new TGraphErrors(STAR_AuAu_Mixed_neta, STAR_AuAu_Mixed_eta, STAR_AuAu_Mixed_v1, 0, STAR_AuAu_Mixed_v1Err);
    STAR_v1_mix_200GeV->SetMarkerColor(kRed);
    STAR_v1_mix_200GeV->SetLineColor(kRed);
    STAR_v1_mix_200GeV->SetMarkerStyle(20);
    STAR_v1_mix_200GeV->SetMarkerSize(1.2);


    # include "../../published_results/PhysRevC73_034903.h" // participant and spectator v1 (62.3 GeV)

    TGraphErrors * STAR_v1_3PC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_3PC_n, STAR_AuAu_62GeV_Fig1_3PC_eta, STAR_AuAu_62GeV_Fig1_3PC_v1, 0, STAR_AuAu_62GeV_Fig1_3PC_v1err);
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.7);

    TGraphErrors * STAR_v1_mix_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_mix_n, STAR_AuAu_62GeV_Fig1_mix_eta, STAR_AuAu_62GeV_Fig1_mix_v1, 0, STAR_AuAu_62GeV_Fig1_mix_v1err);
    STAR_v1_mix_62GeV_eta->SetMarkerColor(kOrange+7);
    STAR_v1_mix_62GeV_eta->SetLineColor(kOrange+7);
    STAR_v1_mix_62GeV_eta->SetMarkerStyle(24);
    STAR_v1_mix_62GeV_eta->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_ZDC_n, STAR_AuAu_62GeV_Fig1_ZDC_eta, STAR_AuAu_62GeV_Fig1_ZDC_v1, 0, STAR_AuAu_62GeV_Fig1_ZDC_v1err);
    STAR_v1_ZDC_62GeV_eta->SetMarkerColor(kBlack);
    STAR_v1_ZDC_62GeV_eta->SetLineColor(kBlack);
    STAR_v1_ZDC_62GeV_eta->SetMarkerStyle(25);
    STAR_v1_ZDC_62GeV_eta->SetMarkerSize(1.1);

    TGraphErrors * STAR_v1_3PC_62GeV_pT = new TGraphErrors(STAR_AuAu_62GeV_3PC_pT_n, STAR_AuAu_62GeV_3PC_pTval, STAR_AuAu_62GeV_3PC_pT_v1, 0, STAR_AuAu_62GeV_3PC_pT_v1_err);
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.7);


    # include "../../published_results/PhysRevLett101_252301.h" // spectator v1

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_0_5 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent0_5_eta, STAR_AuAu_200_ZDC_cent0_5_v1eta, 0, STAR_AuAu_200_ZDC_cent0_5_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_eta_0_5->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerStyle(20);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_5_40 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent5_40_eta, STAR_AuAu_200_ZDC_cent5_40_v1eta, 0, STAR_AuAu_200_ZDC_cent5_40_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerColor(kCyan+2);
    STAR_v1_ZDC_200GeV_eta_5_40->SetLineColor(kCyan+2);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerStyle(29);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerSize(1.7);

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent40_80_eta, STAR_AuAu_200_ZDC_cent40_80_v1eta, 0, STAR_AuAu_200_ZDC_cent40_80_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerColor(kBlue);
    STAR_v1_ZDC_200GeV_eta_40_80->SetLineColor(kBlue);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerStyle(21);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerSize(1.1);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_0_5 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent0_5_pbin, STAR_AuAu_200_ZDC_TPC_cent0_5_pT, 0, STAR_AuAu_200_ZDC_TPC_cent0_5_pTerr);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_pt_0_5->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerStyle(20);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_5_40 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent5_40_pbin, STAR_AuAu_200_ZDC_TPC_cent5_40_pT, 0, STAR_AuAu_200_ZDC_TPC_cent5_40_pTerr);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerColor(kCyan+2);
    STAR_v1_ZDC_200GeV_pt_5_40->SetLineColor(kCyan+2);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerStyle(29);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerSize(1.7);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent40_80_pbin, STAR_AuAu_200_ZDC_TPC_cent40_80_pT, 0, STAR_AuAu_200_ZDC_TPC_cent40_80_pTerr);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_pt_40_80->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerStyle(24);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerSize(1.2);


    # include "../../published_results/PhysRevLett111_232302.h" // spectator v1

    TH1D * ALICE_v1odd_c10_60 = new TH1D("ALICE_v1odd_c10_60", "", 5, etarap);
    for (int i = 0; i<5; i++) {
        ALICE_v1odd_c10_60->SetBinContent(i+1, ALICE_v1odd_10_60[i]);
        ALICE_v1odd_c10_60->SetBinError(i+1, ALICE_v1odd_10_60_err[i]);
    }
    ALICE_v1odd_c10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_c10_60->SetLineColor(kMagenta);
    ALICE_v1odd_c10_60->SetMarkerStyle(21);
    ALICE_v1odd_c10_60->SetMarkerSize(1.2);

    TH1D * ALICE_v1odd_pT_5_80 = new TH1D("ALICE_v1odd_pT_5_80", "", 10, ALICEpTbins);
    for (int i = 0; i<10; i++) {
        ALICE_v1odd_pT_5_80->SetBinContent(i+1, ALICE_v1odd_pT[i]);
        ALICE_v1odd_pT_5_80->SetBinError(i+1, ALICE_v1odd_pT_err[i]);
    }
    ALICE_v1odd_pT_5_80->SetMarkerColor(kMagenta);
    ALICE_v1odd_pT_5_80->SetLineColor(kMagenta);
    ALICE_v1odd_pT_5_80->SetMarkerStyle(21);
    ALICE_v1odd_pT_5_80->SetMarkerSize(1.1);



    TPaveText * txCMS = new TPaveText(0.164, 0.930, 0.377, 0.97,"NDC");
    SetTPaveTxt(txCMS, 20);
    txCMS->AddText("#bf{CMS} #it{Preliminary}");



    TCanvas * cSTAR_200GeV = new TCanvas("cSTAR_200GeV","cSTAR_200GeV",750,700);
    TPad * padSTAR_200GeV = (TPad *) cSTAR_200GeV->cd();
    padSTAR_200GeV->SetTopMargin(0.07);
    // padSTAR_200GeV->SetGrid();
    TH1D * hSTAR_200GeV = new TH1D("hSTAR_200GeV", "", 100, -2.0, 2.0);
    hSTAR_200GeV->SetXTitle("#eta");
    hSTAR_200GeV->SetYTitle("v_{1}^{odd}");
    hSTAR_200GeV->GetYaxis()->SetRangeUser(-0.04, 0.04);
    hSTAR_200GeV->Draw();
    //gAMPTint_10_70->Draw("E3");
    STAR_v1_3PC_200GeV->Draw("same p");
    STAR_v1_mix_200GeV->Draw("same p");
    gint_10_70->SetMarkerColor(kBlue);
    gint_10_70->SetLineColor(kBlue);
    gint_10_70->SetMarkerStyle(21);
    gint_10_70->SetMarkerSize(1.2);
    gint_10_70->Draw("same p");
    // TLegend * legSTAR_200GeV = new TLegend(0.2, 0.783, 0.5, 0.91);
    TLegend * legSTAR_200GeV = new TLegend(0.20, 0.76, 0.42, 0.89);
    SetLegend(legSTAR_200GeV, 20);
    legSTAR_200GeV->AddEntry(gint_10_70,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV (10-70%)","p");
    legSTAR_200GeV->AddEntry(STAR_v1_3PC_200GeV,"v_{1}^{part}, STAR AuAu #sqrt{s_{NN}} = 0.2 TeV, 3PC (10-70%)","p");
    legSTAR_200GeV->AddEntry(STAR_v1_mix_200GeV,"v_{1}^{part}, STAR AuAu #sqrt{s_{NN}} = 0.2 TeV, mixed (20-60%)","p");
    //legSTAR_200GeV->AddEntry(gAMPTint_10_70,"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV (10-70%)");
    legSTAR_200GeV->Draw();
    txCMS->Draw();
    cSTAR_200GeV->Print("plot_comparison_STAR200GeV.png","png");



    TCanvas * cSTAR_62GeV = new TCanvas("cSTAR_62GeV","cSTAR_62GeV",750,700);
    TPad * padSTAR_62GeV = (TPad *) cSTAR_62GeV->cd();
    padSTAR_62GeV->SetTopMargin(0.07);
    // padSTAR_62GeV->SetGrid();
    TH1D * hSTAR_62GeV = new TH1D("hSTAR_62GeV", "", 100, -2.0, 2.0);
    hSTAR_62GeV->SetXTitle("#eta");
    hSTAR_62GeV->SetYTitle("v_{1}^{odd}");
    hSTAR_62GeV->GetYaxis()->SetRangeUser(-0.016, 0.016);
    hSTAR_62GeV->Draw();
    //gAMPTint_10_70->Draw("same E3");
    STAR_v1_3PC_62GeV_eta->Draw("same p");
    STAR_v1_mix_62GeV_eta->Draw("same p");
    STAR_v1_ZDC_62GeV_eta->Draw("same p");
    gint_10_70->Draw("same p");
    // TLegend * legSTAR_62GeV = new TLegend(0.20, 0.18, 0.47, 0.43);
    TLegend * legSTAR_62GeV = new TLegend(0.20, 0.18, 0.47, 0.40);
    SetLegend(legSTAR_62GeV, 20);
    legSTAR_62GeV->SetHeader("10-70% Centrality");
    legSTAR_62GeV->AddEntry(gint_10_70,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV","p");
    legSTAR_62GeV->AddEntry(STAR_v1_3PC_62GeV_eta,"v_{1}^{part}, STAR AuAu #sqrt{s_{NN}} = 62.4GeV, 3PC","p");
    legSTAR_62GeV->AddEntry(STAR_v1_mix_62GeV_eta,"v_{1}^{part}, STAR AuAu #sqrt{s_{NN}} = 62.4GeV, mixed","p");
    legSTAR_62GeV->AddEntry(STAR_v1_ZDC_62GeV_eta,"v_{1}^{spec}, STAR AuAu #sqrt{s_{NN}} = 62.4GeV, ZDC","p");
    //legSTAR_62GeV->AddEntry(gAMPTint_10_70,"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV");
    legSTAR_62GeV->Draw();
    txCMS->Draw();
    cSTAR_62GeV->Print("plot_comparison_STAR62GeV.png","png");


    TCanvas * cALICE = new TCanvas("cALICE","cALICE",750,700);
    TPad * padALICE = (TPad *) cALICE->cd();
    padALICE->SetTopMargin(0.07);
    // padALICE->SetGrid();
    TH1D * hALICE = new TH1D("hALICE", "", 100, -2.0, 2.0);
    hALICE->SetXTitle("#eta");
    hALICE->SetYTitle("v_{1}^{odd}");
    hALICE->GetYaxis()->SetRangeUser(-0.015, 0.015);
    hALICE->Draw();
    //gAMPTint_10_70->Draw("same E3");
    ALICE_v1odd_c10_60->Draw("same");
    gint_10_70->Draw("same p");
    TLegend * legALICE = new TLegend(0.19, 0.21, 0.60, 0.36);
    SetLegend(legALICE, 20);
    legALICE->SetHeader("10-60% Centrality");
    legALICE->AddEntry(gint_10_70,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV","p");
    legALICE->AddEntry(ALICE_v1odd_c10_60,"v_{1}^{spec}, ALICE PbPb #sqrt{s_{NN}} = 2.76TeV","p");
    //legALICE->AddEntry(gAMPTint_10_70,"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV");
    legALICE->Draw();
    txCMS->Draw();
    cALICE->Print("plot_comparison_ALICE_eta.png","png");



    TCanvas * cpT_5_40 = new TCanvas("cpT_5_40","cpT_5_40",750,700);
    TPad * padpT_5_40 = (TPad *) cpT_5_40->cd();
    padpT_5_40->SetTopMargin(0.07);
    TH1D * hpT_5_40 = new TH1D("hpT_5_40", "", 100, 0, 3.5);
    hpT_5_40->SetXTitle("p_{T} (GeV/c)");
    hpT_5_40->SetYTitle("v_{1}^{odd}");
    hpT_5_40->GetYaxis()->SetRangeUser(-0.008, 0.008);
    hpT_5_40->Draw();
    // gAMPTdiff_5_40->Draw("same E3");
    // ampt_v1_pT_eta_0_8_pos[7]->Draw("same E3");
    STAR_v1_ZDC_200GeV_pt_5_40->Draw("same p");
    gdiff_5_40->SetMarkerColor(kBlue);
    gdiff_5_40->SetLineColor(kBlue);
    gdiff_5_40->SetMarkerStyle(21);
    gdiff_5_40->SetMarkerSize(1.1);
    gdiff_5_40->Draw("same p");
    TLegend * legpT_5_40 = new TLegend(0.20, 0.74, 0.49, 0.90);
    SetLegend(legpT_5_40, 20);
    legpT_5_40->SetHeader("5-40% Centrality");
    legpT_5_40->AddEntry(gdiff_5_40,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV","p");
    legpT_5_40->AddEntry(STAR_v1_ZDC_200GeV_pt_5_40,"v_{1}^{spec}, STAR AuAu #sqrt{s_{NN}} = 0.2TeV","p");
    // legpT_5_40->AddEntry(ampt_v1_pT_eta_0_8_pos[7],"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV","pf");
    // legpT_5_40->AddEntry(gAMPTdiff_5_40,"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV","pf");
    legpT_5_40->Draw();
    txCMS->Draw();
    cpT_5_40->Print("plot_pT_5_40_v1odd.png","png");


    TCanvas * cpT_40_80 = new TCanvas("cpT_40_80","cpT_40_80",750,700);
    TPad * padpT_40_80 = (TPad *) cpT_40_80->cd();
    padpT_40_80->SetTopMargin(0.07);
    TH1D * hpT_40_80 = new TH1D("hpT_40_80", "", 100, 0, 3.5);
    hpT_40_80->SetXTitle("p_{T} (GeV/c)");
    hpT_40_80->SetYTitle("v_{1}^{odd}");
    hpT_40_80->GetYaxis()->SetRangeUser(-0.014, 0.014);
    hpT_40_80->Draw();
    //gAMPTdiff_40_80->Draw("same E3");
    // ampt_v1_pT_eta_0_8_pos[8]->Draw("same E3");
    STAR_v1_ZDC_200GeV_pt_40_80->Draw("same p");
    gdiff_40_80->SetMarkerColor(kBlue);
    gdiff_40_80->SetLineColor(kBlue);
    gdiff_40_80->SetMarkerStyle(21);
    gdiff_40_80->SetMarkerSize(1.1);
    gdiff_40_80->Draw("same p");
    TLegend * legpT_40_80 = new TLegend(0.20, 0.74, 0.49, 0.90);
    SetLegend(legpT_40_80, 20);
    legpT_40_80->SetHeader("40-80% Centrality");
    legpT_40_80->AddEntry(gdiff_5_40,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV","p");
    legpT_40_80->AddEntry(STAR_v1_ZDC_200GeV_pt_40_80,"v_{1}^{spec}, STAR AuAu #sqrt{s_{NN}} = 0.2TeV","p");
    // legpT_40_80->AddEntry(gAMPTdiff_40_80,"AMPT PbPb #sqrt{s_{NN}} = 5.02 TeV","pf");
    legpT_40_80->Draw();
    txCMS->Draw();
    cpT_40_80->Print("plot_pT_40_80_v1odd.png","png");


    TCanvas * cpT_5_80 = new TCanvas("cpT_5_80","cpT_5_80",750,700);
    TPad * padpT_5_80 = (TPad *) cpT_5_80->cd();
    padpT_5_80->SetTopMargin(0.07);
    TH1D * hpT_5_80 = new TH1D("hpT_5_80", "", 100, 0, 5);
    hpT_5_80->SetXTitle("p_{T} (GeV/c)");
    hpT_5_80->SetYTitle("v_{1}^{odd}");
    hpT_5_80->GetYaxis()->SetRangeUser(-0.008, 0.008);
    hpT_5_80->Draw();
    // gAMPTdiff_5_80->Draw("same E3");
    //ampt_v1_pT_eta_0_8_pos[9]->Draw("same E3");
    ALICE_v1odd_pT_5_80->Draw("same");
    gdiff_5_80->SetMarkerColor(kBlue);
    gdiff_5_80->SetLineColor(kBlue);
    gdiff_5_80->SetMarkerStyle(21);
    gdiff_5_80->SetMarkerSize(1.1);
    gdiff_5_80->Draw("same p");
    // TLegend * legpT_5_80 = new TLegend(0.21, 0.73, 0.58, 0.89);
    TLegend * legpT_5_80 = new TLegend(0.20, 0.74, 0.57, 0.90);
    SetLegend(legpT_5_80, 20);
    legpT_5_80->SetHeader("10-70% Centrality");
    legpT_5_80->AddEntry(gdiff_5_40,"v_{1}^{part}, CMS PbPb #sqrt{s_{NN}} = 5.02 TeV","p");
    legpT_5_80->AddEntry(ALICE_v1odd_pT_5_80,"v_{1}^{spec}, ALICE PbPb #sqrt{s_{NN}} = 2.76TeV","p");
    // legpT_5_80->AddEntry(gAMPTdiff_5_80,"AMPT (string melting)","pf");
    legpT_5_80->Draw();
    txCMS->Draw();
    cpT_5_80->Print("plot_pT_5_80_v1odd.png","png");


    TCanvas * cSub2Sub3 = new TCanvas("cSub2Sub3","cSub2Sub3",750,700);
    TPad * padSub2Sub3 = (TPad *) cSub2Sub3->cd();
    TH1D * hSub2Sub3 = new TH1D("hSub2Sub3", "", 100, -2.5, 2.5);
    hSub2Sub3->SetXTitle("#eta");
    hSub2Sub3->SetYTitle("v_{1}^{odd}");
    hSub2Sub3->GetYaxis()->SetRangeUser(-0.01, 0.01);
    hSub2Sub3->Draw();
    gint_10_70_N1_sub3->SetMarkerColor(kBlue);
    gint_10_70_N1_sub3->SetLineColor(kBlue);
    gint_10_70_N1_sub3->SetMarkerStyle(21);
    gint_10_70_N1_sub3->SetMarkerSize(1.2);
    gint_10_70_N1_sub3->Draw("same p");
    gint_10_70_N1_sub2->SetMarkerColor(kBlack);
    gint_10_70_N1_sub2->SetLineColor(kBlack);
    gint_10_70_N1_sub2->SetMarkerStyle(24);
    gint_10_70_N1_sub2->SetMarkerSize(1.2);
    gint_10_70_N1_sub2->Draw("same p");
    TLegend * legSub2Sub3 = new TLegend(0.67, 0.78, 0.87, 0.90);
    SetLegend(legSub2Sub3, 20);
    legSub2Sub3->SetHeader("10 - 70%");
    legSub2Sub3->AddEntry(gint_10_70_N1_sub2,"2 subevent","p");
    legSub2Sub3->AddEntry(gint_10_70_N1_sub3,"3 subevent","p");
    legSub2Sub3->Draw();
    cSub2Sub3->Print("plot_2sub_3sub.png","png");



    TCanvas * cAMPT_eta = new TCanvas("cAMPT_eta","cAMPT_eta",750,700);
    TPad * padAMPT_eta = (TPad *) cAMPT_eta->cd();
    padAMPT_eta->SetTopMargin(0.07);
    // padAMPT_eta->SetGrid();
    TH1D * hAMPT_eta = new TH1D("hAMPT_eta", "", 100, -2.0, 2.0);
    hAMPT_eta->SetXTitle("#eta");
    hAMPT_eta->SetYTitle("v_{1}^{odd}");
    hAMPT_eta->GetYaxis()->SetRangeUser(-0.0225, 0.0225);
    hAMPT_eta->Draw();
    gAMPTint_10_70->Draw("E3");
    //ampt_v1true_eta[5]->Draw("same E3");
    gint_10_70->SetMarkerColor(kBlue);
    gint_10_70->SetLineColor(kBlue);
    gint_10_70->SetMarkerStyle(21);
    gint_10_70->SetMarkerSize(1.2);
    gint_10_70->Draw("same p");
    TLegend * legAMPT_eta = new TLegend(0.2, 0.81, 0.50, 0.90);
    SetLegend(legAMPT_eta, 20);
    legAMPT_eta->AddEntry(gint_10_70,"CMS PbPb #sqrt{s_{NN}} = 5.02 TeV (10-70%)","p");
    legAMPT_eta->AddEntry(gAMPTint_10_70,"AMPT","f");
    // legAMPT_eta->Draw();
    legpT_5_80->Draw();
    txCMS->Draw();
    cAMPT_eta->Print("plot_AMPT_eta.png","png");



}
