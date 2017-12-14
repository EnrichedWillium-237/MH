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

TH1D * N1SUB2_Loose_eta[ncbins];
TH1D * N1SUB3_Loose_eta[ncbins];
TH1D * N1MC22SUB2_Loose_eta[ncbins];

TH1D * N1SUB2_Tight_eta[ncbins];
TH1D * N1ASUB3_Tight_eta[ncbins];
TH1D * N1BSUB3_Tight_eta[ncbins];
TH1D * N1SUB3_Tight_eta[ncbins];
TH1D * N1MC22SUB2_Tight_eta[ncbins];

TH1D * N1SUB2_TightB_eta[ncbins];
TH1D * N1SUB3_TightB_eta[ncbins];
TH1D * N1MC22SUB2_TightB_eta[ncbins];

TH1D * N1MC22SUB2_Loose_pt[ncbins];
TH1D * N1MC22SUB2_Tight_pt[ncbins];
TH1D * N1MC22SUB2_TightB_pt[ncbins];

TFile * tfin;
TFile * tfout;

void cutStudy()
{

    TH1::SetDefaultSumw2();

    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_Loose_eta[cbin] = new TH1D(Form("N1SUB2_Loose_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_Loose_eta[cbin] = new TH1D(Form("N1SUB3_Loose_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB2_Loose_eta[cbin] = new TH1D(Form("N1MC22SUB2_Loose_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_Tight_eta[cbin] = new TH1D(Form("N1SUB2_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1ASUB3_Tight_eta[cbin] = new TH1D(Form("N1ASUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1BSUB3_Tight_eta[cbin] = new TH1D(Form("N1BSUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB2_Tight_eta[cbin] = new TH1D(Form("N1MC22SUB2_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_TightB_eta[cbin] = new TH1D(Form("N1SUB2_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_TightB_eta[cbin] = new TH1D(Form("N1SUB3_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB2_TightB_eta[cbin] = new TH1D(Form("N1MC22SUB2_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
    }

    string prevname = "";
    for (int ebin = 0; ebin<netabins; ebin++) {
        string prevname = Form("figures/figures_useLoose_%1.1f_%1.1f/N1SUB2/data/integral.dat",etabins[ebin],etabins[ebin+1]);
        if (prevname.length()>1) {
            int centmin[40];
            int centmax[40];
            double y[40];
            double stat[40];
            FILE * fin = fopen(prevname.data(),"r");
            cout<<fin<<endl;
            char buf[80];
            int cbin = 0;
            while (fgets(buf,80,fin)!=NULL) {
                sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                N1SUB2_Loose_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB2_Loose_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
    }
    //
    //
    //     }
    //
    //     tfin = new TFile(Form("results/results_useTight_-2.4_2.4/%s.root",AnalNames[anal].data()));
    //     for (int cbin = 0; cbin<ncbins; cbin++) {
    //         vnA_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[cbin],cmax[cbin]));
    //         vnB_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[cbin],cmax[cbin]));
    //         vnAB_pt[anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
    //     }
    //
    //
    // //-- average N1SUB2 and N1SUB3
    // for (int cbin = 0; cbin<ncbins; cbin++) {
    //     N1SUB2_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB2][cbin]->Clone(Form("N1SUB2_eta_%d_%d",cmin[cbin],cmax[cbin]));
    //     N1SUB2_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB2][cbin]->Clone(Form("N1SUB2_pt_%d_%d",cmin[cbin],cmax[cbin]));
    //
    //     N1SUB3_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB3][cbin]->Clone(Form("N1SUB3_eta_%d_%d",cmin[cbin],cmax[cbin]));
    //     N1SUB3_eta[cbin]->Add(vnAB_eta[N1BSUB3][cbin]);
    //     N1SUB3_eta[cbin]->Scale(0.5);
    //     N1SUB3_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB3][cbin]->Clone(Form("N1SUB3_pt_%d_%d",cmin[cbin],cmax[cbin]));
    //     N1SUB3_pt[cbin]->Add(vnAB_pt[N1BSUB3][cbin]);
    //     N1SUB3_pt[cbin]->Scale(0.5);
    //
    //     N1MC22SUB3_eta[cbin] = (TH1D *) vnAB_eta[N1MCp22SUB3][cbin]->Clone(Form("N1MC22SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]));
    //     N1MC22SUB3_pt[cbin] = (TH1D *) vnAB_pt[N1MCp22SUB3][cbin]->Clone(Form("N1MC22SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]));
    // }


}
