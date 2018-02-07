# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "Riostream.h"
# include <iostream>

using namespace std;

# include "src/HiEvtPlaneList.h"
# include "src/style.h"

using namespace hi;
static const int ncentbins = 13;
static const int cminCENT[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20,  60};
static const int cmaxCENT[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60, 100};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const int nbinsETA = 14;
static const double eminETA[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0, -2.4,  0.0};
static const double emaxETA[] = {-2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4,  0.0,  2.4};
static const double etaMid[] = {-2.2, -1.8, -1.4, -1.0, -0.6, -0.2,  0.2,  0.6,  1.0,  1.4,  1.8,  2.2};
TString etags[] = {"-24_-20", "-20_-16", "-16_-12", "-12_-8", "-8_-4", "-4_0", "0_4", "4_8", "8_12", "12_16", "16_20", "20_24",
                   "-24_0", "0_24"};
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static int NANALS = 16;
TString ANAL[] = {"N1MCm22SUB2", "N1MCp22SUB2", "N1MCm22SUB3", "N1MCp22SUB3",
                  "N1SUB2",      "N1ASUB2",     "N1BSUB2",     "N112SUB2",    "N112ASUB2",   "N112BSUB2",
                  "N1SUB3",      "N1ASUB3",     "N1BSUB3"};

# include "src/getRatios.h"

TFile * finPt;
TFile * finEta;
TFile * fout;

void comparison()
{
    TH1::SetDefaultSumw2();

    finPt = new TFile("hists/MH_combined_Pt.root","read");

    for (int ebin = 0; ebin<nbinsETA; ebin++) {
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            TString mtag = Form("MH_nominal/eta_%s/%d_%d",etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]);

            N1MCm22SUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1MCm22SUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1MCp22SUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1MCp22SUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1MCm22SUB3_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1MCm22SUB3_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1MCp22SUB3_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1MCp22SUB3_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1SUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1SUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1ASUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1ASUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1BSUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1BSUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N112SUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N112SUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N112ASUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N112ASUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N112BSUB2_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N112BSUB2_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1SUB3_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1SUB3_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1ASUB3_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1ASUB3_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
            N1BSUB3_pT[ebin][cbin] = (TH1D *) finPt->Get(Form("%s/N1BSUB3_eta_%s_%d_%d",mtag.Data(),etags[ebin].Data(),cminCENT[cbin],cmaxCENT[cbin]));
        }
    }

    finEta = new TFile("hists/MH_combined_Eta.root","read");

    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TString mtag = Form("MH_nominal/%d_%d",cminCENT[cbin],cmaxCENT[cbin]);

        N1MCm22SUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MCm22SUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1MCp22SUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MCp22SUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1MC22SUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MC22SUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1MCm22SUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MCm22SUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1MCp22SUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MCp22SUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1MC22SUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1MC22SUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1SUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1SUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1ASUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1ASUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1BSUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1BSUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N112SUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N112SUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N112ASUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N112ASUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N112BSUB2_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N112BSUB2_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1SUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1SUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1ASUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1ASUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
        N1BSUB3_eta[cbin] = (TH1D *) finEta->Get(Form("%s/N1BSUB3_%d_%d",mtag.Data(),cminCENT[cbin],cmaxCENT[cbin]));
    }

    # include "../../published_results/PHOBOS_AuAu.h" // participant v1

    TH1D * PHOBOS_AuAu_Mixed_200GeV = new TH1D("PHOBOS_AuAu_Mixed_200GeV", "", PHOBOS_AuAu_nebins, PHOBOS_AuAu_eta);
    TH1D * PHOBOS_AuAu_2sub_200GeV = new TH1D("PHOBOS_AuAu_2sub_200GeV", "", PHOBOS_AuAu_nebins, PHOBOS_AuAu_eta);
    for (int i = 0; i<PHOBOS_AuAu_nebins; i++) {
        PHOBOS_AuAu_Mixed_200GeV->SetBinContent(i+1, PHOBOS_AuAu_mixed_v1_3[i]);
        PHOBOS_AuAu_Mixed_200GeV->SetBinError(i+1, PHOBOS_AuAu_mixed_v1Err_3[i]);

        PHOBOS_AuAu_Mixed_200GeV->SetMarkerColor(kBlack);
        PHOBOS_AuAu_Mixed_200GeV->SetLineColor(kBlack);
        PHOBOS_AuAu_Mixed_200GeV->SetMarkerStyle(24);
        PHOBOS_AuAu_Mixed_200GeV->SetMarkerSize(1.2);

        PHOBOS_AuAu_2sub_200GeV->SetBinContent(i+1, PHOBOS_AuAu_sym_v1_3[i]);
        PHOBOS_AuAu_2sub_200GeV->SetBinError(i+1, PHOBOS_AuAu_sym_v1Err_3[i]);

        PHOBOS_AuAu_2sub_200GeV->SetMarkerColor(kBlack);
        PHOBOS_AuAu_2sub_200GeV->SetLineColor(kBlack);
        PHOBOS_AuAu_2sub_200GeV->SetMarkerStyle(21);
        PHOBOS_AuAu_2sub_200GeV->SetMarkerSize(1.2);
    }

    # include "../../published_results/PhysRevLett_92_062301.h" // participant v1

    TGraphErrors * STAR_v1_3PC_200GeV = new TGraphErrors(24, STAR_v1_3PC_200GeV_eta, STAR_v1_3PC_200GeV_val, 0, STAR_v1_3PC_200GeV_err);
    STAR_v1_3PC_200GeV->SetMarkerColor(kBlue);
    STAR_v1_3PC_200GeV->SetLineColor(kBlue);
    STAR_v1_3PC_200GeV->SetMarkerStyle(30);
    STAR_v1_3PC_200GeV->SetMarkerSize(1.5);


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
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.5);

    TGraphErrors * STAR_v1_mix_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_mix_n, STAR_AuAu_62GeV_Fig1_mix_eta, STAR_AuAu_62GeV_Fig1_mix_v1, 0, STAR_AuAu_62GeV_Fig1_mix_v1err);
    STAR_v1_mix_62GeV_eta->SetMarkerColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetLineColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetMarkerStyle(24);
    STAR_v1_mix_62GeV_eta->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_ZDC_n, STAR_AuAu_62GeV_Fig1_ZDC_eta, STAR_AuAu_62GeV_Fig1_ZDC_v1, 0, STAR_AuAu_62GeV_Fig1_ZDC_v1err);
    STAR_v1_ZDC_62GeV_eta->SetMarkerColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetLineColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetMarkerStyle(25);
    STAR_v1_ZDC_62GeV_eta->SetMarkerSize(1.1);

    TGraphErrors * STAR_v1_3PC_62GeV_pT = new TGraphErrors(STAR_AuAu_62GeV_3PC_pT_n, STAR_AuAu_62GeV_3PC_pTval, STAR_AuAu_62GeV_3PC_pT_v1, 0, STAR_AuAu_62GeV_3PC_pT_v1_err);
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.5);


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
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerSize(1.5);

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
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerSize(1.5);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent40_80_pbin, STAR_AuAu_200_ZDC_TPC_cent40_80_pT, 0, STAR_AuAu_200_ZDC_TPC_cent40_80_pTerr);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerColor(kBlue);
    STAR_v1_ZDC_200GeV_pt_40_80->SetLineColor(kBlue);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerStyle(21);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerSize(1.1);


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

    TH1D * ALICE_v1even_pT_5_80 = new TH1D("ALICE_v1even_pT_5_80", "", 10, ALICEpTbins);
    for (int i = 0; i<10; i++) {
        ALICE_v1even_pT_5_80->SetBinContent(i+1, ALICE_v1even_pT[i]);
        ALICE_v1even_pT_5_80->SetBinError(i+1, ALICE_v1even_pT_err[i]);
    }
    ALICE_v1even_pT_5_80->SetMarkerColor(kMagenta);
    ALICE_v1even_pT_5_80->SetLineColor(kMagenta);
    ALICE_v1even_pT_5_80->SetMarkerStyle(20);
    ALICE_v1even_pT_5_80->SetMarkerSize(1.2);




    TCanvas * c0 = new TCanvas("c0","c0",750,700);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetGrid();
    TH1D * h0 = new TH1D("h0", "", 100, -2.6, 2.6);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetRangeUser(-0.05, 0.05);
    h0->Draw();
    PHOBOS_AuAu_2sub_200GeV->Draw("same");
    PHOBOS_AuAu_Mixed_200GeV->Draw("same");
    STAR_v1_3PC_200GeV->Draw("same p");
    STAR_v1_mix_200GeV->Draw("same p");
    N1SUB2_eta[12]->SetMarkerColor(kBlue);
    N1SUB2_eta[12]->SetLineColor(kBlue);
    N1SUB2_eta[12]->SetMarkerStyle(21);
    N1SUB2_eta[12]->SetMarkerSize(1.2);
    N1SUB2_eta[12]->Draw("same");
    TLegend * leg0 = new TLegend(0.2, 0.18, 0.5, 0.38);
    SetLegend(leg0, 18);
    leg0->AddEntry(N1SUB2_eta[12],"CMS PbPb 5.02 TeV, SP (20-60%)","p");
    leg0->AddEntry(PHOBOS_AuAu_2sub_200GeV,"PHOBOS 2SUB #sqrt{s_{NN}}=200 GeV (6-40%)","p");
    leg0->AddEntry(PHOBOS_AuAu_Mixed_200GeV,"PHOBOS Mixed #sqrt{s_{NN}}=200 GeV (6-40%)","p");
    leg0->AddEntry(STAR_v1_3PC_200GeV,"STAR 3PC #sqrt{s_{NN}}=200 GeV (10-70%)","p");
    leg0->AddEntry(STAR_v1_mix_200GeV,"STAR mixed #sqrt{s_{NN}}=200 GeV (20-60%)","p");
    leg0->Draw();
    c0->Print("plot_comparison_00.png","png");


    TCanvas * c1 = new TCanvas("c1","c1",750,700);
    TPad * pad1 = (TPad *) c1->cd();
    pad1->SetGrid();
    TH1D * h1 = new TH1D("h1", "", 100, -2.5, 2.5);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetRangeUser(-0.015, 0.015);
    h1->Draw();
    STAR_v1_3PC_62GeV_eta->Draw("same p");
    STAR_v1_mix_62GeV_eta->Draw("same p");
    STAR_v1_ZDC_62GeV_eta->Draw("same p");
    ALICE_v1odd_c10_60->Draw("same");
    N1SUB2_eta[12]->SetMarkerColor(kBlue);
    N1SUB2_eta[12]->SetLineColor(kBlue);
    N1SUB2_eta[12]->SetMarkerStyle(21);
    N1SUB2_eta[12]->SetMarkerSize(1.2);
    N1SUB2_eta[12]->Draw("same");
    N112SUB2_eta[12]->SetMarkerColor(kGreen+2);
    N112SUB2_eta[12]->SetLineColor(kGreen+2);
    N112SUB2_eta[12]->SetMarkerStyle(20);
    N112SUB2_eta[12]->SetMarkerSize(1.2);
    // N112SUB2_eta[12]->Draw("same");
    TLegend * leg1 = new TLegend(0.20, 0.18, 0.60, 0.38);
    SetLegend(leg1, 18);
    leg1->AddEntry(N1SUB2_eta[12],"CMS PbPb 5.02 TeV, SP (20-60%)","p");
    // leg1->AddEntry(N112SUB2_eta[12],"CMS PbPb 5.02 TeV, mixed (20-60%)","p");
    leg1->AddEntry(ALICE_v1odd_c10_60,"ALICE PbPb 2.76TeV, SP (10-60%)","p");
    leg1->AddEntry(STAR_v1_3PC_62GeV_eta,"STAR AuAu 62.4GeV, 3PC (10-70%)","p");
    leg1->AddEntry(STAR_v1_mix_62GeV_eta,"STAR AuAu 62.4GeV, mixed (10-70%)","p");
    leg1->AddEntry(STAR_v1_ZDC_62GeV_eta,"STAR AuAu 62.4GeV, ZDC (10-70%)","p");
    leg1->Draw();
    c1->Print("plot_comparison_01.png","png");


    TCanvas * c2 = new TCanvas("c2","c2",750,700);
    TPad * pad2 = (TPad *) c2->cd();
    pad2->SetGrid();
    TH1D * h2 = new TH1D("h1", "", 100, 0, 5);
    h2->SetXTitle("p_{T} (GeV/c)");
    h2->SetYTitle("v_{1}^{odd}");
    h2->GetYaxis()->SetRangeUser(-0.015, 0.015);
    h2->Draw();
    STAR_v1_ZDC_200GeV_pt_0_5->Draw("same p");
    STAR_v1_ZDC_200GeV_pt_5_40->Draw("same p");
    STAR_v1_ZDC_200GeV_pt_40_80->Draw("same p");
    ALICE_v1odd_pT_5_80->Draw("same");
    // N1SUB2_pT[12][13]->SetMarkerColor(kBlue);
    // N1SUB2_pT[12][13]->SetLineColor(kBlue);
    // N1SUB2_pT[12][13]->SetMarkerStyle(21);
    // N1SUB2_pT[12][13]->SetMarkerSize(1.2);
    // N1SUB2_pT[12][13]->Draw("same");
    TLegend * leg2 = new TLegend(0.20, 0.18, 0.60, 0.38);
    SetLegend(leg2, 18);
    leg2->AddEntry(ALICE_v1odd_pT_5_80,"ALICE PbPb 2.76TeV, SP (5-80%)","p");
    leg2->AddEntry(STAR_v1_ZDC_200GeV_pt_0_5,"STAR AuAu 200GeV, ZDC (0-5%)","p");
    leg2->AddEntry(STAR_v1_ZDC_200GeV_pt_5_40,"STAR AuAu 200GeV, ZDC (5-40%)","p");
    leg2->AddEntry(STAR_v1_ZDC_200GeV_pt_40_80,"STAR AuAu 200GeV, ZDC (40-80%)","p");
    leg2->Draw();


    TCanvas * c3 = new TCanvas("c3","c3",750,700);
    TPad * pad3 = (TPad *) c3->cd();
    pad3->SetGrid();
    N1MCm22SUB2_pT[13][12]->Draw("same");

}
