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

using namespace std;

//  track cut, analysis type, centbin, etabin
TH1D * vnA[2][nanals][ncbins];
TH1D * vnB[2][nanals][ncbins];
TH1D * vnAB[2][nanals][ncbins];

void getVNInt()
{

    bool processAll = false; // make true if you want to process the full data set

    for (int i = 0; i<2; i++) {
        for (int anal = 0; anal<nanals; anal++) {
            for (int cbin = 0; cbin<ncbins-1; cbin++) {
                string tcut = "";
                if (i == 0) tcut = "useTight";
                else tcut = "useLoose";
                string htag = Form("_%s_%s_%d_%d",AnalNames[anal].data(),tcut.data(),cmin[cbin],cmax[cbin]);
                vnA[i][anal][cbin] = new TH1D(Form("vnA_%s",htag.data()), "", netabins, etabins);
                vnB[i][anal][cbin] = new TH1D(Form("vnB_%s",htag.data()), "", netabins, etabins);
                vnAB[i][anal][cbin] = new TH1D(Form("vnAB_%s",htag.data()), "", netabins, etabins);
            }
        }
    }

    string prevname = "";

    for (int i = 0; i<2; i++) {
        for (int anal = 0; anal<nanals; anal++) {
            if (!processAll) {
                if (anal == 16 || anal == 17 || anal == 18 || anal == 19) {
                    string tcut = "";
                    if (i == 0) tcut = "useTight";
                    else tcut = "useLoose";
                    for (int ebin = 0; ebin<netabins; ebin++) {
                        prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/pT_integral.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
                        if (prevname.length()>1) {
                            int centmin[40];
                            int centmax[40];
                            double y[40];
                            double stat[40];
                            FILE * fin = fopen(prevname.data(),"r");
                            char buf[80];
                            int cbin = 0;
                            while (fgets(buf,80,fin)!=NULL) {
                                sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                                // cout<<centmin[cbin]<<"\t"<<centmax[cbin]<<"\t"<<y[cbin]<<"\t"<<syst[cbin]<<endl;
                                vnAB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                                vnAB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                                ++cbin;
                            }

                        }
                    }
                }
            }
        }
    }

    int test = 18;
    TCanvas * ctest = new TCanvas("ctest","ctest",650,600);
    TPad * padtest = (TPad *) ctest->cd();
    padtest->SetGrid();
    vnAB[0][test][0]->SetMarkerColor(kRed);
    vnAB[0][test][0]->SetXTitle("eta");
    vnAB[0][test][0]->SetYTitle("v_{n}");
    vnAB[0][test][0]->GetYaxis()->SetRangeUser(-0.05, 0.1);
    vnAB[0][test][0]->Draw();
    TLine * ltest = new TLine(-2.4, 0, 2.4, 0);
    ltest->Draw();


}
