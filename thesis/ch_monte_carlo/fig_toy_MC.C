# include "TAttPad.h"
# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TLine.h"
# include "TPad.h"
# include "TPaveText.h"
# include "TString.h"
# include "TStyle.h"
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

TH1D * input_eta;
TH1D * input_pt;
TH1D * input_phiPsiRP;
TH1D * input_pt2D;
TH1D * input_pt2D_mc;

TH1D * SPv1_3SE_pt_v1_0;
TH1D * SPv1_mix_pt_v1_0;
TH1D * SPv1_3SE_pt_v1_0_mc;
TH1D * SPv1_mix_pt_v1_0_mc;
TH1D * SPv1_3SE_pt_v1_0_mc_ptweights;

TFile * fin = new TFile("../../data/MH_toy.root","read");

void fig_toy_MC() {

    gStyle->SetPalette(55);

    input_eta = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0150_v2in_0.0600v3in_0.0300/Inputs/Merged_inputs/etain_9");
    input_pt = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0150_v2in_0.0600v3in_0.0300/Inputs/Merged_inputs/ptin_9");
    input_phiPsiRP = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0150_v2in_0.0600v3in_0.0300/Inputs/Merged_inputs/phiPsiRP_9");
    input_pt2D = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0150_v2in_0.0600v3in_0.0300/Inputs/Merged_inputs/pt2D_9");
    input_pt2D_mc = (TH1D *) fin->Get("v1even/results_eta_weights_mom-cons/v1in_0.0150_v2in_0.0600v3in_0.0300/Inputs/Merged_inputs/pt2D_9");

    SPv1_3SE_pt_v1_0 = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0000_v2in_0.0600v3in_0.0300/vn_pt/pos/SPv1_3SE_pt_pos");
    SPv1_mix_pt_v1_0 = (TH1D *) fin->Get("v1even/results_eta_weights/v1in_0.0000_v2in_0.0600v3in_0.0300/vn_pt/pos/SPv1_mix_pt_pos");
    SPv1_3SE_pt_v1_0_mc = (TH1D *) fin->Get("v1even/results_eta_weights_mom-cons/v1in_0.0000_v2in_0.0600v3in_0.0300/vn_pt/pos/SPv1_3SE_pt_pos");
    SPv1_mix_pt_v1_0_mc = (TH1D *) fin->Get("v1even/results_eta_weights_mom-cons/v1in_0.0000_v2in_0.0600v3in_0.0300/vn_pt/pos/SPv1_mix_pt_pos");
    SPv1_3SE_pt_v1_0_mc_ptweights = (TH1D *) fin->Get("v1even/results_eta_weights_pt_weights_mom-cons/v1in_0.0000_v2in_0.0600v3in_0.0300/vn_pt/pos/SPv1_3SE_pt_pos");

    SPv1_3SE_pt_v1_0->SetMarkerStyle(20);
    SPv1_3SE_pt_v1_0->SetMarkerSize(1.2);
    SPv1_3SE_pt_v1_0->SetMarkerColor(kBlue);
    SPv1_3SE_pt_v1_0->SetLineColor(kBlue);

    SPv1_mix_pt_v1_0->SetMarkerStyle(24);
    SPv1_mix_pt_v1_0->SetMarkerSize(1.2);
    SPv1_mix_pt_v1_0->SetMarkerColor(kBlue);
    SPv1_mix_pt_v1_0->SetLineColor(kBlue);

    SPv1_3SE_pt_v1_0_mc->SetMarkerStyle(20);
    SPv1_3SE_pt_v1_0_mc->SetMarkerSize(1.2);
    SPv1_3SE_pt_v1_0_mc->SetMarkerColor(kRed);
    SPv1_3SE_pt_v1_0_mc->SetLineColor(kRed);

    SPv1_mix_pt_v1_0_mc->SetMarkerStyle(24);
    SPv1_mix_pt_v1_0_mc->SetMarkerSize(1.2);
    SPv1_mix_pt_v1_0_mc->SetMarkerColor(kRed);
    SPv1_mix_pt_v1_0_mc->SetLineColor(kRed);

    SPv1_3SE_pt_v1_0_mc_ptweights->SetMarkerStyle(20);
    SPv1_3SE_pt_v1_0_mc_ptweights->SetMarkerSize(1.2);
    SPv1_3SE_pt_v1_0_mc_ptweights->SetMarkerColor(kGreen+2);
    SPv1_3SE_pt_v1_0_mc_ptweights->SetLineColor(kGreen+2);


    TCanvas * c0 = new TCanvas("c0", "c0", 1250, 420);
    c0->Divide(3,1);
    c0->cd(1);
    input_eta->SetXTitle("#eta");
    input_eta->GetXaxis()->CenterTitle();
    input_eta->SetTitleSize(0.06);
    input_eta->Draw();
    TPaveText * tx0 = new TPaveText(0.23, 0.20, 0.43, 0.37, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("Input v_{1} = 0.015");
    tx0->AddText("Input v_{2} = 0.060");
    tx0->Draw();
    c0->cd(2);
    input_pt->SetXTitle("p_{T} (GeV/c)");
    input_pt->GetXaxis()->CenterTitle();
    input_pt->SetTitleSize(0.06);
    input_pt->Draw();
    gPad->SetLogy();
    c0->cd(3);
    input_phiPsiRP->SetXTitle("#phi - #Psi_{RP}");
    input_phiPsiRP->GetXaxis()->CenterTitle();
    input_phiPsiRP->SetTitleSize(0.06);
    input_phiPsiRP->Draw();
    c0->Print("../figures/fig_toy_MC_inputs.pdf","pdf");


    TCanvas * c1 = new TCanvas("c1", "c1", 950, 420);
    c1->Divide(2,1);
    TPad * pad1_0 = (TPad *) c1->cd(1);
    pad1_0->SetTopMargin(0.1);
    pad1_0->SetRightMargin(0.18);
    input_pt2D->SetXTitle("#Sigma p_{T,x} per event");
    input_pt2D->SetYTitle("#Sigma p_{T,y} per event");
    input_pt2D->GetXaxis()->CenterTitle();
    input_pt2D->GetYaxis()->CenterTitle();
    input_pt2D->GetXaxis()->SetTitleSize(0.06);
    input_pt2D->GetYaxis()->SetTitleSize(0.06);
    input_pt2D->GetXaxis()->SetTitleOffset(1.20);
    input_pt2D->GetYaxis()->SetTitleOffset(1.40);
    input_pt2D->Draw("colz");
    TPaveText * tx1_0 = new TPaveText(0.38, 0.91, 0.66, 0.98, "NDC");
    SetTPaveTxt(tx1_0, 22);
    tx1_0->AddText("Before shift");
    tx1_0->Draw();
    TPad * pad1_1 = (TPad *) c1->cd(2);
    pad1_1->SetRightMargin(0.18);
    pad1_1->SetTopMargin(0.1);
    input_pt2D_mc->SetXTitle("#Sigma p_{T,x} per event");
    input_pt2D_mc->SetYTitle("#Sigma p_{T,y} per event");
    input_pt2D_mc->GetXaxis()->CenterTitle();
    input_pt2D_mc->GetYaxis()->CenterTitle();
    input_pt2D_mc->GetXaxis()->SetTitleSize(0.06);
    input_pt2D_mc->GetYaxis()->SetTitleSize(0.06);
    input_pt2D_mc->GetXaxis()->SetTitleOffset(1.20);
    input_pt2D_mc->GetYaxis()->SetTitleOffset(1.40);
    input_pt2D_mc->Draw("colz");
    TPaveText * tx1_1 = new TPaveText(0.38, 0.91, 0.66, 0.98, "NDC");
    SetTPaveTxt(tx1_1, 22);
    tx1_1->AddText("After shift");
    tx1_1->Draw();
    c1->Print("../figures/fig_toy_MC_mc_shift.pdf","pdf");


    TCanvas * c2 = new TCanvas("c2", "c2", 600, 550);
    c2->cd();
    TH1D * h2 = new TH1D("h2", "", 100, 0, 8);
    h2->SetXTitle("p_{T} (GeV/c)");
    h2->SetYTitle("v_{1}");
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->CenterTitle();
    h2->GetXaxis()->SetTitleSize(0.06);
    h2->GetYaxis()->SetTitleSize(0.06);
    h2->GetXaxis()->SetTitleOffset(1.20);
    h2->GetYaxis()->SetTitleOffset(1.40);
    h2->GetYaxis()->SetRangeUser(-0.25, 0.15);
    h2->Draw();
    SPv1_3SE_pt_v1_0->Draw("same p");
    SPv1_mix_pt_v1_0->Draw("same p");
    SPv1_3SE_pt_v1_0_mc->Draw("same p");
    SPv1_mix_pt_v1_0_mc->Draw("same p");
    TLegend * leg2 = new TLegend(0.21, 0.18, 0.65, 0.33);
    SetLegend(leg2, 20);
    leg2->SetNColumns(2);
    leg2->SetHeader("SP   mixed");
    leg2->AddEntry(SPv1_3SE_pt_v1_0, " ", "p");
    leg2->AddEntry(SPv1_mix_pt_v1_0, "    Before shift", "p");
    leg2->AddEntry(SPv1_3SE_pt_v1_0_mc, " ", "p");
    leg2->AddEntry(SPv1_mix_pt_v1_0_mc, "    After shift", "p");
    leg2->Draw();
    TPaveText * tx2 = new TPaveText(0.20, 0.81, 0.42, 0.91, "NDC");
    SetTPaveTxt(tx2, 20);
    tx2->AddText("Input v_{1} = 0.00");
    tx2->AddText("Input v_{2} = 0.06");
    tx2->Draw();
    c2->Print("../figures/fig_toy_MC_v1_0_shift.pdf","pdf");


    TCanvas * c3 = new TCanvas("c3", "c3", 600, 550);
    c3->cd();
    TH1D * h3 = (TH1D *) h2->Clone("h3");
    h2->Draw();
    SPv1_3SE_pt_v1_0_mc->Draw("same p");
    SPv1_3SE_pt_v1_0_mc_ptweights->Draw("same p");
    TLegend * leg3 = new TLegend(0.2, 0.2, 0.4, 0.4);
    SetLegend(leg3, 20);
    leg3->SetHeader("SP after shift");
    leg3->AddEntry(SPv1_3SE_pt_v1_0_mc, "no weighting", "p");
    leg3->AddEntry(SPv1_3SE_pt_v1_0_mc_ptweights, "With p_{T} weighting", "p");
    leg3->Draw();
    TPaveText * tx3 = new TPaveText(0.20, 0.81, 0.42, 0.91, "NDC");
    SetTPaveTxt(tx3, 20);
    tx3->AddText("Input v_{1} = 0.00");
    tx3->AddText("Input v_{2} = 0.06");
    tx3->Draw();
    c3->Print("../figures/fig_toy_MC_v1_0_shift_ptweights.pdf","pdf");



    // functional fits for theory predictions
    // taken from working_macros/momcons_Monte_Carlo/old_09_28_16/EP_test.C
    double xoffset = 0;
    double evtmult = 6306;
    double multQ = 769; // play with
    double ptave2 = 0.815392;
    double ptaveQ = 0.86926;
    double submult = 694.384;
    double wwaveQ2 = 1;
    double evntRes = 0.355506;
    double ff = 0.31944;
    TF1 * fnTheory = new TF1("fnTheory"," - (x-[0])/sqrt([1]*[2]) * ([3]*sqrt([4]/([5]*[1]*[2])))/(sqrt(1-TMath::Power([3]*sqrt([4]/([5]*[1]*[2])),2))) * sqrt(TMath::Pi())/2 * 1/[6]",0,8);
    fnTheory->SetParameters(xoffset, evtmult, ptave2, ptaveQ, multQ, wwaveQ2, evntRes);
    fnTheory->SetLineColor(kBlue);

    TCanvas * c4 = new TCanvas("c4", "c4", 600, 550);
    c4->cd();
    TH1D * h4 = (TH1D *) h2->Clone("h4");
    h4->Draw();
    SPv1_3SE_pt_v1_0_mc->Draw("same p");
    fnTheory->Draw("same");
    TLegend * leg4 = new TLegend(0.63, 0.80, 0.78, 0.92);
    SetLegend(leg4, 20);
    leg4->AddEntry(SPv1_3SE_pt_v1_0_mc, " Toy MC after shift", "p");
    leg4->AddEntry(fnTheory, " Theory prediction", "l");
    leg4->Draw();
    TPaveText * tx4 = new TPaveText(0.20, 0.80, 0.42, 0.91, "NDC");
    SetTPaveTxt(tx4, 20);
    tx4->AddText("Input v_{1} = 0.00");
    tx4->AddText("Input v_{2} = 0.06");
    tx4->Draw();
    c4->Print("../figures/fig_toy_MC_theory_compare.pdf","pdf");

}
