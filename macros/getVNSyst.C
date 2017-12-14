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

TH1D * vnA_eta[nanals][ncbins];
TH1D * vnB_eta[nanals][ncbins];
TH1D * vnAB_eta[nanals][ncbins];
TH1D * N1SUB2_eta[ncbins];
TH1D * N1SUB3_eta[ncbins];

TH1D * vnA_pt[nanals][ncbins];
TH1D * vnB_pt[nanals][ncbins];
TH1D * vnAB_pt[nanals][ncbins];
TH1D * N1SUB2_pt[ncbins];
TH1D * N1SUB3_pt[ncbins];

// symeterized vn
TH1D * N1SUB2_Sym_eta[ncbins];
TH1D * N1SUB3_Sym_eta[ncbins];
TH1D * N1MC22SUB3_Sym_eta[ncbins];

TH1D * N1SUB2_Syst_eta[ncbins];
TH1D * N1SUB3_Syst_eta[ncbins];
TH1D * N1MC22SUB3_Syst_eta[ncbins];

TH1D * N1SUB2_RelErr_eta[ncbins];
TH1D * N1SUB3_RelErr_eta[ncbins];
TH1D * N1MC22SUB3_RelErr_eta[ncbins];

TH1D * N1SUB2_Sym_pt[ncbins];
TH1D * N1SUB3_Sym_pt[ncbins];
TH1D * N1MC22SUB3_Sym_pt[ncbins];

TH1D * N1SUB2_Syst_pt[ncbins];
TH1D * N1SUB3_Syst_pt[ncbins];
TH1D * N1MC22SUB3_Syst_pt[ncbins];

TH1D * N1SUB2_RelErr_pt[ncbins];
TH1D * N1SUB3_RelErr_pt[ncbins];
TH1D * N1MC22SUB3_RelErr_pt[ncbins];

TF1 * fit_N1SUB2_RelErr_eta[ncbins];
TF1 * fit_N1SUB3_RelErr_eta[ncbins];
TF1 * fit_N1MC22SUB3_RelErr_eta[ncbins];

TF1 * fit_N1SUB2_RelErr_pt[ncbins];
TF1 * fit_N1SUB3_RelErr_pt[ncbins];
TF1 * fit_N1MC22SUB3_RelErr_pt[ncbins];

TFile * tfin;
TFile * tfout;

void getVNSyst()
{

    TH1::SetDefaultSumw2();

    for (int anal = 0; anal<nanals; anal++) {
        for (int cbin = 0; cbin<ncbins; cbin++) {
            string htag = Form("_%s_%d_%d",AnalNames[anal].data(),cmin[cbin],cmax[cbin]);
            vnA_eta[anal][cbin]  = new TH1D(Form("vnA_eta_%s",htag.data()), "", netabins, etabins);
            vnB_eta[anal][cbin]  = new TH1D(Form("vnB_eta_%s",htag.data()), "", netabins, etabins);
            vnAB_eta[anal][cbin] = new TH1D(Form("vnAB_eta_%s",htag.data()), "", netabins, etabins);
        }
    }
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_Sym_eta[cbin] = new TH1D(Form("N1SUB2_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_Sym_eta[cbin] = new TH1D(Form("N1SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_Sym_eta[cbin] = new TH1D(Form("N1MC22SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_RelErr_eta[cbin] = new TH1D(Form("N1SUB2_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_RelErr_eta[cbin] = new TH1D(Form("N1SUB3_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_RelErr_eta[cbin] = new TH1D(Form("N1MC22SUB3_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_Sym_pt[cbin] = new TH1D(Form("N1SUB2_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1SUB3_Sym_pt[cbin] = new TH1D(Form("N1SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1MC22SUB3_Sym_pt[cbin] = new TH1D(Form("N1MC22SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);

        N1SUB2_RelErr_pt[cbin] = new TH1D(Form("N1SUB2_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1SUB3_RelErr_pt[cbin] = new TH1D(Form("N1SUB3_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1MC22SUB3_RelErr_pt[cbin] = new TH1D(Form("N1MC22SUB3_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
    }

    string prevname = "";
    for (int anal = 0; anal<nanals; anal++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integral.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                    vnAB_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnAB_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }

            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integralA.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                    vnA_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnA_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }

            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integralB.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                    vnB_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnB_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }
        }

        tfin = new TFile(Form("results/results_useTight_-2.4_2.4/%s.root",AnalNames[anal].data()));
        for (int cbin = 0; cbin<ncbins; cbin++) {
            vnA_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[cbin],cmax[cbin]));
            vnB_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[cbin],cmax[cbin]));
            vnAB_pt[anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        }

    }


    //-- average N!SUB2 and N1SUB3
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB2][cbin]->Clone(Form("N1SUB2_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB2_eta[cbin]->Add(vnAB_eta[N1BSUB2][cbin]);
        N1SUB2_eta[cbin]->Scale(0.5);

        N1SUB3_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB3][cbin]->Clone(Form("N1SUB3_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_eta[cbin]->Add(vnAB_eta[N1BSUB3][cbin]);
        N1SUB3_eta[cbin]->Scale(0.5);

        N1SUB2_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB2][cbin]->Clone(Form("N1SUB2_pt_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB2_pt[cbin]->Add(vnAB_pt[N1BSUB2][cbin]);
        N1SUB2_pt[cbin]->Scale(0.5);

        N1SUB3_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB3][cbin]->Clone(Form("N1SUB3_pt_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_pt[cbin]->Add(vnAB_pt[N1BSUB3][cbin]);
        N1SUB3_pt[cbin]->Scale(0.5);
    }


    //-- symmeterize v1
    for (int cbin = 0; cbin<ncbins; cbin++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            double pos = N1SUB2_eta[cbin]->GetBinContent(netabins - ebin);
            double neg = N1SUB2_eta[cbin]->GetBinContent(ebin + 1);
            double posErr = N1SUB2_eta[cbin]->GetBinError(netabins - ebin);
            double negErr = N1SUB2_eta[cbin]->GetBinError(ebin + 1);
            double vnsym = 0.5*(pos - neg);
            double vnsymErr = 0.5*sqrt( posErr*posErr + negErr*negErr );
            N1SUB2_Sym_eta[cbin]->SetBinContent(netabins - ebin, vnsym);
            N1SUB2_Sym_eta[cbin]->SetBinError(netabins - ebin, vnsymErr);

            double rel = (fabs(pos) - fabs(neg)) / (fabs(pos) + fabs(neg));
            // double relErr = pow(posErr/pos,2) + pow(negErr/neg,2) - 2*fabs((posErr*posErr/pos)*(negErr*negErr/neg));
            double relErr = pow(posErr/pos,2) + pow(negErr/neg,2);
            relErr = rel * sqrt( relErr );
            N1SUB2_RelErr_eta[cbin]->SetBinContent(netabins - ebin, rel);
            N1SUB2_RelErr_eta[cbin]->SetBinError(netabins - ebin, relErr);
        }
        for (int ebin = 0; ebin<netabins; ebin++) {
            double pos = N1SUB3_eta[cbin]->GetBinContent(netabins - ebin);
            double neg = N1SUB3_eta[cbin]->GetBinContent(ebin + 1);
            double posErr = N1SUB3_eta[cbin]->GetBinError(netabins - ebin);
            double negErr = N1SUB3_eta[cbin]->GetBinError(ebin + 1);
            double vnsym = 0.5*(pos - neg);
            double vnsymErr = 0.5*sqrt( posErr*posErr + negErr*negErr );
            N1SUB3_Sym_eta[cbin]->SetBinContent(netabins - ebin, vnsym);
            N1SUB3_Sym_eta[cbin]->SetBinError(netabins - ebin, vnsymErr);

            double rel = (fabs(pos) - fabs(neg)) / (fabs(pos) + fabs(neg));
            double relErr = pow(posErr/pos,2) + pow(negErr/neg,2);
            relErr = rel * sqrt( relErr );
            N1SUB3_RelErr_eta[cbin]->SetBinContent(netabins - ebin, rel);
            N1SUB3_RelErr_eta[cbin]->SetBinError(netabins - ebin, relErr);
        }
    }


    TLine * lnEta = new TLine(-2.4, 0.0, 2.4, 0.0);
    TLine * lnPt  = new TLine(0.0, 0.0, 12.0, 0.0);

    if (!fopen("figures/integralVN","r")) system("mkdir figures/integralVN");
    if (!fopen("figures/integralVN/data","r")) system("mkdir figures/integralVN/data");



}
