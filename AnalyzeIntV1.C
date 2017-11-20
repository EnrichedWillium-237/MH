# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
# include "TH1.h"
# include "TH2.h"
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
static const int ncentbins = 13;
static const int centBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 100};
static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 100};
double EtaMin = -2.4;
double EtaMax = 2.4;
string FigDir = "";
string FigSubDir = "";
static const int nanals = 15;
enum AnalType {
    N1MCm22SUB3, N1MCm18SUB3, N1MCm14SUB3, N1MCm10SUB3, N1MCm06SUB3, N1MCm02SUB3,
    N1MCp22SUB3, N1MCp18SUB3, N1MCp14SUB3, N1MCp10SUB3, N1MCp06SUB3, N1MCp02SUB3,
    N112ASUB2,   N112ASUB3,   N123ASUB2,   N123ASUB3,   N1SUB2,      N1SUB3};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCm18SUB3", "N1MCm14SUB3", "N1MCm10SUB3", "N1MCm06SUB3", "N1MCm02SUB3",
    "N1MCp22SUB3", "N1MCp18SUB3", "N1MCp14SUB3", "N1MCp10SUB3", "N1MCp06SUB3", "N1MCp02SUB3",
    "N112ASUB2",   "N112ASUB3",   "N123ASUB2",   "N123ASUB3",   "N1SUB2",      "N1SUB3"};
string ytitle[] = {
    "v_{1}\{#Psi_{1,MC} (-2.4<#eta<-2.0)\}", "v_{1}\{#Psi_{1,MC} (-2.0<#eta<-1.6)\}", "v_{1}\{#Psi_{1,MC} (-1.6<#eta<-1.2)\}", "v_{1}\{#Psi_{1,MC} (-1.2<#eta<-0.8)\}",
    "v_{1}\{#Psi_{1,MC} (-0.8<#eta<-0.4)\}", "v_{1}\{#Psi_{1,MC} (-0.4<#eta<0.0)\}",
    "v_{1}\{#Psi_{1,MC} (0.0<#eta<0.4)\}",   "v_{1}\{#Psi_{1,MC} (0.4<#eta<0.8)\}",   "v_{1}\{#Psi_{1,MC} (0.8<#eta<1.2)\}",   "v_{1}\{#Psi_{1,MC} (1.2<#eta<1.6)\}",
    "v_{1}\{#Psi_{1,MC} (1.6<#eta<2.0)\}",   "v_{1}\{#Psi_{1,MC} (2.0<#eta<2.4)\}",
    "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",
    "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}"};

// TH1D * v1A_pT[nanals][ncentbins];
// TH1D * v1B_pT[nanals][ncentbins];
// TH1D * v1add_pT[nanals][ncentbins];
// TH1D * v1sub_pT[nanals][ncentbins];


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

FILE * outint;
string soutint;
string sspec;
FILE * outspec;
TFile * fin;
double fw = 1.3;
int ANAL = -1;
double fakescale = 1.;
bool isLoose = false;
bool isTight = false;
bool rew = false;
string stag;
TH1D * centbins;
TH1I * centRef;

double FakeAndEff( int cent, double pt, double &eff ) {
    double cb[14] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 100};
    double cbe[6] = {0, 5, 10, 30, 50, 100};
    TFile * f = 0;
    TFile * e = 0;
    if (isLoose) {
        f = new TFile("EffAndFake/FakeRatesPixelPbPb_loose.root");
        e = new TFile("EffAndFake/EffCorrectionsPixelPbPb_loose.root");
    }
    if (isTight) {
        f = new TFile("EffAndFake/FakeRatesPixelPbPb_tight.root");
        e = new TFile("EffAndFake/EffCorrectionsPixelPbPb_tight.root");
    }
    TH1I * cen = new TH1I("cen", "cen", 13, cb);
    TH1I * cene = new TH1I("cene", "cene", 5, cbe);
    int ib = cen->FindBin(cent) - 1;
    int ibe = cene->FindBin(cent) - 1;
    string rc = "hfak_"+to_string((int)cb[ib])+"_"+to_string((int)cb[ib+1]);
    TH2D * hf = (TH2D *) f->Get(rc.data());
    string re = "Eff_"+to_string((int)cbe[ibe])+"_"+to_string((int)cbe[ibe+1]);
    TH2D * he = (TH2D *) e->Get(re.data());
    int ptbin = hf->GetYaxis()->FindBin(pt);
    int etabinmin = hf->GetXaxis()->FindBin(-0.8);
    int etabinmax = hf->GetXaxis()->FindBin(0.79);
    double val = 0;
    eff = 0;
    for(int i = etabinmin; i<=etabinmax; i++) {
        val += hf->GetBinContent(i,ptbin);
        eff += he->GetBinContent(i,ptbin);
    }
    val /=(double)(etabinmax-etabinmin+1);
    eff /=(double)(etabinmax-etabinmin+1);
    cen->Delete();
    cene->Delete();
    f->Close();
    e->Close();
    return val ;
}

TH2D * ptcntEff(TH2D * ptcnt, double cent) {
    double cbe[6]={0, 5, 10, 30, 50, 100};
    TFile * e = 0;
    if (isLoose) {
        cout<<"use loose cut efficiency"<<endl;
        e = new TFile("EffAndFake/EffCorrectionsPixelPbPb_loose.root");
    }
    if (isTight) {
        cout<<"use tight cut efficiency"<<endl;
        e = new TFile("EffAndFake/EffCorrectionsPixelPbPb_tight.root");
    }
    TH1I * cene = new TH1I("cene", "cene", 5, cbe);
    int ibe = cene->FindBin(cent) - 1;
    string re = "Eff_"+to_string((int)cbe[ibe])+"_"+to_string((int)cbe[ibe+1]);
    TH2D * he = (TH2D *) e->Get(re.data());
    TH2D * hsEff = (TH2D *) ptcnt->Clone("ptcntEff");
    hsEff->Reset();
    hsEff->SetDirectory(0);
    bool skipeff = false;
    for(int i = 1; i<=ptcnt->GetNbinsX(); i++) {
        for(int j = 1; j<=ptcnt->GetNbinsY(); j++) {
            double pt = ptcnt->GetXaxis()->GetBinCenter(i);
            double eta = ptcnt->GetYaxis()->GetBinCenter(j);
            int ptbin = he->GetYaxis()->FindBin(pt);
            int etabin = he->GetXaxis()->FindBin(eta);
            double eff =  he->GetBinContent(etabin,ptbin);

            if(eff<=0 || skipeff) eff = 1;
            hsEff->SetBinContent(i,j,ptcnt->GetBinContent(i,j)/eff);
        }
    }
    cene->Delete();
    e->Close();
    return hsEff ;
}

TGraphErrors * GetV1IntPt( string anal, string tag, int cbin, double etamin, double etamax, TGraphErrors * &g_p, TGraphErrors * &g_m );
//TGraphErrors * GetV1IntEta( string anal, string tag, int cbin, double etamin, double etamax, TGraphErrors * &g_p, TGraphErrors * &g_m );
