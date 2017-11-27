# include "TCanvas.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,
                     0.4,  0.8,  1.2,  1.6, 2.0,  2.4};
static const int ncentbins = 11;
static const int centBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const double centRefBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const int ncbins = 14;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 30,  50};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 30, 50, 100};
string FigDir = "";
string FigSubDir = "";
static const int nanals = 22;
enum AnalType {
    N1MCm22SUB3, N1MCm18SUB3, N1MCm14SUB3, N1MCm10SUB3, N1MCm06SUB3, N1MCm02SUB3,
    N1MCp22SUB3, N1MCp18SUB3, N1MCp14SUB3, N1MCp10SUB3, N1MCp06SUB3, N1MCp02SUB3,
    N112ASUB2,   N112ASUB3,   N123ASUB2,   N123ASUB3,   N1SUB2,      N1SUB3,
    N2SUB2,      N2SUB3,      N3SUB2,      N3SUB3,      LAST};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCm18SUB3", "N1MCm14SUB3", "N1MCm10SUB3", "N1MCm06SUB3", "N1MCm02SUB3",
    "N1MCp22SUB3", "N1MCp18SUB3", "N1MCp14SUB3", "N1MCp10SUB3", "N1MCp06SUB3", "N1MCp02SUB3",
    "N112ASUB2",   "N112ASUB3",   "N123ASUB2",   "N123ASUB3",   "N1SUB2",      "N1SUB3",
    "N2SUB2",      "N2SUB3",      "N3SUB2",      "N3SUB3",      "LAST"};


void GraphToHist( TGraphErrors * gin, TH1D * hout ) {
    int num = gin->GetN();
    Double_t x[100], y[100], yerr[100];
    for (int i = 0; i<num; i++) {
        gin->GetPoint(i, x[i], y[i]);
        yerr[i] = gin->GetErrorY(i);
        hout->SetBinContent(i+1, y[i]);
        hout->SetBinError(i+1, yerr[i]);
    }
}

TFile * tfin;
string infile = "";
string ctag = "";
bool isLoose = false;
bool isTight = false;
TH1D * centbins;

//  track cut, analysis type, centbin, etabin
TH1D * vnA[2][nanals][ncbins][netabins];
TH1D * vnB[2][nanals][ncbins][netabins];
TH1D * vnAB[2][nanals][ncbins][netabins];

void v1pT()
{

    TH1::SetDefaultSumw2();

    isTight = true;
    for (int ebin = 0; ebin<netabins; ebin++) {
        infile = "../macros/results/results_";
        if (isTight) infile+="useTight_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
            for (int cbin = 0; cbin<ncbins; cbin++) {
                ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                vnA[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                vnB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                vnAB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));
            }
            //tfin->Close();
        }
    }

}
