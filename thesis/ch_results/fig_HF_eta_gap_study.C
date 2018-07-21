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
static const double emin[] = {3.0, 3.5, 4.0, 4.5};
static const double emax[] = {3.5, 4.0, 4.5, 5.0};

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
TString type[5] = {"N1HFcSUB3", "N1HFdSUB3", "N1HFeSUB3", "N1HFfSUB3", "N1HFgSUB3"};
TH1D * h0;
TGraphErrors * g0[5];
TGraphErrors * gA0[5];
TGraphErrors * gB0[5];
TGraphErrors * g0ampt[5];
TGraphErrors * gA0ampt[5];
TGraphErrors * gB0ampt[5];

TGraphErrors * g1[5];
TGraphErrors * gA1[5];
TGraphErrors * gB1[5];
TGraphErrors * g1ampt[5];
TGraphErrors * gA1ampt[5];
TGraphErrors * gB1ampt[5];

void fig_HF_eta_gap_study() {

    int mstyle[5] = {20, 25, 21, 24, 20};
    float msize[5] = {1.3, 1.2, 1.2, 1.3, 1.3};
    int color[5] = {kMagenta, kRed, kBlue, kGreen+2, kBlack};

    for (int i = 0; i<5; i++) {
        gA0[i] = (TGraphErrors *) fin->Get(Form("default/%s/1.2_1.6/20_60/gintA",type[i].Data()));
        // gA0[i]->RemovePoint(0);
        // gA0[i]->RemovePoint(gA0[i]->GetN()-1);
        gB0[i] = (TGraphErrors *) fin->Get(Form("default/%s/1.2_1.6/20_60/gintB",type[i].Data()));
        gA0ampt[i] = (TGraphErrors *) fin->Get(Form("AMPT/%s/1.2_1.6/20_60/gintA",type[i].Data()));
        gB0ampt[i] = (TGraphErrors *) fin->Get(Form("AMPT/%s/1.2_1.6/20_60/gintB",type[i].Data()));

        int num =  gA0[i]->GetN();
        double xA[50], xB[50], yA[50], yB[50], yAerr[50], yBerr[50];
        for (int j = 0; j<num; j++) {
            gA0[i]->GetPoint(j, xA[j], yA[j]);
            yAerr[j] = gA0[i]->GetErrorY(j);
            gB0[i]->GetPoint(j, xB[j], yB[j]);
            yBerr[j] = gB0[i]->GetErrorY(j);

            yA[j] = 0.5*(yA[j] - yB[j]);
            yAerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        gA0[i]->SetMarkerStyle(mstyle[i]);
        gA0[i]->SetMarkerSize(msize[i]);
        gA0[i]->SetMarkerColor(color[i]);
        gA0[i]->SetLineColor(color[i]);

        gB0[i]->SetMarkerStyle(mstyle[i]);
        gB0[i]->SetMarkerSize(msize[i]);
        gB0[i]->SetMarkerColor(color[i]);
        gB0[i]->SetLineColor(color[i]);

        g0[i] = new TGraphErrors(num, xA, yA, 0, yAerr);
        g0[i]->SetMarkerStyle(mstyle[i]);
        g0[i]->SetMarkerSize(msize[i]);
        g0[i]->SetMarkerColor(color[i]);
        g0[i]->SetLineColor(color[i]);

        for (int j = 0; j<num; j++) {
            gA0ampt[i]->GetPoint(j, xA[j], yA[j]);
            yAerr[j] = gA0ampt[i]->GetErrorY(j);
            gB0ampt[i]->GetPoint(j, xB[j], yB[j]);
            yBerr[j] = gB0ampt[i]->GetErrorY(j);

            yA[j] = 0.5*(yA[j] - yB[j]);
            yAerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        gA0ampt[i]->SetMarkerStyle(mstyle[i]);
        gA0ampt[i]->SetMarkerSize(msize[i]);
        gA0ampt[i]->SetMarkerColor(color[i]);
        gA0ampt[i]->SetLineColor(color[i]);

        gB0ampt[i]->SetMarkerStyle(mstyle[i]);
        gB0ampt[i]->SetMarkerSize(msize[i]);
        gB0ampt[i]->SetMarkerColor(color[i]);
        gB0ampt[i]->SetLineColor(color[i]);

        g0ampt[i] = new TGraphErrors(num, xA, yA, 0, yAerr);
        g0ampt[i]->SetMarkerStyle(mstyle[i]);
        g0ampt[i]->SetMarkerSize(msize[i]);
        g0ampt[i]->SetMarkerColor(color[i]);
        g0ampt[i]->SetLineColor(color[i]);


        gA1[i] = (TGraphErrors *) fin->Get(Form("default/%s_decor/1.2_1.6/20_60/gintA",type[i].Data()));
        // gA1[i]->RemovePoint(0);
        // gA1[i]->RemovePoint(gA1[i]->GetN()-1);
        gB1[i] = (TGraphErrors *) fin->Get(Form("default/%s_decor/1.2_1.6/20_60/gintB",type[i].Data()));
        gA1ampt[i] = (TGraphErrors *) fin->Get(Form("AMPT/%s_decor/1.2_1.6/20_60/gintA",type[i].Data()));
        gB1ampt[i] = (TGraphErrors *) fin->Get(Form("AMPT/%s_decor/1.2_1.6/20_60/gintB",type[i].Data()));

        for (int j = 0; j<num; j++) {
            gA1[i]->GetPoint(j, xA[j], yA[j]);
            yAerr[j] = gA1[i]->GetErrorY(j);
            gB1[i]->GetPoint(j, xB[j], yB[j]);
            yBerr[j] = gB1[i]->GetErrorY(j);

            yA[j] = 0.5*(yA[j] - yB[j]);
            yAerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        gA1[i]->SetMarkerStyle(mstyle[i]);
        gA1[i]->SetMarkerSize(msize[i]);
        gA1[i]->SetMarkerColor(color[i]);
        gA1[i]->SetLineColor(color[i]);

        gB1[i]->SetMarkerStyle(mstyle[i]);
        gB1[i]->SetMarkerSize(msize[i]);
        gB1[i]->SetMarkerColor(color[i]);
        gB1[i]->SetLineColor(color[i]);

        g1[i] = new TGraphErrors(num, xA, yA, 0, yAerr);
        g1[i]->SetMarkerStyle(mstyle[i]);
        g1[i]->SetMarkerSize(msize[i]);
        g1[i]->SetMarkerColor(color[i]);
        g1[i]->SetLineColor(color[i]);

        for (int j = 0; j<num; j++) {
            gA1ampt[i]->GetPoint(j, xA[j], yA[j]);
            yAerr[j] = gA1ampt[i]->GetErrorY(j);
            gB1ampt[i]->GetPoint(j, xB[j], yB[j]);
            yBerr[j] = gB1ampt[i]->GetErrorY(j);

            yA[j] = 0.5*(yA[j] - yB[j]);
            yAerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        gA1ampt[i]->SetMarkerStyle(mstyle[i]);
        gA1ampt[i]->SetMarkerSize(msize[i]);
        gA1ampt[i]->SetMarkerColor(color[i]);
        gA1ampt[i]->SetLineColor(color[i]);

        gB1ampt[i]->SetMarkerStyle(mstyle[i]);
        gB1ampt[i]->SetMarkerSize(msize[i]);
        gB1ampt[i]->SetMarkerColor(color[i]);
        gB1ampt[i]->SetLineColor(color[i]);

        g1ampt[i] = new TGraphErrors(num, xA, yA, 0, yAerr);
        g1ampt[i]->SetMarkerStyle(mstyle[i]);
        g1ampt[i]->SetMarkerSize(msize[i]);
        g1ampt[i]->SetMarkerColor(color[i]);
        g1ampt[i]->SetLineColor(color[i]);
    }


    h0 = new TH1D("h0", "", 100, -2.8, 2.8);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(24);
    h0->GetXaxis()->SetTitleOffset(1.2);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(20);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(25);
    h0->GetYaxis()->SetTitleOffset(2.1);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(19);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.06, 0.01);

    TCanvas * c0 = new TCanvas("c0", "c0", 950, 530);
    c0->cd();

    TPad * pad0_1 = new TPad("pad0_1", "pad0_1", 0.0, 0.0, 0.53, 1.0);
    pad0_1->SetLeftMargin(0.24);
    pad0_1->SetRightMargin(0);
    pad0_1->SetTopMargin(0.1);
    pad0_1->SetBottomMargin(0.13);
    pad0_1->SetGrid();
    pad0_1->Draw();

    TPad * pad0_2 = new TPad("pad0_2", "pad0_2", 0.53, 0.0, 1.0, 1.0);
    pad0_2->SetLeftMargin(0);
    pad0_2->SetRightMargin(0.12);
    pad0_2->SetTopMargin(0.1);
    pad0_2->SetBottomMargin(0.13);
    pad0_2->SetGrid();
    pad0_2->Draw();

    pad0_1->cd();
    TH1D * h0_1 = (TH1D *) h0->Clone("h0_1");
    h0_1->Draw();
    for (int i = 0; i<4; i++) {
        gA0[i]->Draw("same p");
    }
    TLegend * leg0_1 = new TLegend(0.27, 0.17, 0.60, 0.37);
    SetLegend(leg0_1, 20);
    for (int i = 0; i<4; i++) {
        leg0_1->AddEntry(gA0[i], Form("%0.1f < #eta_{A} < %0.1f",emin[i],emax[i]), "p");
    }
    leg0_1->Draw();
    TPaveText * tx0_1_1 = new TPaveText(0.56, 0.81, 0.68, 0.87, "NDC");
    SetTPaveTxt(tx0_1_1, 22);
    tx0_1_1->AddText("Data");
    tx0_1_1->Draw();

    pad0_2->cd();
    TH1D * h0_2 = (TH1D *) h0->Clone("h0_2");
    h0_2->Draw();
    for (int i = 0; i<4; i++) {
        gA0ampt[i]->Draw("same p"); // change to g0ampt with new TFile
    }
    TPaveText * tx0_2 = new TPaveText(0.04, 0.17, 0.45, 0.33, "NDC");
    SetTPaveTxt(tx0_2, 20);
    tx0_2->AddText("#eta_{C} = 0");
    tx0_2->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx0_2->AddText("20 - 60%");
    tx0_2->Draw();
    TPaveText * tx0_1_2 = new TPaveText(0.36, 0.81, 0.48, 0.87, "NDC");
    SetTPaveTxt(tx0_1_2, 22);
    tx0_1_2->AddText("AMPT");
    tx0_1_2->Draw();
    c0->Print("../figures/fig_HF_eta_gap_study.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 950, 530);
    c1->cd();

    TPad * pad1_1 = new TPad("pad1_1", "pad1_1", 0.0, 0.0, 0.53, 1.0);
    pad1_1->SetLeftMargin(0.24);
    pad1_1->SetRightMargin(0);
    pad1_1->SetTopMargin(0.1);
    pad1_1->SetBottomMargin(0.13);
    pad1_1->SetGrid();
    pad1_1->Draw();

    TPad * pad1_2 = new TPad("pad1_2", "pad1_2", 0.53, 0.0, 1.0, 1.0);
    pad1_2->SetLeftMargin(0);
    pad1_2->SetRightMargin(0.12);
    pad1_2->SetTopMargin(0.1);
    pad1_2->SetBottomMargin(0.13);
    pad1_2->SetGrid();
    pad1_2->Draw();

    pad1_1->cd();
    TH1D * h1_1 = (TH1D *) h0->Clone("h1_1");
    h1_1->Draw();
    for (int i = 0; i<4; i++) {
        gA1[i]->Draw("same p");
    }
    TLegend * leg1_1 = new TLegend(0.27, 0.17, 0.60, 0.37);
    SetLegend(leg1_1, 20);
    for (int i = 0; i<4; i++) {
        leg1_1->AddEntry(gA1[i], Form("%0.1f < #eta_{A} < %0.1f",emin[i],emax[i]), "p");
    }
    leg1_1->Draw();
    TPaveText * tx1_1_1 = new TPaveText(0.56, 0.81, 0.68, 0.87, "NDC");
    SetTPaveTxt(tx1_1_1, 22);
    tx1_1_1->AddText("Data");
    tx1_1_1->Draw();

    pad1_2->cd();
    TH1D * h1_2 = (TH1D *) h0->Clone("h1_2");
    h1_2->Draw();
    for (int i = 0; i<4; i++) {
        gA1ampt[i]->Draw("same p"); // change to g0ampt with new TFile
    }
    TPaveText * tx1_2 = new TPaveText(0.04, 0.17, 0.45, 0.33, "NDC");
    SetTPaveTxt(tx1_2, 20);
    tx1_2->AddText("#eta_{C} = #eta_{ROI}");
    tx1_2->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx1_2->AddText("20 - 60%");
    tx1_2->Draw();
    TPaveText * tx1_1_2 = new TPaveText(0.36, 0.81, 0.48, 0.87, "NDC");
    SetTPaveTxt(tx1_1_2, 22);
    tx1_1_2->AddText("AMPT");
    tx1_1_2->Draw();
    c1->Print("../figures/fig_HF_eta_gap_study_decor.pdf","pdf");

}
