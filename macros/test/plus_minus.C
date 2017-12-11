# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

# include "style.h"

using namespace std;

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
static const int nanals = 10;
enum AnalType {
    N1MCm22SUB3, N1MCp22SUB3, N112ASUB2, N112ASUB3, N123ASUB2, N123ASUB3, N1SUB2, N1SUB3, N2SUB2, N2SUB3};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCp22SUB3", "N112ASUB2", "N112ASUB3", "N123ASUB2", "N123ASUB3", "N1SUB2", "N1SUB3", "N2SUB2", "N2SUB3"};
string ytitle[] = {
        "v_{1}\{#Psi_{1,MC}\} (-2.4<#eta<-2.0)", "v_{1}\{#Psi_{1,MC}\} (2.0<#eta<2.4)",
        "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{1},#Psi_{2}\}",
        "v_{1}\{#Psi_{2},#Psi_{3}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",
        "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",
        "v_{2}\{#Psi_{2}\}",                     "v_{2}\{#Psi_{2}\}"
};
int niov = 6;
string iov[] = {
    "PbPb_262548_262799", "PbPb_262800_263230", "PbPb_263231_263359",
    "PbPb_263360_263379", "PbPb_263615_263757", "PbPb_263380_263614"
}

using namespace std;

//  analysis type, centbin
TH1D * vnA[niov][ncbins];
TH1D * vnB[niov][ncbins];
TH1D * vnAB[niov][ncbins];

TFile * tfin;

void plus_minus()
{

    TH1::SetDefaultSumw2();

    if (!fopen("figures/plus_minus_test")) system("mkdir figures/plus_minus_test");
    for (int i = 0; i<niov; i++) {
        if (!fopen(Form("figures/plus_minus_test/%s",iov[i].data())) system(Form("mkdir figures/plus_minus_test/%s",iov[i].data()));
        for (int cbin = 0; cbin<ncentbins; cbin++) {

        }
    }


}
