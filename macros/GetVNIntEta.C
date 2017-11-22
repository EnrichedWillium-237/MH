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
    "v_{1}\{#Psi_{1,MC} (0.0<#eta<0.4)\}",   "v_{1}\{#Psi_{1,MC} (0.4<#eta<0.8)\}",   "v_{1}\{#Psi_{1,MC} (0.8<#eta<1.2)\}",   "v_{1}\{#Psi_{1,MC} (1.2<#eta<1.6)\}",
    "v_{1}\{#Psi_{1,MC} (1.6<#eta<2.0)\}",   "v_{1}\{#Psi_{1,MC} (2.0<#eta<2.4)\}",
    "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",
    "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",
    "v_{2}\{#Psi_{2}\}",                     "v_{2}\{#Psi_{2}\}",                     "v_{3}\{#Psi_{3}\}",                     "v_{3}\{#Psi_{3}\}", "LAST"};


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

double FakeAndEff( int cent, double eta, double &eff ) {
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
    int etabin = hf->GetXaxis()->FindBin(eta);
    int ptbinmin = hf->GetYaxis()->FindBin(-2.4);
    int ptbinmax = hf->GetYaxis()->FindBin(2.39);
    double val = 0;
    eff = 0;
    for(int i = ptbinmin; i<=ptbinmax; i++) {
        val += hf->GetBinContent(i,etabin);
        eff += he->GetBinContent(i,etabin);
    }
    val/=(double)(ptbinmax-ptbinmin+1);
    eff/=(double)(ptbinmax-ptbinmin+1);
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

TGraphErrors * heta;
TGraphErrors * hdenom;
TGraphErrors * hA;
TGraphErrors * hB;
TGraphErrors * hAdenom;
TGraphErrors * hBdenom;
TGraphErrors * nwspec;
TGraphErrors * nwspec2;
string rootFile;
TGraphErrors * GetVNEta( int replay, int cbin, double ptmin, double ptmax, TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gspec, double * resA, double * resB, double &vint, double &vinte, bool nonorm = false ) {

    cout<<"========================== "<<AnalNames[replay]<<"  with cbin, ptmin, ptmax: "<<cbin<<"\t"<<ptmin<<"\t"<<ptmax<<endl;
    TH1D * hspec = 0;
    TH1D * xeta = 0;
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
    int iptmin1=0;
    int iptmax1=0;
    int iptmin2=0;
    int iptmax2=0;
    double sign = 1.;
    if (replay==N112ASUB2 || replay==N112ASUB3) sign=-1.;

    iptmin1 = qA->GetXaxis()->FindBin(ptmin);
    iptmax1 = qA->GetXaxis()->FindBin(ptmax);
    qA1 = (TH1D *) qA->ProjectionY("qA1",iptmin1,iptmax1);
    qB1 = (TH1D *) qB->ProjectionY("qB1",iptmin1,iptmax1);
    wA1 = (TH1D *) wnA->ProjectionY("wA1",iptmin1,iptmax1);
    wB1 = (TH1D *) wnB->ProjectionY("wB1",iptmin1,iptmax1);

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
        qAe1[i] = (TH1D *) qAe[i]->ProjectionY(Form("qAe1_%d",i),iptmin1,iptmax1);
        qBe1[i] = (TH1D *) qBe[i]->ProjectionY(Form("qBe1_%d",i),iptmin2,iptmax2);
        wAe1[i] = (TH1D *) wnAe[i]->ProjectionY(Form("wA1_%d",i),iptmin1,iptmax1);
        wBe1[i] = (TH1D *) wnBe[i]->ProjectionY(Form("wB1_%d",i),iptmin2,iptmax2);

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
    if (ptmin*ptmax>0) {
        xeta = (TH1D *) ptav->ProjectionY("xeta",iptmin1,iptmax1);
        double c = (cmin[cbin]+cmax[cbin])/2.;
        TH2D * hsEff = ptcntEff(ptcnt,c);

        sp = (TH1D *) hsEff->ProjectionY("sp",iptmin1,iptmax1);
        double pbinsA = iptmax1-iptmin1+1 ;
        xeta->Scale(1./pbinsA);
        sp->Scale(1./pbinsA);
        if (!rew) {
            vnA = (TH1D *) qA->ProjectionY("vnA",iptmin1,iptmax1);
            vnB = (TH1D *) qB->ProjectionY("vnB",iptmin1,iptmax1);
            vn = (TH1D *) vnA->Clone("vn");
            vn->Add(vnB,sign);
            vn->Scale(sign);
            vnA->Scale(1./pbinsA);
            vnB->Scale(1./pbinsA);
            vn->Scale(1./(pbinsA+pbinsA));
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
                vnAe = (TH1D *) qAe[i]->ProjectionY(Form("vnA%d",i),iptmin1,iptmax1);
                vnBe = (TH1D *) qBe[i]->ProjectionY(Form("vnB%d",i),iptmin1,iptmax1);
                vne = (TH1D *) vnAe->Clone(Form("vn%d",i));
                vne->Add(vnBe,sign);
                vne->Scale(sign);
                vnAe->Scale(1./pbinsA);
                vnBe->Scale(1./pbinsA);
                vne->Scale(1./(pbinsA+pbinsA));
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

    TH1D * yld = ptcnt->ProjectionY("yld",iptmin1,iptmax2);
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
    int neta = 0;
    double wvn = 0;
    double wvne = 0;
    double w = 0;
    for (int i = 1; i<=xeta->GetNbinsX(); i++) {
        double eta = xeta->GetBinCenter(i);
        if (sp->GetBinContent(i)<10) break;
        if (eta>=-2.4 && eta<2.4) {
            x[neta] = eta;
            y[neta] = vn->GetBinContent(i);
            yA[neta] = vnA->GetBinContent(i);
            yB[neta] = vnB->GetBinContent(i);
            ex[neta] = 0;
            ey[neta] = vn->GetBinError(i);
            eyA[neta] = vnA->GetBinError(i);
            eyB[neta] = vnB->GetBinError(i);
            xspec[neta] = eta;
            yspec[neta] = sp->GetBinContent(i)/sp->GetBinWidth(i)/(ptmax-ptmin)/centcnt;
            exspec[neta] = 0;
            eyspec[neta] = 0;
            if (sp->GetBinContent(i)>1) eyspec[neta] = sqrt(sp->GetBinContent(i))/sp->GetBinWidth(i)/(ptmax-ptmin)/centcnt;

            double eff = 0;
            double cent = (cmin[cbin] + cmax[cbin])/2.;
            double fake = FakeAndEff(cent,eta,eff);
            wvn  += y[neta]*yld->GetBinContent(i)/eff;
            wvne += ey[neta]*yld->GetBinContent(i)/eff;
            w    += yld->GetBinContent(i)/eff;;
            ++neta;
        }
    }
    vint = wvn/w;
    vinte = wvne/w;
    cout<<"INTEGRAL (Eta): "<<vint<<"\t"<<vinte<<endl;

    TGraphErrors * g = new TGraphErrors(neta, x, y, ex, ey);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlue);
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    gspec = new TGraphErrors(neta, xspec, yspec, exspec, eyspec);
    gspec->SetMarkerStyle(20);
    gspec->SetMarkerColor(kBlue);
    gspec->SetLineColor(kBlue);
    gspec->SetLineWidth(2);
    gA = new TGraphErrors(neta, x, yA, ex, eyA);
    gA->SetMarkerStyle(28);
    gA->SetMarkerColor(kMagenta);
    gA->SetLineColor(kMagenta);
    gA->SetLineWidth(2);
    gB = new TGraphErrors(neta,x,yB,ex,eyB);
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
    system(Form("touch %s/%s/data/eta_integral.dat",FigDir.data(),AnalNames[replay].data()));
    soutint = Form("%s/%s/data/eta_integral.dat",FigDir.data(),AnalNames[replay].data());

    string cname = "eta_"+AnalNames[replay]+"_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin]);
    TString subtest = AnalNames[replay];

    TCanvas * c = new TCanvas(cname.data(),cname.data(),650,500);
    h = new TH1D("h", "h", 100, -2.4, 2.4);
    h->SetDirectory(0);
    h->SetMinimum(-0.1);
    h->SetMaximum(0.1);
    double vint = 0;
    double vinte = 0;
    double vintdenom = 0;
    double vintedenom = 0;
    double resA[ncbins];
    double resB[ncbins];
    double resAdenom[ncbins];
    double resBdenom[ncbins];
    if (replay==N112ASUB2 || replay==N112ASUB3) {
        hdenom = GetVNEta( N2SUB3, cbin, PtMin, PtMax, hAdenom, hBdenom, nwspec2, resAdenom, resBdenom, vintdenom, vintedenom, false );
        fin->Close();
        fin = new TFile(rootFile.data(),"r");
        heta = GetVNEta( N112ASUB3, cbin, PtMin, PtMax, hA, hB, nwspec, resA, resB, vint, vinte, false );
        double res = (resAdenom[0]+resBdenom[0])/2.;
        for (int i = 0; i<heta->GetN(); i++) {
            double ef = heta->GetEY()[i]/heta->GetY()[i];
            heta->GetY()[i]/=res;
            heta->GetEY()[i]/=res;

            ef = hA->GetEY()[i]/hA->GetY()[i];
            hA->GetY()[i]/=resBdenom[0];
            hA->GetEY()[i]/=resBdenom[0];

            ef = hB->GetEY()[i]/hB->GetY()[i];
            hB->GetY()[i]/=resAdenom[0];
            hB->GetEY()[i]/=resAdenom[0];
        }

    } else if (replay==N123ASUB2 || replay==N123ASUB3) {
        hdenom = GetVNEta( N3SUB3, cbin, PtMin, PtMax, hAdenom, hBdenom, nwspec2, resAdenom, resBdenom, vintdenom, vintedenom, false );
        fin->Close();
        fin = new TFile(rootFile.data(),"r");
        heta = GetVNEta( N123ASUB3, cbin, PtMin, PtMax, hA, hB, nwspec, resA, resB, vint, vinte, false);
        double res = (resAdenom[0]+resBdenom[0])/2.;
        for (int i = 0; i<heta->GetN(); i++) {
            double ef = heta->GetEY()[i]/heta->GetY()[i];
            heta->GetY()[i]/=res;
            heta->GetEY()[i]/=res;

            ef = hA->GetEY()[i]/hA->GetY()[i];
            hA->GetY()[i]/=resBdenom[0];
            hA->GetEY()[i]/=resBdenom[0];

            ef = hB->GetEY()[i]/hB->GetY()[i];
            hB->GetY()[i]/=resAdenom[0];
            hB->GetEY()[i]/=resAdenom[0];
        }
    } else {
        heta = GetVNEta( replay, cbin, PtMin, PtMax, hA, hB, nwspec, resA, resB, vint, vinte);
    }
    outint = fopen(soutint.data(),"a+");

    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[cbin],cmax[cbin],vint,vinte);
    fclose(outint);
    double ymax = -1;
    double ymin = 1;
    double ymaxspec = 0;
    for (int n = 0; n<heta->GetN(); n++) {
        if (heta->GetX()[n]>4) break;
        if (heta->GetY()[n]+heta->GetEY()[n]>ymax) ymax = heta->GetY()[n]+heta->GetEY()[n];
        if (heta->GetY()[n]-heta->GetEY()[n]<ymin) ymin = heta->GetY()[n]-heta->GetEY()[n];
        if (hA->GetY()[n]+hA->GetEY()[n]>ymax)   ymax = hA->GetY()[n]+hA->GetEY()[n];
        if (hA->GetY()[n]-hA->GetEY()[n]<ymin)   ymin = hA->GetY()[n]-hA->GetEY()[n];
        if (hB->GetY()[n]+hB->GetEY()[n]>ymax)   ymax = hB->GetY()[n]+hB->GetEY()[n];
        if (hB->GetY()[n]-hB->GetEY()[n]<ymin)   ymin = hB->GetY()[n]-hB->GetEY()[n];

        if (nwspec->GetY()[n]+nwspec->GetEY()[n]>ymaxspec) ymaxspec = nwspec->GetY()[n]+nwspec->GetEY()[n];
    }

    if (ymax<0.0002) {
        ymax = 0.0002;
    } else if (ymax<0.004) {
        ymax = 0.01;
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
    } else if (ymin>-0.0002) {
        ymin=-0.0002;
    } else if (ymin>-0.004) {
        ymin=-0.01;
    } else if (ymin>-0.02) {
        ymin=-0.03;
    } else if (ymin>-0.05) {
        ymin = -0.07;
    } else if (ymin>-0.1) {
        ymin = -0.2;
    } else if (ymin>-0.3) {
        ymin = -0.4;
    } else if (ymin>-0.8) {
        ymin = -1.0;
    } else if (ymin>-2.) {
        ymin = -2.0;
    }
    h->SetMinimum(ymin);
    h->SetMaximum(ymax);
    gPad->SetGrid(1,1);
    h->Draw();
    h->SetXTitle("#eta");
    string numdenom = "";
    if (NumOnly) numdenom = " (Numerator) ";
    if (DenomOnly) numdenom = " (Denominator) ";
    string yt = ytitle[replay]+numdenom+" ("+to_string(cmin[cbin])+" - "+to_string(cmax[cbin])+"%)";
    h->SetYTitle(yt.data());
    heta->Draw("p");

    TLegend * leg = new TLegend(0.65, 0.65, 0.9, 0.9);
    leg->SetTextFont(43);
    leg->SetTextSize(20);
    leg->SetFillColor(kWhite);
    leg->SetBorderSize(0);
    leg->AddEntry(heta,AnalNames[replay].data(),"lp");
    if (subtest.Contains("MC")) {
        leg->AddEntry(hA,"track+ only","lp");
        leg->AddEntry(hB,"track- only","lp");
    } else {
        leg->AddEntry(hA,"HF+ only","lp");
        leg->AddEntry(hB,"HF- only","lp");
    }
    leg->Draw();
    hA->Draw("p");
    hB->Draw("p");
    heta->Draw("p");
    TLatex * text = new TLatex(1,0.87*ymax,AnalNames[replay].data());
    text->SetTextFont(43);
    text->SetTextSize(28);
    text->Draw();
    TLatex * t2 = new TLatex(1,0.77*ymax,Form("%d - %d%c",cmin[cbin],cmax[cbin],'%'));
    t2->SetTextFont(43);
    t2->SetTextSize(22);
    t2->Draw();
    TLatex * t3 = new TLatex(0.8,0.67*ymax,Form("%4.2f < p_{T} < %4.2f (GeV/c)",PtMin,PtMax));
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
    for(int i = 0; i<heta->GetN(); i++){
        fprintf(fout,"%5.3f\t%9.7f\t%9.7f\n",heta->GetX()[i],heta->GetY()[i],heta->GetEY()[i]);
    }
    fclose(fout);
    //tdcent->cd();
    // hA->SetName("vnA");
    // hA->Write();
    // hB->SetName("vnB");
    // hB->Write();
    // heta->SetName("vnComb");
    // heta->Write();
    bool drawSpec = true;
    if (drawSpec){
        string c2name = "eta_c2_"+AnalNames[replay]+"_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin]);
        TCanvas * c2Eta = new TCanvas(c2name.data(),c2name.data(),700,500);
        hspec = new TH1D("hspec", "hspec", 600, -2.4, 2.4);
        hspec->SetDirectory(0);
        hspec->SetMaximum(100*pow(10.,(double)((int) TMath::Log10(ymaxspec))));
        hspec->SetMinimum(0.00001);
        c2Eta->cd();
        gPad->SetLogy();
        hspec->Draw();
        hspec->SetXTitle("#eta");
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
        TLatex * t7 = new TLatex(7.8,0.004*ym,Form("%4.1f < p_{T} < %4.1f (GeV/c)",PtMin,PtMax));
        t7->SetTextFont(43);
        t7->SetTextSize(22);
        t7->Draw();
        if (isTight) {
            c2Eta->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),c2name.data()),"png");
            sspec = FigDir+"/"+AnalNames[replay]+"/data/eta_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
        } else {
            c2Eta->Print(Form("%s/%s/%s.png",FigDir.data(),AnalNames[replay].data(),c2name.data()),"png");
            sspec = FigDir+"/"+AnalNames[replay]+"/eta_data/spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
        }
    }
    if (isTight) {
        sspec = FigDir+"/"+AnalNames[replay]+"/data/eta_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
    } else {
        sspec = FigDir+"/"+AnalNames[replay]+"/data/eta_spec_"+to_string(cmin[cbin])+"_"+to_string(cmax[cbin])+".dat";
    }
    outspec = fopen(sspec.data(),"w");
    for (int i = 0; i<nwspec->GetN(); i++) fprintf(outspec,"%7.2f\t%12.5f\t%12.5f\n",nwspec->GetX()[i],nwspec->GetY()[i],nwspec->GetEY()[i]);
    //tfget->Close();

}


TH1D * vnA;
TH1D * vnB;
TH1D * vnAB;
void GetVNIntEta( string name="N1SUB3", string tag="useTight", double mineta = -2.4, double maxeta = 2.4, double minpt = 0.3, double maxpt = 3.0, bool override = false ) {
    bool found = false;
    centRef = new TH1I("centRef", "centRef", 11, centRefBins);
    EtaMin = mineta;
    EtaMax = maxeta;
    PtMin = minpt;
    PtMax = maxpt;
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
    if (!fopen(FigDir.data(),"r")) system(Form("mkdir %s",FigDir.data()));
    if ((ftest=fopen(FigSubDir.data(),"r")) == NULL) {
        system(Form("mkdir %s",FigSubDir.data()));
    }

    if (!fopen("results","r")) system("mkdir results");
    if (!fopen(Form("results/results%s",stag.data()),"r")) system(Form("mkdir results/results%s",stag.data()));
    tfout = new TFile(Form("results/results%s/%s_eta.root",stag.data(),name.data()),"recreate");
    TDirectory * tdanal = (TDirectory *) tfout->mkdir(Form("%s",name.data()));
    TDirectory * tdeta = (TDirectory *) tdanal->mkdir("VN_Eta");

    for (int cbin = 0; cbin<13; cbin++) {
        GetVNCreate(en,cbin);

        TDirectory * tdcent = (TDirectory *) tdeta->mkdir(Form("%d_%d",cmin[cbin],cmax[cbin]));
        tdcent->cd();
        vnA = new TH1D("vnA", "", netabins, etabins);
        GraphToHist(hA, vnA);
        vnA->Write();
        vnB = new TH1D("vnB", "", netabins, etabins);
        GraphToHist(hB, vnB);
        vnB->Write();
        vnAB = new TH1D("vnAB", "", netabins, etabins);
        GraphToHist(heta, vnAB);
        vnAB->Write();

        fin->Close();
        fin = new TFile(rootFile.data(),"read");
    }
    // tfout->Close();
}
