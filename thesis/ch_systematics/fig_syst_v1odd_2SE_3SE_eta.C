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

TFile * fin = new TFile("../../data/vnPlots.root","read");
TH1D * h0;
TGraphErrors * N1HFgSUB2[ncbins];
TGraphErrors * N1HFgSUB3[ncbins];
TGraphErrors * N1HFgRatio[ncbins];

void fig_syst_v1odd_2SE_3SE_eta() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1HFgSUB2[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB2/0.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1HFgSUB2[cbin]->SetMarkerStyle(25);
        N1HFgSUB2[cbin]->SetMarkerSize(1.2);
        N1HFgSUB2[cbin]->SetMarkerColor(kRed);
        N1HFgSUB2[cbin]->SetLineColor(kRed);
        N1HFgSUB2[cbin]->SetFillColor(kRed-9);
        N1HFgSUB2[cbin]->RemovePoint(0);
        N1HFgSUB2[cbin]->RemovePoint(N1HFgSUB2[cbin]->GetN()-1);
    }
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1HFgSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3/0.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1HFgSUB3[cbin]->SetMarkerStyle(21);
        N1HFgSUB3[cbin]->SetMarkerSize(1.2);
        N1HFgSUB3[cbin]->SetMarkerColor(kBlue);
        N1HFgSUB3[cbin]->SetLineColor(kBlue);
        N1HFgSUB3[cbin]->SetFillColor(kBlue-9);
        N1HFgSUB3[cbin]->RemovePoint(0);
        N1HFgSUB3[cbin]->RemovePoint(N1HFgSUB3[cbin]->GetN()-1);
    }
    for (int cbin = 0; cbin<ncbins; cbin++) {
        int num = N1HFgSUB2[cbin]->GetN();
        double xvalsub2[50], yvalsub2[50], yerrsub2[50];
        double xvalsub3[50], yvalsub3[50], yerrsub3[50];
        double yvalrat[50], yerrrat[50];
        for (int j = 0; j<num; j++) {
            N1HFgSUB2[cbin]->GetPoint(j, xvalsub2[j], yvalsub2[j]);
            yerrsub2[j] = N1HFgSUB2[cbin]->GetErrorY(j);
            N1HFgSUB3[cbin]->GetPoint(j, xvalsub3[j], yvalsub3[j]);
            yerrsub3[j] = N1HFgSUB3[cbin]->GetErrorY(j);

            yvalrat[j] = yvalsub3[j]/yvalsub2[j];
            yerrrat[j] = sqrt( pow(yerrsub2[j]/yvalsub2[j],2) + pow(yerrsub3[j]/yvalsub3[j],2) );
        }
        N1HFgRatio[cbin] = new TGraphErrors(num, xvalsub2, yvalrat, 0, yerrrat);

        N1HFgRatio[cbin]->SetMarkerStyle(20);
        N1HFgRatio[cbin]->SetMarkerSize(1.3);
        N1HFgRatio[cbin]->SetMarkerColor(kBlack);
        N1HFgRatio[cbin]->SetLineColor(kBlack);
    }


    TCanvas * c0 = new TCanvas("c0", "c0", 1100, 580);
    TPad * pad0[8];
    c0->cd();
    pad0[0] = new TPad("pad0_0", "pad0_0", 0.0, 0.5, 0.28, 1.0);
    pad0[0]->SetLeftMargin(0.22);
    pad0[0]->SetTopMargin(0.15);
    pad0[0]->SetBottomMargin(0);
    pad0[0]->SetRightMargin(0);
    pad0[0]->Draw();

    c0->cd();
    pad0[1] = new TPad("pad0_1", "pad0_1", 0.28, 0.5, 0.50, 1.0);
    pad0[1]->SetLeftMargin(0);
    pad0[1]->SetRightMargin(0);
    pad0[1]->SetTopMargin(0.15);
    pad0[1]->SetBottomMargin(0);
    pad0[1]->Draw();

    c0->cd();
    pad0[2] = new TPad("pad0_2", "pad0_2", 0.50, 0.5, 0.72, 1.0);
    pad0[2]->SetLeftMargin(0);
    pad0[2]->SetRightMargin(0);
    pad0[2]->SetTopMargin(0.15);
    pad0[2]->SetBottomMargin(0);
    pad0[2]->Draw();

    c0->cd();
    pad0[3] = new TPad("pad0_3", "pad0_3", 0.72, 0.5, 0.99, 1.0);
    pad0[3]->SetLeftMargin(0);
    pad0[3]->SetRightMargin(0.20);
    pad0[3]->SetTopMargin(0.15);
    pad0[3]->SetBottomMargin(0);
    pad0[3]->Draw();

    c0->cd();
    pad0[4] = new TPad("pad0_4", "pad0_4", 0.0, 0, 0.28, 0.5);
    pad0[4]->SetLeftMargin(0.22);
    pad0[4]->SetRightMargin(0);
    pad0[4]->SetTopMargin(0);
    pad0[4]->SetBottomMargin(0.18);
    pad0[4]->SetGrid();
    pad0[4]->Draw();

    c0->cd();
    pad0[5] = new TPad("pad0_5", "pad0_5", 0.28, 0, 0.50, 0.5);
    pad0[5]->SetLeftMargin(0);
    pad0[5]->SetRightMargin(0);
    pad0[5]->SetTopMargin(0);
    pad0[5]->SetBottomMargin(0.18);
    pad0[5]->SetGrid();
    pad0[5]->Draw();

    c0->cd();
    pad0[6] = new TPad("pad0_6", "pad0_6", 0.50, 0, 0.72, 0.5);
    pad0[6]->SetLeftMargin(0);
    pad0[6]->SetRightMargin(0);
    pad0[6]->SetTopMargin(0);
    pad0[6]->SetBottomMargin(0.18);
    pad0[6]->SetGrid();
    pad0[6]->Draw();

    c0->cd();
    pad0[7] = new TPad("pad0_3", "pad0_3", 0.72, 0, 0.99, 0.5);
    pad0[7]->SetLeftMargin(0);
    pad0[7]->SetRightMargin(0.20);
    pad0[7]->SetTopMargin(0);
    pad0[7]->SetBottomMargin(0.18);
    pad0[7]->SetGrid();
    pad0[7]->Draw();

    h0 = new TH1D("h0", "h0", 100, -2.4, 2.4);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{odd}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(22);
    h0->GetXaxis()->SetTitleOffset(2.1);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(17);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(22);
    h0->GetYaxis()->SetTitleOffset(2.7);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(16);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.045, 0.045);

    for (int cbin = 0; cbin<4; cbin++) {
        pad0[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->Draw();
        N1HFgSUB2[cbin]->Draw("same p");
        N1HFgSUB3[cbin]->Draw("same p");

        if (cbin == 0) {
            TPaveText * tx0_CMS_0 = new TPaveText(0.21, 0.86, 0.37, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_0, 18);
            tx0_CMS_0->AddText("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV");
            tx0_CMS_0->Draw();

            TPaveText * tx0_c0 = new TPaveText(0.51, 0.71, 0.71, 0.81, "NDC");
            SetTPaveTxt(tx0_c0, 18);
            tx0_c0->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            tx0_c0->Draw();

            TLegend * leg0 = new TLegend(0.26, 0.05, 0.64, 0.25);
            SetLegend(leg0, 18);
            leg0->AddEntry(N1HFgSUB2[cbin], "2 subevent v_{1}^{odd}", "p");
            leg0->AddEntry(N1HFgSUB3[cbin], "3 subevent v_{1}^{odd}", "p");
            leg0->Draw();
        }

        if (cbin == 1) {
            TPaveText * tx0_CMS_1 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_1, 18);
            tx0_CMS_1->AddText("0.3 < p_{T} < 3.0 GeV/c  ");
            tx0_CMS_1->Draw();

            TPaveText * tx0_c1 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx0_c1, 18);
            tx0_c1->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            tx0_c1->Draw();
        }

        if (cbin == 2) {
            TPaveText * tx0_CMS_2 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_2, 18);
            tx0_CMS_2->AddText("#eta_{C} = 0");
            tx0_CMS_2->Draw();

            TPaveText * tx0_c2 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx0_c2, 18);
            tx0_c2->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            tx0_c2->Draw();
        }

        if (cbin == 3) {
            TPaveText * tx0_c3 = new TPaveText(0.30, 0.71, 0.50, 0.81, "NDC");
            SetTPaveTxt(tx0_c3, 18);
            tx0_c3->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            tx0_c3->Draw();
        }

    }
    TLine * ln0 = new TLine(-2.4, 1.0, 2.4, 1.0);
    for (int cbin = 4; cbin<8; cbin++) {
        pad0[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->SetYTitle("v_{1}^{odd} Ratio: Sub3/Sub2");
        htmp->GetYaxis()->SetRangeUser(0.35, 1.65);
        htmp->Draw();
        ln0->Draw();
        N1HFgRatio[cbin-4]->Draw("same p");
    }

    c0->Print("../figures/fig_syst_v1odd_2SE_3SE_eta_0-20.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 1100, 580);
    TPad * pad1[8];
    for (int cbin = 0; cbin<4; cbin++) {
        c1->cd();
        pad1[cbin] = (TPad *) pad0[cbin]->Clone(Form("pad1_%d",cbin));
        pad1[cbin]->Draw();
        pad1[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h1_%d",cbin));
        htmp->Draw();
        N1HFgSUB2[cbin+4]->Draw("same p");
        N1HFgSUB3[cbin+4]->Draw("same p");

        if (cbin == 0) {
            TPaveText * tx0_CMS_0 = new TPaveText(0.21, 0.86, 0.37, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_0, 18);
            tx0_CMS_0->AddText("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV");
            tx0_CMS_0->Draw();

            TPaveText * tx0_c0 = new TPaveText(0.51, 0.71, 0.71, 0.81, "NDC");
            SetTPaveTxt(tx0_c0, 18);
            tx0_c0->AddText(Form("%d - %d%%",cmin[cbin+4],cmax[cbin+4]));
            tx0_c0->Draw();

            TLegend * leg0 = new TLegend(0.26, 0.05, 0.64, 0.25);
            SetLegend(leg0, 18);
            leg0->AddEntry(N1HFgSUB2[cbin], "2 subevent v_{1}^{odd}", "p");
            leg0->AddEntry(N1HFgSUB3[cbin], "3 subevent v_{1}^{odd}", "p");
            leg0->Draw();
        }

        if (cbin == 1) {
            TPaveText * tx0_CMS_1 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_1, 18);
            tx0_CMS_1->AddText("0.3 < p_{T} < 3.0 GeV/c  ");
            tx0_CMS_1->Draw();

            TPaveText * tx0_c1 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx0_c1, 18);
            tx0_c1->AddText(Form("%d - %d%%",cmin[cbin+4],cmax[cbin+4]));
            tx0_c1->Draw();
        }

        if (cbin == 2) {
            TPaveText * tx0_CMS_2 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx0_CMS_2, 18);
            tx0_CMS_2->AddText("#eta_{C} = 0");
            tx0_CMS_2->Draw();

            TPaveText * tx0_c2 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx0_c2, 18);
            tx0_c2->AddText(Form("%d - %d%%",cmin[cbin+4],cmax[cbin+4]));
            tx0_c2->Draw();
        }

        if (cbin == 3) {
            TPaveText * tx0_c3 = new TPaveText(0.30, 0.71, 0.50, 0.81, "NDC");
            SetTPaveTxt(tx0_c3, 18);
            tx0_c3->AddText(Form("%d - %d%%",cmin[cbin+4],cmax[cbin+4]));
            tx0_c3->Draw();
        }

    }
    for (int cbin = 4; cbin<8; cbin++) {
        c1->cd();
        pad1[cbin] = (TPad *) pad0[cbin]->Clone(Form("pad1_%d",cbin));
        pad1[cbin]->Draw();
        pad1[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->SetYTitle("v_{1}^{odd} Ratio: Sub3/Sub2");
        htmp->GetYaxis()->SetRangeUser(0.35, 1.65);
        htmp->Draw();
        ln0->Draw();
        N1HFgRatio[cbin]->Draw("same p");
    }

    c1->Print("../figures/fig_syst_v1odd_2SE_3SE_eta_20-40.pdf","pdf");



    TCanvas * c2 = new TCanvas("c2", "c2", 830, 580);
    TPad * pad2[6];
    c2->cd();
    pad2[0] = new TPad("pad2_0", "pad2_0", 0.0, 0.5, 0.38, 1.0);
    pad2[0]->SetLeftMargin(0.22);
    pad2[0]->SetTopMargin(0.15);
    pad2[0]->SetBottomMargin(0);
    pad2[0]->SetRightMargin(0);
    pad2[0]->Draw();

    c2->cd();
    pad2[1] = new TPad("pad2_1", "pad2_1", 0.38, 0.5, 0.69, 1.0);
    pad2[1]->SetLeftMargin(0);
    pad2[1]->SetRightMargin(0);
    pad2[1]->SetTopMargin(0.15);
    pad2[1]->SetBottomMargin(0);
    pad2[1]->Draw();

    c2->cd();
    pad2[2] = new TPad("pad2_2", "pad2_2", 0.69, 0.5, 1.0, 1.0);
    pad2[2]->SetLeftMargin(0);
    pad2[2]->SetRightMargin(0.05);
    pad2[2]->SetTopMargin(0.15);
    pad2[2]->SetBottomMargin(0);
    pad2[2]->Draw();

    c2->cd();
    pad2[3] = new TPad("pad2_3", "pad2_3", 0.0, 0, 0.38, 0.5);
    pad2[3]->SetLeftMargin(0.22);
    pad2[3]->SetRightMargin(0);
    pad2[3]->SetTopMargin(0);
    pad2[3]->SetBottomMargin(0.18);
    pad2[3]->SetGrid();
    pad2[3]->Draw();

    c2->cd();
    pad2[4] = new TPad("pad2_4", "pad2_4", 0.38, 0, 0.69, 0.5);
    pad2[4]->SetLeftMargin(0);
    pad2[4]->SetRightMargin(0);
    pad2[4]->SetTopMargin(0);
    pad2[4]->SetBottomMargin(0.18);
    pad2[4]->SetGrid();
    pad2[4]->Draw();

    c2->cd();
    pad2[5] = new TPad("pad2_5", "pad2_5", 0.69, 0, 1.0, 0.5);
    pad2[5]->SetLeftMargin(0);
    pad2[5]->SetRightMargin(0.05);
    pad2[5]->SetTopMargin(0);
    pad2[5]->SetBottomMargin(0.18);
    pad2[5]->SetGrid();
    pad2[5]->Draw();

    for (int cbin = 0; cbin<3; cbin++) {
        pad2[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h2_%d",cbin));
        htmp->Draw();
        N1HFgSUB2[cbin+8]->Draw("same p");
        N1HFgSUB3[cbin+8]->Draw("same p");

        if (cbin == 0) {
            TPaveText * tx2_CMS_0 = new TPaveText(0.21, 0.86, 0.37, 0.95, "NDC");
            SetTPaveTxt(tx2_CMS_0, 18);
            tx2_CMS_0->AddText("#bf{CMS}  PbPb #sqrt{s_{NN}} = 5.02 TeV");
            tx2_CMS_0->Draw();

            TPaveText * tx2_c0 = new TPaveText(0.51, 0.71, 0.71, 0.81, "NDC");
            SetTPaveTxt(tx2_c0, 18);
            tx2_c0->AddText(Form("%d - %d%%",cmin[cbin+8],cmax[cbin+8]));
            tx2_c0->Draw();

            TLegend * leg2 = new TLegend(0.26, 0.05, 0.64, 0.25);
            SetLegend(leg2, 18);
            leg2->AddEntry(N1HFgSUB2[cbin], "2 subevent v_{1}^{odd}", "p");
            leg2->AddEntry(N1HFgSUB3[cbin], "3 subevent v_{1}^{odd}", "p");
            leg2->Draw();
        }

        if (cbin == 1) {
            TPaveText * tx2_CMS_1 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx2_CMS_1, 18);
            tx2_CMS_1->AddText("0.3 < p_{T} < 3.0 GeV/c  ");
            tx2_CMS_1->Draw();

            TPaveText * tx2_c1 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx2_c1, 18);
            tx2_c1->AddText(Form("%d - %d%%",cmin[cbin+8],cmax[cbin+8]));
            tx2_c1->Draw();
        }

        if (cbin == 2) {
            TPaveText * tx2_CMS_2 = new TPaveText(0.0, 0.86, 0.16, 0.95, "NDC");
            SetTPaveTxt(tx2_CMS_2, 18);
            tx2_CMS_2->AddText("#eta_{C} = 0");
            tx2_CMS_2->Draw();

            TPaveText * tx2_c2 = new TPaveText(0.40, 0.71, 0.60, 0.81, "NDC");
            SetTPaveTxt(tx2_c2, 18);
            tx2_c2->AddText(Form("%d - %d%%",cmin[cbin+8],cmax[cbin+8]));
            tx2_c2->Draw();
        }
    }
    for (int cbin = 3; cbin<6; cbin++) {
        pad2[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h2_%d",cbin));
        htmp->SetYTitle("v_{1}^{odd} Ratio: Sub3/Sub2");
        htmp->GetYaxis()->SetRangeUser(0.35, 1.65);
        htmp->Draw();
        ln0->Draw();
        N1HFgRatio[cbin+3]->Draw("same p");
    }

    c2->Print("../figures/fig_syst_v1odd_2SE_3SE_eta_40-70.pdf","pdf");

}
