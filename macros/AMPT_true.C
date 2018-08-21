# include "TDirectory.h"
# include "TFile.h"
# include "TH1.h"
# include "TH2.h"
# include <iostream>

using namespace std;

static const int ncentbinsCENT = 13;
static const int centBinsCENT[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 100};
static const double centRefBinsCENT[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 100};
static const int cbinsCENT = 23;
static const int cminCENT[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70,   0, 10, 20, 30,  10, 10,  0,  40,   0, 20,   5};
static const int cmaxCENT[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80,  10, 20, 30, 40,  60, 70, 40,  80,  20, 60,  80};

TFile * fin = new TFile("../MH_AMPT.root");

TH2D * v1in[ncentbinsCENT];
TH2D * v1Cntin[ncentbinsCENT];
TH1D * v1_eta[cbinsCENT];
TH1D * v1A_pT[cbinsCENT];
TH1D * v1B_pT[cbinsCENT];
TH1D * v1_pT[cbinsCENT];
double pmin = 0.3;
double pmax = 3.0;
double emin = 1.2;
double emax = 1.6;

void AMPT_true() {

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TFile * fout = new TFile("vnAMPT_true.root","recreate");

    int ietaminA = 0;
    int ietamaxA = 0;
    int ietaminB = 0;
    int ietamaxB = 0;
    int iptmin = 0;
    int iptmax = 0;
    for (int cbin = 0; cbin<ncentbinsCENT; cbin++) {

        TDirectory * dir = (TDirectory *) fout->mkdir(Form("%d_%d",centBinsCENT[cbin],centBinsCENT[cbin+1]));
        dir->cd();

        v1in[cbin] = (TH2D *) fin->Get(Form("vnanalyzer/MC/%d_%d/v1",centBinsCENT[cbin],centBinsCENT[cbin+1]));
        v1Cntin[cbin] = (TH2D *) fin->Get(Form("vnanalyzer/MC/%d_%d/vnCntMC",centBinsCENT[cbin],centBinsCENT[cbin+1]));
        v1in[cbin]->Divide(v1Cntin[cbin]);

        ietaminA = v1in[cbin]->GetYaxis()->FindBin(emin+0.001);
        ietamaxA = v1in[cbin]->GetYaxis()->FindBin(emax-0.001);
        ietaminB = v1in[cbin]->GetYaxis()->FindBin(-1.*emax+0.001);
        ietamaxB = v1in[cbin]->GetYaxis()->FindBin(-1.*emin-0.001);
        // cout<<"cbin: "<<cbin<<"\temin: "<<emin<<"\tietaminA: "<<ietaminA<<"\temax: "<<emax<<"\tietamaxA: "<<ietamaxA<<endl;
        v1A_pT[cbin] = (TH1D *) v1in[cbin]->ProjectionX("v1A",ietaminA,ietamaxA);
        v1B_pT[cbin] = (TH1D *) v1in[cbin]->ProjectionX("v1B",ietaminB,ietamaxB);
        v1_pT[cbin] = (TH1D *) v1B_pT[cbin]->Clone("v1_pT");
        v1_pT[cbin]->Add(v1A_pT[cbin],-1);
        v1_pT[cbin]->Scale(0.5);

        iptmin = v1in[cbin]->GetXaxis()->FindBin(pmin+0.001);
        iptmax = v1in[cbin]->GetXaxis()->FindBin(pmax-0.001);
        // cout<<"cbin: "<<cbin<<"\tpmin: "<<pmin<<"\tiptmin: "<<iptmin<<"\tpmax: "<<pmax<<"\tiptmax: "<<iptmax<<endl;
        v1_eta[cbin] = (TH1D *) v1in[cbin]->ProjectionY("v1_eta",iptmin,iptmax);
        v1_eta[cbin]->Scale(-1./(iptmax-iptmin));

        v1_pT[cbin]->Write();
        v1_eta[cbin]->Write();
    }

    TDirectory * dir0_20 = (TDirectory *) fout->mkdir("0_20");
    dir0_20->cd();
    int x0_20 = ncentbinsCENT+1;
    v1_pT[x0_20] = (TH1D *) v1_pT[0]->Clone("v1_pT");
    v1_eta[x0_20] = (TH1D *) v1_eta[0]->Clone("v1_eta");
    for (int x = 1; x<5; x++) {
        v1_pT[x0_20]->Add(v1_pT[x]);
        v1_eta[x0_20]->Add(v1_eta[x]);
    }
    v1_pT[x0_20]->Scale(1./5);
    v1_pT[x0_20]->Write();
    v1_eta[x0_20]->Scale(1./5);
    v1_eta[x0_20]->Write();

    TDirectory * dir20_60 = (TDirectory *) fout->mkdir("20_60");
    dir20_60->cd();
    int x20_60 = ncentbinsCENT+2;
    v1_pT[x20_60] = (TH1D *) v1_pT[5]->Clone("v1_pT");
    v1_eta[x20_60] = (TH1D *) v1_eta[5]->Clone("v1_eta");
    for (int x = 5; x<11; x++) {
        v1_pT[x20_60]->Add(v1_pT[x]);
        v1_eta[x20_60]->Add(v1_eta[x]);
    }
    v1_pT[x20_60]->Scale(1./6);
    v1_pT[x20_60]->Write();
    v1_eta[x20_60]->Scale(1./6);
    v1_eta[x20_60]->Write();

}
