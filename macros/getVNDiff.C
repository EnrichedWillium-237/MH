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

TH1D * vnA_pt[nanals][ncbins][netabins];
TH1D * vnB_pt[nanals][ncbins][netabins];
TH1D * vnAB_pt[nanals][ncbins][netabins];
TH1D * N1SUB3_pt[ncbins][netabins];

TFile * tfin;

void getVNDiff()
{

    TH1::SetDefaultSumw2();

    for (int ebin = 0; ebin<netabins; ebin++) {
        for (int anal = 0; anal<nanals; anal++) {
            TFile * tfin = new TFile(Form("results/results_useTight_%1.1f_%1.1f/%s.root",etabins[ebin],etabins[ebin+1],AnalNames[anal].data()));
            for (int cbin = 0; cbin<ncbins; cbin++) {
                vnA_pt[anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[cbin],cmax[cbin]));
                vnB_pt[anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[cbin],cmax[cbin]));
                vnAB_pt[anal][cbin][ebin] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
            }
        }
    }

    //-- average N1SUB3
    for (int ebin = 0; ebin<netabins; ebin++) {
        for (int cbin = 0; cbin<ncbins; cbin++) {
            N1SUB3_pt[cbin][ebin] = (TH1D *) vnAB_pt[N1ASUB3][cbin][ebin]->Clone(Form("N1SUB3_pt_%d_%d_e%d",cmin[cbin],cmax[cbin],ebin));
            N1SUB3_pt[cbin][ebin]->Add(vnAB_pt[N1BSUB3][cbin][ebin]);
            N1SUB3_pt[cbin][ebin]->Scale(0.5);
        }
    }

    TLine * lnPt  = new TLine(0.0, 0.0, 12.0, 0.0);

    if (!fopen("figures/differentialVN","r")) system("mkdir figures/differentialVN");



    //-- differential v1(pT) for N1MC22SUB3
    if (!fopen("figures/differentialVN/N1MCSUB3","r")) system("mkdir figures/differentialVN/N1MCSUB3");
    for (int cbin = 0; cbin<ncbins; cbin++) {
        TCanvas * cN1MCSUB3 = new TCanvas(Form("cN1MCSUB3_%d",cbin), Form("cN1MCSUB3_%d",cbin), 950, 750);
        cN1MCSUB3->Divide(4,3,0,0);
        for (int ebin = 0; ebin<netabins; ebin++) {
            TPad * padN1MCSUB3 = (TPad *) cN1MCSUB3->cd(ebin+1);
            if (gridlines) padN1MCSUB3->SetGrid();
            if (ebin == 3 || ebin == 7 || ebin == 11) padN1MCSUB3->SetRightMargin(0.02);
            if (ebin <= 3) padN1MCSUB3->SetTopMargin(0.1);
            if (ebin >= 8) padN1MCSUB3->SetBottomMargin(0.2);

            TH1D * hN1MCSUB3 = new TH1D(Form("hN1MCSUB3_c%d_e%d",cbin,ebin), "", 50, 0, 12);
            hN1MCSUB3->SetXTitle("p_{T} (GeV/c)");
            hN1MCSUB3->SetYTitle("v_{1}");
            hN1MCSUB3->GetYaxis()->SetRangeUser(-0.035, 0.26);
            //if (cbin == 8 || cbin == 9) hN1MCSUB3->GetYaxis()->SetRangeUser(-0.035, 0.36);
            hN1MCSUB3->GetXaxis()->CenterTitle();
            hN1MCSUB3->GetYaxis()->CenterTitle();
            hN1MCSUB3->GetYaxis()->SetNdivisions(509);
            if (ebin == 0 || ebin == 4) {
                hN1MCSUB3->GetYaxis()->SetTitleSize(0.07);
                hN1MCSUB3->GetYaxis()->SetLabelSize(0.06);
                hN1MCSUB3->GetYaxis()->SetTitleOffset(1.35);
                hN1MCSUB3->GetYaxis()->SetLabelOffset(0.015);
            }
            if (ebin == 8) {
                hN1MCSUB3->GetXaxis()->SetTitleSize(0.06);
                hN1MCSUB3->GetXaxis()->SetLabelSize(0.05);
                hN1MCSUB3->GetXaxis()->SetTitleOffset(1.20);
                hN1MCSUB3->GetXaxis()->SetLabelOffset(0.014);

                hN1MCSUB3->GetYaxis()->SetTitleSize(0.06);
                hN1MCSUB3->GetYaxis()->SetLabelSize(0.05);
                hN1MCSUB3->GetYaxis()->SetTitleOffset(1.58);
                hN1MCSUB3->GetYaxis()->SetLabelOffset(0.015);
            }
            if (ebin >= 9) {
                hN1MCSUB3->GetXaxis()->SetTitleSize(0.07);
                hN1MCSUB3->GetXaxis()->SetLabelSize(0.06);
                hN1MCSUB3->GetXaxis()->SetTitleOffset(1.02);
                hN1MCSUB3->GetXaxis()->SetLabelOffset(0.006);
            }
            hN1MCSUB3->Draw();

            if (ebin<6) {
                vnA_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerColor(kBlue);
                vnA_pt[N1MCp22SUB3][cbin][ebin]->SetLineColor(kBlue);
                vnA_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerStyle(21);
                vnA_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerSize(1.1);
                vnA_pt[N1MCp22SUB3][cbin][ebin]->Draw("same");
            } else {
                vnB_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerColor(kBlue);
                vnB_pt[N1MCp22SUB3][cbin][ebin]->SetLineColor(kBlue);
                vnB_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerStyle(21);
                vnB_pt[N1MCp22SUB3][cbin][ebin]->SetMarkerSize(1.1);
                vnB_pt[N1MCp22SUB3][cbin][ebin]->Draw("same");
            }

            TPaveText * txN1MCSUB3_cent;
            if (ebin == 0) txN1MCSUB3_cent = new TPaveText(0.23, 0.56, 0.67, 0.65, "NDC");
            if (ebin >= 1 && ebin <=3) txN1MCSUB3_cent = new TPaveText(0.06, 0.75, 0.50, 0.84, "NDC");
            if (ebin == 4 || ebin == 8) txN1MCSUB3_cent = new TPaveText(0.23, 0.85, 0.67, 0.94, "NDC");
            if ((ebin >= 5 && ebin <=7) || ebin >= 9) txN1MCSUB3_cent = new TPaveText(0.06, 0.85, 0.50, 0.94, "NDC");
            SetTPaveTxt(txN1MCSUB3_cent, 16);
            txN1MCSUB3_cent->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
            txN1MCSUB3_cent->Draw();

        }
        cN1MCSUB3->cd(1);
        TPaveText * txN1MCSUB3_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
        SetTPaveTxt(txN1MCSUB3_CMS, 16);
        txN1MCSUB3_CMS->AddText("#bf{CMS} #it{Preliminary}");
        txN1MCSUB3_CMS->Draw();

        TPaveText * txN1MCSUB3_label = new TPaveText(0.22, 0.66, 0.82, 0.85, "NDC");
        SetTPaveTxt(txN1MCSUB3_label, 16);
        txN1MCSUB3_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
        txN1MCSUB3_label->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txN1MCSUB3_label->Draw();

        cN1MCSUB3->Print(Form("figures/differentialVN/N1MCSUB3/vndiff_%d_%d.png",cmin[cbin],cmax[cbin]),"png");
        cN1MCSUB3->Close();
    }



    //-- differential v1(pT) for N1SUB3
    if (!fopen("figures/differentialVN/N1SUB3","r")) system("mkdir figures/differentialVN/N1SUB3");
    for (int cbin = 0; cbin<ncbins; cbin++) {
        TCanvas * cN1SUB3 = new TCanvas(Form("cN1SUB3_%d",cbin), Form("cN1SUB3_%d",cbin), 950, 750);
        cN1SUB3->Divide(4,3,0,0);
        for (int ebin = 0; ebin<netabins; ebin++) {
            TPad * padN1SUB3 = (TPad *) cN1SUB3->cd(ebin+1);
            if (gridlines) padN1SUB3->SetGrid();
            if (ebin == 3 || ebin == 7 || ebin == 11) padN1SUB3->SetRightMargin(0.02);
            if (ebin <= 3) padN1SUB3->SetTopMargin(0.1);
            if (ebin >= 8) padN1SUB3->SetBottomMargin(0.2);

            TH1D * hN1SUB3 = new TH1D(Form("hN1SUB3_c%d_e%d",cbin,ebin), "", 50, 0, 12);
            hN1SUB3->SetXTitle("p_{T} (GeV/c)");
            hN1SUB3->SetYTitle("v_{1}");
            hN1SUB3->GetYaxis()->SetRangeUser(-0.1, 0.1);
            if (cbin == 8 || cbin == 9) hN1SUB3->GetYaxis()->SetRangeUser(-0.2, 0.2);
            if (cbin == 10) hN1SUB3->GetYaxis()->SetRangeUser(-0.3, 0.3);
            hN1SUB3->GetXaxis()->CenterTitle();
            hN1SUB3->GetYaxis()->CenterTitle();
            hN1SUB3->GetYaxis()->SetNdivisions(509);
            if (ebin == 0 || ebin == 4) {
                hN1SUB3->GetYaxis()->SetTitleSize(0.07);
                hN1SUB3->GetYaxis()->SetLabelSize(0.06);
                hN1SUB3->GetYaxis()->SetTitleOffset(1.35);
                hN1SUB3->GetYaxis()->SetLabelOffset(0.015);
            }
            if (ebin == 8) {
                hN1SUB3->GetXaxis()->SetTitleSize(0.06);
                hN1SUB3->GetXaxis()->SetLabelSize(0.05);
                hN1SUB3->GetXaxis()->SetTitleOffset(1.20);
                hN1SUB3->GetXaxis()->SetLabelOffset(0.014);

                hN1SUB3->GetYaxis()->SetTitleSize(0.06);
                hN1SUB3->GetYaxis()->SetLabelSize(0.05);
                hN1SUB3->GetYaxis()->SetTitleOffset(1.58);
                hN1SUB3->GetYaxis()->SetLabelOffset(0.015);
            }
            if (ebin >= 9) {
                hN1SUB3->GetXaxis()->SetTitleSize(0.07);
                hN1SUB3->GetXaxis()->SetLabelSize(0.06);
                hN1SUB3->GetXaxis()->SetTitleOffset(1.02);
                hN1SUB3->GetXaxis()->SetLabelOffset(0.006);
            }
            hN1SUB3->Draw();

            N1SUB3_pt[cbin][ebin]->SetMarkerColor(kBlue);
            N1SUB3_pt[cbin][ebin]->SetLineColor(kBlue);
            N1SUB3_pt[cbin][ebin]->SetMarkerStyle(21);
            N1SUB3_pt[cbin][ebin]->SetMarkerSize(1.1);
            N1SUB3_pt[cbin][ebin]->Draw("same");

            TPaveText * txN1SUB3_cent;
            if (ebin == 0) txN1SUB3_cent = new TPaveText(0.23, 0.75, 0.67, 0.84, "NDC");
            if (ebin >= 1 && ebin <=3) txN1SUB3_cent = new TPaveText(0.06, 0.75, 0.50, 0.84, "NDC");
            if (ebin == 4 || ebin == 8) txN1SUB3_cent = new TPaveText(0.23, 0.85, 0.67, 0.94, "NDC");
            if ((ebin >= 5 && ebin <=7) || ebin >= 9) txN1SUB3_cent = new TPaveText(0.06, 0.85, 0.50, 0.94, "NDC");
            SetTPaveTxt(txN1SUB3_cent, 16);
            txN1SUB3_cent->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
            txN1SUB3_cent->Draw();

        }
        cN1SUB3->cd(1);
        TPaveText * txN1SUB3_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
        SetTPaveTxt(txN1SUB3_CMS, 16);
        txN1SUB3_CMS->AddText("#bf{CMS} #it{Preliminary}");
        txN1SUB3_CMS->Draw();

        TPaveText * txN1SUB3_label = new TPaveText(0.22, 0.05, 0.82, 0.24, "NDC");
        SetTPaveTxt(txN1SUB3_label, 16);
        txN1SUB3_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
        txN1SUB3_label->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txN1SUB3_label->Draw();

        cN1SUB3->Print(Form("figures/differentialVN/N1SUB3/vndiff_%d_%d.png",cmin[cbin],cmax[cbin]),"png");
        if (cbin != 0) cN1SUB3->Close();
    }








}
