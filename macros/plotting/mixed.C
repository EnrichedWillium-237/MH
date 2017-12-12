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

//  track cut, analysis type, centbin
TH1D * vnA[3][nanals][ncbins];
TH1D * vnB[3][nanals][ncbins];
TH1D * vnAB[3][nanals][ncbins];

TH1D * vnAmix[3][nanals][ncbins];
TH1D * vnBmix[3][nanals][ncbins];
TH1D * vnABmix[3][nanals][ncbins];

void mixed()
{

    bool processAll = false; // make true if you want to process the full data set

    for (int i = 0; i<3; i++) {
        for (int anal = 0; anal<nanals; anal++) {
            for (int cbin = 0; cbin<ncbins-1; cbin++) {
                string tcut = "";
                if (i == 0) tcut = "useTight";
                else if (i == 1) tcut = "useTightB";
                else tcut = "useLoose";
                string htag = Form("_%s_%s_%d_%d",AnalNames[anal].data(),tcut.data(),cmin[cbin],cmax[cbin]);
                vnA[i][anal][cbin] = new TH1D(Form("vnA_%s",htag.data()), "", netabins, etabins);
                vnB[i][anal][cbin] = new TH1D(Form("vnB_%s",htag.data()), "", netabins, etabins);
                vnAB[i][anal][cbin] = new TH1D(Form("vnAB_%s",htag.data()), "", netabins, etabins);
            }
        }
    }

    string prevname = "";

    int ctest = 6;

    string tcut = "";
    for (int i = 0; i<1; i++) {
        if (i == 0) tcut = "useTight";
        else if (i == 1) tcut = "useTightB";
        else tcut = "useLoose";
        for (int anal = 12; anal<18; anal++) {
            for (int ebin = 0; ebin<netabins; ebin++) {
                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integral.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                        vnAB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnAB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        ++cbin;
                    }
                    fclose(fin);
                }

                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integralA.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                        vnA[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnA[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        ++cbin;
                    }
                    fclose(fin);
                }

                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integralB.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                        vnB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        ++cbin;
                    }
                    fclose(fin);
                }
            }
        }
    }

    //-- get int pT
    for (int anal = 0; anal<nanals; anal++) {
        TFile * tfinmix = new TFile("../results/results_useTight_-2.4_2.4/%s.root",AnalNames[anal].data(),"read");
        for (int cbin = 0; cbin<ncentbins; cbin++) {
            vnAmix[0][anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[cbin],cmax[cbin]));
            vnBmix[0][anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[cbin],cmax[cbin]));
            vnABmix[0][anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
            cout<<vnAmix[0][anal][cbin]<<endl;
        }

    }


    TCanvas * c0 = new TCanvas("c0","c0",650,600);
    TPad * pad0 = (TPad *) c0->cd();
    pad0->SetGrid();
    vnAB[0][13][ctest]->SetMarkerColor(kRed);
    vnAB[0][13][ctest]->SetLineColor(kRed);
    vnAB[0][13][ctest]->SetMarkerStyle(28);
    vnAB[0][13][ctest]->SetMarkerSize(1.4);
    vnAB[0][13][ctest]->SetXTitle("#eta");
    vnAB[0][13][ctest]->SetYTitle("v_{1}");
    vnAB[0][13][ctest]->GetYaxis()->SetRangeUser(-0.015, 0.015);
    vnAB[0][13][ctest]->Draw();

    vnAB[0][16][ctest]->SetMarkerColor(kBlue);
    vnAB[0][16][ctest]->SetLineColor(kBlue);
    vnAB[0][16][ctest]->SetMarkerStyle(21);
    vnAB[0][16][ctest]->SetMarkerSize(1.2);
    vnAB[0][16][ctest]->Draw("same");

    vnAB[0][15][ctest]->SetMarkerColor(kGreen+2);
    vnAB[0][15][ctest]->SetLineColor(kGreen+2);
    vnAB[0][15][ctest]->SetMarkerStyle(28);
    vnAB[0][15][ctest]->SetMarkerSize(1.4);
    vnAB[0][15][ctest]->Draw("same");

    TLine * ltest = new TLine(-2.4, 0, 2.4, 0);
    ltest->Draw();
    TPaveText * tx0 = new TPaveText(0.66, 0.81, 0.92, 0.92, "NDC");
    SetTPaveTxt(tx0, 18);
    tx0->AddText(Form("%d-%d%%",cmin[ctest],cmax[ctest]));
    tx0->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();
    TLegend * leg0 = new TLegend(0.66, 0.67, 0.85, 0.81);
    SetLegend(leg0, 18);
    leg0->AddEntry(vnAB[0][16][ctest],"N1SUB2","p");
    leg0->AddEntry(vnAB[0][13][ctest],"N112SUB3","p");
    leg0->AddEntry(vnAB[0][15][ctest],"N123SUB3","p");
    leg0->Draw();
    c0->Print("vmix0.png","png");



    TCanvas * c0_zoom = new TCanvas("c0_zoom","c0_zoom",650,600);
    TPad * pad0_zoom = (TPad *) c0_zoom->cd();
    pad0_zoom->SetGrid();
    vnAB[0][13][ctest]->GetYaxis()->SetRangeUser(-0.0003, 0.0003);
    vnAB[0][13][ctest]->Draw();
    vnAB[0][16][ctest]->Draw("same");
    vnAB[0][15][ctest]->Draw("same");
    ltest->Draw();
    tx0->Draw();
    leg0->Draw();
    c0_zoom->Print("vmix0_zoom.png","png");



    TCanvas *



}
