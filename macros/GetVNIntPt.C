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
double EtaMin = -2.4;
double EtaMax = 2.4;
double PtMin = 0.3;
double PtMax = 3.0;
string FigDir = "";
string FigSubDir = "";
static const int nanals = 18;
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
string ytitle[] = {
    "v_{1}\{#Psi_{1,MC} (-2.4<#eta<-2.0)\}", "v_{1}\{#Psi_{1,MC} (-2.0<#eta<-1.6)\}", "v_{1}\{#Psi_{1,MC} (-1.6<#eta<-1.2)\}", "v_{1}\{#Psi_{1,MC} (-1.2<#eta<-0.8)\}",
    "v_{1}\{#Psi_{1,MC} (-0.8<#eta<-0.4)\}", "v_{1}\{#Psi_{1,MC} (-0.4<#eta<0.0)\}",
    "v_{1}\{#Psi_{1,MC} (2.0<#eta<2.4)\}",   "v_{1}\{#Psi_{1,MC} (1.6<#eta<2.0)\}",   "v_{1}\{#Psi_{1,MC} (1.2<#eta<1.6)\}",   "v_{1}\{#Psi_{1,MC} (0.8<#eta<1.2)\}",
    "v_{1}\{#Psi_{1,MC} (0.4<#eta<0.8)\}",   "v_{1}\{#Psi_{1,MC} (0.0<#eta<0.4)\}",
    "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",
    "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",
    "v_{2}\{#Psi_{2}\}",                     "v_{2}\{#Psi_{2}\}",                     "v_{3}\{#Psi_{3}\}",                     "v_{3}\{#Psi_{3}\}", "LAST"};

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
TFile * tfout;
double fw = 1.3;
int ANAL = -1;
double fakescale = 1.;
bool isLoose = false;
bool isTight = false;
bool rew = false;
string stag;
TH1D * centbins;
TH1I * centRef;

double FakeAndEffPt( int cent, double pt, double &eff ) {
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
    val/=(double)(etabinmax-etabinmin+1);
    eff/=(double)(etabinmax-etabinmin+1);
    cen->Delete();
    cene->Delete();
    f->Close();
    e->Close();
    return val;
}


TH2D * ptcntEff(TH2D * ptcnt, double cent) {
    double cbe[6] = {0, 5, 10, 30, 50, 100};
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


TGraphErrors * hpt;
TGraphErrors * hdenom;
TGraphErrors * hA;
TGraphErrors * hB;
TGraphErrors * hAdenom;
TGraphErrors * hBdenom;
TGraphErrors * nwspec;
TGraphErrors * nwspec2;
string rootFile;
TGraphErrors * GetVNPt( int replay, int cbin, double etamin, double etamax, TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gspec, double * resA, double * resB, double &vint, double &vinte, bool nonorm = false ) {

    cout<<"========================== "<<AnalNames[replay]<<"  with cbin, etamin, etamax: "<<cbin<<"\t"<<etamin<<"\t"<<etamax<<endl;
    TH1D * hspec = 0;
    TH1D * xpt = 0;
    TH1D * sp = 0;
    TH1D * vn = 0;
    TH1D * vnA = 0;
    TH1D * vnB = 0;
    TH1D * vn2 = 0;
    TH1D * vnA2 = 0;
    TH1D * vnB2 = 0;
    TH1D * qA1 = 0;
    TH1D * qB1 = 0;
    TH1D * wA1 = 0;
    TH1D * wB1 = 0;
    TH2D * qAe[10];
    TH2D * qBe[10];
    TH2D * wnAe[10];
    TH2D * wnBe[10];
    TH1D * qAe1[10] = {0};
    TH1D * qBe1[10] = {0};
    TH1D * wAe1[10] = {0};
    TH1D * wBe1[10] = {0};
    TH1D * vnAe = 0;
    TH1D * vnBe = 0;
    TH1D * vne = 0;
    TH2D * ptav = 0;
    TH2D * ptcnt = 0;
    TH2D * badcnt = 0;
    TH2D * qA = 0;
    TH2D * qB = 0;
    TH2D * wnA = 0;
    TH2D * wnB = 0;
    int jmin = centRef->FindBin(cmin[cbin])-1;
    int jmax = centRef->FindBin(cmax[cbin]-0.01)-1;
    cout<<"jmin, jmax: "<<jmin<<"\t"<<jmax<<endl;
    ANAL = replay;
    string strip = AnalNames[replay];
    bool sub2 = false;
    TString subtest = AnalNames[replay];
    if (subtest.Contains("SUB2")) sub2 = true;
    if (sub2) {
        cout<<"Use 2 subevent weighting"<<endl;
        strip = strip.substr(0,strip.find("SUB2"));
    } else {
        cout<<"Use 3 subevent weighting"<<endl;
        strip = strip.substr(0,strip.find("SUB3"));
    }
    double qBA = 0;
    double qCA = 0;
    double qCB = 0;
    double qBAcnt = 0;
    double qCAcnt = 0;
    double qCBcnt = 0;
    double qBAe[10] = {0};
    double qCAe[10] = {0};
    double qCBe[10] = {0};
    double qBAecnt[10] = {0};
    double qCAecnt[10] = {0};
    double qCBecnt[10] = {0};
    double centcnt = 0;
    for (int j = jmin; j<=jmax; j++) {
        string crange = to_string(cmin[j])+"_"+to_string(cmax[j]);
        cout<<"crange: "<<crange<<endl;
        if (j == jmin) {
            ptav = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/ptav",crange.data()));
            ptcnt = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/ptcnt",crange.data()));
            badcnt = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/badcnt",crange.data()));
            centbins = (TH1D * ) fin->Get("vnanalyzer/centres");
            centcnt+=centbins->GetBinContent(j);
            qA = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qA",crange.data(),strip.data()));
            qB = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qB",crange.data(),strip.data()));
            wnA = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wnA",crange.data(),strip.data()));
            wnB = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wnB",crange.data(),strip.data()));
            qBA += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",crange.data(),strip.data())))->GetBinContent(1);
            qBAcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",crange.data(),strip.data())))->GetBinContent(1);
            qCA += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",crange.data(),strip.data())))->GetBinContent(1);
            qCAcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",crange.data(),strip.data())))->GetBinContent(1);
            qCB += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",crange.data(),strip.data())))->GetBinContent(1);
            qCBcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",crange.data(),strip.data())))->GetBinContent(1);

            for (int i = 0; i<10; i++) {
                qAe[i] = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qA_%d",crange.data(),strip.data(),i+1));
            	qBe[i] = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qB_%d",crange.data(),strip.data(),i+1));
            	wnAe[i] = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/wnA_%d",crange.data(),strip.data(),i+1));
            	wnBe[i] = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/wnB_%d",crange.data(),strip.data(),i+1));
                qBAe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBA_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            	qBAecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBAcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            	qCAe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCA_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            	qCAecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCAcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            	qCBe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCB_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            	qCBecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCBcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            }
        } else {
            centcnt+=centbins->GetBinContent(j);
            ptav->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/ptav",crange.data())));
            ptcnt->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/ptcnt",crange.data())));
            badcnt->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/badcnt",crange.data())));
            qA->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qA",crange.data(),strip.data())));
            qB->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qB",crange.data(),strip.data())));
            wnA->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wnA",crange.data(),strip.data())));
            wnB->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wnB",crange.data(),strip.data())));
            qBA += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",crange.data(),strip.data())))->GetBinContent(1);
            qBAcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",crange.data(),strip.data())))->GetBinContent(1);
            qCA += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",crange.data(),strip.data())))->GetBinContent(1);
            qCAcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",crange.data(),strip.data())))->GetBinContent(1);
            qCB += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",crange.data(),strip.data())))->GetBinContent(1);
            qCBcnt+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",crange.data(),strip.data())))->GetBinContent(1);

            for (int i = 0; i<10; i++) {
                qAe[i]->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qA_%d",crange.data(),strip.data(),i+1)));
                qBe[i]->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qB_%d",crange.data(),strip.data(),i+1)));
                wnAe[i]->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/wnA_%d",crange.data(),strip.data(),i+1)));
                wnBe[i]->Add( (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/wnB_%d",crange.data(),strip.data(),i+1)));
                qBAe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBA_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
                qBAecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBAcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
                qCAe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCA_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
                qCAecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCAcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
                qCBe[i] += ((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCB_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
                qCBecnt[i]+=((TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCBcnt_%d",crange.data(),strip.data(),i+1)))->GetBinContent(1);
            }
        }
    }

    qBA/=qBAcnt;
    qCA/=qCAcnt;
    qCB/=qCBcnt;
    for (int i = 0; i<10; i++) {
        qBAe[i]/=qBAecnt[i];
        qCAe[i]/=qCAecnt[i];
        qCBe[i]/=qCBecnt[i];
    }
    ptav->Divide(ptcnt);
    int ietamin1=0;
    int ietamax1=0;
    int ietamin2=0;
    int ietamax2=0;
    double sign = 1.;
    if (replay==N112ASUB2 || replay==N112ASUB3) sign=-1.;
     if (etamin*etamax<0) {
         ietamin1 = qA->GetYaxis()->FindBin(etamin);
         ietamax1 = qA->GetYaxis()->FindBin(-0.001);
         ietamin2 = qA->GetYaxis()->FindBin(0.);
         ietamax2 = qA->GetYaxis()->FindBin(etamax);
         qA1 = (TH1D *) qA->ProjectionX("qA1",ietamin1,ietamax1);
         qB1 = (TH1D *) qB->ProjectionX("qB1",ietamin2,ietamax2);
         wA1 = (TH1D *) wnA->ProjectionX("wA1",ietamin1,ietamax1);
         wB1 = (TH1D *) wnB->ProjectionX("wB1",ietamin2,ietamax2);
     } else {
         ietamin1 = qA->GetYaxis()->FindBin(etamin);
         ietamax1 = qA->GetYaxis()->FindBin(etamax);
         qA1 = (TH1D *) qA->ProjectionX("qA1",ietamin1,ietamax1);
         qB1 = (TH1D *) qB->ProjectionX("qB1",ietamin1,ietamax1);
         wA1 = (TH1D *) wnA->ProjectionX("wA1",ietamin1,ietamax1);
         wB1 = (TH1D *) wnB->ProjectionX("wB1",ietamin1,ietamax1);
     }
     qA->Divide(wnA);
     qB->Divide(wnB);
     qA1->Divide(wA1);
     qB1->Divide(wB1);
     if (!nonorm) {
         qBA = fabs(qBA);
         qCA = fabs(qCA);
         qCB = fabs(qCB);
         if (sub2) {
             qA->Scale(1./sqrt(qBA));
             qB->Scale(1./sqrt(qBA));
             qA1->Scale(1./sqrt(qBA));
             qB1->Scale(1./sqrt(qBA));
             resA[0]= sqrt(qBA);
             resB[0]= sqrt(qBA);
         } else {
             qA->Scale(1./sqrt(qBA*qCA/qCB));
             qB->Scale(1./sqrt(qBA*qCB/qCA));
             qA1->Scale(1./sqrt(qBA*qCA/qCB));
             qB1->Scale(1./sqrt(qBA*qCB/qCA));
             resA[0]= sqrt(qBA*qCA/qCB);
             resB[0]= sqrt(qBA*qCB/qCA);
         }
     }

     for (int i = 0; i<10; i++) {
         qAe1[i] = (TH1D *) qAe[i]->ProjectionX(Form("qAe1_%d",i),ietamin1,ietamax1);
         qBe1[i] = (TH1D *) qBe[i]->ProjectionX(Form("qBe1_%d",i),ietamin2,ietamax2);
         wAe1[i] = (TH1D *) wnAe[i]->ProjectionX(Form("wA1_%d",i),ietamin1,ietamax1);
         wBe1[i] = (TH1D *) wnBe[i]->ProjectionX(Form("wB1_%d",i),ietamin2,ietamax2);

         qAe[i]->Divide(wnAe[i]);
         qBe[i]->Divide(wnBe[i]);
         qAe1[i]->Divide(wAe1[i]);
         qBe1[i]->Divide(wBe1[i]);
         if (!nonorm) {
             qBAe[i]=fabs(qBAe[i]);
             qCAe[i]=fabs(qCAe[i]);
             qCBe[i]=fabs(qCBe[i]);
             if (sub2) {
                 qAe[i]->Scale(1./sqrt(qBAe[i]));
                 qBe[i]->Scale(1./sqrt(qBAe[i]));
                 resA[i+1]= sqrt(qBAe[i]);
                 resB[i+1]= sqrt(qBAe[i]);
             } else {
                 qAe[i]->Scale(1./sqrt(qBAe[i]*qCAe[i]/qCBe[i]));
                 qBe[i]->Scale(1./sqrt(qBAe[i]*qCBe[i]/qCAe[i]));
                 resA[i+1]= sqrt(qBAe[i]*qCAe[i]/qCBe[i]);
                 resB[i+1]= sqrt(qBAe[i]*qCBe[i]/qCAe[i]);
             }
         }
     }
     if (etamin*etamax<0) {
         xpt = (TH1D *) ptav->ProjectionX("xpt",ietamin1,ietamax2);
         double c = (cmin[cbin]+cmax[cbin])/2.;
         TH2D * hsEff = ptcntEff(ptcnt,c);

         sp = (TH1D *) hsEff->ProjectionX("sp",ietamin1,ietamax2);
         double ebinsA = ietamax1-ietamin1+1 ;
         double ebinsB = ietamax2-ietamin2+1;
         xpt->Scale(1./(ebinsA+ebinsB));
         sp->Scale(1./(ebinsA+ebinsB));
         if (!rew) {
             vnA = (TH1D *) qA->ProjectionX("vnA",ietamin1,ietamax1);
             vnB = (TH1D *) qB->ProjectionX("vnB",ietamin2,ietamax2);
             vn = (TH1D *) vnA->Clone("vn");
             vn->Add(vnB,sign);
             vn->Scale(sign);
             vnA->Scale(1./ebinsA);
             vnB->Scale(1./ebinsB);
             vn->Scale(1./(ebinsA+ebinsB));
         } else {
             vnA = (TH1D *) qA1->Clone("vnA");
             vnB = (TH1D *) qB1->Clone("vnB");
             vn = (TH1D *) vnA->Clone("vn");
             vn->Add(vnB,sign);
             vn->Scale(sign);
             vn->Scale(0.5);
         }
         double vnm[50] = {0};
         double vnAm[50] = {0};
         double vnBm[50] = {0};
         double vn2[50] = {0};
         double vnA2[50] = {0};
         double vnB2[50] = {0};
         for (int i = 0; i<50; i++) {
             vnm[i] = 0;
             vnAm[i] = 0;
             vnBm[i] = 0;
             vn2[i] = 0;
             vnA2[i] = 0;
             vnB2[i] = 0;
         }
         for (int i = 0; i<10; i++) {
             if (!rew) {
                 vnAe = (TH1D *) qAe[i]->ProjectionX(Form("vnA%d",i),ietamin1,ietamax1);
                 vnBe = (TH1D *) qBe[i]->ProjectionX(Form("vnB%d",i),ietamin2,ietamax2);
                 vne = (TH1D *) vnAe->Clone(Form("vn%d",i));
                 vne->Add(vnBe,sign);
                 vn->Scale(sign);
                 vnAe->Scale(1./ebinsA);
                 vnBe->Scale(1./ebinsB);
                 vne->Scale(1./(ebinsA+ebinsB));
             } else {
                 vnAe = (TH1D *) qAe1[i]->Clone(Form("vnA%d",i));
                 vnBe = (TH1D *) qBe1[i]->Clone(Form("vnB%d",i));
                 vne = (TH1D *) vnAe->Clone(Form("vn%d",i));
                 vne->Add(vnBe,sign);
                 vne->Scale(sign);
                 vne->Scale(0.5);
             }

             for (int j = 0; j<vne->GetNbinsX(); j++) {
                 vnm[j]+= vne->GetBinContent(j+1);
                 vnAm[j]+= vnAe->GetBinContent(j+1);
                 vnBm[j]+= vnBe->GetBinContent(j+1);
                 vn2[j] += pow(vne->GetBinContent(j+1),2);
                 vnA2[j]+= pow(vnAe->GetBinContent(j+1),2);
                 vnB2[j]+= pow(vnBe->GetBinContent(j+1),2);
             }
         }
         for (int j = 0; j<vn->GetNbinsX(); j++) {
             vnm[j]/=10.;
             vnAm[j]/=10.;
             vnBm[j]/=10.;
             vn2[j]/=10.;
             vnA2[j]/=10.;
             vnB2[j]/=10.;
             vn->SetBinError(j+1, sqrt((1./9.)*( vn2[j] - pow(vnm[j], 2))));
             vnA->SetBinError(j+1,sqrt((1./9.)*(vnA2[j] - pow(vnAm[j],2))));
             vnB->SetBinError(j+1,sqrt((1./9.)*(vnB2[j] - pow(vnBm[j],2))));
         }
     } else {
         xpt = (TH1D *) ptav->ProjectionX("xpt",ietamin1,ietamax1);
         double c = (cmin[cbin]+cmax[cbin])/2.;
         TH2D * hsEff = ptcntEff(ptcnt,c);

         sp = (TH1D *) hsEff->ProjectionX("sp",ietamin1,ietamax1);
         double ebinsA = ietamax1-ietamin1+1 ;
         xpt->Scale(1./ebinsA);
         sp->Scale(1./ebinsA);
         if (!rew) {
             vnA = (TH1D *) qA->ProjectionX("vnA",ietamin1,ietamax1);
             vnB = (TH1D *) qB->ProjectionX("vnB",ietamin1,ietamax1);
             vn = (TH1D *) vnA->Clone("vn");
             vn->Add(vnB,sign);
             vn->Scale(sign);
             vnA->Scale(1./ebinsA);
             vnB->Scale(1./ebinsA);
             vn->Scale(1./(ebinsA+ebinsA));
         } else {
             vnA = (TH1D *) qA1->Clone("vnA");
             vnB = (TH1D *) qB1->Clone("vnB");
             vn = (TH1D *) vnA->Clone("vn");
             vn->Add(vnB,sign);
             vn->Scale(sign);
             vn->Scale(0.5);
         }
         double vnm[50] = {0};
         double vnAm[50] = {0};
         double vnBm[50] = {0};
         double vn2[50] = {0};
         double vnA2[50] = {0};
         double vnB2[50] = {0};
         for (int i = 0; i<50; i++) {
             vnm[i] = 0;
             vnAm[i] = 0;
             vnBm[i] = 0;
             vn2[i] = 0;
             vnA2[i] = 0;
             vnB2[i] = 0;
         }
         for (int i = 0; i<10; i++) {
             if (!rew) {
                 vnAe = (TH1D *) qAe[i]->ProjectionX(Form("vnA%d",i),ietamin1,ietamax1);
                 vnBe = (TH1D *) qBe[i]->ProjectionX(Form("vnB%d",i),ietamin1,ietamax1);
                 vne = (TH1D *) vnAe->Clone(Form("vn%d",i));
                 vne->Add(vnBe,sign);
                 vne->Scale(sign);
                 vnAe->Scale(1./ebinsA);
                 vnBe->Scale(1./ebinsA);
                 vne->Scale(1./(ebinsA+ebinsA));
             } else {
                 vnAe = (TH1D *) qAe1[i]->Clone(Form("vnA%d",i));
                 vnBe = (TH1D *) qBe1[i]->Clone(Form("vnB%d",i));
                 vne = (TH1D *) vnAe->Clone(Form("vn%d",i));
                 vne->Add(vnBe,sign);
                 vne->Scale(sign);
                 vne->Scale(0.5);
             }

             for (int j = 0; j<vne->GetNbinsX(); j++) {
                 vnm[j]+= vne->GetBinContent(j+1);
                 vnAm[j]+= vnAe->GetBinContent(j+1);
                 vnBm[j]+= vnBe->GetBinContent(j+1);
                 vn2[j] += pow(vne->GetBinContent(j+1),2);
                 vnA2[j]+= pow(vnAe->GetBinContent(j+1),2);
                 vnB2[j]+= pow(vnBe->GetBinContent(j+1),2);
             }
         }
        for (int j = 0; j<vn->GetNbinsX(); j++) {
            vnm[j]/=10.;
            vnAm[j]/=10.;
            vnBm[j]/=10.;
            vn2[j]/=10.;
            vnA2[j]/=10.;
            vnB2[j]/=10.;
            vn->SetBinError(j+1, sqrt((1./9.)*( vn2[j] - pow(vnm[j], 2))));
            vnA->SetBinError(j+1,sqrt((1./9.)*(vnA2[j] - pow(vnAm[j],2))));
            vnB->SetBinError(j+1,sqrt((1./9.)*(vnB2[j] - pow(vnBm[j],2))));
        }
    }

    TH1D * yld;
    if (ietamax2>0) {
        yld = ptcnt->ProjectionX("yld",ietamin1,ietamax2);
    } else {
        yld = ptcnt->ProjectionX("yld",ietamin1,ietamax1);
    }
    double x[20];
    double y[20];
    double yA[20];
    double yB[20];
    double ex[20];
    double ey[20];
    double eyA[20];
    double eyB[20];
    double xspec[20];
    double yspec[20];
    double exspec[20];
    double eyspec[20];
    for (int i = 0; i<20; i++) {
        x[i] = 0;
        y[i] = 0;
        yA[i] = 0;
        yB[i] = 0;
        ex[i] = 0;
        ey[i] = 0;
        eyA[i] = 0;
        eyB[i] = 0;
        xspec[i] = 0;
        yspec[i] = 0;
        exspec[i] = 0;
        eyspec[i] = 0;
    }
    int npt = 0;
    double wvn = 0;
    double wvne = 0;
    double w = 0;
    for (int i = 1; i<=xpt->GetNbinsX(); i++) {
        double pt = xpt->GetBinContent(i);
        if (sp->GetBinContent(i)<10) break;
        if (pt>=0.3 && pt<12.) {
            x[npt] = pt;
            y[npt] = vn->GetBinContent(i);
            yA[npt] = vnA->GetBinContent(i);
            yB[npt] = vnB->GetBinContent(i);
            ex[npt] = 0;
            ey[npt] = vn->GetBinError(i);
            eyA[npt] = vnA->GetBinError(i);
            eyB[npt] = vnB->GetBinError(i);
            xspec[npt] = pt;
            yspec[npt] = sp->GetBinContent(i)/sp->GetBinWidth(i)/(etamax-etamin)/centcnt;
            exspec[npt] = 0;
            eyspec[npt] = 0;
            if (sp->GetBinContent(i)>1) eyspec[npt] = sqrt(sp->GetBinContent(i))/sp->GetBinWidth(i)/(etamax-etamin)/centcnt;
            if (pt<3.) {
                double eff = 0;
                double cent = (cmin[cbin] + cmax[cbin])/2.;

                double fake = FakeAndEffPt(cent,pt,eff);
                wvn  += y[npt]*yld->GetBinContent(i)/eff;
                wvne += ey[npt]*yld->GetBinContent(i)/eff;
                w    += yld->GetBinContent(i)/eff;;
            }
            ++npt;
        }
    }
    vint = wvn/w;
    vinte = wvne/w;
    cout<<"INTEGRAL (Pt): "<<vint<<"\t"<<vinte<<endl;

    TGraphErrors * g = new TGraphErrors(npt, x, y, ex, ey);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlue);
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    gspec = new TGraphErrors(npt, xspec, yspec, exspec, eyspec);
    gspec->SetMarkerStyle(20);
    gspec->SetMarkerColor(kBlue);
    gspec->SetLineColor(kBlue);
    gspec->SetLineWidth(2);
    gA = new TGraphErrors(npt, x, yA, ex, eyA);
    gA->SetMarkerStyle(28);
    gA->SetMarkerColor(kMagenta);
    gA->SetLineColor(kMagenta);
    gA->SetLineWidth(2);
    gB = new TGraphErrors(npt,x,yB,ex,eyB);
    gB->SetMarkerStyle(28);
    gB->SetMarkerColor(kCyan+2);
    gB->SetLineColor(kCyan+2);
    gB->SetLineWidth(2);
    return g;

}


TH1D * h = 0;
void GetVNCreate( int replay = N1SUB3, int cbin = 0, bool NumOnly = false, bool DenomOnly = false ) {

    TH1D * hspec = 0;
    FILE * ftest;

    if ((ftest = fopen(Form("%s/%s",FigDir.data(),AnalNames[replay].data()),"r")) == NULL) {
        system(Form("mkdir %s/%s",FigDir.data(),AnalNames[replay].data()));
    } else {
        fclose(ftest);
    }

    if ((ftest = fopen(Form("%s/%s/data",FigDir.data(),AnalNames[replay].data()),"r")) == NULL) {
        system(Form("mkdir %s/%s/data",FigDir.data(),AnalNames[replay].data()));
    } else {
        fclose(ftest);
    }
    system(Form("touch %s/%s/data/pT_integral.dat",FigDir.data(),AnalNames[replay].data()));
    soutint = Form("%s/%s/data/pT_integral.dat",FigDir.data(),AnalNames[replay].data());

    string cname = "pT_"+AnalNames[replay]+"_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin]);
    TString subtest = AnalNames[replay];

    TCanvas * c = new TCanvas(cname.data(),cname.data(),650,500);

    h = new TH1D("h", "h", 100, 0, 12.);
    h->SetDirectory(0);
    h->SetMinimum(-0.05);
    h->SetMaximum(0.5);
    double vint = 0;
    double vinte = 0;
    double vintdenom = 0;
    double vintedenom = 0;
    double resA[ncbins];
    double resB[ncbins];
    double resAdenom[ncbins];
    double resBdenom[ncbins];
    if (replay==N112ASUB2 || replay==N112ASUB3) {
        hdenom = GetVNPt( N2SUB3, cbin, EtaMin, EtaMax, hAdenom, hBdenom, nwspec2, resAdenom, resBdenom, vintdenom, vintedenom, false );
        fin->Close();
        fin = new TFile(rootFile.data(),"r");
        hpt = GetVNPt( N112ASUB3, cbin, EtaMin, EtaMax, hA, hB, nwspec, resA, resB, vint, vinte, false );
        double res = (resAdenom[0]+resBdenom[0])/2.;
        for (int i = 0; i<hpt->GetN(); i++) {
            double ef = hpt->GetEY()[i]/hpt->GetY()[i];
            hpt->GetY()[i]/=res;
            hpt->GetEY()[i]/=res;

            ef = hA->GetEY()[i]/hA->GetY()[i];
            hA->GetY()[i]/=resBdenom[0];
            hA->GetEY()[i]/=resBdenom[0];

            ef = hB->GetEY()[i]/hB->GetY()[i];
            hB->GetY()[i]/=resAdenom[0];
            hB->GetEY()[i]/=resAdenom[0];
        }

    } else if (replay==N123ASUB2 || replay==N123ASUB3) {
        hdenom = GetVNPt( N3SUB3, cbin, EtaMin, EtaMax, hAdenom, hBdenom, nwspec2, resAdenom, resBdenom, vintdenom, vintedenom, false );
        fin->Close();
        fin = new TFile(rootFile.data(),"r");
        hpt = GetVNPt( N123ASUB3, cbin, EtaMin, EtaMax, hA, hB, nwspec, resA, resB, vint, vinte, false);
        double res = (resAdenom[0]+resBdenom[0])/2.;
        for (int i = 0; i<hpt->GetN(); i++) {
            double ef = hpt->GetEY()[i]/hpt->GetY()[i];
            hpt->GetY()[i]/=res;
            hpt->GetEY()[i]/=res;

            ef = hA->GetEY()[i]/hA->GetY()[i];
            hA->GetY()[i]/=resBdenom[0];
            hA->GetEY()[i]/=resBdenom[0];

            ef = hB->GetEY()[i]/hB->GetY()[i];
            hB->GetY()[i]/=resAdenom[0];
            hB->GetEY()[i]/=resAdenom[0];
        }
    } else {
        hpt = GetVNPt( replay, cbin, EtaMin, EtaMax, hA, hB, nwspec, resA, resB, vint, vinte);
    }
    outint = fopen(soutint.data(),"a+");

    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[cbin],cmax[cbin],vint,vinte);
    fclose(outint);
    double ymax = -1;
    double ymin = 1;
    double ymaxspec = 0;
    for (int n = 0; n<hpt->GetN(); n++) {
        if (hpt->GetX()[n]>4) break;
        if (hpt->GetY()[n]+hpt->GetEY()[n]>ymax) ymax = hpt->GetY()[n]+hpt->GetEY()[n];
        if (hpt->GetY()[n]-hpt->GetEY()[n]<ymin) ymin = hpt->GetY()[n]-hpt->GetEY()[n];
        if (hA->GetY()[n]+hA->GetEY()[n]>ymax)   ymax = hA->GetY()[n]+hA->GetEY()[n];
        if (hA->GetY()[n]-hA->GetEY()[n]<ymin)   ymin = hA->GetY()[n]-hA->GetEY()[n];
        if (hB->GetY()[n]+hB->GetEY()[n]>ymax)   ymax = hB->GetY()[n]+hB->GetEY()[n];
        if (hB->GetY()[n]-hB->GetEY()[n]<ymin)   ymin = hB->GetY()[n]-hB->GetEY()[n];

        if (nwspec->GetY()[n]+nwspec->GetEY()[n]>ymaxspec) ymaxspec = nwspec->GetY()[n]+nwspec->GetEY()[n];
    }

    if (ymax<0.0002) {
        ymax = 0.0002;
    } else if (ymax<0.004) {
        ymax = 0.001;
    } else if (ymax<0.01) {
        ymax = 0.02;
    } else if (ymax<0.02) {
        ymax = 0.03;
    } else if (ymax<0.05) {
        ymax = 0.07;
    } else if (ymax<0.1) {
        ymax = 0.2;
    } else if (ymax<0.3) {
        ymax = 0.4;
    } else if (ymax<0.8) {
        ymax = 1.0;
    } else if (ymax < 2.) {
        ymax = 2.0;
    } else {
        ymax = 10;
    }

    if (ymin>0) {
        ymin=0;
    } else if (ymin>-0.003) {
        ymin=-0.006;
    } else if (ymin>-0.005) {
        ymin=-0.01;
    } else if (ymin>-0.01) {
        ymin=-0.015;
    } else if (ymin>-0.02) {
        ymin = -0.025;
    } else if (ymin>-0.04) {
        ymin = -0.05;
    } else if (ymin>-0.1) {
        ymin = -0.125;
    } else if (ymin>-0.2) {
        ymin = -0.225;
    } else if (ymin>-0.4) {
        ymin = -0.425;
    } else if( ymin>-0.8) {
        ymin = -0.8;
    } else if( ymin > -2) {
        ymin = -2.2;
    } else {
        ymin =-1;
    }
    h->SetMinimum(ymin);
    h->SetMaximum(ymax);
    gPad->SetGrid(1,1);
    h->Draw();
    h->SetXTitle("P_{T} (GeV/c)");
    string numdenom = "";
    if (NumOnly) numdenom = " (Numerator) ";
    if (DenomOnly) numdenom = " (Denominator) ";
    string yt = ytitle[replay]+numdenom+" ("+to_string(cmin[cbin])+" - "+to_string(cmax[cbin])+"%)";
    h->SetYTitle(yt.data());
    hpt->Draw("p");
    string prevname = "";
    string shengquan = "";
    if (ANAL==N2SUB3 || ANAL==N2SUB2) {
        prevname = Form("data/EP_10_002_PtDists/v2_pt_ep_cen%d_%d_eta08.txt",cmin[cbin],cmax[cbin]);
        if(cmin[cbin]<=50) shengquan = Form("data/forSteveNov11/v22_%d_%d.txt",cmin[cbin],cmax[cbin]);
    }
    if (ANAL==N3SUB3 || ANAL==N3SUB2) prevname = Form("data/hin_11_005_data/EPResults/PtDists/v3_%d_%d.txt",cmin[cbin],cmax[cbin]);
    TLegend * leg = new TLegend(0.65, 0.65, 0.9, 0.9);
    leg->SetTextFont(43);
    leg->SetTextSize(20);
    leg->SetFillColor(kWhite);
    leg->SetBorderSize(0);
    leg->AddEntry(hpt,AnalNames[replay].data(),"lp");
    if (subtest.Contains("MC")) {
        leg->AddEntry(hA,"track+ only","lp");
        leg->AddEntry(hB,"track- only","lp");
    } else {
        leg->AddEntry(hA,"HF+ only","lp");
        leg->AddEntry(hB,"HF- only","lp");
    }
    if (prevname.length()>1 && cbin<11) {
        double x[40];
        double y[40];
        double stat[40];
        double sys[40];
        FILE * fin = fopen(prevname.data(),"r");
        char buf[80];
        int n = 0;
        while (fgets(buf,80,fin)!=NULL) {
            sscanf(buf,"%lf\t%lf\t%lf\t%lf",&x[n],&y[n],&stat[n],&sys[n]);
            ++n;
        }
        TGraphErrors * gold = new TGraphErrors(n,x,y,0,stat);
        gold->SetMarkerStyle(25);
        gold->SetMarkerColor(kRed);
        gold->SetLineColor(kRed);
        gold->Draw("p");
        leg->AddEntry(gold,"CMS Published","lp");
    }

    if (shengquan.length()>1 && cbin<11) {
        double x[40];
        double y[40];
        double stat[40];
        double sys[40];
        FILE * fin = fopen(shengquan.data(),"r");
        char buf[80];
        int n = 0;
        while (fgets(buf,80,fin)!=NULL) {
            sscanf(buf,"%lf\t%lf\t%lf",&x[n],&y[n],&stat[n]);
            x[n]+=0.05;
            ++n;
        }
        TGraphErrors * sheng = new TGraphErrors(n,x,y,0,stat);
        sheng->SetMarkerStyle(24);
        sheng->SetMarkerColor(kGreen+2);
        sheng->SetLineColor(kGreen+2);
        sheng->Draw("p");
        leg->AddEntry(sheng,"Shengquan (offset)","lp");
    }
    leg->Draw();
    hA->Draw("p");
    hB->Draw("p");
    hpt->Draw("p");
    TLatex * text = new TLatex(1,0.87*ymax,AnalNames[replay].data());
    text->SetTextFont(43);
    text->SetTextSize(28);
    text->Draw();
    TLatex * t2 = new TLatex(1,0.77*ymax,Form("%d - %d%c",cmin[cbin],cmax[cbin],'%'));
    t2->SetTextFont(43);
    t2->SetTextSize(22);
    t2->Draw();
    TLatex * t3 = new TLatex(0.8,0.67*ymax,Form("%4.1f < #eta < %4.1f",EtaMin,EtaMax));
    t3->SetTextFont(43);
    t3->SetTextSize(22);
    t3->Draw();
    FILE * fout;
    if (isTight) {
        c->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),cname.data()),"png");
        fout = fopen(Form("%s/%s/data/%s.dat",FigDir.data(),AnalNames[replay].data(),cname.data()),"w");
    } else {
        c->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),cname.data()),"png");
        fout = fopen(Form("%s/%s/data/%s.dat",FigDir.data(),AnalNames[replay].data(),cname.data()),"w");
    }
    for(int i = 0; i<hpt->GetN(); i++){
        fprintf(fout,"%5.3f\t%9.7f\t%9.7f\n",hpt->GetX()[i],hpt->GetY()[i],hpt->GetEY()[i]);
    }
    fclose(fout);
    bool drawSpec = true;
    if (drawSpec){
        string c2name = "pT_c2_"+AnalNames[replay]+"_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin]);
        TCanvas * c2 = new TCanvas(c2name.data(),c2name.data(),700,500);
        hspec = new TH1D("hspec", "hspec", 600, 0, 12);
        hspec->SetDirectory(0);
        hspec->SetMaximum(100*pow(10.,(double)((int) TMath::Log10(ymaxspec))));
        hspec->SetMinimum(0.00001);
        c2->cd();
        gPad->SetLogy();
        hspec->Draw();
        hspec->SetXTitle("p_{T} (GeV/c)");
        hspec->SetYTitle("1/(N_{ev}) d^{2}N/dp_{T}d#eta");
        nwspec->Draw("p");
        double ym = hspec->GetMaximum();
        TLatex * t4 = new TLatex(8,0.1*ym,AnalNames[replay].data());
        t4->SetTextFont(43);
        t4->SetTextSize(28);
        t4->Draw();
        TLatex * t6 = new TLatex(8,0.02*ym,Form("%d - %d%c",cmin[cbin],cmax[cbin],'%'));
        t6->SetTextFont(43);
        t6->SetTextSize(22);
        t6->Draw();
        TLatex * t7 = new TLatex(7.8,0.004*ym,Form("%4.1f < #eta < %4.1f",EtaMin,EtaMax));
        t7->SetTextFont(43);
        t7->SetTextSize(22);
        t7->Draw();
        if (isTight) {
            c2->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),c2name.data()),"png");
            sspec = FigDir+"/"+AnalNames[replay]+"/data/pT_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
        } else {
            c2->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),c2name.data()),"png");
            sspec = FigDir+"/"+AnalNames[replay]+"/pT_data/spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
        }
    }
    if (isTight) {
        sspec = FigDir+"/"+AnalNames[replay]+"/data/pT_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
    } else {
        sspec = FigDir+"/"+AnalNames[replay]+"/data/pT_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
    }
    outspec = fopen(sspec.data(),"w");
    for (int i = 0; i<nwspec->GetN(); i++) fprintf(outspec,"%7.2f\t%12.5f\t%12.5f\n",nwspec->GetX()[i],nwspec->GetY()[i],nwspec->GetEY()[i]);

}


TH1D * vnA;
TH1D * vnB;
TH1D * vnAB;
void GetVNIntPt( string name="N1SUB3", string tag="useTight", double mineta = -2.4, double maxeta = 2.4, bool override = false ) {
    bool found = false;
    centRef = new TH1I("centRef", "centRef", 11, centRefBins);
    EtaMin = mineta;
    EtaMax = maxeta;
    stag = "_"+tag+"_"+Form("%0.1f_%0.1f",EtaMin,EtaMax);
    rootFile = "";
    if (tag == "useTight") {
        isTight = true;
        isLoose = false;
        rootFile = "../MH.root";
        fin = new TFile("../MH.root","read");
    } else {
        isTight = false;
        isLoose = true;
        rootFile = "../MH_loose.root";
        fin = new TFile("../MH_loose.root","read");
    }

    int en = 0;
    for (int indx = 0; indx<LAST; ++indx) {
        if (AnalNames[indx] == name) {
            found = true;
            en = indx;
            break;
        }
    }
    if (!found) {
        cout<<"Failed to locate analysis type"<<endl;
        return;
    }
    FILE * ftest;
    if (!fopen("figures","r")) system("mkdir figures");
    FigDir = Form("figures/figures%s",stag.data());
    FigSubDir = FigDir+"/"+name.data();
    if (fopen(FigDir.data(),"r") != NULL) {
        cout<<"Output directory "<<FigDir.data()<<" exists."<<endl;
    } else {
        system(Form("mkdir %s",FigDir.data()));
    }
    if ((ftest=fopen(FigSubDir.data(),"r")) == NULL) {
        system(Form("mkdir %s",FigSubDir.data()));
    } else {
        if (override) {
            system(Form("rm -rf %s",FigSubDir.data()));
        } else {
            cout<<"Directory "<<FigSubDir.data()<<" exists.  ABORT."<<endl;
            return;
        }
        fclose(ftest);
    }

    if (!fopen("results","r")) system("mkdir results");
    if (!fopen(Form("results/results%s",stag.data()),"r")) system(Form("mkdir results/results%s",stag.data()));
    tfout = new TFile(Form("results/results%s/%s_pt.root",stag.data(),name.data()),"recreate");
    TDirectory * tdanal = (TDirectory *) tfout->mkdir(Form("%s",name.data()));
    TDirectory * tdpt = (TDirectory *) tdanal->mkdir("VN_pt");

    for (int cbin = 0; cbin<13; cbin++) {
        GetVNCreate(en,cbin);

        TDirectory * tdcent = (TDirectory *) tdpt->mkdir(Form("%d_%d",cmin[cbin],cmax[cbin]));
        tdcent->cd();
        vnA = new TH1D("vnA", "", nptbins, ptbins);
        GraphToHist(hA, vnA);
        vnA->Write();
        vnB = new TH1D("vnB", "", nptbins, ptbins);
        GraphToHist(hB, vnB);
        vnB->Write();
        vnAB = new TH1D("vnAB", "", nptbins, ptbins);
        GraphToHist(hpt, vnAB);
        vnAB->Write();

        fin->Close();
        fin = new TFile(rootFile.data(),"read");
    }
}
