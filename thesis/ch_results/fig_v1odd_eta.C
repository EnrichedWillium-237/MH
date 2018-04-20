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
static const double ebinmid[] = {-2.2, -1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2};

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

TFile * fin;
TFile * finSyst;
TH1D * h0;
TH1D * h1;
TGraphErrors * N1HFgSUB2[ncbins];
TGraphErrors * N1HFgSUB2_syst[ncbins];

const double syst_v1odd_eta[ncbins] = {2.6e-4, 2.6e-4, 2.6e-4, 2.6e-4, 2.6e-4, 4.0e-4, 4.0e-4, 4.0e-4, 4.0e-4, 7.8e-4, 7.8e-4};

void fig_v1odd_eta() {

    fin = new TFile("../../data/MH_hists_master.root","read");

    for (int i = 0; i<ncbins; i++) {
        N1HFgSUB2[i] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[i],cmax[i]));
        N1HFgSUB2[i]->SetMarkerStyle(21);
        N1HFgSUB2[i]->SetMarkerSize(1.2);
        N1HFgSUB2[i]->SetMarkerColor(kBlue);
        N1HFgSUB2[i]->SetLineColor(kBlue);
        N1HFgSUB2[i]->RemovePoint(0);
        N1HFgSUB2[i]->RemovePoint(N1HFgSUB2[i]->GetN()-1);
    }


    //-- systematics
    for (int i = 0; i<ncbins; i++) {
        Double_t x[50], y[50], xerr[50], ysyst[50];
        int num = N1HFgSUB2[i]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFgSUB2[i]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.15;
            ysyst[j] = syst_v1odd_eta[i]*ebinmid[j];
        }
        N1HFgSUB2_syst[i] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1HFgSUB2_syst[i]->SetLineColor(kBlue-10);
        N1HFgSUB2_syst[i]->SetFillColor(kBlue-10);
    }
    //--


    TCanvas * c0 = new TCanvas("c0", "c0", 900, 650);
    c0->Divide(3,2,0,0);
    h0 = new TH1D("h0", "", 100, -2.4, 2.4);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetYaxis()->SetRangeUser(-0.05, 0.05);
    for (int cbin = 0; cbin<6; cbin++) {
        TPad * pad0 = (TPad *) c0->cd(cbin+1);
        if (cbin == 0 || cbin == 3) pad0->SetLeftMargin(0.22);
        if (cbin == 2 || cbin == 5) pad0->SetRightMargin(0.02);
        if (cbin<3) pad0->SetTopMargin(0.11);
        if (cbin>=3) pad0->SetBottomMargin(0.24);
        TH1D * htmp = (TH1D *) h0->Clone(Form("htmp_%d",cbin));
        if (cbin == 0) {
            htmp->GetYaxis()->SetTitleSize(0.10);
            htmp->GetYaxis()->SetTitleOffset(1.07);
            htmp->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 3) {
            htmp->GetXaxis()->SetTitleSize(0.08);
            htmp->GetXaxis()->SetTitleOffset(0.98);
            htmp->GetXaxis()->SetLabelSize(0.06);
            htmp->GetXaxis()->SetLabelOffset(0.017);
            htmp->GetYaxis()->SetTitleSize(0.09);
            htmp->GetYaxis()->SetTitleOffset(1.18);
            htmp->GetYaxis()->SetLabelSize(0.05);
        }
        if (cbin>=4) {
            htmp->GetXaxis()->SetTitleSize(0.10);
            htmp->GetXaxis()->SetTitleOffset(0.78);
            htmp->GetXaxis()->SetLabelSize(0.07);
            htmp->GetYaxis()->SetLabelOffset(0.010);
        }
        htmp->Draw();
        N1HFgSUB2_syst[cbin]->Draw("same 2");
        N1HFgSUB2[cbin]->Draw("same p");

        TPaveText * txcent;
        if (cbin == 0) txcent = new TPaveText(0.50, 0.75, 0.72, 0.82, "NDC");
        if (cbin == 1 || cbin == 2) txcent = new TPaveText(0.37, 0.75, 0.62, 0.82, "NDC");
        if (cbin == 3) txcent = new TPaveText(0.50, 0.87, 0.72, 0.94, "NDC");
        if (cbin == 4 || cbin == 5) txcent = new TPaveText(0.37, 0.87, 0.62, 0.94, "NDC");
        SetTPaveTxt(txcent, 20);
        txcent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txcent->Draw();
    }

    c0->cd(1);
    TPaveText * tx0_0 = new TPaveText(0.204, 0.929, 0.732, 0.997, "NDC");
    SetTPaveTxt(tx0_0, 20);
    tx0_0->AddText("#bf{CMS}, PbPb 5.02 TeV");
    tx0_0->Draw();

    c0->cd(2);
    TPaveText * tx0_1 = new TPaveText(0.000, 0.914, 0.527, 0.986, "NDC");
    SetTPaveTxt(tx0_1, 20);
    tx0_1->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx0_1->Draw();

    c0->cd(3);
    TPaveText * tx0_2 = new TPaveText(0.000, 0.914, 0.245, 0.986, "NDC");
    SetTPaveTxt(tx0_2, 20);
    tx0_2->AddText("#eta_{C} = 0");
    tx0_2->Draw();

    c0->Print("../fig_v1odd_eta_0_30.pdf","pdf");


    //-- --//

    TCanvas * c1 = new TCanvas("c1", "c1", 900, 650);
    c1->Divide(3,2,0,0);
    h1 = new TH1D("h1", "", 100, -2.4, 2.4);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->SetNdivisions(508);
    h1->GetYaxis()->SetNdivisions(508);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(-0.05, 0.05);
    for (int cbin = 0; cbin<5; cbin++) {
        TPad * pad0 = (TPad *) c1->cd(cbin+1);
        if (cbin == 0 || cbin == 3) pad0->SetLeftMargin(0.22);
        if (cbin == 2 || cbin == 5) pad0->SetRightMargin(0.05);
        if (cbin<3) pad0->SetTopMargin(0.11);
        if (cbin>=3) pad0->SetBottomMargin(0.24);
        TH1D * htmp = (TH1D *) h1->Clone(Form("htmp_%d",cbin));
        if (cbin == 0) {
            htmp->GetYaxis()->SetTitleSize(0.10);
            htmp->GetYaxis()->SetTitleOffset(1.07);
            htmp->GetYaxis()->SetLabelSize(0.06);
        }
        if (cbin == 3) {
            htmp->GetXaxis()->SetTitleSize(0.08);
            htmp->GetXaxis()->SetTitleOffset(0.98);
            htmp->GetXaxis()->SetLabelSize(0.06);
            htmp->GetXaxis()->SetLabelOffset(0.017);
            htmp->GetYaxis()->SetTitleSize(0.09);
            htmp->GetYaxis()->SetTitleOffset(1.18);
            htmp->GetYaxis()->SetLabelSize(0.05);
        }
        if (cbin>=4) {
            htmp->GetXaxis()->SetTitleSize(0.10);
            htmp->GetXaxis()->SetTitleOffset(0.78);
            htmp->GetXaxis()->SetLabelSize(0.07);
            htmp->GetYaxis()->SetLabelOffset(0.010);
        }
        htmp->Draw();
        N1HFgSUB2_syst[cbin+6]->Draw("same 2");
        N1HFgSUB2[cbin+6]->Draw("same p");

        TPaveText * txcent;
        if (cbin == 0) txcent = new TPaveText(0.50, 0.75, 0.72, 0.82, "NDC");
        if (cbin == 1 || cbin == 2) txcent = new TPaveText(0.37, 0.75, 0.62, 0.82, "NDC");
        if (cbin == 3) txcent = new TPaveText(0.50, 0.87, 0.72, 0.94, "NDC");
        if (cbin == 4 || cbin == 5) txcent = new TPaveText(0.37, 0.87, 0.62, 0.94, "NDC");
        SetTPaveTxt(txcent, 20);
        txcent->AddText(Form("%d - %d%%",cmin[cbin+6],cmax[cbin+6]));
        txcent->Draw();
    }
    // TPad * pad1 = (TPad *) c1->cd(6);
    // pad1->SetBBoxY1(0.2);
    //pad1->SetBBoxX1(0.1);
    // pad1->SetBBoxX2(1.0);
    // c1->Update();
    // pad1->SetBBoxY2(0.1);
    // c1->Update();
    // pad1->SetBottomMargin(0.25);
    // pad1->SetTopMargin(0.25);
    // pad1->SetLeftMargin(0.25);
    // pad1->SetRightMargin(0.25);
    // TH1D * htest = new TH1D("h", "", 10, 0, 2);
    // htest->Draw();
    TPad * pad1 = (TPad *) c1->cd(6);
    pad1->SetRightMargin(0.05);
    pad1->SetBottomMargin(0.24);
    h1->Draw();
    TBox * box1 = new TBox(-2.38, -0.1, 2.5, 0.0496);
    box1->SetFillColor(0);
    box1->Draw();
    TPaveText * txeta = new TPaveText(0.035, 0.912, 0.89, 0.982, "NDC");
    SetTPaveTxt2(txeta, 20);
    txeta->AddText("-2       -1       0       1        2");
    txeta->Draw();
    TPaveText * txeta1 = new TPaveText(0.44, 0.83, 0.54, 0.904, "NDC");
    SetTPaveTxt2(txeta1, 28);
    txeta1->AddText("#eta");
    txeta1->Draw();

    c1->cd(1);
    TPaveText * tx1_0 = new TPaveText(0.204, 0.929, 0.732, 0.997, "NDC");
    SetTPaveTxt(tx1_0, 20);
    tx1_0->AddText("#bf{CMS}, PbPb 5.02 TeV");
    tx1_0->Draw();

    c1->cd(2);
    TPaveText * tx1_1 = new TPaveText(0.000, 0.914, 0.527, 0.986, "NDC");
    SetTPaveTxt(tx1_1, 20);
    tx1_1->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx1_1->Draw();

    c1->cd(3);
    TPaveText * tx1_2 = new TPaveText(0.000, 0.914, 0.245, 0.986, "NDC");
    SetTPaveTxt(tx1_2, 20);
    tx1_2->AddText("#eta_{C} = 0");
    tx1_2->Draw();

    c1->Print("../fig_v1odd_eta_30_70.pdf","pdf");

}
