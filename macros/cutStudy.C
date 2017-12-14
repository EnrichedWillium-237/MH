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
static const int centBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
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
TH1D * N1MC22SUB3_Loose_eta[ncbins];

TH1D * N1SUB2_Tight_eta[ncbins];
TH1D * N1ASUB3_Tight_eta[ncbins];
TH1D * N1BSUB3_Tight_eta[ncbins];
TH1D * N1SUB3_Tight_eta[ncbins];
TH1D * N1MC22SUB3_Tight_eta[ncbins];

TH1D * N1SUB2_TightB_eta[ncbins];
TH1D * N1SUB3_TightB_eta[ncbins];
TH1D * N1MC22SUB3_TightB_eta[ncbins];

TH1D * N1MC22SUB3_Loose_pt[ncbins];
TH1D * N1MC22SUB3_Tight_pt[ncbins];
TH1D * N1MC22SUB3_TightB_pt[ncbins];

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

// store pol0 fit parameters
TH1D * systN1SUB2_Loose_Tight_eta;
TH1D * systN1SUB3_Loose_Tight_eta;
TH1D * systN1MC22SUB3_Loose_Tight_eta;
TH1D * systN1MC22SUB3_Loose_Tight_pt;

TH1D * systN1SUB2_TightB_Tight_eta;
TH1D * systN1SUB3_TightB_Tight_eta;
TH1D * systN1MC22SUB3_TightB_Tight_eta;
TH1D * systN1MC22SUB3_TightB_Tight_pt;


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
        N1MC22SUB3_Loose_eta[cbin] = new TH1D(Form("N1MC22SUB3_Loose_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_Tight_eta[cbin] = new TH1D(Form("N1SUB2_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1ASUB3_Tight_eta[cbin] = new TH1D(Form("N1ASUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1BSUB3_Tight_eta[cbin] = new TH1D(Form("N1BSUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_Tight_eta[cbin] = new TH1D(Form("N1MC22SUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_TightB_eta[cbin] = new TH1D(Form("N1SUB2_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_TightB_eta[cbin] = new TH1D(Form("N1SUB3_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_TightB_eta[cbin] = new TH1D(Form("N1MC22SUB3_TightB_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
    }
    systN1SUB2_Loose_Tight_eta = new TH1D("systN1SUB2_Loose_Tight_eta", "", ncbins, 0, ncbins);
        systN1SUB3_Loose_Tight_eta = new TH1D("systN1SUB3_Loose_Tight_eta", "", ncbins, 0, ncbins);
    systN1MC22SUB3_Loose_Tight_eta = new TH1D("systN1MC22SUB3_Loose_Tight_eta", "", ncbins, 0, ncbins);
    systN1MC22SUB3_Loose_Tight_pt = new TH1D("systN1MC22SUB3_Loose_Tight_pt", "", ncbins, 0, ncbins);

    systN1SUB2_TightB_Tight_eta = new TH1D("systN1SUB2_TightB_Tight_eta", "", ncbins, 0, ncbins);
    systN1SUB3_TightB_Tight_eta = new TH1D("systN1SUB3_TightB_Tight_eta", "", ncbins, 0, ncbins);
    systN1MC22SUB3_TightB_Tight_eta = new TH1D("systN1MC22SUB3_TightB_Tight_eta", "", ncbins, 0, ncbins);
    systN1MC22SUB3_TightB_Tight_pt = new TH1D("systN1MC22SUB3_TightB_Tight_pt", "", ncbins, 0, ncbins);

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
        N1MC22SUB3_Loose_pt[cbin] = (TH1D *) tfinLoose->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        N1MC22SUB3_Tight_pt[cbin] = (TH1D *) tfinTight->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        N1MC22SUB3_TightB_pt[cbin] = (TH1D *) tfinTightB->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
    }

    //-- average N1SUB2 and N1SUB3
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB3_Tight_eta[cbin] = (TH1D *) N1ASUB3_Tight_eta[cbin]->Clone(Form("N1SUB3_Tight_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_Tight_eta[cbin]->Add(N1BSUB3_Tight_eta[cbin]);
        N1SUB3_Tight_eta[cbin]->Scale(0.5);
    }


    //-- calculate ratios
    for (int cbin = 0; cbin<ncbins; cbin++) {
        ratN1SUB2_Loose_Tight_eta[cbin] = (TH1D *) N1SUB2_Loose_eta[cbin]->Clone(Form("ratN1SUB2_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1SUB2_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB2_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1SUB2_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB2_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB2_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight));
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1SUB2_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1SUB2_Loose_Tight_eta[cbin] = new TF1(Form("fitN1SUB2_Loose_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1SUB2_Loose_Tight_eta[cbin]->Fit(fitN1SUB2_Loose_Tight_eta[cbin],"QR");
        systN1SUB2_Loose_Tight_eta->SetBinContent(cbin+1, fitN1SUB2_Loose_Tight_eta[0]->GetParameter(0));
        systN1SUB2_Loose_Tight_eta->SetBinError(cbin+1, fitN1SUB2_Loose_Tight_eta[0]->GetChisquare());

        ratN1SUB3_Loose_Tight_eta[cbin] = (TH1D *) N1SUB3_Loose_eta[cbin]->Clone(Form("ratN1SUB3_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1SUB3_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1SUB3_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB3_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight));
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1SUB3_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1SUB3_Loose_Tight_eta[cbin] = new TF1(Form("fitN1SUB3_Loose_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1SUB3_Loose_Tight_eta[cbin]->Fit(fitN1SUB3_Loose_Tight_eta[cbin],"QR");
        systN1SUB2_Loose_Tight_eta->SetBinContent(cbin+1, fitN1SUB3_Loose_Tight_eta[0]->GetParameter(0));
        systN1SUB3_Loose_Tight_eta->SetBinError(cbin+1, fitN1SUB3_Loose_Tight_eta[0]->GetChisquare());

        ratN1MC22SUB3_Loose_Tight_eta[cbin] = (TH1D *) N1MC22SUB3_Loose_eta[cbin]->Clone(Form("ratN1MC22SUB3_Loose_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnLoose = N1MC22SUB3_Loose_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1MC22SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnLooseErr = N1MC22SUB3_Loose_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1MC22SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetBinContent(ebin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight));
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1MC22SUB3_Loose_Tight_eta[cbin] = new TF1(Form("fitN1MC22SUB3_Loose_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1MC22SUB3_Loose_Tight_eta[cbin]->Fit(fitN1MC22SUB3_Loose_Tight_eta[cbin],"QR");
        systN1MC22SUB3_Loose_Tight_eta->SetBinContent(cbin+1, fitN1MC22SUB3_Loose_Tight_eta[0]->GetParameter(0));
        systN1MC22SUB3_Loose_Tight_eta->SetBinError(cbin+1, fitN1MC22SUB3_Loose_Tight_eta[0]->GetChisquare());

        ratN1MC22SUB3_Loose_Tight_pt[cbin] = (TH1D *) N1MC22SUB3_Loose_pt[cbin]->Clone(Form("ratN1MC22SUB3_Loose_Tight_pt"));
        for (int pbin = 1; pbin<=nptbins; pbin++) {
            double vnLoose = N1MC22SUB3_Loose_pt[cbin]->GetBinContent(pbin);
            double vnTight = N1MC22SUB3_Tight_pt[cbin]->GetBinContent(pbin);
            double vnLooseErr = N1MC22SUB3_Loose_pt[cbin]->GetBinError(pbin);
            double vnTightErr = N1MC22SUB3_Tight_pt[cbin]->GetBinError(pbin);
            ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetBinContent(pbin, vnLoose/vnTight);

            double ratErr = pow(vnLooseErr/vnLoose,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnLooseErr/vnLoose)*(vnTightErr/vnTight));
            ratErr = (vnLoose/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetBinError(pbin, ratErr);
        }
        fitN1MC22SUB3_Loose_Tight_pt[cbin] = new TF1(Form("fitN1MC22SUB3_Loose_Tight_pt_%d",cbin), "pol0", 0, 12);
        ratN1MC22SUB3_Loose_Tight_pt[cbin]->Fit(fitN1MC22SUB3_Loose_Tight_pt[cbin],"QR");
        systN1MC22SUB3_Loose_Tight_pt->SetBinContent(cbin+1, fitN1MC22SUB3_Loose_Tight_pt[0]->GetParameter(0));
        systN1MC22SUB3_Loose_Tight_pt->SetBinError(cbin+1, fitN1MC22SUB3_Loose_Tight_pt[0]->GetChisquare());

        ratN1SUB2_TightB_Tight_eta[cbin] = (TH1D *) N1SUB2_TightB_eta[cbin]->Clone(Form("ratN1SUB2_TightB_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnTightB = N1SUB2_TightB_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB2_Tight_eta[cbin]->GetBinContent(ebin);
            double vnTightBErr = N1SUB2_TightB_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB2_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB2_TightB_Tight_eta[cbin]->SetBinContent(ebin, vnTightB/vnTight);

            double ratErr = pow(vnTightBErr/vnTightB,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnTightBErr/vnTightB)*(vnTightErr/vnTight));
            ratErr = (vnTightB/vnTight)*sqrt( ratErr );
            ratN1SUB2_TightB_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1SUB2_TightB_Tight_eta[cbin] = new TF1(Form("fitN1SUB2_TightB_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1SUB2_TightB_Tight_eta[cbin]->Fit(fitN1SUB2_TightB_Tight_eta[cbin],"QR");
        systN1SUB2_Loose_Tight_eta->SetBinContent(cbin+1, fitN1SUB2_TightB_Tight_eta[cbin]->GetParameter(0));
        systN1SUB2_Loose_Tight_eta->SetBinError(cbin+1, fitN1SUB2_TightB_Tight_eta[cbin]->GetChisquare());

        ratN1SUB3_TightB_Tight_eta[cbin] = (TH1D *) N1SUB3_TightB_eta[cbin]->Clone(Form("ratN1SUB3_TightB_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnTightB = N1SUB3_TightB_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnTightBErr = N1SUB3_TightB_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1SUB3_TightB_Tight_eta[cbin]->SetBinContent(ebin, vnTightB/vnTight);

            double ratErr = pow(vnTightBErr/vnTightB,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnTightBErr/vnTightB)*(vnTightErr/vnTight));
            ratErr = (vnTightB/vnTight)*sqrt( ratErr );
            ratN1SUB3_TightB_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1SUB3_TightB_Tight_eta[cbin] = new TF1(Form("fitN1SUB3_TightB_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1SUB3_TightB_Tight_eta[cbin]->Fit(fitN1SUB3_TightB_Tight_eta[cbin],"QR");
        systN1SUB3_Loose_Tight_eta->SetBinContent(cbin+1, fitN1SUB3_TightB_Tight_eta[0]->GetParameter(0));
        systN1SUB3_Loose_Tight_eta->SetBinError(cbin+1, fitN1SUB3_TightB_Tight_eta[0]->GetChisquare());

        ratN1MC22SUB3_TightB_Tight_eta[cbin] = (TH1D *) N1MC22SUB3_TightB_eta[cbin]->Clone(Form("ratN1MC22SUB3_TightB_Tight_eta"));
        for (int ebin = 1; ebin<=netabins; ebin++) {
            double vnTightB = N1MC22SUB3_TightB_eta[cbin]->GetBinContent(ebin);
            double vnTight = N1MC22SUB3_Tight_eta[cbin]->GetBinContent(ebin);
            double vnTightBErr = N1MC22SUB3_TightB_eta[cbin]->GetBinError(ebin);
            double vnTightErr = N1MC22SUB3_Tight_eta[cbin]->GetBinError(ebin);
            ratN1MC22SUB3_TightB_Tight_eta[cbin]->SetBinContent(ebin, vnTightB/vnTight);

            double ratErr = pow(vnTightBErr/vnTightB,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnTightBErr/vnTightB)*(vnTightErr/vnTight));
            ratErr = (vnTightB/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_TightB_Tight_eta[cbin]->SetBinError(ebin, ratErr);
        }
        fitN1MC22SUB3_TightB_Tight_eta[cbin] = new TF1(Form("fitN1MC22SUB3_TightB_Tight_eta_%d",cbin), "pol0", -2.4, 2.4);
        ratN1MC22SUB3_TightB_Tight_eta[cbin]->Fit(fitN1MC22SUB3_TightB_Tight_eta[cbin],"QR");
        systN1MC22SUB3_Loose_Tight_eta->SetBinContent(cbin+1, fitN1MC22SUB3_TightB_Tight_eta[0]->GetParameter(0));
        systN1MC22SUB3_Loose_Tight_eta->SetBinError(cbin+1, fitN1MC22SUB3_TightB_Tight_eta[0]->GetChisquare());

        ratN1MC22SUB3_TightB_Tight_pt[cbin] = (TH1D *) N1MC22SUB3_TightB_pt[cbin]->Clone(Form("ratN1MC22SUB3_TightB_Tight_pt"));
        for (int pbin = 1; pbin<=nptbins; pbin++) {
            double vnTightB = N1MC22SUB3_TightB_pt[cbin]->GetBinContent(pbin);
            double vnTight = N1MC22SUB3_Tight_pt[cbin]->GetBinContent(pbin);
            double vnTightBErr = N1MC22SUB3_TightB_pt[cbin]->GetBinError(pbin);
            double vnTightErr = N1MC22SUB3_Tight_pt[cbin]->GetBinError(pbin);
            ratN1MC22SUB3_TightB_Tight_pt[cbin]->SetBinContent(pbin, vnTightB/vnTight);

            double ratErr = pow(vnTightBErr/vnTightB,2) + pow(vnTightErr/vnTight,2) - 2*fabs((vnTightBErr/vnTightB)*(vnTightErr/vnTight));
            ratErr = (vnTightB/vnTight)*sqrt( ratErr );
            ratN1MC22SUB3_TightB_Tight_pt[cbin]->SetBinError(pbin, ratErr);
        }
        fitN1MC22SUB3_TightB_Tight_pt[cbin] = new TF1(Form("fitN1MC22SUB3_TightB_Tight_pt_%d",cbin), "pol0", 0, 12);
        ratN1MC22SUB3_TightB_Tight_pt[cbin]->Fit(fitN1MC22SUB3_TightB_Tight_pt[cbin],"QR");
        systN1MC22SUB3_Loose_Tight_pt->SetBinContent(cbin+1, fitN1MC22SUB3_TightB_Tight_pt[0]->GetParameter(0));
        systN1MC22SUB3_Loose_Tight_pt->SetBinError(cbin+1, fitN1MC22SUB3_TightB_Tight_pt[0]->GetChisquare());
    }

    //-- fit ratios



    //-- plot options
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_Loose_eta[cbin]->SetMarkerColor(kMagenta);
        N1SUB2_Loose_eta[cbin]->SetLineColor(kMagenta);
        N1SUB2_Loose_eta[cbin]->SetMarkerStyle(28);
        N1SUB2_Loose_eta[cbin]->SetMarkerSize(1.4);

        N1SUB3_Loose_eta[cbin]->SetMarkerColor(kMagenta);
        N1SUB3_Loose_eta[cbin]->SetLineColor(kMagenta);
        N1SUB3_Loose_eta[cbin]->SetMarkerStyle(28);
        N1SUB3_Loose_eta[cbin]->SetMarkerSize(1.4);

        N1MC22SUB3_Loose_eta[cbin]->SetMarkerColor(kMagenta);
        N1MC22SUB3_Loose_eta[cbin]->SetLineColor(kMagenta);
        N1MC22SUB3_Loose_eta[cbin]->SetMarkerStyle(28);
        N1MC22SUB3_Loose_eta[cbin]->SetMarkerSize(1.4);

        N1SUB2_Tight_eta[cbin]->SetMarkerColor(kBlue);
        N1SUB2_Tight_eta[cbin]->SetLineColor(kBlue);
        N1SUB2_Tight_eta[cbin]->SetMarkerStyle(21);
        N1SUB2_Tight_eta[cbin]->SetMarkerSize(1.2);

        N1SUB3_Tight_eta[cbin]->SetMarkerColor(kBlue);
        N1SUB3_Tight_eta[cbin]->SetLineColor(kBlue);
        N1SUB3_Tight_eta[cbin]->SetMarkerStyle(21);
        N1SUB3_Tight_eta[cbin]->SetMarkerSize(1.2);

        N1MC22SUB3_Tight_eta[cbin]->SetMarkerColor(kBlue);
        N1MC22SUB3_Tight_eta[cbin]->SetLineColor(kBlue);
        N1MC22SUB3_Tight_eta[cbin]->SetMarkerStyle(21);
        N1MC22SUB3_Tight_eta[cbin]->SetMarkerSize(1.2);

        N1SUB2_TightB_eta[cbin]->SetMarkerColor(kRed);
        N1SUB2_TightB_eta[cbin]->SetLineColor(kRed);
        N1SUB2_TightB_eta[cbin]->SetMarkerStyle(24);
        N1SUB2_TightB_eta[cbin]->SetMarkerSize(1.2);

        N1SUB3_TightB_eta[cbin]->SetMarkerColor(kRed);
        N1SUB3_TightB_eta[cbin]->SetLineColor(kRed);
        N1SUB3_TightB_eta[cbin]->SetMarkerStyle(24);
        N1SUB3_TightB_eta[cbin]->SetMarkerSize(1.2);

        N1MC22SUB3_TightB_eta[cbin]->SetMarkerColor(kRed);
        N1MC22SUB3_TightB_eta[cbin]->SetLineColor(kRed);
        N1MC22SUB3_TightB_eta[cbin]->SetMarkerStyle(24);
        N1MC22SUB3_TightB_eta[cbin]->SetMarkerSize(1.2);

        N1MC22SUB3_Loose_pt[cbin]->SetMarkerColor(kMagenta);
        N1MC22SUB3_Loose_pt[cbin]->SetLineColor(kMagenta);
        N1MC22SUB3_Loose_pt[cbin]->SetMarkerStyle(28);
        N1MC22SUB3_Loose_pt[cbin]->SetMarkerSize(1.4);

        N1MC22SUB3_Tight_pt[cbin]->SetMarkerColor(kBlue);
        N1MC22SUB3_Tight_pt[cbin]->SetLineColor(kBlue);
        N1MC22SUB3_Tight_pt[cbin]->SetMarkerStyle(21);
        N1MC22SUB3_Tight_pt[cbin]->SetMarkerSize(1.2);

        N1MC22SUB3_TightB_pt[cbin]->SetMarkerColor(kRed);
        N1MC22SUB3_TightB_pt[cbin]->SetLineColor(kRed);
        N1MC22SUB3_TightB_pt[cbin]->SetMarkerStyle(24);
        N1MC22SUB3_TightB_pt[cbin]->SetMarkerSize(1.2);

        ratN1SUB2_Loose_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1SUB2_Loose_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1SUB3_Loose_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1SUB3_Loose_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1MC22SUB3_Loose_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetMarkerStyle(21);
        ratN1MC22SUB3_Loose_Tight_pt[cbin]->SetMarkerSize(1.2);

        ratN1SUB2_TightB_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1SUB2_TightB_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1SUB3_TightB_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1SUB3_TightB_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1MC22SUB3_TightB_Tight_eta[cbin]->SetMarkerStyle(21);
        ratN1MC22SUB3_TightB_Tight_eta[cbin]->SetMarkerSize(1.2);

        ratN1MC22SUB3_TightB_Tight_pt[cbin]->SetMarkerStyle(21);
        ratN1MC22SUB3_TightB_Tight_pt[cbin]->SetMarkerSize(1.2);
    }


    TLine * lnEta = new TLine(-2.4, 0.0, 2.4, 0.0);
    TLine * lnPt  = new TLine(0.0, 0.0, 12.0, 0.0);
    TLine * lnEta_rat = new TLine(-2.8, 1.0, 2.8, 1.0);
    TLine * lnPt_rat  = new TLine(0.0, 1.0, 12.0, 1.0);

    if (!fopen("figures/integralVN","r")) system("mkdir figures/integralVN");
    if (!fopen("figures/integralVN/systematics","r")) system("mkdir figures/integralVN/systematics");


    TCanvas * cratN1SUB2_eta_0 = new TCanvas("cratN1SUB2_eta_0", "cratN1SUB2_eta_0", 1300, 650);
    cratN1SUB2_eta_0->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padratN1SUB2_eta_0 = (TPad *) cratN1SUB2_eta_0->cd(cbin+1);
        if (gridlines) padratN1SUB2_eta_0->SetGrid();
        if (cbin == 4 || cbin == 9) padratN1SUB2_eta_0->SetRightMargin(0.02);
        if (cbin <= 4) padratN1SUB2_eta_0->SetTopMargin(0.1);
        if (cbin > 4) padratN1SUB2_eta_0->SetBottomMargin(0.25);

        TH1D * hratN1SUB2_eta_0 = new TH1D(Form("hratN1SUB2_eta_0_%d",cbin), "", 50, -2.8, 2.8);
        hratN1SUB2_eta_0->SetXTitle("|#eta|");
        if (cbin <= 4) hratN1SUB2_eta_0->SetYTitle("v_{1}^{odd}");
        else hratN1SUB2_eta_0->SetYTitle("v_{1}^{odd}{Loose} / v_{1}^{odd}{Tight}");
        hratN1SUB2_eta_0->GetXaxis()->CenterTitle();
        hratN1SUB2_eta_0->GetYaxis()->CenterTitle();
        if (cbin<=4) hratN1SUB2_eta_0->GetYaxis()->SetRangeUser(-0.022, 0.022);
        else hratN1SUB2_eta_0->GetYaxis()->SetRangeUser(0.5, 1.5);
        hratN1SUB2_eta_0->GetYaxis()->SetNdivisions(509);
        hratN1SUB2_eta_0->GetYaxis()->SetTitleSize(0.07);
        hratN1SUB2_eta_0->GetYaxis()->SetLabelSize(0.05);
        hratN1SUB2_eta_0->GetYaxis()->SetTitleOffset(1.20);
        hratN1SUB2_eta_0->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hratN1SUB2_eta_0->GetXaxis()->SetTitleSize(0.07);
            hratN1SUB2_eta_0->GetXaxis()->SetLabelSize(0.05);
            hratN1SUB2_eta_0->GetXaxis()->SetTitleOffset(1.00);
            hratN1SUB2_eta_0->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hratN1SUB2_eta_0->GetXaxis()->SetTitleSize(0.08);
            hratN1SUB2_eta_0->GetXaxis()->SetLabelSize(0.06);
            hratN1SUB2_eta_0->GetXaxis()->SetTitleOffset(0.83);
            hratN1SUB2_eta_0->GetXaxis()->SetLabelOffset(0.011);
        }
        hratN1SUB2_eta_0->Draw();
        if (cbin <= 4) lnEta->Draw();
        else lnEta_rat->Draw();

        if (cbin<=4) {N1SUB2_Tight_eta[cbin]->Draw("same"); N1SUB2_Loose_eta[cbin]->Draw("same");}
        else ratN1SUB2_Loose_Tight_eta[cbin-5]->Draw("same");

        TPaveText * txratN1SUB2_eta_0_cent;
        if (cbin <= 4) {
            if (cbin == 0) txratN1SUB2_eta_0_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
            else txratN1SUB2_eta_0_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
            SetTPaveTxt(txratN1SUB2_eta_0_cent, 17);
            txratN1SUB2_eta_0_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            txratN1SUB2_eta_0_cent->Draw();
        }

        TPaveText * txtxratN1SUB2_eta_0_fit;
        if (cbin >= 5) {
            if (cbin == 5) txtxratN1SUB2_eta_0_fit = new TPaveText(0.23, 0.29, 0.60, 0.35, "NDC");
            else txtxratN1SUB2_eta_0_fit = new TPaveText(0.04, 0.29, 0.49, 0.35, "NDC");
            SetTPaveTxt(txtxratN1SUB2_eta_0_fit, 16);
            txtxratN1SUB2_eta_0_fit->AddText(Form("mean = %1.4f",systN1SUB2_Loose_Tight_eta->GetBinContent(cbin+1)));
            txtxratN1SUB2_eta_0_fit->Draw();
        }
    }
    cratN1SUB2_eta_0->cd(1);
    TPaveText * txratN1SUB2_eta_0_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txratN1SUB2_eta_0_CMS, 18);
    txratN1SUB2_eta_0_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txratN1SUB2_eta_0_CMS->Draw();

    TLegend * legratN1SUB2_eta_0 = new TLegend(0.22, 0.05, 0.72, 0.23);
    SetLegend(legratN1SUB2_eta_0, 16);
    legratN1SUB2_eta_0->AddEntry(N1SUB2_Tight_eta[0],"Tight (default)","p");
    legratN1SUB2_eta_0->AddEntry(N1SUB2_Loose_eta[0],"Loose","p");
    legratN1SUB2_eta_0->Draw();

    cratN1SUB2_eta_0->cd(1);
    TPaveText * txratN1SUB2_eta_0_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txratN1SUB2_eta_0_label, 16);
    txratN1SUB2_eta_0_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txratN1SUB2_eta_0_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txratN1SUB2_eta_0_label->Draw();

    cratN1SUB2_eta_0->Print("figures/integralVN/systematics/trkcuts_ratio_N1SUB2_eta_0.pdf","pdf");



    TCanvas * cratN1SUB2_eta_1 = new TCanvas("cratN1SUB2_eta_1", "cratN1SUB2_eta_1", 1300, 650);
    cratN1SUB2_eta_1->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padratN1SUB2_eta_1 = (TPad *) cratN1SUB2_eta_1->cd(cbin+1);
        if (gridlines) padratN1SUB2_eta_1->SetGrid();
        if (cbin == 4 || cbin == 9) padratN1SUB2_eta_1->SetRightMargin(0.02);
        if (cbin <= 4) padratN1SUB2_eta_1->SetTopMargin(0.1);
        if (cbin > 4) padratN1SUB2_eta_1->SetBottomMargin(0.25);

        TH1D * hratN1SUB2_eta_1 = new TH1D(Form("hratN1SUB2_eta_1_%d",cbin), "", 50, -2.8, 2.8);
        hratN1SUB2_eta_1->SetXTitle("|#eta|");
        if (cbin <= 4) hratN1SUB2_eta_1->SetYTitle("v_{1}^{odd}");
        else hratN1SUB2_eta_1->SetYTitle("v_{1}^{odd}{Loose} / v_{1}^{odd}{Tight}");
        hratN1SUB2_eta_1->GetXaxis()->CenterTitle();
        hratN1SUB2_eta_1->GetYaxis()->CenterTitle();
        if (cbin<=4) hratN1SUB2_eta_1->GetYaxis()->SetRangeUser(-0.022, 0.022);
        else hratN1SUB2_eta_1->GetYaxis()->SetRangeUser(0.5, 1.5);
        hratN1SUB2_eta_1->GetYaxis()->SetNdivisions(509);
        hratN1SUB2_eta_1->GetYaxis()->SetTitleSize(0.07);
        hratN1SUB2_eta_1->GetYaxis()->SetLabelSize(0.05);
        hratN1SUB2_eta_1->GetYaxis()->SetTitleOffset(1.20);
        hratN1SUB2_eta_1->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hratN1SUB2_eta_1->GetXaxis()->SetTitleSize(0.07);
            hratN1SUB2_eta_1->GetXaxis()->SetLabelSize(0.05);
            hratN1SUB2_eta_1->GetXaxis()->SetTitleOffset(1.00);
            hratN1SUB2_eta_1->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hratN1SUB2_eta_1->GetXaxis()->SetTitleSize(0.08);
            hratN1SUB2_eta_1->GetXaxis()->SetLabelSize(0.06);
            hratN1SUB2_eta_1->GetXaxis()->SetTitleOffset(0.83);
            hratN1SUB2_eta_1->GetXaxis()->SetLabelOffset(0.011);
        }
        hratN1SUB2_eta_1->Draw();
        if (cbin <= 4) lnEta->Draw();
        else lnEta_rat->Draw();

        if (cbin<=4) {N1SUB2_Tight_eta[cbin]->Draw("same"); N1SUB2_Loose_eta[cbin]->Draw("same");}
        else ratN1SUB2_Loose_Tight_eta[cbin-5]->Draw("same");

        TPaveText * txratN1SUB2_eta_1_cent;
        if (cbin <= 4) {
            if (cbin == 0) txratN1SUB2_eta_1_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
            else txratN1SUB2_eta_1_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
            SetTPaveTxt(txratN1SUB2_eta_1_cent, 17);
            txratN1SUB2_eta_1_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
            txratN1SUB2_eta_1_cent->Draw();
        }

        TPaveText * txtxratN1SUB2_eta_1_fit;
        if (cbin >= 5) {
            if (cbin == 5) txtxratN1SUB2_eta_1_fit = new TPaveText(0.23, 0.29, 0.60, 0.35, "NDC");
            else txtxratN1SUB2_eta_1_fit = new TPaveText(0.04, 0.29, 0.49, 0.35, "NDC");
            SetTPaveTxt(txtxratN1SUB2_eta_1_fit, 16);
            txtxratN1SUB2_eta_1_fit->AddText(Form("mean = %1.4f",systN1SUB2_Loose_Tight_eta->GetBinContent(cbin+1)));
            txtxratN1SUB2_eta_1_fit->Draw();
        }
    }
    cratN1SUB2_eta_1->cd(1);
    TPaveText * txratN1SUB2_eta_1_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txratN1SUB2_eta_1_CMS, 18);
    txratN1SUB2_eta_1_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txratN1SUB2_eta_1_CMS->Draw();

    TLegend * legratN1SUB2_eta_1 = new TLegend(0.22, 0.05, 0.72, 0.23);
    SetLegend(legratN1SUB2_eta_1, 16);
    legratN1SUB2_eta_1->AddEntry(N1SUB2_Tight_eta[0],"Tight (default)","p");
    legratN1SUB2_eta_1->AddEntry(N1SUB2_Loose_eta[0],"Loose","p");
    legratN1SUB2_eta_1->Draw();

    cratN1SUB2_eta_1->cd(1);
    TPaveText * txratN1SUB2_eta_1_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txratN1SUB2_eta_1_label, 16);
    txratN1SUB2_eta_1_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txratN1SUB2_eta_1_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txratN1SUB2_eta_1_label->Draw();

    cratN1SUB2_eta_1->Print("figures/integralVN/systematics/trkcuts_ratio_N1SUB2_eta_1.pdf","pdf");


}
