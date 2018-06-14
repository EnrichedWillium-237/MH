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

TFile * fin0 = new TFile("PRC_72_14904.root","read");
TFile * fin1 = new TFile("PRC_73_034903.root","read");
TFile * fin2 = new TFile("PRC_86_014907.root","read");
TFile * fin3 = new TFile("PRL_101_252301.root","read");
TFile * fin4 = new TFile("PRL_111_232302.root","read");
TFile * fin5 = new TFile("PRL_92_062301.root","read");
TFile * fin6 = new TFile("PRL_97_012301.root","read");
TFile * fout;

void combine() {

    fout = new TFile("published_results.root", "recreate");

    TDirectory * dirodd = (TDirectory *) fout->mkdir("v1odd");
    TDirectory * direven = (TDirectory *) fout->mkdir("v1even");


    //----- v1odd
    dirodd->cd();


    //-- PHOBOS
    TGraphErrors * gPHOBOSodd_0 = (TGraphErrors *) fin6->Get("PHOBOS_EP_19GeV_15_30");
    gPHOBOSodd_0->SetName("PHOBOS_EP_19GeV_15_30");
    gPHOBOSodd_0->Write();
    TGraphErrors * gPHOBOSodd_1 = (TGraphErrors *) fin6->Get("PHOBOS_EP_62GeV_6_40");
    gPHOBOSodd_1->SetName("PHOBOS_EP_62GeV_6_40");
    gPHOBOSodd_1->Write();
    TGraphErrors * gPHOBOSodd_2 = (TGraphErrors *) fin6->Get("PHOBOS_EP_130GeV_6_40");
    gPHOBOSodd_2->SetName("PHOBOS_EP_130GeV_6_40");
    gPHOBOSodd_2->Write();
    TGraphErrors * gPHOBOSodd_3 = (TGraphErrors *) fin6->Get("PHOBOS_EP_200GeV_6_40");
    gPHOBOSodd_3->SetName("PHOBOS_EP_200GeV_6_40");
    gPHOBOSodd_3->Write();

    TGraphErrors * gPHOBOSodd_4 = (TGraphErrors *) fin6->Get("PHOBOS_mixed_19GeV_15_30");
    gPHOBOSodd_4->SetName("PHOBOS_mixed_19GeV_15_30");
    gPHOBOSodd_4->Write();
    TGraphErrors * gPHOBOSodd_5 = (TGraphErrors *) fin6->Get("PHOBOS_mixed_62GeV_6_40");
    gPHOBOSodd_5->SetName("PHOBOS_mixed_62GeV_6_40");
    gPHOBOSodd_5->Write();
    TGraphErrors * gPHOBOSodd_6 = (TGraphErrors *) fin6->Get("PHOBOS_mixed_130GeV_6_40");
    gPHOBOSodd_6->SetName("PHOBOS_mixed_130GeV_6_40");
    gPHOBOSodd_6->Write();
    TGraphErrors * gPHOBOSodd_7 = (TGraphErrors *) fin6->Get("PHOBOS_mixed_200GeV_6_40");
    gPHOBOSodd_7->SetName("PHOBOS_mixed_200GeV_6_40");
    gPHOBOSodd_7->Write();


    //-- STAR
    TGraphErrors * gSTARodd0_0 = (TGraphErrors *) fin0->Get("STAR_v1odd_mix_200GeV_c_10_70");
    gSTARodd0_0->SetName("STAR_v1odd_eta_mix_200GeV_10_70");
    gSTARodd0_0->Write();

    TGraphErrors * gSTARodd1_0 = (TGraphErrors *) fin1->Get("STAR_v1odd_3PC_62GeV_eta_c_10_70");
    gSTARodd1_0->SetName("STAR_v1odd_eta_3PC_62GeV_10_70");
    gSTARodd1_0->Write();
    TGraphErrors * gSTARodd1_1 = (TGraphErrors *) fin1->Get("STAR_v1odd_mix_62GeV_eta_c_10_70");
    gSTARodd1_1->SetName("STAR_v1odd_eta_mix_62GeV_10_70");
    gSTARodd1_1->Write();
    TGraphErrors * gSTARodd1_2 = (TGraphErrors *) fin1->Get("STAR_v1odd_ZDC_62GeV_eta_c_10_70");
    gSTARodd1_2->SetName("STAR_v1odd_eta_ZDC_62GeV_10_70");
    gSTARodd1_2->Write();

    TGraphErrors * gSTARodd2_0 = (TGraphErrors *) fin3->Get("STAR_v1odd_ZDC_200GeV_eta_0_5");
    gSTARodd2_0->SetName("STAR_v1odd_eta_ZDC_200GeV_0_5");
    gSTARodd2_0->Write();
    TGraphErrors * gSTARodd2_1 = (TGraphErrors *) fin3->Get("STAR_v1odd_ZDC_200GeV_eta_5_40");
    gSTARodd2_1->SetName("STAR_v1odd_eta_ZDC_200GeV_5_40");
    gSTARodd2_1->Write();
    TGraphErrors * gSTARodd2_2 = (TGraphErrors *) fin3->Get("STAR_v1odd_ZDC_200GeV_eta_40_80");
    gSTARodd2_2->SetName("STAR_v1odd_eta_ZDC_200GeV_40_80");
    gSTARodd2_2->Write();

    TGraphErrors * gSTARodd3_0 = (TGraphErrors *) fin5->Get("STAR_v1odd_3PC_200GeV_c_10_70");
    gSTARodd3_0->SetName("STAR_v1odd_eta_3PC_200GeV_10_70");
    gSTARodd3_0->Write();

    TGraphErrors * gSTARodd1_3 = (TGraphErrors *) fin1->Get("STAR_v1odd_3PC_62GeV_pT_c_10_70");
    gSTARodd1_3->SetName("STAR_v1odd_pT_3PC_62GeV_10_70");
    gSTARodd1_3->Write();


    //-- ALICE
    TH1D * hALICE0_0 = (TH1D *) fin4->Get("ALICE_v1odd_eta_c10_60");
    int num;
    Double_t x[500], y[500], xerr[500], yerr[500];
    num = hALICE0_0->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hALICE0_0->GetBinCenter(i+1);
        y[i] = hALICE0_0->GetBinContent(i+1);
        xerr[i] = 0.5*hALICE0_0->GetBinWidth(i+1);
        yerr[i] = hALICE0_0->GetBinError(i+1);
    }
    TGraphErrors * gALICE0_0 = new TGraphErrors(num, x, y, 0, yerr);
    gALICE0_0->SetName("ALICE_v1odd_eta_2TeV_10_60");
    gALICE0_0->GetXaxis()->SetTitle("#eta");
    gALICE0_0->GetYaxis()->SetTitle("v_{1}^{odd}");
    gALICE0_0->Write();

    TH1D * hALICE1_0 = (TH1D *) fin4->Get("ALICE_v1odd_pT_5_80");
    num = hALICE1_0->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hALICE1_0->GetBinCenter(i+1);
        y[i] = hALICE1_0->GetBinContent(i+1);
        xerr[i] = 0.5*hALICE1_0->GetBinWidth(i+1);
        yerr[i] = hALICE1_0->GetBinError(i+1);
    }
    TGraphErrors * gALICE1_0 = new TGraphErrors(num, x, y, 0, yerr);
    gALICE1_0->SetName("ALICE_v1odd_pT_2TeV_5_80");
    gALICE1_0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gALICE1_0->GetYaxis()->SetTitle("v_{1}^{odd}");
    gALICE1_0->Write();



    //----- v1even
    direven->cd();

    //-- ALICE
    TH1D * hALICE1_1 = (TH1D *) fin4->Get("ALICE_v1even_pT_5_80");
    num = hALICE1_1->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hALICE1_1->GetBinCenter(i+1);
        y[i] = hALICE1_1->GetBinContent(i+1);
        xerr[i] = 0.5*hALICE1_1->GetBinWidth(i+1);
        yerr[i] = hALICE1_1->GetBinError(i+1);
    }
    TGraphErrors * gALICE1_1 = new TGraphErrors(num, x, y, 0, yerr);
    gALICE1_1->SetName("ALICE_v1even_pT_2TeV_5_80");
    gALICE1_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gALICE1_1->GetYaxis()->SetTitle("v_{1}^{even}");
    gALICE1_1->Write();

    //-- ATLAS
    TH1D * hATLAS2_0 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_0_5");
    num = hATLAS2_0->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_0->GetBinCenter(i+1);
        y[i] = hATLAS2_0->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_0->GetBinWidth(i+1);
        yerr[i] = hATLAS2_0->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_0 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_0->SetName("ATLAS_v1even_pT_2TeV_0_5");
    gATLAS2_0->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_0->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_0->Write();

    TH1D * hATLAS2_1 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_5_10");
    num = hATLAS2_1->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_1->GetBinCenter(i+1);
        y[i] = hATLAS2_1->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_1->GetBinWidth(i+1);
        yerr[i] = hATLAS2_1->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_1 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_1->SetName("ATLAS_v1even_pT_2TeV_5_10");
    gATLAS2_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_1->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_1->Write();

    TH1D * hATLAS2_2 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_10_20");
    num = hATLAS2_2->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_2->GetBinCenter(i+1);
        y[i] = hATLAS2_2->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_2->GetBinWidth(i+1);
        yerr[i] = hATLAS2_2->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_2 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_2->SetName("ATLAS_v1even_pT_2TeV_10_20");
    gATLAS2_2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_2->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_2->Write();

    TH1D * hATLAS2_3 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_20_30");
    num = hATLAS2_3->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_3->GetBinCenter(i+1);
        y[i] = hATLAS2_3->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_3->GetBinWidth(i+1);
        yerr[i] = hATLAS2_3->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_3 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_3->SetName("ATLAS_v1even_pT_2TeV_20_30");
    gATLAS2_3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_3->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_3->Write();

    TH1D * hATLAS2_4 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_30_40");
    num = hATLAS2_4->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_4->GetBinCenter(i+1);
        y[i] = hATLAS2_4->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_4->GetBinWidth(i+1);
        yerr[i] = hATLAS2_4->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_4 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_4->SetName("ATLAS_v1even_pT_2TeV_30_40");
    gATLAS2_4->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_4->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_4->Write();

    TH1D * hATLAS2_5 = (TH1D *) fin2->Get("ATLAS_v1even_2PC_PbPb_40_50");
    num = hATLAS2_5->GetNbinsX();
    for (int i = 0; i<num; i++) {
        x[i] = hATLAS2_5->GetBinCenter(i+1);
        y[i] = hATLAS2_5->GetBinContent(i+1);
        xerr[i] = 0.5*hATLAS2_5->GetBinWidth(i+1);
        yerr[i] = hATLAS2_5->GetBinError(i+1);
    }
    TGraphErrors * gATLAS2_5 = new TGraphErrors(num, x, y, 0, yerr);
    gATLAS2_5->SetName("ATLAS_v1even_pT_2TeV_40_50");
    gATLAS2_5->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gATLAS2_5->GetYaxis()->SetTitle("v_{1}^{even}");
    gATLAS2_5->Write();

    // fout->Close();

}
