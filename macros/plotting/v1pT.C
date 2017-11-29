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
TH1D * vnA[2][nanals][ncbins][netabins];
TH1D * vnB[2][nanals][ncbins][netabins];
TH1D * vnAB[2][nanals][ncbins][netabins];

void v1pT()
{

    TH1::SetDefaultSumw2();
    bool processAll = false; // make true if you want to process the full data set

    for (int ebin = 0; ebin<netabins; ebin++) {
        infile = "../results/results_useTight_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            if (!processAll) {
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
            } else {
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
        infile = "../results/results_useLoose_";
        infile+=Form("%1.1f_%1.1f/",etabins[ebin],etabins[ebin+1]);
        for (int anal = 0; anal<nanals; anal++) {
            if (!processAll) {
                if (anal == 0 || anal == 6 || anal == 15 || anal == 16 || anal == 18) {
                    tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
                    for (int cbin = 0; cbin<ncbins-1; cbin++) {
                        ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                        vnA[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                        vnB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                        vnAB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));
                    }
                }
            } else {
                tfin = new TFile(Form("%s%s.root",infile.data(),AnalNames[anal].data()),"read");
                for (int cbin = 0; cbin<ncbins-1; cbin++) {
                    ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
                    vnA[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnA",ctag.data()));
                    vnB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnB",ctag.data()));
                    vnAB[0][anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%s/vnAB",ctag.data()));
                }
            }
        }
    }


    if (!fopen("figures","r")) system("mkdir figures");


    //-- v1even (N1MCm22SUB3 and N1MCp22SUB3) vs. pT for each eta-bin
    TCanvas * cv1evenDiffPt_30_50 = new TCanvas("cv1evenDiffPt_30_50","cv1evenDiffPt_30_50",1100,700);
    cv1evenDiffPt_30_50->Divide(4,3,0,0);
    TH1D * hv1evenDiffPt_30_50_tmp = new TH1D("hv1evenDiffPt_30_50_tmp", "", 50, 0, 12);
    hv1evenDiffPt_30_50_tmp->SetStats(0);
    hv1evenDiffPt_30_50_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1evenDiffPt_30_50_tmp->SetYTitle("v_{1}");
    hv1evenDiffPt_30_50_tmp->GetXaxis()->SetTitleSize(0.06);
    hv1evenDiffPt_30_50_tmp->GetYaxis()->SetTitleSize(0.07);
    hv1evenDiffPt_30_50_tmp->GetXaxis()->SetTitleOffset(1.10);
    hv1evenDiffPt_30_50_tmp->GetYaxis()->SetTitleOffset(1.10);
    hv1evenDiffPt_30_50_tmp->GetXaxis()->SetLabelSize(0.06);
    hv1evenDiffPt_30_50_tmp->GetYaxis()->SetLabelSize(0.06);
    hv1evenDiffPt_30_50_tmp->GetYaxis()->SetNdivisions(509);
    hv1evenDiffPt_30_50_tmp->GetYaxis()->SetRangeUser(-0.075, 0.22);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * padv1evenDiffPt_30_50 = (TPad *) cv1evenDiffPt_30_50->cd(ebin+1);
        if (gridlines) padv1evenDiffPt_30_50->SetGrid();
        if (ebin == 3 || ebin == 7 || ebin == 11) padv1evenDiffPt_30_50->SetRightMargin(0.02);
        if (ebin <=3) padv1evenDiffPt_30_50->SetTopMargin(0.02);
        TH1D * hv1evenDiffPt_30_50 = (TH1D *) hv1evenDiffPt_30_50_tmp->Clone(Form("hv1evenDiffPt_30_50_%d",ebin));
        hv1evenDiffPt_30_50->Draw();

        vnA[0][0][12][ebin]->SetMarkerColor(kMagenta);
        vnA[0][0][12][ebin]->SetLineColor(kMagenta);
        vnA[0][0][12][ebin]->SetMarkerStyle(28);
        vnA[0][0][12][ebin]->SetMarkerSize(1.2);

        vnA[0][6][12][ebin]->SetMarkerColor(kCyan+2);
        vnA[0][6][12][ebin]->SetLineColor(kCyan+2);
        vnA[0][6][12][ebin]->SetMarkerStyle(28);
        vnA[0][6][12][ebin]->SetMarkerSize(1.2);

        vnA[0][0][12][ebin]->Draw("same");
        vnA[0][6][12][ebin]->Draw("same");

        TPaveText * txv1evenDiffPt_30_50_ebin;
        if (ebin>=8) txv1evenDiffPt_30_50_ebin = new TPaveText(0.53, 0.21, 0.90, 0.33,"NDC");
        else txv1evenDiffPt_30_50_ebin = new TPaveText(0.53, 0.06, 0.88, 0.18,"NDC");
        SetTPaveTxt(txv1evenDiffPt_30_50_ebin, 17);
        txv1evenDiffPt_30_50_ebin->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        txv1evenDiffPt_30_50_ebin->Draw();
    }
    cv1evenDiffPt_30_50->cd(2);
    TPaveText * txv1evenDiffPt_30_50_cbin = new TPaveText(0.06, 0.81, 0.22, 0.93,"NDC");
    SetTPaveTxt(txv1evenDiffPt_30_50_cbin, 17);
    txv1evenDiffPt_30_50_cbin->AddText("30-50%");
    txv1evenDiffPt_30_50_cbin->Draw();

    cv1evenDiffPt_30_50->cd(1);
    TLegend * legv1evenDiffPt_30_50 = new TLegend(0.23, 0.71, 0.56, 0.93);
    SetLegend(legv1evenDiffPt_30_50, 17);
    legv1evenDiffPt_30_50->AddEntry(vnA[0][6][12][0],"track+ only","lp");
    legv1evenDiffPt_30_50->AddEntry(vnA[0][0][12][0],"track- only","lp");
    legv1evenDiffPt_30_50->Draw();

    cv1evenDiffPt_30_50->Print("figures/vN1MCm22SUB3_N1MCp22SUB3_Pt_30_50.png","png");



    //-- v1even (N1MCm22SUB3 and N1MCp22SUB3) vs. pT for each eta-bin
    TCanvas * cv1evenDiffPt_A_B_30_50 = new TCanvas("cv1evenDiffPt_A_B_30_50","cv1evenDiffPt_A_B_30_50",1000,800);
    cv1evenDiffPt_A_B_30_50->Divide(4,3,0,0);
    TH1D * hv1evenDiffPt_A_B_30_50_tmp = new TH1D("hv1evenDiffPt_A_B_30_50_tmp", "", 50, 0, 12);
    hv1evenDiffPt_A_B_30_50_tmp->SetStats(0);
    hv1evenDiffPt_A_B_30_50_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1evenDiffPt_A_B_30_50_tmp->SetYTitle("v_{1}^{even}");
    hv1evenDiffPt_A_B_30_50_tmp->GetXaxis()->SetTitleSize(0.06);
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->SetTitleSize(0.07);
    hv1evenDiffPt_A_B_30_50_tmp->GetXaxis()->SetTitleOffset(1.10);
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->SetTitleOffset(1.10);
    hv1evenDiffPt_A_B_30_50_tmp->GetXaxis()->SetLabelSize(0.06);
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->SetLabelSize(0.06);
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->SetNdivisions(509);
    hv1evenDiffPt_A_B_30_50_tmp->GetXaxis()->CenterTitle();
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->CenterTitle();
    hv1evenDiffPt_A_B_30_50_tmp->GetYaxis()->SetRangeUser(-0.075, 0.22);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * padv1evenDiffPt_A_B_30_50 = (TPad *) cv1evenDiffPt_A_B_30_50->cd(ebin+1);
        if (gridlines) padv1evenDiffPt_A_B_30_50->SetGrid();
        if (ebin == 3 || ebin == 7 || ebin == 11) padv1evenDiffPt_A_B_30_50->SetRightMargin(0.02);
        if (ebin <=3) padv1evenDiffPt_A_B_30_50->SetTopMargin(0.02);
        if (ebin <=3) padv1evenDiffPt_A_B_30_50->SetTopMargin(0.08);
        TH1D * hv1evenDiffPt_A_B_30_50 = (TH1D *) hv1evenDiffPt_A_B_30_50_tmp->Clone(Form("hv1evenDiffPt_A_B_30_50_%d",ebin));
        hv1evenDiffPt_A_B_30_50->Draw();

        vnA[0][0][12][ebin]->SetMarkerColor(kBlue);
        vnA[0][0][12][ebin]->SetLineColor(kBlue);
        vnA[0][0][12][ebin]->SetMarkerStyle(21);
        vnA[0][0][12][ebin]->SetMarkerSize(1.1);

        vnA[0][6][12][ebin]->SetMarkerColor(kBlue);
        vnA[0][6][12][ebin]->SetLineColor(kBlue);
        vnA[0][6][12][ebin]->SetMarkerStyle(21);
        vnA[0][6][12][ebin]->SetMarkerSize(1.1);
        if (ebin<=5) vnA[0][6][12][ebin]->Draw("same");
        else vnA[0][0][12][ebin]->Draw("same");

        TPaveText * txv1evenDiffPt_A_B_30_50_ebin;
        if (ebin == 0 || ebin == 4) txv1evenDiffPt_A_B_30_50_ebin = new TPaveText(0.56, 0.05, 0.96, 0.16,"NDC");
        else if (ebin>=1 && ebin<=3) txv1evenDiffPt_A_B_30_50_ebin = new TPaveText(0.48, 0.05, 0.86, 0.16,"NDC");
        else if (ebin == 8) txv1evenDiffPt_A_B_30_50_ebin = new TPaveText(0.56, 0.25, 0.96, 0.36,"NDC");
        else txv1evenDiffPt_A_B_30_50_ebin = new TPaveText(0.48, 0.25, 0.86, 0.36,"NDC");
        SetTPaveTxt(txv1evenDiffPt_A_B_30_50_ebin, 17);
        txv1evenDiffPt_A_B_30_50_ebin->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        txv1evenDiffPt_A_B_30_50_ebin->Draw();
    }
    cv1evenDiffPt_A_B_30_50->cd(1);
    TPaveText * txv1evenDiffPt_A_B_30_50_cbin = new TPaveText(0.24, 0.68, 0.76, 0.87,"NDC");
    SetTPaveTxt(txv1evenDiffPt_A_B_30_50_cbin, 18);
    txv1evenDiffPt_A_B_30_50_cbin->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenDiffPt_A_B_30_50_cbin->AddText("30-50%");
    txv1evenDiffPt_A_B_30_50_cbin->Draw();

    TPaveText * txv1evenDiffPt_A_B_30_50_cbin_cms = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1evenDiffPt_A_B_30_50_cbin_cms, 18);
    txv1evenDiffPt_A_B_30_50_cbin_cms->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenDiffPt_A_B_30_50_cbin_cms->Draw();

    cv1evenDiffPt_A_B_30_50->Print("figures/vN1MC22SUB3_Pt_30_50.png","png");



    //-- v1odd (N1SUB2) vs. pT for each eta-bin
    TCanvas * cv1oddDiffPt_30_50 = new TCanvas("cv1oddDiffPt_30_50","cv1oddDiffPt_30_50",1000,800);
    cv1oddDiffPt_30_50->Divide(4,3,0,0);
    TH1D * hv1oddDiffPt_30_50_tmp = new TH1D("hv1oddDiffPt_30_50_tmp", "", 50, 0, 13);
    hv1oddDiffPt_30_50_tmp->SetStats(0);
    hv1oddDiffPt_30_50_tmp->SetXTitle("p_{T} (GeV/c)");
    hv1oddDiffPt_30_50_tmp->SetYTitle("v_{1}^{odd}");
    hv1oddDiffPt_30_50_tmp->GetXaxis()->SetTitleSize(0.06);
    hv1oddDiffPt_30_50_tmp->GetYaxis()->SetTitleSize(0.07);
    hv1oddDiffPt_30_50_tmp->GetXaxis()->SetTitleOffset(1.10);
    hv1oddDiffPt_30_50_tmp->GetYaxis()->SetTitleOffset(1.20);
    hv1oddDiffPt_30_50_tmp->GetXaxis()->SetLabelSize(0.06);
    hv1oddDiffPt_30_50_tmp->GetYaxis()->SetLabelSize(0.06);
    hv1oddDiffPt_30_50_tmp->GetXaxis()->CenterTitle();
    hv1oddDiffPt_30_50_tmp->GetYaxis()->CenterTitle();
    hv1oddDiffPt_30_50_tmp->GetYaxis()->SetNdivisions(509);
    hv1oddDiffPt_30_50_tmp->GetYaxis()->SetRangeUser(-0.12, 0.12);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * padv1oddDiffPt_30_50 = (TPad *) cv1oddDiffPt_30_50->cd(ebin+1);
        if (gridlines) padv1oddDiffPt_30_50->SetGrid();
        if (ebin == 3 || ebin == 7 || ebin == 11) padv1oddDiffPt_30_50->SetRightMargin(0.02);
        if (ebin <=3) padv1oddDiffPt_30_50->SetTopMargin(0.08);
        TH1D * hv1oddDiffPt_30_50 = (TH1D *) hv1oddDiffPt_30_50_tmp->Clone(Form("hv1oddDiffPt_30_50_%d",ebin));
        hv1oddDiffPt_30_50->Draw();

        vnA[0][16][12][ebin]->SetMarkerColor(kCyan+2);
        vnA[0][16][12][ebin]->SetLineColor(kCyan+2);
        vnA[0][16][12][ebin]->SetMarkerStyle(28);
        vnA[0][16][12][ebin]->SetMarkerSize(1.2);

        vnB[0][16][12][ebin]->SetMarkerColor(kMagenta);
        vnB[0][16][12][ebin]->SetLineColor(kMagenta);
        vnB[0][16][12][ebin]->SetMarkerStyle(28);
        vnB[0][16][12][ebin]->SetMarkerSize(1.2);

        vnAB[0][16][12][ebin]->SetMarkerColor(kBlue);
        vnAB[0][16][12][ebin]->SetLineColor(kBlue);
        vnAB[0][16][12][ebin]->SetMarkerStyle(21);
        vnAB[0][16][12][ebin]->SetMarkerSize(1.1);

        // vnA[0][16][12][ebin]->Draw("same");
        // vnB[0][16][12][ebin]->Draw("same");
        vnAB[0][16][12][ebin]->Draw("same");

        TPaveText * txv1oddDiffPt_30_50_ebin;
        if (ebin == 0) txv1oddDiffPt_30_50_ebin = new TPaveText(0.23, 0.75, 0.59, 0.86,"NDC");
        else if (ebin>=1 && ebin<=3) txv1oddDiffPt_30_50_ebin = new TPaveText(0.04, 0.75, 0.41, 0.86,"NDC");
        else if (ebin == 4 || ebin == 8) txv1oddDiffPt_30_50_ebin = new TPaveText(0.23, 0.82, 0.59, 0.94,"NDC");
        else txv1oddDiffPt_30_50_ebin = new TPaveText(0.04, 0.82, 0.41, 0.94,"NDC");
        SetTPaveTxt(txv1oddDiffPt_30_50_ebin, 17);
        txv1oddDiffPt_30_50_ebin->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        txv1oddDiffPt_30_50_ebin->Draw();
    }
    cv1oddDiffPt_30_50->cd(1);
    TPaveText * txv1oddDiffPt_30_50_cbin = new TPaveText(0.24, 0.06, 0.76, 0.28,"NDC");
    SetTPaveTxt(txv1oddDiffPt_30_50_cbin, 18);
    txv1oddDiffPt_30_50_cbin->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddDiffPt_30_50_cbin->AddText("30-50%");
    txv1oddDiffPt_30_50_cbin->Draw();

    TPaveText * txv1oddDiffPt_30_50_cbin_cms = new TPaveText(0.18, 0.93, 0.58, 1.0,"NDC");
    SetTPaveTxt(txv1oddDiffPt_30_50_cbin_cms, 18);
    txv1oddDiffPt_30_50_cbin_cms->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddDiffPt_30_50_cbin_cms->Draw();

    cv1oddDiffPt_30_50->cd(1);
    TLegend * legv1oddDiffPt_30_50 = new TLegend(0.24, 0.06, 0.96, 0.28);
    SetLegend(legv1oddDiffPt_30_50, 18);
    legv1oddDiffPt_30_50->AddEntry(vnA[0][16][12][0],"HF+ only","lp");
    legv1oddDiffPt_30_50->AddEntry(vnB[0][16][12][0],"HF- only","lp");
    legv1oddDiffPt_30_50->AddEntry(vnAB[0][16][12][0],Form("%s",AnalNames[16].data()),"lp");
    // legv1oddDiffPt_30_50->Draw();

    cv1oddDiffPt_30_50->Print("figures/vN1SUB3_Pt_30_50.png","png");

}
