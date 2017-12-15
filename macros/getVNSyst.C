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
static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 30,  50};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 30, 50, 100};
static const int nanals = 14;
enum AnalType {
    N1ASUB2,     N1ASUB3,     N1BSUB2,   N1BSUB3,   N112ASUB2,   N112ASUB3,   N123ASUB2, N123ASUB3,
    N1MCm22SUB3, N1MCp22SUB3, N2SUB2,    N2SUB3,    N3SUB2,      N3SUB3,      LAST
};
string AnalNames[] = {
    "N1ASUB2",     "N1ASUB3",     "N1BSUB2",   "N1BSUB3",   "N112ASUB2",   "N112ASUB3",   "N123ASUB2", "N123ASUB3",
    "N1MCm22SUB3", "N1MCp22SUB3", "N2SUB2",    "N2SUB3",    "N3SUB2",      "N3SUB3",      "LAST"
};

static const bool gridlines = false;

TH1D * N1SUB2_Sym_eta[ncbins];
TH1D * N1SUB3_Sym_eta[ncbins];
TH1D * N1MC22SUB3_Sym_pt[ncbins];

TH1D * systN1SUB2_eta;
TH1D * systN1SUB3_eta;
TH1D * systN1MC22SUB3_pt;

TH1D * systN1SUB2_Loose_Tight_eta;
TH1D * systN1SUB3_Loose_Tight_eta;
TH1D * systN1MC22SUB3_Loose_Tight_pt;
TH1D * systN1SUB2_TightB_Tight_eta;
TH1D * systN1SUB3_TightB_Tight_eta;
TH1D * systN1MC22SUB3_TightB_Tight_pt;

TFile * tfinSym;
TFile * tfincut;

void getVNSyst()
{

    TH1::SetDefaultSumw2();

    tfinSym = new TFile("figures/integralVN/data/symmetrizedVN.root","read");
    tfincut = new TFile("figures/integralVN/data/trkcuts.root","read");

    for (int cbin = 0; cbin<ncbins; cbin++) {
        string ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
        N1SUB2_Sym_eta[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1SUB2_Sym_eta_%s",ctag.data(),ctag.data()));
        N1SUB3_Sym_eta[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1SUB3_Sym_eta_%s",ctag.data(),ctag.data()));
        N1MC22SUB3_Sym_pt[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1MC22SUB3_Sym_pt_%s",ctag.data(),ctag.data()));
    }
    systN1SUB2_eta = (TH1D *) tfinSym->Get("systN1SUB2_eta");
    systN1SUB3_eta = (TH1D *) tfinSym->Get("systN1SUB3_eta");
    systN1MC22SUB3_pt = (TH1D *) tfinSym->Get("systN1MC22SUB3_pt");

    systN1SUB2_Loose_Tight_eta = (TH1D *) tfincut->Get("systN1SUB2_Loose_Tight_eta");
    systN1SUB3_Loose_Tight_eta = (TH1D *) tfincut->Get("systN1SUB3_Loose_Tight_eta");
    systN1MC22SUB3_Loose_Tight_pt = (TH1D *) tfincut->Get("systN1MC22SUB3_Loose_Tight_pt");
    systN1SUB2_TightB_Tight_eta = (TH1D *) tfincut->Get("systN1SUB2_TightB_Tight_eta");
    systN1SUB3_TightB_Tight_eta = (TH1D *) tfincut->Get("systN1SUB3_TightB_Tight_eta");
    systN1MC22SUB3_TightB_Tight_pt = (TH1D *) tfincut->Get("systN1MC22SUB3_TightB_Tight_pt");


}
