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

static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60};
static const double ebinmid[] = {-2.2, -1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2};

//#include "../../data/published_results.h"

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
TH1D * h2;
TGraphErrors * N1HFgSUB2[ncbins];
TGraphErrors * N1HFgSUB3[ncbins];
TGraphErrors * N1HFgSUB3_syst[ncbins];
TGraphErrors * N1HFgSUB3_decor[ncbins];
TGraphErrors * N1HFgSUB3_decor_syst[ncbins];
TGraphErrors * N112ASUB3[ncbins];
TGraphErrors * PHOBOS_EP_62GeV_6_40;
TGraphErrors * PHOBOS_EP_200GeV_6_40;
TGraphErrors * PHOBOS_mixed_62GeV_6_40;
TGraphErrors * PHOBOS_mixed_200GeV_6_40;
TGraphErrors * STAR_v1odd_eta_mix_200GeV_10_70;
TGraphErrors * STAR_v1odd_eta_3PC_62GeV_10_70;
TGraphErrors * STAR_v1odd_eta_mix_62GeV_10_70;
TGraphErrors * STAR_v1odd_eta_ZDC_62GeV_10_70;
TGraphErrors * STAR_v1odd_eta_ZDC_200GeV_0_5;
TGraphErrors * STAR_v1odd_eta_ZDC_200GeV_5_40;
TGraphErrors * STAR_v1odd_eta_ZDC_200GeV_40_80;
TGraphErrors * STAR_v1odd_eta_3PC_200GeV_10_70;
TGraphErrors * ALICE_v1odd_eta_2TeV_10_60;

void fig_comp_v1odd_eta() {

    const double syst_v1odd_eta[ncbins] = {2.6e-4, 2.6e-4, 2.6e-4, 2.6e-4, 2.6e-4, 4.0e-4, 4.0e-4, 4.0e-4, 4.0e-4, 7.8e-4, 7.8e-4,  5.2E-4, 8.41e-4};
    const double syst_v1odd_eta_decor[ncbins] = {0.9e-4, 0.9e-4, 0.9e-4, 0.9e-4, 0.9e-4, 1.3e-4, 1.3e-4, 1.3e-4, 1.3e-4, 1.5e-4, 1.5e-4,  1.8e-4, 2.75e-4};

    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1HFgSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3/0.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        cout<<N1HFgSUB3[cbin]<<endl;
        N1HFgSUB3[cbin]->SetMarkerStyle(21);
        N1HFgSUB3[cbin]->SetMarkerSize(1.2);
        N1HFgSUB3[cbin]->SetMarkerColor(kBlue);
        N1HFgSUB3[cbin]->SetLineColor(kBlue);
        N1HFgSUB3[cbin]->RemovePoint(0);
        N1HFgSUB3[cbin]->RemovePoint(N1HFgSUB3[cbin]->GetN()-1);

        N1HFgSUB3_decor[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3_decor/1.2_1.6/%d_%d/gint",cmin[cbin],cmax[cbin]));
        cout<<N1HFgSUB3_decor[cbin]<<endl;
        N1HFgSUB3_decor[cbin]->SetMarkerStyle(20);
        N1HFgSUB3_decor[cbin]->SetMarkerSize(1.2);
        N1HFgSUB3_decor[cbin]->SetMarkerColor(kRed);
        N1HFgSUB3_decor[cbin]->SetLineColor(kRed);
        N1HFgSUB3_decor[cbin]->RemovePoint(0);
        N1HFgSUB3_decor[cbin]->RemovePoint(N1HFgSUB3_decor[cbin]->GetN()-1);

        N112ASUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N112ASUB3/0.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        cout<<N112ASUB3[cbin]<<endl;
        N112ASUB3[cbin]->SetMarkerStyle(33);
        N112ASUB3[cbin]->SetMarkerSize(1.7);
        N112ASUB3[cbin]->SetMarkerColor(kGreen+2);
        N112ASUB3[cbin]->SetLineColor(kGreen+2);
        N112ASUB3[cbin]->RemovePoint(0);
        N112ASUB3[cbin]->RemovePoint(N112ASUB3[cbin]->GetN()-1);

        //-- systematics
        Double_t x[50], y[50], xerr[50], ysyst[50];
        int num = N1HFgSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.15;
            // ysyst[j] = syst_v1odd_eta[i]*ebinmid[j];
            ysyst[j] = syst_v1odd_eta[cbin];
        }
        N1HFgSUB3_syst[cbin] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1HFgSUB3_syst[cbin]->SetLineColor(kBlue-10);
        N1HFgSUB3_syst[cbin]->SetFillColor(kBlue-10);

        Double_t xd[50], yd[50], xderr[50], ydsyst[50];
        int numd = N1HFgSUB3_decor[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3_decor[cbin]->GetPoint(j, xd[j], yd[j]);
            xderr[j] = 0.15;
            // ydsyst[j] = syst_v1odd_eta_decor[i]*ebinmid[j];
            ydsyst[j] = syst_v1odd_eta_decor[cbin];
        }
        N1HFgSUB3_decor_syst[cbin] = new TGraphErrors(numd, xd, yd, xderr, ydsyst);
        N1HFgSUB3_decor_syst[cbin]->SetLineColor(kGray);
        N1HFgSUB3_decor_syst[cbin]->SetFillColor(kGray);
        //--
    }


    PHOBOS_EP_62GeV_6_40 = (TGraphErrors *) fdata->Get("v1odd/PHOBOS_EP_62GeV_6_40");
    PHOBOS_EP_62GeV_6_40->SetMarkerStyle(20);
    PHOBOS_EP_62GeV_6_40->SetMarkerSize(1.3);
    PHOBOS_EP_62GeV_6_40->SetMarkerColor(kBlack);
    PHOBOS_EP_62GeV_6_40->SetLineColor(kBlack);

    PHOBOS_EP_200GeV_6_40 = (TGraphErrors *) fdata->Get("v1odd/PHOBOS_EP_200GeV_6_40");
    PHOBOS_EP_200GeV_6_40->SetMarkerStyle(20);
    PHOBOS_EP_200GeV_6_40->SetMarkerSize(1.3);
    PHOBOS_EP_200GeV_6_40->SetMarkerColor(kBlack);
    PHOBOS_EP_200GeV_6_40->SetLineColor(kBlack);

    PHOBOS_mixed_62GeV_6_40 = (TGraphErrors *) fdata->Get("v1odd/PHOBOS_mixed_62GeV_6_40");
    PHOBOS_mixed_62GeV_6_40->SetMarkerStyle(24);
    PHOBOS_mixed_62GeV_6_40->SetMarkerSize(1.3);
    PHOBOS_mixed_62GeV_6_40->SetMarkerColor(kBlack);
    PHOBOS_mixed_62GeV_6_40->SetLineColor(kBlack);

    PHOBOS_mixed_200GeV_6_40 = (TGraphErrors *) fdata->Get("v1odd/PHOBOS_mixed_200GeV_6_40");
    PHOBOS_mixed_200GeV_6_40->SetMarkerStyle(24);
    PHOBOS_mixed_200GeV_6_40->SetMarkerSize(1.3);
    PHOBOS_mixed_200GeV_6_40->SetMarkerColor(kBlack);
    PHOBOS_mixed_200GeV_6_40->SetLineColor(kBlack);

    STAR_v1odd_eta_mix_200GeV_10_70 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_mix_200GeV_10_70");
    STAR_v1odd_eta_3PC_62GeV_10_70 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_3PC_62GeV_10_70");
    STAR_v1odd_eta_mix_62GeV_10_70 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_mix_62GeV_10_70");
    STAR_v1odd_eta_ZDC_62GeV_10_70 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_ZDC_62GeV_10_70");
    STAR_v1odd_eta_ZDC_200GeV_0_5 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_ZDC_200GeV_0_5");
    STAR_v1odd_eta_ZDC_200GeV_5_40 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_ZDC_200GeV_5_40");
    STAR_v1odd_eta_ZDC_200GeV_40_80 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_ZDC_200GeV_40_80");
    STAR_v1odd_eta_3PC_200GeV_10_70 = (TGraphErrors *) fdata->Get("v1odd/STAR_v1odd_eta_3PC_200GeV_10_70");
    ALICE_v1odd_eta_2TeV_10_60 = (TGraphErrors *) fdata->Get("v1odd/ALICE_v1odd_eta_2TeV_10_60");


    TCanvas * c0 = new TCanvas("c0", "c0", 1300, 450);
    c0->Divide(3,1);
    c0->cd(1);
    h0 = new TH1D("h0", "h0", 100, -2.4, 2.4);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(507);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleSize(0.06);
    h0->GetXaxis()->SetLabelSize(0.04);
    h0->GetXaxis()->SetTitleOffset(1.00);
    h0->GetYaxis()->SetTitleSize(0.06);
    h0->GetYaxis()->SetLabelSize(0.04);
    h0->GetYaxis()->SetTitleOffset(1.46);
    h0->GetYaxis()->SetRangeUser(-0.02, 0.02);
    h0->Draw();
    N1HFgSUB3_syst[12]->Draw("same 2");
    // PHOBOS_EP_62GeV_6_40->Draw("same p");
    // PHOBOS_mixed_62GeV_6_40->Draw("same p");
    STAR_v1odd_eta_3PC_62GeV_10_70->SetMarkerStyle(25);
    STAR_v1odd_eta_3PC_62GeV_10_70->SetMarkerSize(1.3);
    STAR_v1odd_eta_3PC_62GeV_10_70->SetMarkerColor(kViolet-6);
    STAR_v1odd_eta_3PC_62GeV_10_70->SetLineColor(kViolet-6);
    STAR_v1odd_eta_3PC_62GeV_10_70->Draw("same p");
    STAR_v1odd_eta_mix_62GeV_10_70->SetMarkerStyle(27);
    STAR_v1odd_eta_mix_62GeV_10_70->SetMarkerSize(1.8);
    STAR_v1odd_eta_mix_62GeV_10_70->SetMarkerColor(kRed);
    STAR_v1odd_eta_mix_62GeV_10_70->SetLineColor(kRed);
    STAR_v1odd_eta_mix_62GeV_10_70->Draw("same p");
    STAR_v1odd_eta_ZDC_62GeV_10_70->SetMarkerStyle(34);
    STAR_v1odd_eta_ZDC_62GeV_10_70->SetMarkerSize(1.8);
    STAR_v1odd_eta_ZDC_62GeV_10_70->SetMarkerColor(kBlack);
    STAR_v1odd_eta_ZDC_62GeV_10_70->SetLineColor(kBlack);
    STAR_v1odd_eta_ZDC_62GeV_10_70->Draw("same p");
    N1HFgSUB3[12]->Draw("same p");

    TPaveText * tx0_0 = new TPaveText(0.36, 0.77, 0.93, 0.89, "NDC");
    SetTPaveTxt(tx0_0, 19);
    tx0_0->SetTextAlign(31);
    tx0_0->AddText("STAR AuAu #sqrt{s_{NN}} = 62.4 GeV");
    tx0_0->AddText("10 - 70%");
    tx0_0->Draw();

    TLegend * leg0_0 = new TLegend(0.20, 0.19, 0.56, 0.40);
    SetLegend(leg0_0, 19);
    //leg0_0->SetNColumns(2);
    leg0_0->AddEntry(STAR_v1odd_eta_3PC_62GeV_10_70,"3PC","p");
    leg0_0->AddEntry(STAR_v1odd_eta_mix_62GeV_10_70,"Mixed","p");
    leg0_0->AddEntry(STAR_v1odd_eta_ZDC_62GeV_10_70,"ZDC","p");
    leg0_0->Draw();


    c0->cd(2);
    h1 = (TH1D *) h0->Clone("h1");
    h1->GetYaxis()->SetRangeUser(-0.03, 0.03);
    h1->Draw();
    N1HFgSUB3_syst[12]->Draw("same 2");
    STAR_v1odd_eta_mix_200GeV_10_70->SetMarkerStyle(27);
    STAR_v1odd_eta_mix_200GeV_10_70->SetMarkerSize(1.8);
    STAR_v1odd_eta_mix_200GeV_10_70->SetMarkerColor(kRed);
    STAR_v1odd_eta_mix_200GeV_10_70->SetLineColor(kRed);
    STAR_v1odd_eta_mix_200GeV_10_70->Draw("same p");
    STAR_v1odd_eta_ZDC_200GeV_5_40->SetMarkerStyle(34);
    STAR_v1odd_eta_ZDC_200GeV_5_40->SetMarkerSize(1.8);
    STAR_v1odd_eta_ZDC_200GeV_5_40->SetMarkerColor(kBlack);
    STAR_v1odd_eta_ZDC_200GeV_5_40->SetLineColor(kBlack);
    STAR_v1odd_eta_ZDC_200GeV_5_40->Draw("same p");
    STAR_v1odd_eta_3PC_200GeV_10_70->SetMarkerStyle(25);
    STAR_v1odd_eta_3PC_200GeV_10_70->SetMarkerSize(1.3);
    STAR_v1odd_eta_3PC_200GeV_10_70->SetMarkerColor(kViolet-6);
    STAR_v1odd_eta_3PC_200GeV_10_70->SetLineColor(kViolet-6);
    STAR_v1odd_eta_3PC_200GeV_10_70->Draw("same p");
    N1HFgSUB3[12]->Draw("same p");

    TPaveText * tx0_1 = new TPaveText(0.36, 0.77, 0.93, 0.89, "NDC");
    SetTPaveTxt(tx0_1, 19);
    tx0_1->SetTextAlign(31);
    tx0_1->AddText("STAR AuAu #sqrt{s_{NN}} = 200 GeV");
    tx0_1->AddText("10 - 70% (5 - 40% for ZDC)");
    tx0_1->Draw();

    c0->cd(3);
    h2 = (TH1D *) h0->Clone("h2");
    h2->GetYaxis()->SetRangeUser(-0.018, 0.018);
    h2->Draw();
    N1HFgSUB3_syst[12]->Draw("same 2");
    ALICE_v1odd_eta_2TeV_10_60->SetMarkerStyle(28);
    ALICE_v1odd_eta_2TeV_10_60->SetMarkerSize(1.8);
    ALICE_v1odd_eta_2TeV_10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_eta_2TeV_10_60->SetLineColor(kMagenta);
    ALICE_v1odd_eta_2TeV_10_60->Draw("same p");
    N1HFgSUB3[12]->Draw("same p");

    TPaveText * tx0_2 = new TPaveText(0.36, 0.77, 0.93, 0.89, "NDC");
    SetTPaveTxt(tx0_2, 19);
    tx0_2->SetTextAlign(31);
    tx0_2->AddText("PbPb #sqrt{s_{NN}} = 2.76 TeV");
    tx0_2->AddText("10 - 60%");
    tx0_2->Draw();

    TLegend * leg0_2 = new TLegend(0.21, 0.19, 0.42, 0.32);
    SetLegend(leg0_2, 18);
    leg0_2->AddEntry(ALICE_v1odd_eta_2TeV_10_60,"ALICE ZDC","p");
    leg0_2->AddEntry(N1HFgSUB3[12],"CMS #eta_{C} = 0, 5.02 TeV","p");
    leg0_2->Draw();

    c0->Print("../figures/fig_v1odd_compare_SP.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 550, 500);
    c1->cd();
    TH1D * h0_1 = (TH1D *) h0->Clone("h0_1");
    h0_1->GetYaxis()->SetRangeUser(-0.005, 0.005);
    h0_1->Draw();
    N1HFgSUB3_decor_syst[12]->Draw("same 2");
    ALICE_v1odd_eta_2TeV_10_60->SetMarkerSize(1.9);
    ALICE_v1odd_eta_2TeV_10_60->Draw("same p");
    N1HFgSUB3_decor[12]->Draw("same p");

    TPaveText * tx1_0 = new TPaveText(0.21, 0.85, 0.47, 0.91, "NDC");
    SetTPaveTxt(tx1_0, 20);
    tx1_0->AddText("PbPb 10 - 60%");
    tx1_0->Draw();

    TLegend * leg1_0 = new TLegend(0.20, 0.19, 0.50, 0.33);
    SetLegend(leg1_0, 20);
    leg1_0->AddEntry(N1HFgSUB3_decor[12],"CMS #eta_{C} = #eta_{ROI}, 5.02 TeV","p");
    leg1_0->AddEntry(ALICE_v1odd_eta_2TeV_10_60,"ALICE ZDC, 2.76 TeV","p");
    leg1_0->Draw();

    c1->Print("../figures/fig_v1odd_compare_decor.pdf","pdf");


}
