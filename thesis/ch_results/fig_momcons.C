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
TH1D * h0;
TGraphErrors * gN1HFgSUB3[ncbins];
TGraphErrors * gN1EVENSUB3[ncbins];
TGraphErrors * gN1HFgSUB3_decor[ncbins];
TGraphErrors * gN1EVENSUB3_decor[ncbins];
TGraphErrors * gDiff[ncbins];
TGraphErrors * gDiff_decor[ncbins];

TGraphErrors * gintN1HFgSUB3[ncbins];
TGraphErrors * gintN1EVENSUB3[ncbins];
TGraphErrors * gintN1HFgSUB3_decor[ncbins];
TGraphErrors * gintN1EVENSUB3_decor[ncbins];
TGraphErrors * gintDiff[ncbins];
TGraphErrors * gintDiff_decor[ncbins];

void fig_momcons() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        gN1HFgSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3/1.2_1.6/%d_%d/g",cmin[cbin],cmax[cbin]));
        gN1EVENSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3/1.2_1.6/%d_%d/gA",cmin[cbin],cmax[cbin]));
        gN1HFgSUB3_decor[cbin] = (TGraphErrors *) fin->Get(Form("default/N1HFgSUB3_decor/1.2_1.6/%d_%d/g",cmin[cbin],cmax[cbin]));
        gN1EVENSUB3_decor[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3_decor/1.2_1.6/%d_%d/gA",cmin[cbin],cmax[cbin]));

        int numg = gN1HFgSUB3[cbin]->GetN();
        double x[50], y1[50], y2[50], y1err[50], y2err[50];
        for (int j = 0; j<numg; j++) {
            gN1HFgSUB3[cbin]->GetPoint(j, x[j], y1[j]);
            y1err[j] = gN1HFgSUB3[cbin]->GetErrorY(j);
            gN1EVENSUB3[cbin]->GetPoint(j, x[j], y2[j]);
            y2err[cbin] = gN1EVENSUB3[cbin]->GetErrorY(j);
            y1[j]-=y2[j];
            y1err[j] = y1[j]*sqrt( pow(y1err[j]/y1[j],2) + pow(y2err[j]/y2[j],2) );
        }
        gDiff[cbin] = new TGraphErrors(numg, x, y1, 0, y1err);
        for (int j = 0; j<numg; j++) {
            gN1HFgSUB3_decor[cbin]->GetPoint(j, x[j], y1[j]);
            y1err[j] = gN1HFgSUB3_decor[cbin]->GetErrorY(j);
            gN1EVENSUB3_decor[cbin]->GetPoint(j, x[j], y2[j]);
            y2err[cbin] = gN1EVENSUB3_decor[cbin]->GetErrorY(j);
            y1[j]-=y2[j];
            y1err[j] = y1[j]*sqrt( pow(y1err[j]/y1[j],2) + pow(y2err[j]/y2[j],2) );
        }
        gDiff_decor[cbin] = new TGraphErrors(numg, x, y1, 0, y1err);

        // int numgint = gintN1HFgSUB3[cbin]->GetN();

    }

    // gN1HFgSUB3[10]->Draw("alp");
    // gN1HFgSUB3_decor[10]->Draw("same lp");
    // gN1EVENSUB3_decor[4]->Draw("same lp");
    gDiff_decor[4]->Draw("same alp");
    gDiff[4]->Draw("same lp");

}
