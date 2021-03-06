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

TFile * fin = new TFile("../../data/vnPlots.root","read");
TH1D * h0;
TGraphErrors * N1EVENSUB3[ncbins];
TGraphErrors * N1EVENSUB3_syst[ncbins];

# include "systematics.h"

void fig_v1even_SP_eta() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1EVENSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3/-2.4_-0.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3[cbin]->SetMarkerStyle(21);
        N1EVENSUB3[cbin]->SetMarkerSize(1.1);
        N1EVENSUB3[cbin]->SetMarkerColor(kBlue);
        N1EVENSUB3[cbin]->SetLineColor(kBlue);
        N1EVENSUB3[cbin]->RemovePoint(5);
        N1EVENSUB3[cbin]->RemovePoint(5);

        //-- systematics
        Double_t x[50], y[50], xerr[50], ysyst[50];
        int num = N1EVENSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            N1EVENSUB3[cbin]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.15;
            ysyst[j] = getSyst( "N1EVEN", "eta", cbin );
        }
        N1EVENSUB3_syst[cbin] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1EVENSUB3_syst[cbin]->SetLineColor(kBlue-10);
        N1EVENSUB3_syst[cbin]->SetFillColor(kBlue-10);
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

    TPaveText * tx0_CMS = new TPaveText(0.04, 0.33, 0.61, 0.94, "NDC");
    SetTPaveTxt(tx0_CMS, 20);
    tx0_CMS->AddText("#bf{CMS}");
    tx0_CMS->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    tx0_CMS->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx0_CMS->AddText("#eta_{C} = 0");
    tx0_CMS->Draw();

    h0 = new TH1D("h0", "h0", 100, -2.8, 2.8);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{even}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(507);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(22);
    h0->GetXaxis()->SetTitleOffset(2.7);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(17);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(22);
    h0->GetYaxis()->SetTitleOffset(3.7);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(16);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.025, 0.025);

    for (int cbin = 0; cbin<11; cbin++) {
        pad0[cbin]->cd();
        TH1D * htmp = (TH1D *) h0->Clone(Form("h0_%d",cbin));
        htmp->Draw();
        N1EVENSUB3_syst[cbin]->Draw("same 2");
        N1EVENSUB3[cbin]->Draw("same p");

        TPaveText * tx0_cent;
        // if (cbin == 0) tx0_cent = new TPaveText(0.48, 0.76, 0.74, 0.88, "NDC");
        // else if (cbin == 1 || cbin == 2) tx0_cent = new TPaveText(0.40, 0.76, 0.66, 0.88, "NDC");
        // else if (cbin == 3) tx0_cent = new TPaveText(0.27, 0.76, 0.53, 0.89, "NDC");
        // else if (cbin == 4) tx0_cent = new TPaveText(0.48, 0.79, 0.74, 0.92, "NDC");
        // else if (cbin == 5 || cbin == 6) tx0_cent = new TPaveText(0.40, 0.79, 0.66, 0.92, "NDC");
        // else if (cbin == 7) tx0_cent = new TPaveText(0.30, 0.82, 0.55, 0.95, "NDC");
        // else if (cbin == 8) tx0_cent = new TPaveText(0.48, 0.81, 0.74, 0.94, "NDC");
        // else if (cbin == 9 || cbin == 10) tx0_cent = new TPaveText(0.30, 0.83, 0.76, 0.92, "NDC");
        // alternative placement
        if (cbin == 0) tx0_cent = new TPaveText(0.47, 0.05, 0.74, 0.18, "NDC");
        else if (cbin == 1 || cbin == 2) tx0_cent = new TPaveText(0.37, 0.05, 0.63, 0.18, "NDC");
        else if (cbin == 3) tx0_cent = new TPaveText(0.27, 0.05, 0.53, 0.18, "NDC");
        else if (cbin == 4) tx0_cent = new TPaveText(0.47, 0.07, 0.74, 0.19, "NDC");
        else if (cbin == 5 || cbin == 6) tx0_cent = new TPaveText(0.37, 0.07, 0.63, 0.19, "NDC");
        else if (cbin == 7) tx0_cent = new TPaveText(0.27, 0.23, 0.53, 0.36, "NDC");
        else if (cbin == 8) tx0_cent = new TPaveText(0.47, 0.23, 0.74, 0.34, "NDC");
        else if (cbin == 9 || cbin == 10) tx0_cent = new TPaveText(0.37, 0.23, 0.63, 0.34, "NDC");
        else tx0_cent = new TPaveText(0.0, 0.0, 0.01, 0.01, "NDC");
        SetTPaveTxt2(tx0_cent, 20);
        tx0_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        tx0_cent->Draw();
    }

    c0->Print("../figures/fig_v1even_SP_eta.pdf","pdf");

}
