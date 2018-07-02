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
TH1D * h0;
TGraphErrors * N1AHFgSUB3[ncbins];
TGraphErrors * N1BHFgSUB3[ncbins];
TGraphErrors * N1HFgSUB3[ncbins];
TGraphErrors * N1HFgSUB3_syst[ncbins];
TGraphErrors * N1AHFgSUB3_decor[ncbins];
TGraphErrors * N1BHFgSUB3_decor[ncbins];
TGraphErrors * N1HFgSUB3_decor[ncbins];
TGraphErrors * N1HFgSUB3_decor_syst[ncbins];

const double syst_v1odd_pt = 3.2e-4;
const double syst_v1odd_pt_decor = 5.4e-4;

void fig_v1odd_decor_pT() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        // Average negative and positive side v1even
        N1AHFgSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3/-1.6_-1.2/%d_%d/g",cmin[cbin],cmax[cbin]));
        N1BHFgSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3/1.2_1.6/%d_%d/g",cmin[cbin],cmax[cbin]));
        int num =  N1AHFgSUB3[cbin]->GetN();
        double xvalA[50], xvalB[50], yvalA[50], yvalB[50], yerrA[50], yerrB[50];
        for (int j = 0; j<num; j++) {
            N1AHFgSUB3[cbin]->GetPoint(j, xvalA[j], yvalA[j]);
            yerrA[j] = N1AHFgSUB3[cbin]->GetErrorY(j);
            N1BHFgSUB3[cbin]->GetPoint(j, xvalB[j], yvalB[j]);
            yerrB[j] = N1BHFgSUB3[cbin]->GetErrorY(j);

            yvalA[j]*=-1.;
            yvalA[j] = 0.5*(yvalA[j] + yvalB[j]);
            yerrA[j] = 0.5*sqrt( pow(yerrA[j],2) + pow(yerrB[j],2) );
        }

        N1AHFgSUB3_decor[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3_decor/-1.6_-1.2/%d_%d/g",cmin[cbin],cmax[cbin]));
        N1BHFgSUB3_decor[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3_decor/1.2_1.6/%d_%d/g",cmin[cbin],cmax[cbin]));
        int numd =  N1AHFgSUB3_decor[cbin]->GetN();
        double xvalAd[50], xvalBd[50], yvalAd[50], yvalBd[50], yerrAd[50], yerrBd[50];
        for (int j = 0; j<numd; j++) {
            N1AHFgSUB3_decor[cbin]->GetPoint(j, xvalAd[j], yvalAd[j]);
            yerrAd[j] = N1AHFgSUB3_decor[cbin]->GetErrorY(j);
            N1BHFgSUB3_decor[cbin]->GetPoint(j, xvalBd[j], yvalBd[j]);
            yerrBd[j] = N1BHFgSUB3_decor[cbin]->GetErrorY(j);

            yvalAd[j]*=-1.;
            yvalAd[j] = 0.5*(yvalAd[j] + yvalBd[j]);
            yerrAd[j] = 0.5*sqrt( pow(yerrAd[j],2) + pow(yerrBd[j],2) );
        }

        N1HFgSUB3[cbin] = new TGraphErrors(num, xvalA, yvalA, 0, yerrA);
        N1HFgSUB3_decor[cbin] = new TGraphErrors(numd, xvalAd, yvalAd, 0, yerrAd);

        N1HFgSUB3[cbin]->SetMarkerStyle(21);
        N1HFgSUB3[cbin]->SetMarkerSize(1.1);
        N1HFgSUB3[cbin]->SetMarkerColor(kBlue);
        N1HFgSUB3[cbin]->SetLineColor(kBlue);
        N1HFgSUB3[cbin]->SetFillColor(kBlue-9);

        N1HFgSUB3_decor[cbin]->SetMarkerStyle(20);
        N1HFgSUB3_decor[cbin]->SetMarkerSize(1.2);
        N1HFgSUB3_decor[cbin]->SetMarkerColor(kRed);
        N1HFgSUB3_decor[cbin]->SetLineColor(kRed);
        N1HFgSUB3_decor[cbin]->SetFillColor(kRed-9);

        //-- systematics
        Double_t x[50], y[50], xerr[50], ysyst[50];
        num = N1HFgSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.18;
            ysyst[j] = syst_v1odd_pt;
        }
        N1HFgSUB3_syst[cbin] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1HFgSUB3_syst[cbin]->SetLineColor(kBlue-9);
        N1HFgSUB3_syst[cbin]->SetFillColor(kBlue-9);

        Double_t xd[50], yd[50], xderr[50], ydsyst[50];
        numd = N1HFgSUB3_decor[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3_decor[cbin]->GetPoint(j, xd[j], yd[j]);
            xderr[j] = 0.18;
            ydsyst[j] = syst_v1odd_pt_decor;
        }
        N1HFgSUB3_decor_syst[cbin] = new TGraphErrors(numd, xd, yd, xderr, ydsyst);
        N1HFgSUB3_decor_syst[cbin]->SetLineColor(kRed-9);
        N1HFgSUB3_decor_syst[cbin]->SetFillColor(kRed-9);
        //--
    }

    TCanvas * c0 = new TCanvas("c0", "c0", 1100, 770);
    TPad * pad0[12];
    c0->cd();
    pad0[0] = new TPad("pad0_0", "pad0_0", 0.0, 0.68, 0.28, 1.0);
    pad0[0]->SetLeftMargin(0.22);
    pad0[0]->SetBottomMargin(0);
    pad0[0]->SetRightMargin(0);
    pad0[0]->Draw();

    c0->cd();
    pad0[1] = new TPad("pad0_1", "pad0_1", 0.28, 0.68, 0.50, 1.0);
    pad0[1]->SetLeftMargin(0);
    pad0[1]->SetRightMargin(0);
    pad0[1]->SetBottomMargin(0);
    pad0[1]->Draw();

    c0->cd();
    pad0[2] = new TPad("pad0_2", "pad0_2", 0.50, 0.68, 0.72, 1.0);
    pad0[2]->SetLeftMargin(0);
    pad0[2]->SetRightMargin(0);
    pad0[2]->SetBottomMargin(0);
    pad0[2]->Draw();

    c0->cd();
    pad0[3] = new TPad("pad0_3", "pad0_3", 0.72, 0.68, 0.99, 1.0);
    pad0[3]->SetLeftMargin(0);
    pad0[3]->SetRightMargin(0.20);
    pad0[3]->SetBottomMargin(0);
    pad0[3]->Draw();

    c0->cd();
    pad0[4] = new TPad("pad0_4", "pad0_4", 0.0, 0.38, 0.28, 0.68);
    pad0[4]->SetLeftMargin(0.22);
    pad0[4]->SetRightMargin(0);
    pad0[4]->SetTopMargin(0);
    pad0[4]->SetBottomMargin(0);
    pad0[4]->Draw();

    c0->cd();
    pad0[5] = new TPad("pad0_5", "pad0_5", 0.28, 0.38, 0.50, 0.68);
    pad0[5]->SetLeftMargin(0);
    pad0[5]->SetRightMargin(0);
    pad0[5]->SetTopMargin(0);
    pad0[5]->SetBottomMargin(0);
    pad0[5]->Draw();

    c0->cd();
    pad0[6] = new TPad("pad0_6", "pad0_6", 0.50, 0.38, 0.72, 0.68);
    pad0[6]->SetLeftMargin(0);
    pad0[6]->SetRightMargin(0);
    pad0[6]->SetTopMargin(0);
    pad0[6]->SetBottomMargin(0);
    pad0[6]->Draw();

    c0->cd();
    pad0[7] = new TPad("pad0_3", "pad0_3", 0.72, 0.305, 0.99, 0.68);
    pad0[7]->SetLeftMargin(0);
    pad0[7]->SetRightMargin(0.20);
    pad0[7]->SetTopMargin(0);
    pad0[7]->SetBottomMargin(0.2);
    pad0[7]->Draw();

    c0->cd();
    pad0[8] = new TPad("pad0_8", "pad0_8", 0.0, 0.00, 0.28, 0.38);
    pad0[8]->SetLeftMargin(0.22);
    pad0[8]->SetRightMargin(0);
    pad0[8]->SetTopMargin(0);
    pad0[8]->SetBottomMargin(0.18);
    pad0[8]->Draw();

    c0->cd();
    pad0[9] = new TPad("pad0_9", "pad0_9", 0.28, 0.00, 0.50, 0.38);
    pad0[9]->SetLeftMargin(0);
    pad0[9]->SetRightMargin(0);
    pad0[9]->SetTopMargin(0);
    pad0[9]->SetBottomMargin(0.18);
    pad0[9]->Draw();

    c0->cd();
    pad0[10] = new TPad("pad0_10", "pad0_10", 0.5, 0.00, 0.721, 0.38);
    pad0[10]->SetLeftMargin(0);
    pad0[10]->SetRightMargin(0.005);
    pad0[10]->SetTopMargin(0);
    pad0[10]->SetBottomMargin(0.18);
    pad0[10]->Draw();

    c0->cd();
    pad0[11] = new TPad("pad0_11", "pad0_11", 0.73, 0.0, 1.0, 0.3);
    pad0[11]->SetTopMargin(0.22);
    pad0[11]->Draw();
    pad0[11]->cd();

    TPaveText * tx0_CMS = new TPaveText(0.04, 0.33, 0.61, 0.79, "NDC");
    SetTPaveTxt(tx0_CMS, 20);
    tx0_CMS->AddText("#bf{CMS}");
    tx0_CMS->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    tx0_CMS->AddText("1.2 < |#eta| < 1.6");
    tx0_CMS->Draw();

    h0 = new TH1D("h0", "h0", 100, 0.001, 7.8);
    h0->SetStats(0);
    h0->SetXTitle("p_{T} (GeV/c)");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(20);
    h0->GetXaxis()->SetTitleOffset(3);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(17);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(22);
    h0->GetYaxis()->SetTitleOffset(3.76);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(16);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.17, 0.07);

    for (int cbin = 0; cbin<11; cbin++) {
        pad0[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->Draw();
        N1HFgSUB3_syst[cbin]->Draw("same 2");
        N1HFgSUB3_decor_syst[cbin]->Draw("same 2");
        N1HFgSUB3[cbin]->Draw("same p");
        N1HFgSUB3_decor[cbin]->Draw("same p");

        TPaveText * tx0_cent;
        if (cbin == 0) tx0_cent = new TPaveText(0.26, 0.05, 0.46, 0.16, "NDC");
        else if (cbin == 1 || cbin == 2) tx0_cent = new TPaveText(0.08, 0.05, 0.33, 0.16, "NDC");
        else if (cbin == 3) tx0_cent = new TPaveText(0.08, 0.05, 0.31, 0.16, "NDC");
        else if (cbin == 4) tx0_cent = new TPaveText(0.30, 0.07, 0.50, 0.16, "NDC");
        else if (cbin == 5 || cbin == 6) tx0_cent = new TPaveText(0.10, 0.05, 0.37, 0.16, "NDC");
        else if (cbin == 7) tx0_cent = new TPaveText(0.08, 0.23, 0.31, 0.33, "NDC");
        else if (cbin == 8) tx0_cent = new TPaveText(0.30, 0.24, 0.50, 0.30, "NDC");
        else if (cbin == 9 || cbin == 10) tx0_cent = new TPaveText(0.10, 0.24, 0.37, 0.30, "NDC");
        else tx0_cent = new TPaveText(0.0, 0.0, 0.01, 0.01, "NDC");
        SetTPaveTxt2(tx0_cent, 20);
        tx0_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        tx0_cent->Draw();
    }
    pad0[0]->cd();
    TLegend * leg0 = new TLegend(0.59, 0.06, 0.90, 0.29);
    SetLegend(leg0, 20);
    leg0->AddEntry(N1HFgSUB3[0],"  #eta_{C} = 0","lpf");
    leg0->AddEntry(N1HFgSUB3_decor[0],"  #eta_{C} = #eta_{ROI}","lpf");
    leg0->Draw();

    c0->Print("../figures/fig_v1odd_decor_pT.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 1000, 450);
    c1->Divide(3,1,0,0);
    TLine * ln1 = new TLine(0.001, 0.0, 7.8, 0.0);

    TPad * pad1_1 = (TPad *) c1->cd(1);
    pad1_1->SetTopMargin(0.08);
    pad1_1->SetBottomMargin(0.17);
    h0->GetYaxis()->SetRangeUser(-0.10, 0.06);
    h0->GetXaxis()->SetTitleSize(22);
    h0->GetXaxis()->SetLabelSize(18);
    h0->GetXaxis()->SetTitleOffset(1.4);
    h0->GetXaxis()->SetLabelOffset(0.02);
    h0->GetYaxis()->SetTitleSize(22);
    h0->GetYaxis()->SetLabelSize(18);
    h0->GetYaxis()->SetTitleOffset(1.85);
    h0->GetYaxis()->SetLabelOffset(0.015);
    h0->DrawCopy("_1");
    ln1->Draw();
    N1HFgSUB3_syst[0]->Draw("same 2");
    N1HFgSUB3_decor_syst[0]->Draw("same 2");
    N1HFgSUB3[0]->Draw("same p");
    N1HFgSUB3_decor[0]->Draw("same p");
    TPaveText * txCMS_1 = new TPaveText(0.186, 0.928, 0.364, 0.988, "NDC");
    SetTPaveTxt(txCMS_1, 19);
    txCMS_1->AddText("#bf{CMS}");
    txCMS_1->Draw();
    TLegend * leg1 = new TLegend(0.23, 0.22, 0.50, 0.38);
    SetLegend(leg1, 20);
    leg1->AddEntry(N1HFgSUB3[0]," #eta_{C} = 0","lpf");
    leg1->AddEntry(N1HFgSUB3_decor[0]," #eta_{C} = #eta_{ROI}","lpf");
    leg1->Draw();
    TPaveText * tx1_1_cent = new TPaveText(0.24, 0.81, 0.38, 0.89, "NDC");
    SetTPaveTxt(tx1_1_cent, 20);
    tx1_1_cent->AddText("0 - 5%");
    tx1_1_cent->Draw();

    TPad * pad1_2 = (TPad *) c1->cd(2);
    pad1_2->SetTopMargin(0.08);
    pad1_2->SetBottomMargin(0.17);
    h0->DrawCopy("_2");
    ln1->Draw();
    N1HFgSUB3_syst[4]->Draw("same 2");
    N1HFgSUB3_decor_syst[4]->Draw("same 2");
    N1HFgSUB3[4]->Draw("same p");
    N1HFgSUB3_decor[4]->Draw("same p");
    TPaveText * txCMS_2 = new TPaveText(0.0, 0.928, 0.510, 0.988, "NDC");
    SetTPaveTxt(txCMS_2, 19);
    txCMS_2->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txCMS_2->Draw();
    TPaveText * tx1_2_cent = new TPaveText(0.06, 0.81, 0.33, 0.89, "NDC");
    SetTPaveTxt(tx1_2_cent, 20);
    tx1_2_cent->AddText("20 - 25%");
    tx1_2_cent->Draw();

    TPad * pad1_3 = (TPad *) c1->cd(3);
    pad1_3->SetRightMargin(0.01);
    pad1_3->SetTopMargin(0.08);
    pad1_3->SetBottomMargin(0.17);
    h0->DrawCopy("_3");
    ln1->Draw();
    N1HFgSUB3_syst[8]->Draw("same 2");
    N1HFgSUB3_decor_syst[8]->Draw("same 2");
    N1HFgSUB3[8]->Draw("same p");
    N1HFgSUB3_decor[8]->Draw("same p");
    TPaveText * txCMS_3 = new TPaveText(0.0, 0.928, 0.257, 0.988, "NDC");
    SetTPaveTxt(txCMS_3, 19);
    txCMS_3->AddText("1.2 < |#eta| < 1.6");
    txCMS_3->Draw();
    TPaveText * tx1_3_cent = new TPaveText(0.07, 0.81, 0.23, 0.89, "NDC");
    SetTPaveTxt(tx1_3_cent, 20);
    tx1_3_cent->AddText("40 - 50%");
    tx1_3_cent->Draw();

    c1->Print("../figures/fig_v1odd_decor_pT_alt.pdf","pdf");

}
