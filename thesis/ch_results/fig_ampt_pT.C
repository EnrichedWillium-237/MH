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

static const int ncbins = 18;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,   0, 10, 20, 30,   0, 20,   5};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70,  10, 20, 30, 40,  20, 60,  80};

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
TGraphErrors * N1AHFgSUB3[ncbins];
TGraphErrors * N1BHFgSUB3[ncbins];
TGraphErrors * N1HFgSUB3[ncbins];
TGraphErrors * N1HFgSUB3_syst[ncbins];
TGraphErrors * N1AHFgSUB3_decor[ncbins];
TGraphErrors * N1BHFgSUB3_decor[ncbins];
TGraphErrors * N1HFgSUB3_decor[ncbins];
TGraphErrors * N1HFgSUB3_decor_syst[ncbins];
TGraphErrors * N112ASUB3[ncbins];
TGraphErrors * N112BSUB3[ncbins];
TGraphErrors * N112SUB3[ncbins];
TGraphErrors * N112SUB3_syst[ncbins];
TGraphErrors * ALICE_v1odd_pT_2TeV_5_80;

TGraphErrors * ampt_N1HFgASUB3[ncbins];
TGraphErrors * ampt_N1HFgBSUB3[ncbins];
TGraphErrors * ampt_N1HFgSUB3[ncbins];

# include "systematics.h"

void fig_ampt_pT() {

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

        N112ASUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N112ASUB3/-1.6_-1.2/%d_%d/g",cmin[cbin],cmax[cbin]));
        N112BSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N112BSUB3/1.2_1.6/%d_%d/g",cmin[cbin],cmax[cbin]));
        int numm =  N112ASUB3[cbin]->GetN();
        double xvalAm[50], xvalBm[50], yvalAm[50], yvalBm[50], yerrAm[50], yerrBm[50];
        for (int j = 0; j<num; j++) {
            N112ASUB3[cbin]->GetPoint(j, xvalAm[j], yvalAm[j]);
            yerrAm[j] = N112ASUB3[cbin]->GetErrorY(j);
            N112BSUB3[cbin]->GetPoint(j, xvalBm[j], yvalBm[j]);
            yerrBm[j] = N112BSUB3[cbin]->GetErrorY(j);

            //yvalAm[j]*=-1.;
            yvalAm[j] = 0.5*(yvalAm[j] + yvalBm[j]);
            yerrAm[j] = 0.5*sqrt( pow(yerrAm[j],2) + pow(yerrBm[j],2) );
        }

        N1HFgSUB3[cbin] = new TGraphErrors(num, xvalA, yvalA, 0, yerrA);
        N1HFgSUB3_decor[cbin] = new TGraphErrors(numd, xvalAd, yvalAd, 0, yerrAd);
        N112SUB3[cbin] = new TGraphErrors(num, xvalAm, yvalAm, 0, yerrAm);

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

        N112SUB3[cbin]->SetMarkerStyle(33);
        N112SUB3[cbin]->SetMarkerSize(1.7);
        N112SUB3[cbin]->SetMarkerColor(kGreen+2);
        N112SUB3[cbin]->SetLineColor(kGreen+2);
        N112SUB3[cbin]->SetFillColor(kGreen-8);

        //-- systematics
        Double_t x[50], y[50], xerr[50], ysyst[50];
        num = N1HFgSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.18;
            if (x[j]<3) ysyst[j] = getSyst( "N1HFgSUB3", "pt0", cbin );
            if (x[j]>3) ysyst[j] = getSyst( "N1HFgSUB3", "pt1", cbin );
        }
        N1HFgSUB3_syst[cbin] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1HFgSUB3_syst[cbin]->SetLineColor(kBlue-9);
        N1HFgSUB3_syst[cbin]->SetFillColor(kBlue-9);

        numd = N1HFgSUB3_decor[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB3_decor[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.18;
            if (x[j]<3) ysyst[j] = getSyst( "N1HFgSUB3_decor", "pt0", cbin );
            if (x[j]>3) ysyst[j] = getSyst( "N1HFgSUB3_decor", "pt1", cbin );
        }
        N1HFgSUB3_decor_syst[cbin] = new TGraphErrors(numd, x, y, xerr, ysyst);
        N1HFgSUB3_decor_syst[cbin]->SetLineColor(kRed-9);
        N1HFgSUB3_decor_syst[cbin]->SetFillColor(kRed-9);

        numm = N112SUB3[cbin]->GetN();
        for (int j = 0; j<numm; j++) {
            N112SUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.15;
            if (x[j]<3) ysyst[j] = getSyst( "N112A", "pt0", cbin );
            if (x[j]>3) ysyst[j] = getSyst( "N112A", "pt1", cbin );
        }
        N112SUB3_syst[cbin] = new TGraphErrors(numd, x, y, xerr, ysyst);
        N112SUB3_syst[cbin]->SetLineColor(kGreen-8);
        N112SUB3_syst[cbin]->SetFillColor(kGreen-8);
        //--

        // fix event plane weighting on AMPT calculation
        ampt_N1HFgASUB3[cbin] = (TGraphErrors *) fin->Get(Form("AMPT/N1HFgSUB3/0.0_2.0/%d_%d/gA",cmin[cbin],cmax[cbin]));
        ampt_N1HFgBSUB3[cbin] = (TGraphErrors *) fin->Get(Form("AMPT/N1HFgSUB3/0.0_2.0/%d_%d/gB",cmin[cbin],cmax[cbin]));
        double yA[50], yAerr[50], yB[50], yBerr[50], yerr[50];
        for (int j = 0; j<num; j++) {
            ampt_N1HFgASUB3[cbin]->GetPoint(j, x[j], yA[j]);
            yAerr[j] = ampt_N1HFgASUB3[cbin]->GetErrorY(j);
            ampt_N1HFgBSUB3[cbin]->GetPoint(j, x[j], yB[j]);
            yBerr[j] = ampt_N1HFgBSUB3[cbin]->GetErrorY(j);

            y[j] = 0.5*(yA[j] + yB[j]);
            yerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        ampt_N1HFgSUB3[cbin] = new TGraphErrors(num, x, y, 0, yerr);
        ampt_N1HFgSUB3[cbin]->SetMarkerStyle(20);
        ampt_N1HFgSUB3[cbin]->SetMarkerSize(0.1);
        ampt_N1HFgSUB3[cbin]->SetMarkerColor(kOrange-4);
        ampt_N1HFgSUB3[cbin]->SetLineColor(kOrange-4);
        ampt_N1HFgSUB3[cbin]->SetFillColor(kOrange-4);
    }

    ALICE_v1odd_pT_2TeV_5_80 = (TGraphErrors *) fdata->Get("v1odd/ALICE_v1odd_pT_2TeV_5_80");
    ALICE_v1odd_pT_2TeV_5_80->SetMarkerStyle(33);
    ALICE_v1odd_pT_2TeV_5_80->SetMarkerSize(2.1);
    ALICE_v1odd_pT_2TeV_5_80->SetMarkerColor(kMagenta);
    ALICE_v1odd_pT_2TeV_5_80->SetLineColor(kMagenta);


    TCanvas * c0 = new TCanvas("c0", "c0", 1000, 450);
    c0->Divide(3,1,0,0);

    TPad * pad0_1 = (TPad *) c0->cd(1);
    pad0_1->SetTopMargin(0.08);
    pad0_1->SetBottomMargin(0.17);
    h0 = new TH1D("h0", "", 100, 0.001, 7.95);
    h0->SetStats(0);
    h0->SetXTitle("p_{T} (GeV/c)");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(24);
    h0->GetXaxis()->SetTitleOffset(1.2);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(18);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(24);
    h0->GetYaxis()->SetTitleOffset(1.7);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(17);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.09, 0.06);
    h0->Draw();
    int bin0 = 11;
    ampt_N1HFgSUB3[bin0]->Draw("same E3");
    N1HFgSUB3_syst[bin0]->Draw("same 2");
    N1HFgSUB3_decor_syst[bin0]->Draw("same 2");
    N112SUB3_syst[bin0]->Draw("same 2");
    N1HFgSUB3[bin0]->Draw("same p");
    N1HFgSUB3_decor[bin0]->Draw("same p");
    N112SUB3[bin0]->Draw("same p");
    TLegend * leg0 = new TLegend(0.23, 0.20, 0.50, 0.48);
    SetLegend(leg0, 18);
    leg0->AddEntry(N1HFgSUB3[bin0],"  #eta_{C} = 0","lpf");
    leg0->AddEntry(N1HFgSUB3_decor[bin0],"  #eta_{C} = #eta_{ROI}","lpf");
    leg0->AddEntry(N112SUB3[bin0], "  mixed", "lpf");
    leg0->AddEntry(ampt_N1HFgSUB3[0], "  AMPT", "f");
    leg0->Draw();
    TPaveText * tx0_1_cent = new TPaveText(0.50, 0.81, 0.64, 0.89, "NDC");
    SetTPaveTxt(tx0_1_cent, 20);
    tx0_1_cent->AddText(Form("%d - %d%%",cmin[bin0],cmax[bin0]));
    tx0_1_cent->Draw();

    TPad * pad0_2 = (TPad *) c0->cd(2);
    pad0_2->SetTopMargin(0.08);
    pad0_2->SetBottomMargin(0.17);
    h0->Draw();
    int bin1 = 14;
    ampt_N1HFgSUB3[bin1]->Draw("same E3");
    N1HFgSUB3_syst[bin1]->Draw("same 2");
    N1HFgSUB3_decor_syst[bin1]->Draw("same 2");
    N112SUB3_syst[bin1]->Draw("same 2");
    N1HFgSUB3[bin1]->Draw("same p");
    N1HFgSUB3_decor[bin1]->Draw("same p");
    N112SUB3[bin1]->Draw("same p");
    TPaveText * tx0_2_cent = new TPaveText(0.39, 0.81, 0.66, 0.89, "NDC");
    SetTPaveTxt(tx0_2_cent, 20);
    tx0_2_cent->AddText(Form("%d - %d%%",cmin[bin1],cmax[bin1]));
    tx0_2_cent->Draw();

    TPad * pad0_3 = (TPad *) c0->cd(3);
    pad0_3->SetRightMargin(0.01);
    pad0_3->SetTopMargin(0.08);
    pad0_3->SetBottomMargin(0.17);
    h0->Draw();
    int bin2 = 9;
    ampt_N1HFgSUB3[bin2]->Draw("same E3");
    N1HFgSUB3_syst[bin2]->Draw("same 2");
    N1HFgSUB3_decor_syst[bin2]->Draw("same 2");
    N112SUB3_syst[bin2]->Draw("same 2");
    N1HFgSUB3[bin2]->Draw("same p");
    N1HFgSUB3_decor[bin2]->Draw("same p");
    N112SUB3[bin2]->Draw("same p");
    TPaveText * tx0_3_cent = new TPaveText(0.38, 0.81, 0.54, 0.89, "NDC");
    SetTPaveTxt(tx0_3_cent, 20);
    tx0_3_cent->AddText(Form("%d - %d%%",cmin[bin2],cmax[bin2]));
    tx0_3_cent->Draw();

    c0->Print("../figures/fig_ampt_pT.pdf","pdf");


    TCanvas * c1 = new TCanvas("c1", "c1", 600, 550);
    c1->cd();
    TH1D * h1 = (TH1D *) h0->Clone("h1");
    h1->GetXaxis()->SetTitleSize(26);
    h1->GetXaxis()->SetLabelSize(22);
    h1->GetYaxis()->SetTitleSize(26);
    h1->GetYaxis()->SetLabelSize(22);
    h1->GetXaxis()->SetRangeUser(0, 5);
    h1->GetYaxis()->SetRangeUser(-0.025, 0.01);
    h1->Draw();
    bin0 = 16;
    ampt_N1HFgSUB3[bin0]->Draw("same E3");
    N1HFgSUB3_decor_syst[bin0]->Draw("same 2");
    N112SUB3_syst[bin0]->Draw("same 2");
    N1HFgSUB3_decor[bin0]->Draw("same p");
    N112SUB3[bin0]->Draw("same p");
    ALICE_v1odd_pT_2TeV_5_80->Draw("same cp");
    TLegend * leg1 = new TLegend(0.22, 0.20, 0.49, 0.42);
    SetLegend(leg1, 20);
    leg1->AddEntry(N1HFgSUB3_decor[bin0],"  #eta_{C} = #eta_{ROI}","lpf");
    leg1->AddEntry(N112SUB3[bin0], "  mixed", "lpf");
    leg1->AddEntry(ALICE_v1odd_pT_2TeV_5_80, "  ALICE spectator 2.76 TeV (5 - 80%)", "lp");
    leg1->AddEntry(ampt_N1HFgSUB3[0], "  AMPT", "f");
    leg1->Draw();
    TPaveText * tx1_0 = new TPaveText(0.21, 0.43, 0.34, 0.48, "NDC");
    SetTPaveTxt(tx1_0, 22);
    tx1_0->AddText(Form("%d - %d%%",cmin[bin0],cmax[bin0]));
    tx1_0->Draw();

    c1->Print("../figures/fig_ampt_pT_ALICE.pdf","pdf");

}
