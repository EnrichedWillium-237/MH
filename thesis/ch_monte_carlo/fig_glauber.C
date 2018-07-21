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
