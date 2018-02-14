# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TMath.h"
# include <iostream>

using namespace std;

TGraphErrors * STAR_v1_3PC_200GeV;
TGraphErrors * STAR_v1_mix_200GeV;
TGraphErrors * STAR_v1_ZDC_200GeV_eta_0_5;
TGraphErrors * STAR_v1_ZDC_200GeV_eta_5_40;
TGraphErrors * STAR_v1_ZDC_200GeV_eta_40_80;
TGraphErrors * STAR_v1_3PC_62GeV_eta;
TGraphErrors * STAR_v1_mix_62GeV_eta;
TGraphErrors * STAR_v1_ZDC_62GeV_eta;
TGraphErrors * STAR_v1_3PC_62GeV_pT;
TH1D * ALICE_v1odd_c10_60;
TH1D * ALICE_v1odd_pT_5_80;
TH1D * ALICE_v1even_pT_5_80;
TH1D * ATLAS_PbPb[6];

TFile * fout_PRL_92_062301;
TFile * fout_PRC_72_14904;
TFile * fout_PRL_101_252301;
TFile * fout_PRC_73_034903;
TFile * fout_PRL_111_232302;
TFile * fout_PRC_86_014907;


void getPublishedResults() {

    if (!fopen("../../published_results/data","r")) system("mkdir ../../published_results/data");

    # include "../../published_results/PhysRevLett_92_062301.h" // STAR participant v1 (200 GeV) 10 to 70%
    fout_PRL_92_062301 = new TFile("../../published_results/data/PRL_92_062301.root","recreate");
    fout_PRL_92_062301->cd();
    STAR_v1_3PC_200GeV = new TGraphErrors(24, STAR_v1_3PC_200GeV_eta, STAR_v1_3PC_200GeV_val, 0, STAR_v1_3PC_200GeV_err);
    STAR_v1_3PC_200GeV->SetName("STAR_v1odd_3PC_200GeV_c_10_70");
    STAR_v1_3PC_200GeV->GetXaxis()->SetTitle("#eta");
    STAR_v1_3PC_200GeV->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_3PC_200GeV->Write();
    fout_PRL_92_062301->Close();

    # include "../../published_results/PhysRevC72_14904.h" // STAR participant v1 (200GeV)
    fout_PRC_72_14904 = new TFile("../../published_results/data/PRC_72_14904.root","recreate");
    fout_PRC_72_14904->cd();
    STAR_v1_mix_200GeV = new TGraphErrors(STAR_AuAu_Mixed_neta, STAR_AuAu_Mixed_eta, STAR_AuAu_Mixed_v1, 0, STAR_AuAu_Mixed_v1Err);
    STAR_v1_mix_200GeV->SetName("STAR_v1odd_mix_200GeV_c_10_70");
    STAR_v1_mix_200GeV->GetXaxis()->SetTitle("#eta");
    STAR_v1_mix_200GeV->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_mix_200GeV->Write();
    fout_PRC_72_14904->Close();

    # include "../../published_results/PhysRevLett101_252301.h" // spectator v1 (200 GeV)
    fout_PRL_101_252301 = new TFile("../../published_results/data/PRL_101_252301.root","recreate");
    fout_PRL_101_252301->cd();
    STAR_v1_ZDC_200GeV_eta_0_5 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent0_5_eta, STAR_AuAu_200_ZDC_cent0_5_v1eta, 0, STAR_AuAu_200_ZDC_cent0_5_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_0_5->SetName("STAR_v1odd_ZDC_200GeV_eta_0_5");
    STAR_v1_ZDC_200GeV_eta_0_5->GetXaxis()->SetTitle("#eta");
    STAR_v1_ZDC_200GeV_eta_0_5->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_ZDC_200GeV_eta_5_40 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent5_40_eta, STAR_AuAu_200_ZDC_cent5_40_v1eta, 0, STAR_AuAu_200_ZDC_cent5_40_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_5_40->SetName("STAR_v1odd_ZDC_200GeV_eta_5_40");
    STAR_v1_ZDC_200GeV_eta_5_40->GetXaxis()->SetTitle("#eta");
    STAR_v1_ZDC_200GeV_eta_5_40->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_ZDC_200GeV_eta_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent40_80_eta, STAR_AuAu_200_ZDC_cent40_80_v1eta, 0, STAR_AuAu_200_ZDC_cent40_80_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_40_80->SetName("STAR_v1odd_ZDC_200GeV_eta_40_80");
    STAR_v1_ZDC_200GeV_eta_40_80->GetXaxis()->SetTitle("#eta");
    STAR_v1_ZDC_200GeV_eta_40_80->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_ZDC_200GeV_eta_0_5->Write();
    STAR_v1_ZDC_200GeV_eta_5_40->Write();
    STAR_v1_ZDC_200GeV_eta_40_80->Write();
    fout_PRL_101_252301->Close();

    # include "../../published_results/PhysRevC73_034903.h" // participant and spectator v1 (62.3 GeV)
    fout_PRC_73_034903 = new TFile("../../published_results/data/PRC_73_034903.root","recreate");
    fout_PRC_73_034903->cd();
    STAR_v1_3PC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_3PC_n, STAR_AuAu_62GeV_Fig1_3PC_eta, STAR_AuAu_62GeV_Fig1_3PC_v1, 0, STAR_AuAu_62GeV_Fig1_3PC_v1err);
    STAR_v1_3PC_62GeV_eta->SetName("STAR_v1odd_3PC_62GeV_eta_c_10_70");
    STAR_v1_3PC_62GeV_eta->GetXaxis()->SetTitle("#eta");
    STAR_v1_3PC_62GeV_eta->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_mix_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_mix_n, STAR_AuAu_62GeV_Fig1_mix_eta, STAR_AuAu_62GeV_Fig1_mix_v1, 0, STAR_AuAu_62GeV_Fig1_mix_v1err);
    STAR_v1_mix_62GeV_eta->SetName("STAR_v1odd_mix_62GeV_eta_c_10_70");
    STAR_v1_mix_62GeV_eta->GetXaxis()->SetTitle("#eta");
    STAR_v1_mix_62GeV_eta->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_ZDC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_ZDC_n, STAR_AuAu_62GeV_Fig1_ZDC_eta, STAR_AuAu_62GeV_Fig1_ZDC_v1, 0, STAR_AuAu_62GeV_Fig1_ZDC_v1err);
    STAR_v1_ZDC_62GeV_eta->SetName("STAR_v1odd_ZDC_62GeV_eta_c_10_70");
    STAR_v1_ZDC_62GeV_eta->GetXaxis()->SetTitle("#eta");
    STAR_v1_ZDC_62GeV_eta->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_3PC_62GeV_pT = new TGraphErrors(STAR_AuAu_62GeV_3PC_pT_n, STAR_AuAu_62GeV_3PC_pTval, STAR_AuAu_62GeV_3PC_pT_v1, 0, STAR_AuAu_62GeV_3PC_pT_v1_err);
    STAR_v1_3PC_62GeV_pT->SetName("STAR_v1odd_3PC_62GeV_pT_c_10_70");
    STAR_v1_3PC_62GeV_pT->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    STAR_v1_3PC_62GeV_pT->GetYaxis()->SetTitle("v_{1}^{odd}");
    STAR_v1_3PC_62GeV_eta->Write();
    STAR_v1_mix_62GeV_eta->Write();
    STAR_v1_ZDC_62GeV_eta->Write();
    STAR_v1_3PC_62GeV_pT->Write();
    fout_PRC_73_034903->Close();

    # include "../../published_results/PhysRevLett111_232302.h" // spectator v1
    fout_PRL_111_232302 = new TFile("../../published_results/data/PRL_111_232302.root","recreate");
    fout_PRL_111_232302->cd();
    ALICE_v1odd_c10_60 = new TH1D("ALICE_v1odd_eta_c10_60", "", 5, etarap);
    ALICE_v1odd_c10_60->SetXTitle("#eta");
    ALICE_v1odd_c10_60->SetYTitle("v_{1}^{odd}");
    for (int i = 0; i<5; i++) {
        ALICE_v1odd_c10_60->SetBinContent(i+1, ALICE_v1odd_10_60[i]);
        ALICE_v1odd_c10_60->SetBinError(i+1, ALICE_v1odd_10_60_err[i]);
    }
    ALICE_v1odd_c10_60->Write();
    ALICE_v1odd_pT_5_80 = new TH1D("ALICE_v1odd_pT_5_80", "", 10, ALICEpTbins);
    ALICE_v1odd_pT_5_80->SetXTitle("p_{T} (GeV/c)");
    ALICE_v1odd_pT_5_80->SetYTitle("v_{1}^{odd}");
    for (int i = 0; i<10; i++) {
        ALICE_v1odd_pT_5_80->SetBinContent(i+1, ALICE_v1odd_pT[i]);
        ALICE_v1odd_pT_5_80->SetBinError(i+1, ALICE_v1odd_pT_err[i]);
    }
    ALICE_v1odd_pT_5_80->Write();
    ALICE_v1even_pT_5_80 = new TH1D("ALICE_v1even_pT_5_80", "", 10, ALICEpTbins);
    ALICE_v1even_pT_5_80->SetXTitle("p_{T} (GeV/c)");
    ALICE_v1even_pT_5_80->SetYTitle("v_{1}^{even}");
    for (int i = 0; i<10; i++) {
        ALICE_v1even_pT_5_80->SetBinContent(i+1, ALICE_v1even_pT[i]);
        ALICE_v1even_pT_5_80->SetBinError(i+1, ALICE_v1even_pT_err[i]);
    }
    ALICE_v1even_pT_5_80->Write();
    fout_PRL_111_232302->Close();

    //-- ATLAS PbPb, 2.76 TeV, 2-particle correlations (participant)
    # include "../../published_results/PhysRevC86_014907.h"
    fout_PRC_86_014907 = new TFile("../../published_results/data/PRC_86_014907.root","recreate");
    fout_PRC_86_014907->cd();
    int ATLAScbins[7] = {0, 5, 10, 20, 30, 40, 50};
    for (int i = 0; i<6; i++) {
        ATLAS_PbPb[i] = new TH1D(Form("ATLAS_v1even_2PC_PbPb_%d_%d",ATLAScbins[i],ATLAScbins[i+1]), "", 85, 0.45, 9.05);
        ATLAS_PbPb[i]->SetXTitle("p_{T} (GeV/c)");
        ATLAS_PbPb[i]->SetYTitle("v_{1}^{even}");
    }
    for (int pbin = 1; pbin<=85; pbin++) {
        ATLAS_PbPb[0]->SetBinContent(pbin,v1ATLAS_c00to05[pbin-1]);
        ATLAS_PbPb[0]->SetBinError(pbin,v1ATLAS_c00to05_err[pbin-1]);
        ATLAS_PbPb[1]->SetBinContent(pbin,v1ATLAS_c05to10[pbin-1]);
        ATLAS_PbPb[1]->SetBinError(pbin,v1ATLAS_c05to10_err[pbin-1]);
        ATLAS_PbPb[2]->SetBinContent(pbin,v1ATLAS_c10to20[pbin-1]);
        ATLAS_PbPb[2]->SetBinError(pbin,v1ATLAS_c10to20_err[pbin-1]);
        ATLAS_PbPb[3]->SetBinContent(pbin,v1ATLAS_c20to30[pbin-1]);
        ATLAS_PbPb[3]->SetBinError(pbin,v1ATLAS_c20to30_err[pbin-1]);
        ATLAS_PbPb[4]->SetBinContent(pbin,v1ATLAS_c30to40[pbin-1]);
        ATLAS_PbPb[4]->SetBinError(pbin,v1ATLAS_c30to40_err[pbin-1]);
        ATLAS_PbPb[5]->SetBinContent(pbin,v1ATLAS_c40to50[pbin-1]);
        ATLAS_PbPb[5]->SetBinError(pbin,v1ATLAS_c40to50_err[pbin-1]);
    }
    for (int i = 0; i<6; i++) {
        ATLAS_PbPb[i]->SetMarkerColor(kBlack);
        ATLAS_PbPb[i]->SetMarkerStyle(27);
        ATLAS_PbPb[i]->SetMarkerSize(0.2);
        ATLAS_PbPb[i]->SetLineColor(kGray+1);
        ATLAS_PbPb[i]->SetLineWidth(5);
        ATLAS_PbPb[i]->SetFillColor(kGray+1);
        ATLAS_PbPb[i]->SetFillStyle(1001);
        ATLAS_PbPb[i]->SetLineWidth(2);
        ATLAS_PbPb[i]->Write();
    }
    fout_PRC_86_014907->Close();

    cout << "Output root files written to ../../published_results/data/ \n...Done" << endl;

}
