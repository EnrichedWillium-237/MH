# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGaxis.h"
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

double ErrDiffCalc( double x, double y, double delx, double dely ) {
    double f = x;
    f-=y;
    double delf = sqrt( fabs(delx*delx - dely*dely) );
    return delf;
}

TFile * fin;
TH1D * h0;
TGraphErrors * gN1HFm1gSUB3[ncbins];
TGraphErrors * gN1HFp1gSUB3[ncbins];
TGraphErrors * gN1HF1gSUB3[ncbins];

void plotv1HFEven() {

    fin = new TFile("data_figHF23SUB.root");

    int col[] = {kRed, kOrange+5, kBlue, kGreen+2, kCyan+2, kMagenta, kBlack, kRed, kBlue, kGreen+2, kCyan+2};
    int mrkstyle[] =   {20,  25,  21,  28,  33,  27,  24,  34, 27,  20,  31};
    double mrksize[] = {1.3, 1.2, 1.2, 1.6, 1.8, 1.8, 1.2, 1.6, 1.8, 1.2, 1.4};

    for (int i = 0; i<ncbins; i++) {
        gN1HFm1gSUB3[i] = (TGraphErrors *) fin->Get(Form("default/N1HFm1gSUB3/-2.0_2.0/%d_%d/gintA",cmin[i],cmax[i]));
        gN1HFp1gSUB3[i] = (TGraphErrors *) fin->Get(Form("default/N1HFp1gSUB3/-2.0_2.0/%d_%d/gintA",cmin[i],cmax[i]));

        gN1HFm1gSUB3[i]->SetMarkerStyle(mrkstyle[i]);
        gN1HFm1gSUB3[i]->SetMarkerSize(mrksize[i]);
        gN1HFm1gSUB3[i]->SetMarkerColor(col[i]);
        gN1HFm1gSUB3[i]->SetLineColor(col[i]);
        gN1HFm1gSUB3[i]->RemovePoint(0);
        gN1HFm1gSUB3[i]->RemovePoint(gN1HFm1gSUB3[i]->GetN()-1);

        gN1HFp1gSUB3[i]->SetMarkerStyle(mrkstyle[i]);
        gN1HFp1gSUB3[i]->SetMarkerSize(mrksize[i]);
        gN1HFp1gSUB3[i]->SetMarkerColor(col[i]);
        gN1HFp1gSUB3[i]->SetLineColor(col[i]);
        gN1HFp1gSUB3[i]->RemovePoint(0);
        gN1HFp1gSUB3[i]->RemovePoint(gN1HFp1gSUB3[i]->GetN()-1);

        //-- average side to get v1even

        int num = gN1HFm1gSUB3[i]->GetN();
        double xA[30],  yA[30],  yAerr[30];
        double xB[30],  yB[30],  yBerr[30];
        double xAB[30], yAB[30], yABerr[30];
        for (int j = 0; j<num; j++) {
            gN1HFp1gSUB3[i]->GetPoint(j, xA[j], yA[j]);
            yAerr[j] = gN1HFp1gSUB3[i]->GetErrorY(j);
            gN1HFm1gSUB3[i]->GetPoint(j, xB[j], yB[j]);
            yBerr[j] = gN1HFm1gSUB3[i]->GetErrorY(j);

            yAB[j] = 0.5*(yA[j] + yB[j]);
            yABerr[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
        }
        gN1HF1gSUB3[i] = new TGraphErrors(num, xA, yAB, 0, yABerr);
        gN1HF1gSUB3[i]->SetMarkerStyle(mrkstyle[i]);
        gN1HF1gSUB3[i]->SetMarkerSize(mrksize[i]);
        gN1HF1gSUB3[i]->SetMarkerColor(col[i]);
        gN1HF1gSUB3[i]->SetLineColor(col[i]);
    }


    TCanvas * c0 = new TCanvas("c0", "c0", 620, 600);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetTopMargin(0.08);
    pad0->SetLeftMargin(0.18);
    h0 = new TH1D("hA", "", 100, -2.5, 2.5);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}");
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(509);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleOffset(1.15);
    h0->GetYaxis()->SetTitleOffset(1.65);
    h0->GetYaxis()->SetRangeUser(-0.12, 0.0);
    h0->Draw();
    for (int i = 0; i<ncbins; i++) {
        gN1HF1gSUB3[i]->Draw("same p");
    }

    TPaveText * tx00 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx00, 20);
    tx00->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    // tx00->Draw();

    TLegend * leg00 = new TLegend(0.27, 0.19, 0.45, 0.39);
    SetLegend(leg00, 20);
    for (int i = 0; i<=3; i++) {
        leg00->AddEntry(gN1HF1gSUB3[i],Form("%d - %d%%",cmin[i],cmax[i]),"p");
    }
    leg00->Draw();

    TLegend * leg01 = new TLegend(0.48, 0.19, 0.66, 0.39);
    SetLegend(leg01, 20);
    for (int i = 4; i<=7; i++) {
        leg01->AddEntry(gN1HF1gSUB3[i],Form("%d - %d%%",cmin[i],cmax[i]),"p");
    }
    leg01->Draw();

    TLegend * leg02 = new TLegend(0.69, 0.23, 0.87, 0.39);
    SetLegend(leg02, 20);
    for (int i = 8; i<11; i++) {
        leg02->AddEntry(gN1HF1gSUB3[i],Form("%d - %d%%",cmin[i],cmax[i]),"p");
    }
    leg02->Draw();

    c0->Print("fig_v1HFEven.pdf","pdf");
    c0->Print("fig_v1HFEven.png","png");

}
