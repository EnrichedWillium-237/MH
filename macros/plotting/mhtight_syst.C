# include "TCanvas.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

using namespace std;
bool gridlines = true;
# include "style.h"

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
string FigDir = "";
string FigSubDir = "";
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

TFile * tfin;
string infile = "";
string ctag = "";
bool isLoose = false;
bool isTight = false;
TH1D * centbins;

//  track cut, analysis type, centbin, etabin
TH1D * vnA[3][nanals][ncbins][netabins];
TH1D * vnB[3][nanals][ncbins][netabins];
TH1D * vnAB[3][nanals][ncbins][netabins];

void mhtight_syst()
{

    TH1::SetDefaultSumw2();

    for (int ebin = 0; ebin<netabins; ebin++) {
        infile = "../results/results_useTight_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            if (anal == 0 || anal == 6 || anal == 15 || anal == 16 || anal == 18) {
                tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
                for (int cbin = 0; cbin<ncbins-1; cbin++) {
                    ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                    vnA[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                    vnB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                    vnAB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));

                    vnA[0][anal][cbin][ebin]->SetMarkerColor(kCyan+2);
                    vnA[0][anal][cbin][ebin]->SetLineColor(kCyan+2);
                    vnA[0][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnA[0][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnB[0][anal][cbin][ebin]->SetMarkerColor(kMagenta);
                    vnB[0][anal][cbin][ebin]->SetLineColor(kMagenta);
                    vnB[0][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnB[0][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnAB[0][anal][cbin][ebin]->SetMarkerColor(kBlue);
                    vnAB[0][anal][cbin][ebin]->SetLineColor(kBlue);
                    vnAB[0][anal][cbin][ebin]->SetMarkerStyle(21);
                    vnAB[0][anal][cbin][ebin]->SetMarkerSize(1.1);
                }
            }
        }
    }

    for (int ebin = 0; ebin<netabins; ebin++) {
        infile = "../results/results_useTight2_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            if (anal == 0 || anal == 6 || anal == 15 || anal == 16 || anal == 18) {
                tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
                for (int cbin = 0; cbin<ncbins-1; cbin++) {
                    ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                    vnA[1][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                    vnB[1][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                    vnAB[1][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));

                    vnA[1][anal][cbin][ebin]->SetMarkerColor(kCyan+2);
                    vnA[1][anal][cbin][ebin]->SetLineColor(kCyan+2);
                    vnA[1][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnA[1][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnB[1][anal][cbin][ebin]->SetMarkerColor(kMagenta);
                    vnB[1][anal][cbin][ebin]->SetLineColor(kMagenta);
                    vnB[1][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnB[1][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnAB[1][anal][cbin][ebin]->SetMarkerColor(kBlue);
                    vnAB[1][anal][cbin][ebin]->SetLineColor(kBlue);
                    vnAB[1][anal][cbin][ebin]->SetMarkerStyle(21);
                    vnAB[1][anal][cbin][ebin]->SetMarkerSize(1.1);
                }
            }
        }
    }

    for (int ebin = 0; ebin<netabins; ebin++) {
        infile = "../results/results_useLoose_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            if (anal == 0 || anal == 6 || anal == 15 || anal == 16 || anal == 18) {
                tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
                for (int cbin = 0; cbin<ncbins-1; cbin++) {
                    ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                    vnA[2][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                    vnB[2][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                    vnAB[2][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));

                    vnA[2][anal][cbin][ebin]->SetMarkerColor(kCyan+2);
                    vnA[2][anal][cbin][ebin]->SetLineColor(kCyan+2);
                    vnA[2][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnA[2][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnB[2][anal][cbin][ebin]->SetMarkerColor(kMagenta);
                    vnB[2][anal][cbin][ebin]->SetLineColor(kMagenta);
                    vnB[2][anal][cbin][ebin]->SetMarkerStyle(28);
                    vnB[2][anal][cbin][ebin]->SetMarkerSize(1.2);

                    vnAB[2][anal][cbin][ebin]->SetMarkerColor(kBlue);
                    vnAB[2][anal][cbin][ebin]->SetLineColor(kBlue);
                    vnAB[2][anal][cbin][ebin]->SetMarkerStyle(21);
                    vnAB[2][anal][cbin][ebin]->SetMarkerSize(1.1);
                }
            }
        }
    }


    //-- make plots

    TCanvas * c0 = new TCanvas("c0","c0",1200,800);
    c0->Divide(4,3);
    TH1D * h0 = new TH1D("h0", "h0", 50, 0, 12);
    h0->SetXTitle("p_{T} (GeV/c");
    h0->SetYTitle("v_{1}^{even}");
    h0->GetYaxis()->SetNdivisions(509);
    h0->GetYaxis()->SetRangeUser(-0.05, 0.15);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * pad0 = (TPad *) c0->cd(ebin+1);
        if (gridlines) pad0->SetGrid();
        h0->Draw();
        if (ebin<6) {
            vnA[2][N1MCp22SUB3][0][ebin]->SetMarkerColor(kGreen+3);
            vnA[2][N1MCp22SUB3][0][ebin]->SetLineColor(kGreen+3);
            vnA[2][N1MCp22SUB3][0][ebin]->Draw("same");
            vnA[1][N1MCp22SUB3][0][ebin]->SetMarkerColor(kRed);
            vnA[1][N1MCp22SUB3][0][ebin]->SetLineColor(kRed);
            vnA[1][N1MCp22SUB3][0][ebin]->Draw("same");
        } else {
            vnA[2][N1MCm22SUB3][0][ebin]->SetMarkerColor(kGreen+3);
            vnA[2][N1MCm22SUB3][0][ebin]->SetLineColor(kGreen+3);
            vnA[2][N1MCm22SUB3][0][ebin]->Draw("same");
            vnA[1][N1MCm22SUB3][0][ebin]->SetMarkerColor(kRed);
            vnA[1][N1MCm22SUB3][0][ebin]->SetLineColor(kRed);
            vnA[1][N1MCm22SUB3][0][ebin]->Draw("same");
        }
        TPaveText * tx0 = new TPaveText(0.51, 0.19, 0.94, 0.29, "NDC");
        SetTPaveTxt(tx0, 18);
        tx0->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        tx0->Draw();
    }
    c0->cd(1);
    TPaveText * txCent0 = new TPaveText(0.77, 0.81, 0.87, 0.91, "NDC");
    SetTPaveTxt(txCent0, 18);
    txCent0->AddText(Form("%d-%d%%",centBins[0],centBins[0+1]));
    txCent0->Draw();

    c0->cd(2);
    TLegend * leg0 = new TLegend(0.66, 0.71, 0.93, 0.91);
    SetLegend(leg0, 18);
    leg0->AddEntry(vnA[1][N1MCp22SUB3][0][0], "Tight2", "lp");
    leg0->AddEntry(vnA[2][N1MCp22SUB3][0][7], "Loose", "lp");
    leg0->Draw();

    c0->Print("c0.png","png");




    TCanvas * c1 = new TCanvas("c1","c1",1200,800);
    c1->Divide(4,3);
    TH1D * h1 = new TH1D("h1", "h1", 50, 0, 12);
    h1->SetXTitle("p_{T} (GeV/c");
    h1->SetYTitle("v_{1}^{even}");
    h1->GetYaxis()->SetNdivisions(509);
    h1->GetYaxis()->SetRangeUser(-0.15, 0.15);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * pad1 = (TPad *) c1->cd(ebin+1);
        if (gridlines) pad1->SetGrid();
        h1->Draw();
        vnAB[2][N1SUB2][0][ebin]->SetMarkerColor(kGreen+3);
        vnAB[2][N1SUB2][0][ebin]->SetLineColor(kGreen+3);
        vnAB[2][N1SUB2][0][ebin]->Draw("same");
        vnAB[1][N1SUB2][0][ebin]->SetMarkerColor(kRed);
        vnAB[1][N1SUB2][0][ebin]->SetLineColor(kRed);
        vnAB[1][N1SUB2][0][ebin]->Draw("same");
        TPaveText * tx1 = new TPaveText(0.51, 0.19, 0.94, 0.29, "NDC");
        SetTPaveTxt(tx1, 18);
        tx1->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        tx1->Draw();
    }
    c1->cd(1);
    TPaveText * txCent1 = new TPaveText(0.77, 0.81, 0.87, 0.91, "NDC");
    SetTPaveTxt(txCent1, 18);
    txCent1->AddText(Form("%d-%d%%",centBins[0],centBins[0+1]));
    txCent1->Draw();

    c1->cd(2);
    TLegend * leg1 = new TLegend(0.66, 0.71, 0.93, 0.91);
    SetLegend(leg1, 18);
    leg1->AddEntry(vnAB[1][N1SUB2][0][0], "Tight2", "lp");
    leg1->AddEntry(vnAB[2][N1SUB2][0][7], "Loose", "lp");
    leg1->Draw();

    c1->Print("c1.png","png");




    //-- calculate percent error for systematics
    // TH1D * hevenSyst = (TH1D *) vnA[0][N1MCm22SUB3][0][ebin]->Clone("hevenSyst");
    // hevenSyst->SetMarkerColor(kBlue);
    // hevenSyst->SetLineColor(kBlue);
    // double v1evenSystval;
    // double v1evenSystval1;
    // for (int ebin = 0; ebin<netabins; ebin++) {
    //     for (int pbin = 0; pbin<nptbins; pbin++) {
    //         v1evenSystval = vnA[1][N1MCm22SUB3][0][ebin]->GetBinContent(ebin+1);
    //         v1evenSystval1 = vnA[2][N1MCm22SUB3][0][ebin]->GetBinContent(ebin+1);
    //         double D = fabs(v1evenSystval - v1evenSystval1|/|v1evenSystval + v1evenSystval1|);
    //         double delEven = D * vnA[0][N1MCm22SUB3][0][ebin]->GetBinContent(ebin+1);
    //     }
    // }

    TCanvas * cSytOdd = new TCanvas("cSytOdd","cSytOdd",1200,800);
    cSytOdd->Divide(4,3);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * padSytOdd = (TPad *) cSytOdd->cd(ebin+1);
        if (gridlines) padSytOdd->SetGrid();
        TH1D * hoddv1 = (TH1D *) vnAB[0][N1SUB2][0][ebin]->Clone(Form("hoddv1_%d",ebin));
        hoddv1->GetYaxis()->SetRangeUser(-0.05, 0.05);
        hoddv1->Draw();
    }



}
