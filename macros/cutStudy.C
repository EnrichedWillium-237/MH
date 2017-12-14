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

// ratio plots

TH1D * ratN1SUB2_Loose_Tight_eta[ncbins];
TH1D * ratN1SUB3_Loose_Tight_eta[ncbins];
TH1D * ratN1MC22SUB3_Loose_Tight_eta[ncbins];
TH1D * ratN1MC22SUB3_Loose_Tight_pt[ncbins];

TH1D * ratN1SUB2_TightB_Tight_eta[ncbins];
TH1D * ratN1SUB3_TightB_Tight_eta[ncbins];
TH1D * ratN1MC22SUB3_TightB_Tight_eta[ncbins];
TH1D * ratN1MC22SUB3_TightB_Tight_pt[ncbins];

TF1 * fitN1SUB2_Loose_Tight_eta[ncbins];
TF1 * fitN1SUB3_Loose_Tight_eta[ncbins];
TF1 * fitN1MC22SUB3_Loose_Tight_eta[ncbins];
TF1 * fitN1MC22SUB3_Loose_Tight_pt[ncbins];

TF1 * fitN1SUB2_TightB_Tight_eta[ncbins];
TF1 * fitN1SUB3_TightB_Tight_eta[ncbins];
TF1 * fitN1MC22SUB3_TightB_Tight_eta[ncbins];
TF1 * fitN1MC22SUB3_TightB_Tight_pt[ncbins];


TFile * tfinLoose;
TFile * tfinTight;
TFile * tfinTightNA;
TFile * tfinTightNB;
TFile * tfinTightB;
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
        prevname = Form("figures/figures_useLoose_%1.1f_%1.1f/N1SUB2/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1SUB2_Loose_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB2_Loose_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useLoose_%1.1f_%1.1f/N1SUB3/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1SUB3_Loose_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB3_Loose_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useTightB_%1.1f_%1.1f/N1SUB2/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1SUB2_TightB_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB2_TightB_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useTightB_%1.1f_%1.1f/N1SUB3/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1SUB3_TightB_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB3_TightB_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useTight_%1.1f_%1.1f/N1ASUB2/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1SUB2_Tight_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1SUB2_Tight_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useTight_%1.1f_%1.1f/N1ASUB3/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1ASUB3_Tight_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1ASUB3_Tight_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
        prevname = Form("figures/figures_useTight_%1.1f_%1.1f/N1BSUB3/data/integral.dat",etabins[ebin],etabins[ebin+1]);
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
                N1BSUB3_Tight_eta[cbin]->SetBinContent(ebin+1,y[cbin]);
                N1BSUB3_Tight_eta[cbin]->SetBinError(ebin+1,stat[cbin]);
                ++cbin;
            }
            fclose(fin);
        }
    }

    tfinLoose = new TFile("results/results_useLoose_-2.4_2.4/N1MCp22SUB3.root");
    tfinTight = new TFile("results/results_useTight_-2.4_2.4/N1MCp22SUB3.root");
    tfinTightB = new TFile("results/results_useTightB_-2.4_2.4/N1MCp22SUB3.root");
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1MC22SUB2_Loose_pt[cbin] = (TH1D *) tfinLoose->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        N1MC22SUB2_Tight_pt[cbin] = (TH1D *) tfinTight->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        N1MC22SUB2_TightB_pt[cbin] = (TH1D *) tfinTightB->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
    }

    //-- average N1SUB2 and N1SUB3
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB3_Tight_eta[cbin] = (TH1D *) N1ASUB3_Tight_eta[cbin]->Clone(Form("N1SUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_Tight_eta[cbin]->Add(N1BSUB3_Tight_eta[cbin]);
        N1SUB3_Tight_eta[cbin]->Scale(0.5);
    }


    //-- calculate ratios
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        ratN1SUB2_Loose_Tight_eta[cbin] = (TH1D *) N1SUB2_Loose_eta[cbin]->Clone(Form("ratN1SUB2_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1SUB2_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB2_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1SUB2_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB2_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB2_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight))
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1SUB2_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }

        ratN1SUB3_Loose_Tight_eta[cbin] = (TH1D *) N1SUB3_Loose_eta[cbin]->Clone(Form("ratN1SUB3_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1SUB3_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1SUB3_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB3_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight))
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1SUB3_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }

        ratN1MC22SUB3_Loose_Tight_eta[cbin] = (TH1D *) N1MC22SUB3_Loose_eta[cbin]->Clone(Form("ratN1MC22SUB3_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1MC22SUB3_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1MC22SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1MC22SUB3_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1MC22SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight))
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }

        ratN1MC22SUB3_Loose_Tight_pt[cbin] = (TH1D *) N1MC22SUB3_Loose_pt[cbin]->Clone(Form("ratN1MC22SUB3_Loose_Tight_pt"));
        for (int pbin = 1; pbin<=nptbins; pbin++) {
            double vnLoose = N1MC22SUB3_Loose_pt[cbin]->GetBinContent(pbin);
            double vnTight = N1MC22SUB3_Tight_pt[cbin]->GetBinContent(pbin);
            double vnLooseErr = N1MC22SUB3_Loose_pt[cbin]->GetBinError(pbin);
            double vnTightErr = N1MC22SUB3_Tight_pt[cbin]->GetBinError(pbin);
            ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight))
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetBinError(ebin, ratErr);
        }

        ratN1SUB2_TightB_Tight_eta[cbin] = (TH1D *) N1SUB2_TightB_eta[cbin]->Clone(Form("ratN1SUB2_TightB_Tight_eta"));
        ratN1SUB3_TightB_Tight_eta[cbin] = (TH1D *) N1SUB3_TightB_eta[cbin]->Clone(Form("ratN1SUB3_TightB_Tight_eta"));
        ratN1MC22SUB3_TightB_Tight_eta[cbin] = (TH1D *) N1MC22SUB3_TightB_eta[cbin]->Clone(Form("ratN1MC22SUB3_TightB_Tight_eta"));
        ratN1MC22SUB3_TightB_Tight_pt[cbin] = (TH1D *) N1MC22SUB3_TightB_pt[cbin]->Clone(Form("ratN1MC22SUB3_TightB_Tight_pt"));
    }





}
