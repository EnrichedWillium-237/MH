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

TH1D * N1SUB2_Sym_eta[ncbins];
TH1D * N1SUB3_Sym_eta[ncbins];
TH1D * N1MC22SUB3_Sym_pt[ncbins];

TH1D * systN1SUB2_eta;
TH1D * systN1SUB3_eta;
TH1D * systN1MC22SUB3_pt;

TH1D * systN1SUB2_Loose_Tight_eta;
TH1D * systN1SUB3_Loose_Tight_eta;
TH1D * systN1MC22SUB3_Loose_Tight_pt;
TH1D * systN1SUB2_TightB_Tight_eta;
TH1D * systN1SUB3_TightB_Tight_eta;
TH1D * systN1MC22SUB3_TightB_Tight_pt;

TGraphErrors * gN1SUB2_Sym_eta[ncbins];
TGraphErrors * gN1SUB3_Sym_eta[ncbins];
TGraphErrors * gN1MC22SUB3_Sym_pt[ncbins];

TGraphErrors * gN1SUB2_cut_eta[ncbins];
TGraphErrors * gN1SUB3_cut_eta[ncbins];
TGraphErrors * gN1MC22SUB3_cut_pt[ncbins];

TGraphErrors * gN1SUB2_final_eta[ncbins];
TGraphErrors * gN1SUB3_final_eta[ncbins];
TGraphErrors * gN1MC22SUB3_final_pt[ncbins];


TFile * tfinSym;
TFile * tfincut;

void getVNSyst()
{

    TH1::SetDefaultSumw2();

    tfinSym = new TFile("figures/integralVN/data/symmetrizedVN.root","read");
    tfincut = new TFile("figures/integralVN/data/trkcuts.root","read");

    for (int cbin = 0; cbin<ncbins; cbin++) {
        string ctag = Form("%d_%d",cmin[cbin],cmax[cbin]);
        N1SUB2_Sym_eta[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1SUB2_Sym_eta_%s",ctag.data(),ctag.data()));
        N1SUB3_Sym_eta[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1SUB3_Sym_eta_%s",ctag.data(),ctag.data()));
        N1MC22SUB3_Sym_pt[cbin] = (TH1D *) tfinSym->Get(Form("%s/N1MC22SUB3_Sym_pt_%s",ctag.data(),ctag.data()));
    }
    systN1SUB2_eta = (TH1D *) tfinSym->Get("systN1SUB2_eta");
    systN1SUB3_eta = (TH1D *) tfinSym->Get("systN1SUB3_eta");
    systN1MC22SUB3_pt = (TH1D *) tfinSym->Get("systN1MC22SUB3_pt");

    systN1SUB2_Loose_Tight_eta = (TH1D *) tfincut->Get("systN1SUB2_Loose_Tight_eta");
    systN1SUB3_Loose_Tight_eta = (TH1D *) tfincut->Get("systN1SUB3_Loose_Tight_eta");
    systN1MC22SUB3_Loose_Tight_pt = (TH1D *) tfincut->Get("systN1MC22SUB3_Loose_Tight_pt");
    systN1SUB2_TightB_Tight_eta = (TH1D *) tfincut->Get("systN1SUB2_TightB_Tight_eta");
    systN1SUB3_TightB_Tight_eta = (TH1D *) tfincut->Get("systN1SUB3_TightB_Tight_eta");
    systN1MC22SUB3_TightB_Tight_pt = (TH1D *) tfincut->Get("systN1MC22SUB3_TightB_Tight_pt");

    double xN1SUB2_Sym_eta[50] = {0};
    double xN1SUB2_Sym_eta_err[50] = {0};
    double yN1SUB2_Sym_eta[50] = {0};
    double yN1SUB2_Sym_eta_err[50] = {0};

    double xN1SUB3_Sym_eta[50] = {0};
    double xN1SUB3_Sym_eta_err[50] = {0};
    double yN1SUB3_Sym_eta[50] = {0};
    double yN1SUB3_Sym_eta_err[50] = {0};

    double xN1MC22SUB3_Sym_pt[50] = {0};
    double xN1MC22SUB3_Sym_pt_err[50] = {0};
    double yN1MC22SUB3_Sym_pt[50] = {0};
    double yN1MC22SUB3_Sym_pt_err[50] = {0};

    int neta = N1SUB2_Sym_eta[0]->GetNbinsX();
    int npt = N1MC22SUB3_Sym_pt[0]->GetNbinsX();
    for (int cbin = 0; cbin<ncbins; cbin++) {
        for (int ebin = 0; ebin<neta; ebin++) {
            xN1SUB2_Sym_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB2_Sym_eta_err[ebin] = 0.75*(N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB2_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB2_Sym_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB2_Sym_eta_err[ebin] = fabs(N1SUB2_Sym_eta[cbin]->GetBinContent(ebin+1) * systN1SUB2_eta->GetBinContent(cbin+1));

            xN1SUB3_Sym_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB3_Sym_eta_err[ebin] = 0.75*(N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB3_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB3_Sym_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB3_Sym_eta_err[ebin] = fabs(N1SUB3_Sym_eta[cbin]->GetBinContent(ebin+1) * systN1SUB3_eta->GetBinContent(cbin+1));
        }
        for (int pbin = 0; pbin<npt; pbin++) {
            xN1MC22SUB3_Sym_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1);
            xN1MC22SUB3_Sym_pt_err[pbin] = 0.75*(N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1) - N1MC22SUB3_Sym_pt[cbin]->GetBinLowEdge(pbin+1));
            yN1MC22SUB3_Sym_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinContent(pbin+1);
            yN1MC22SUB3_Sym_pt_err[pbin] = fabs(N1MC22SUB3_Sym_pt[cbin]->GetBinContent(pbin+1) * systN1MC22SUB3_pt->GetBinContent(cbin+1));
        }
        gN1SUB2_Sym_eta[cbin] = new TGraphErrors(neta, xN1SUB2_Sym_eta, yN1SUB2_Sym_eta, xN1SUB2_Sym_eta_err, yN1SUB2_Sym_eta_err);
        gN1SUB3_Sym_eta[cbin] = new TGraphErrors(neta, xN1SUB3_Sym_eta, yN1SUB3_Sym_eta, xN1SUB3_Sym_eta_err, yN1SUB3_Sym_eta_err);
        gN1MC22SUB3_Sym_pt[cbin] = new TGraphErrors(npt, xN1MC22SUB3_Sym_pt, yN1MC22SUB3_Sym_pt, xN1MC22SUB3_Sym_pt_err, yN1MC22SUB3_Sym_pt_err);
    }

    double xN1SUB2_cut_eta[50] = {0};
    double xN1SUB2_cut_eta_err[50] = {0};
    double yN1SUB2_cut_eta[50] = {0};
    double yN1SUB2_cut_eta_err[50] = {0};

    double xN1SUB3_cut_eta[50] = {0};
    double xN1SUB3_cut_eta_err[50] = {0};
    double yN1SUB3_cut_eta[50] = {0};
    double yN1SUB3_cut_eta_err[50] = {0};

    double xN1MC22SUB3_cut_pt[50] = {0};
    double xN1MC22SUB3_cut_pt_err[50] = {0};
    double yN1MC22SUB3_cut_pt[50] = {0};
    double yN1MC22SUB3_cut_pt_err[50] = {0};

    for (int cbin = 0; cbin<ncbins; cbin++) {
        for (int ebin = 0; ebin<neta; ebin++) {
            xN1SUB2_cut_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB2_cut_eta_err[ebin] = 0.75*(N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB2_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB2_cut_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB2_cut_eta_err[ebin] = fabs(N1SUB2_Sym_eta[cbin]->GetBinContent(ebin+1) * (1 - systN1SUB2_TightB_Tight_eta->GetBinContent(cbin+1)));

            xN1SUB3_cut_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB3_cut_eta_err[ebin] = 0.75*(N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB3_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB3_cut_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB3_cut_eta_err[ebin] = fabs(N1SUB3_Sym_eta[cbin]->GetBinContent(ebin+1) * (1 - systN1SUB3_TightB_Tight_eta->GetBinContent(cbin+1)));
        }
        for (int pbin = 0; pbin<npt; pbin++) {
            xN1MC22SUB3_cut_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1);
            xN1MC22SUB3_cut_pt_err[pbin] = 0.75*(N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1) - N1MC22SUB3_Sym_pt[cbin]->GetBinLowEdge(pbin+1));
            yN1MC22SUB3_cut_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinContent(pbin+1);
            yN1MC22SUB3_cut_pt_err[pbin] = fabs(N1MC22SUB3_Sym_pt[cbin]->GetBinContent(pbin+1) * (1 - systN1MC22SUB3_TightB_Tight_pt->GetBinContent(cbin+1)));
        }
        gN1SUB2_cut_eta[cbin] = new TGraphErrors(neta, xN1SUB2_cut_eta, yN1SUB2_cut_eta, xN1SUB2_cut_eta_err, yN1SUB2_cut_eta_err);
        gN1SUB3_cut_eta[cbin] = new TGraphErrors(neta, xN1SUB3_cut_eta, yN1SUB3_cut_eta, xN1SUB3_cut_eta_err, yN1SUB3_cut_eta_err);
        gN1MC22SUB3_cut_pt[cbin] = new TGraphErrors(npt, xN1MC22SUB3_cut_pt, yN1MC22SUB3_cut_pt, xN1MC22SUB3_cut_pt_err, yN1MC22SUB3_cut_pt_err);
    }

    //-- add systematic uncertainties in quadrature
    double xN1SUB2_final_eta[50] = {0};
    double xN1SUB2_final_eta_err[50] = {0};
    double yN1SUB2_final_eta[50] = {0};
    double yN1SUB2_final_eta_err[50] = {0};

    double xN1SUB3_final_eta[50] = {0};
    double xN1SUB3_final_eta_err[50] = {0};
    double yN1SUB3_final_eta[50] = {0};
    double yN1SUB3_final_eta_err[50] = {0};

    double xN1MC22SUB3_final_pt[50] = {0};
    double xN1MC22SUB3_final_pt_err[50] = {0};
    double yN1MC22SUB3_final_pt[50] = {0};
    double yN1MC22SUB3_final_pt_err[50] = {0};

    for (int cbin = 0; cbin<ncbins; cbin++) {
        for (int ebin = 0; ebin<neta; ebin++) {
            xN1SUB2_final_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB2_final_eta_err[ebin] = 0.75*(N1SUB2_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB2_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB2_final_eta[ebin] = N1SUB2_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB2_final_eta_err[ebin] = sqrt( pow(yN1SUB2_Sym_eta_err[cbin],2) + pow(yN1SUB2_cut_eta_err[cbin],2) );

            xN1SUB3_final_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1);
            xN1SUB3_final_eta_err[ebin] = 0.75*(N1SUB3_Sym_eta[cbin]->GetBinCenter(ebin+1) - N1SUB3_Sym_eta[cbin]->GetBinLowEdge(ebin+1));
            yN1SUB3_final_eta[ebin] = N1SUB3_Sym_eta[cbin]->GetBinContent(ebin+1);
            yN1SUB3_final_eta_err[ebin] = sqrt( pow(yN1SUB3_Sym_eta_err[cbin],2) + pow(yN1SUB3_cut_eta_err[cbin],2) );
        }
        for (int pbin = 0; pbin<npt; pbin++) {
            xN1MC22SUB3_final_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1);
            xN1MC22SUB3_final_pt_err[pbin] = 0.75*(N1MC22SUB3_Sym_pt[cbin]->GetBinCenter(pbin+1) - N1MC22SUB3_Sym_pt[cbin]->GetBinLowEdge(pbin+1));
            yN1MC22SUB3_final_pt[pbin] = N1MC22SUB3_Sym_pt[cbin]->GetBinContent(pbin+1);
            yN1MC22SUB3_final_pt_err[pbin] = sqrt( pow(yN1MC22SUB3_Sym_pt_err[cbin],2) + pow(yN1MC22SUB3_cut_pt_err[cbin],2) );
        }
        gN1SUB2_final_eta[cbin] = new TGraphErrors(neta, xN1SUB2_final_eta, yN1SUB2_final_eta, xN1SUB2_final_eta_err, yN1SUB2_final_eta_err);
        gN1SUB3_final_eta[cbin] = new TGraphErrors(neta, xN1SUB3_final_eta, yN1SUB3_final_eta, xN1SUB3_final_eta_err, yN1SUB3_final_eta_err);
        gN1MC22SUB3_final_pt[cbin] = new TGraphErrors(npt, xN1MC22SUB3_final_pt, yN1MC22SUB3_final_pt, xN1MC22SUB3_final_pt_err, yN1MC22SUB3_final_pt_err);
    }


    if (!fopen("figures/integralVN","r")) system("mkdir figures/integralVN");
    if (!fopen("figures/integralVN/data","r")) system("mkdir figures/integralVN/data");
    if (!fopen("figures/integralVN/systematics","r")) system("mkdir figures/integralVN/systematics");



    //-- centrality dependence of integral v1odd(eta) SUB3 for Symmetric subevents
    TCanvas * cv1oddEta = new TCanvas("cv1oddEta", "cv1oddEta", 1300, 650);
    cv1oddEta->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1oddEta = (TPad *) cv1oddEta->cd(cbin+1);
        if (gridlines) padv1oddEta->SetGrid();
        if (cbin == 4 || cbin == 9) padv1oddEta->SetRightMargin(0.02);
        if (cbin <= 4) padv1oddEta->SetTopMargin(0.1);
        if (cbin > 4) padv1oddEta->SetBottomMargin(0.25);

        TH1D * hv1oddEta = new TH1D(Form("hv1oddEta_%d",cbin), "", 50, -2.8, 2.8);
        hv1oddEta->SetXTitle("#eta");
        hv1oddEta->SetYTitle("v_{1}^{odd}");
        hv1oddEta->GetXaxis()->CenterTitle();
        hv1oddEta->GetYaxis()->CenterTitle();
        hv1oddEta->GetYaxis()->SetRangeUser(-0.022, 0.022);
        hv1oddEta->GetYaxis()->SetNdivisions(509);
        hv1oddEta->GetYaxis()->SetTitleSize(0.07);
        hv1oddEta->GetYaxis()->SetLabelSize(0.05);
        hv1oddEta->GetYaxis()->SetTitleOffset(1.20);
        hv1oddEta->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1oddEta->GetXaxis()->SetTitleSize(0.07);
            hv1oddEta->GetXaxis()->SetLabelSize(0.05);
            hv1oddEta->GetXaxis()->SetTitleOffset(1.00);
            hv1oddEta->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1oddEta->GetXaxis()->SetTitleSize(0.08);
            hv1oddEta->GetXaxis()->SetLabelSize(0.06);
            hv1oddEta->GetXaxis()->SetTitleOffset(0.83);
            hv1oddEta->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1oddEta->Draw();

        gN1SUB3_Sym_eta[cbin]->SetMarkerColor(kBlue);
        gN1SUB3_Sym_eta[cbin]->SetLineColor(kBlue);
        gN1SUB3_Sym_eta[cbin]->SetMarkerStyle(21);
        gN1SUB3_Sym_eta[cbin]->SetMarkerSize(1.1);
        gN1SUB3_Sym_eta[cbin]->SetFillColor(kGray+1);
        gN1SUB3_Sym_eta[cbin]->Draw("same []2");

        N1SUB3_Sym_eta[cbin]->SetMarkerColor(kBlue);
        N1SUB3_Sym_eta[cbin]->SetLineColor(kBlue);
        N1SUB3_Sym_eta[cbin]->SetMarkerStyle(21);
        N1SUB3_Sym_eta[cbin]->SetMarkerSize(1.1);
        N1SUB3_Sym_eta[cbin]->Draw("same");

        TPaveText * txv1oddEta_cent;
        if (cbin == 0) txv1oddEta_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1oddEta_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1oddEta_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1oddEta_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1oddEta_cent, 17);
        txv1oddEta_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1oddEta_cent->Draw();
    }
    cv1oddEta->cd(1);
    TPaveText * txv1oddEta_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1oddEta_CMS, 16);
    txv1oddEta_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddEta_CMS->Draw();

    TPaveText * txv1oddEta_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1oddEta_label, 16);
    txv1oddEta_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddEta_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1oddEta_label->Draw();

    cv1oddEta->Print("figures/integralVN/systematics/v1_Sym_syst_N1SUB3_eta.pdf","pdf");



    //-- centrality dependence of integral v1pt(pt) SUB3 for Symmetric subevents
    TCanvas * cv1evenPt = new TCanvas("cv1evenPt", "cv1evenPt", 1300, 650);
    cv1evenPt->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1evenPt = (TPad *) cv1evenPt->cd(cbin+1);
        if (gridlines) padv1evenPt->SetGrid();
        if (cbin == 4 || cbin == 9) padv1evenPt->SetRightMargin(0.02);
        if (cbin <= 4) padv1evenPt->SetTopMargin(0.1);
        if (cbin > 4) padv1evenPt->SetBottomMargin(0.25);

        TH1D * hv1evenPt = new TH1D(Form("hv1evenPt_%d",cbin), "", 50, 0, 12);
        hv1evenPt->SetXTitle("p_{T} (GeV/c)");
        hv1evenPt->SetYTitle("v_{1}^{even}");
        hv1evenPt->GetXaxis()->CenterTitle();
        hv1evenPt->GetYaxis()->CenterTitle();
        hv1evenPt->GetYaxis()->SetRangeUser(-0.05, 0.22);
        hv1evenPt->GetYaxis()->SetNdivisions(509);
        hv1evenPt->GetYaxis()->SetTitleSize(0.07);
        hv1evenPt->GetYaxis()->SetLabelSize(0.05);
        hv1evenPt->GetYaxis()->SetTitleOffset(1.20);
        hv1evenPt->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1evenPt->GetXaxis()->SetTitleSize(0.07);
            hv1evenPt->GetXaxis()->SetLabelSize(0.05);
            hv1evenPt->GetXaxis()->SetTitleOffset(1.00);
            hv1evenPt->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1evenPt->GetXaxis()->SetTitleSize(0.08);
            hv1evenPt->GetXaxis()->SetLabelSize(0.06);
            hv1evenPt->GetXaxis()->SetTitleOffset(0.83);
            hv1evenPt->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1evenPt->Draw();

        gN1MC22SUB3_Sym_pt[cbin]->SetMarkerColor(kBlue);
        gN1MC22SUB3_Sym_pt[cbin]->SetLineColor(kBlue);
        gN1MC22SUB3_Sym_pt[cbin]->SetMarkerStyle(21);
        gN1MC22SUB3_Sym_pt[cbin]->SetMarkerSize(1.1);
        gN1MC22SUB3_Sym_pt[cbin]->SetFillColor(kGray+1);
        gN1MC22SUB3_Sym_pt[cbin]->Draw("same []2");

        N1MC22SUB3_Sym_pt[cbin]->SetMarkerColor(kBlue);
        N1MC22SUB3_Sym_pt[cbin]->SetLineColor(kBlue);
        N1MC22SUB3_Sym_pt[cbin]->SetMarkerStyle(21);
        N1MC22SUB3_Sym_pt[cbin]->SetMarkerSize(1.1);
        N1MC22SUB3_Sym_pt[cbin]->Draw("same");

        TPaveText * txv1evenPt_cent;
        if (cbin == 0) txv1evenPt_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1evenPt_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1evenPt_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1evenPt_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1evenPt_cent, 17);
        txv1evenPt_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1evenPt_cent->Draw();
    }
    cv1evenPt->cd(1);
    TPaveText * txv1evenPt_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1evenPt_CMS, 16);
    txv1evenPt_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenPt_CMS->Draw();

    TPaveText * txv1evenPt_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1evenPt_label, 16);
    txv1evenPt_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenPt_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1evenPt_label->Draw();

    cv1evenPt->Print("figures/integralVN/systematics/v1_Sym_syst_N1MC22SUB3_pt.pdf","pdf");



    //-- centrality dependence of integral v1odd(eta) SUB3 for tracker cuts
    TCanvas * cv1oddEta_cut = new TCanvas("cv1oddEta_cut", "cv1oddEta_cut", 1300, 650);
    cv1oddEta_cut->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1oddEta_cut = (TPad *) cv1oddEta_cut->cd(cbin+1);
        if (gridlines) padv1oddEta_cut->SetGrid();
        if (cbin == 4 || cbin == 9) padv1oddEta_cut->SetRightMargin(0.02);
        if (cbin <= 4) padv1oddEta_cut->SetTopMargin(0.1);
        if (cbin > 4) padv1oddEta_cut->SetBottomMargin(0.25);

        TH1D * hv1oddEta_cut = new TH1D(Form("hv1oddEta_cut_%d",cbin), "", 50, -2.8, 2.8);
        hv1oddEta_cut->SetXTitle("#eta");
        hv1oddEta_cut->SetYTitle("v_{1}^{odd}");
        hv1oddEta_cut->GetXaxis()->CenterTitle();
        hv1oddEta_cut->GetYaxis()->CenterTitle();
        hv1oddEta_cut->GetYaxis()->SetRangeUser(-0.022, 0.022);
        hv1oddEta_cut->GetYaxis()->SetNdivisions(509);
        hv1oddEta_cut->GetYaxis()->SetTitleSize(0.07);
        hv1oddEta_cut->GetYaxis()->SetLabelSize(0.05);
        hv1oddEta_cut->GetYaxis()->SetTitleOffset(1.20);
        hv1oddEta_cut->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1oddEta_cut->GetXaxis()->SetTitleSize(0.07);
            hv1oddEta_cut->GetXaxis()->SetLabelSize(0.05);
            hv1oddEta_cut->GetXaxis()->SetTitleOffset(1.00);
            hv1oddEta_cut->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1oddEta_cut->GetXaxis()->SetTitleSize(0.08);
            hv1oddEta_cut->GetXaxis()->SetLabelSize(0.06);
            hv1oddEta_cut->GetXaxis()->SetTitleOffset(0.83);
            hv1oddEta_cut->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1oddEta_cut->Draw();

        gN1SUB3_cut_eta[cbin]->SetMarkerColor(kBlue);
        gN1SUB3_cut_eta[cbin]->SetLineColor(kBlue);
        gN1SUB3_cut_eta[cbin]->SetMarkerStyle(21);
        gN1SUB3_cut_eta[cbin]->SetMarkerSize(1.1);
        gN1SUB3_cut_eta[cbin]->SetFillColor(kGray+1);
        gN1SUB3_cut_eta[cbin]->Draw("same []2");

        N1SUB3_Sym_eta[cbin]->Draw("same");

        TPaveText * txv1oddEta_cut_cent;
        if (cbin == 0) txv1oddEta_cut_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1oddEta_cut_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1oddEta_cut_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1oddEta_cut_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1oddEta_cut_cent, 17);
        txv1oddEta_cut_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1oddEta_cut_cent->Draw();
    }
    cv1oddEta_cut->cd(1);
    TPaveText * txv1oddEta_cut_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1oddEta_cut_CMS, 16);
    txv1oddEta_cut_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddEta_cut_CMS->Draw();

    TPaveText * txv1oddEta_cut_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1oddEta_cut_label, 16);
    txv1oddEta_cut_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddEta_cut_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1oddEta_cut_label->Draw();

    cv1oddEta_cut->Print("figures/integralVN/systematics/v1_cut_syst_N1SUB3_eta.pdf","pdf");



    //-- centrality dependence of integral v1pt(pt) SUB3 for tracker cuts
    TCanvas * cv1evenPt_cut = new TCanvas("cv1evenPt_cut", "cv1evenPt_cut", 1300, 650);
    cv1evenPt_cut->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1evenPt_cut = (TPad *) cv1evenPt_cut->cd(cbin+1);
        if (gridlines) padv1evenPt_cut->SetGrid();
        if (cbin == 4 || cbin == 9) padv1evenPt_cut->SetRightMargin(0.02);
        if (cbin <= 4) padv1evenPt_cut->SetTopMargin(0.1);
        if (cbin > 4) padv1evenPt_cut->SetBottomMargin(0.25);

        TH1D * hv1evenPt_cut = new TH1D(Form("hv1evenPt_cut_%d",cbin), "", 50, 0, 12);
        hv1evenPt_cut->SetXTitle("p_{T} (GeV/c)");
        hv1evenPt_cut->SetYTitle("v_{1}^{even}");
        hv1evenPt_cut->GetXaxis()->CenterTitle();
        hv1evenPt_cut->GetYaxis()->CenterTitle();
        hv1evenPt_cut->GetYaxis()->SetRangeUser(-0.05, 0.22);
        hv1evenPt_cut->GetYaxis()->SetNdivisions(509);
        hv1evenPt_cut->GetYaxis()->SetTitleSize(0.07);
        hv1evenPt_cut->GetYaxis()->SetLabelSize(0.05);
        hv1evenPt_cut->GetYaxis()->SetTitleOffset(1.20);
        hv1evenPt_cut->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1evenPt_cut->GetXaxis()->SetTitleSize(0.07);
            hv1evenPt_cut->GetXaxis()->SetLabelSize(0.05);
            hv1evenPt_cut->GetXaxis()->SetTitleOffset(1.00);
            hv1evenPt_cut->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1evenPt_cut->GetXaxis()->SetTitleSize(0.08);
            hv1evenPt_cut->GetXaxis()->SetLabelSize(0.06);
            hv1evenPt_cut->GetXaxis()->SetTitleOffset(0.83);
            hv1evenPt_cut->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1evenPt_cut->Draw();

        gN1MC22SUB3_cut_pt[cbin]->SetMarkerColor(kBlue);
        gN1MC22SUB3_cut_pt[cbin]->SetLineColor(kBlue);
        gN1MC22SUB3_cut_pt[cbin]->SetMarkerStyle(21);
        gN1MC22SUB3_cut_pt[cbin]->SetMarkerSize(1.1);
        gN1MC22SUB3_cut_pt[cbin]->SetFillColor(kGray+1);
        gN1MC22SUB3_cut_pt[cbin]->Draw("same []2");

        N1MC22SUB3_Sym_pt[cbin]->Draw("same");

        TPaveText * txv1evenPt_cut_cent;
        if (cbin == 0) txv1evenPt_cut_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1evenPt_cut_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1evenPt_cut_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1evenPt_cut_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1evenPt_cut_cent, 17);
        txv1evenPt_cut_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1evenPt_cut_cent->Draw();
    }
    cv1evenPt_cut->cd(1);
    TPaveText * txv1evenPt_cut_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1evenPt_cut_CMS, 16);
    txv1evenPt_cut_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenPt_cut_CMS->Draw();

    TPaveText * txv1evenPt_cut_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1evenPt_cut_label, 16);
    txv1evenPt_cut_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenPt_cut_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1evenPt_cut_label->Draw();

    cv1evenPt->Print("figures/integralVN/systematics/v1_cut_syst_N1MC22SUB3_pt.pdf","pdf");



    //-- final systematics---------------

    //-- centrality dependence of integral v1odd(eta) SUB3 (final)
    TCanvas * cv1oddEta_final = new TCanvas("cv1oddEta_final", "cv1oddEta_final", 1300, 650);
    cv1oddEta_final->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1oddEta_final = (TPad *) cv1oddEta_final->cd(cbin+1);
        if (gridlines) padv1oddEta_final->SetGrid();
        if (cbin == 4 || cbin == 9) padv1oddEta_final->SetRightMargin(0.02);
        if (cbin <= 4) padv1oddEta_final->SetTopMargin(0.1);
        if (cbin > 4) padv1oddEta_final->SetBottomMargin(0.25);

        TH1D * hv1oddEta_final = new TH1D(Form("hv1oddEta_final_%d",cbin), "", 50, -2.8, 2.8);
        hv1oddEta_final->SetXTitle("#eta");
        hv1oddEta_final->SetYTitle("v_{1}^{odd}");
        hv1oddEta_final->GetXaxis()->CenterTitle();
        hv1oddEta_final->GetYaxis()->CenterTitle();
        hv1oddEta_final->GetYaxis()->SetRangeUser(-0.022, 0.022);
        hv1oddEta_final->GetYaxis()->SetNdivisions(509);
        hv1oddEta_final->GetYaxis()->SetTitleSize(0.07);
        hv1oddEta_final->GetYaxis()->SetLabelSize(0.05);
        hv1oddEta_final->GetYaxis()->SetTitleOffset(1.20);
        hv1oddEta_final->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1oddEta_final->GetXaxis()->SetTitleSize(0.07);
            hv1oddEta_final->GetXaxis()->SetLabelSize(0.05);
            hv1oddEta_final->GetXaxis()->SetTitleOffset(1.00);
            hv1oddEta_final->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1oddEta_final->GetXaxis()->SetTitleSize(0.08);
            hv1oddEta_final->GetXaxis()->SetLabelSize(0.06);
            hv1oddEta_final->GetXaxis()->SetTitleOffset(0.83);
            hv1oddEta_final->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1oddEta_final->Draw();

        gN1SUB3_final_eta[cbin]->SetMarkerColor(kBlue);
        gN1SUB3_final_eta[cbin]->SetLineColor(kBlue);
        gN1SUB3_final_eta[cbin]->SetMarkerStyle(21);
        gN1SUB3_final_eta[cbin]->SetMarkerSize(1.1);
        gN1SUB3_final_eta[cbin]->SetFillColor(kGray+1);
        gN1SUB3_final_eta[cbin]->Draw("same []2");

        N1SUB3_Sym_eta[cbin]->Draw("same");

        TPaveText * txv1oddEta_final_cent;
        if (cbin == 0) txv1oddEta_final_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1oddEta_final_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1oddEta_final_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1oddEta_final_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1oddEta_final_cent, 17);
        txv1oddEta_final_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1oddEta_final_cent->Draw();
    }
    cv1oddEta_final->cd(1);
    TPaveText * txv1oddEta_final_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1oddEta_final_CMS, 16);
    txv1oddEta_final_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddEta_final_CMS->Draw();

    TPaveText * txv1oddEta_final_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1oddEta_final_label, 16);
    txv1oddEta_final_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddEta_final_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1oddEta_final_label->Draw();

    cv1oddEta_final->Print("figures/integralVN/systematics/v1_final_syst_N1SUB3_eta.pdf","pdf");



    //-- centrality dependence of integral v1pt(pt) SUB3 (final)
    TCanvas * cv1evenPt_final = new TCanvas("cv1evenPt_final", "cv1evenPt_final", 1300, 650);
    cv1evenPt_final->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1evenPt_final = (TPad *) cv1evenPt_final->cd(cbin+1);
        if (gridlines) padv1evenPt_final->SetGrid();
        if (cbin == 4 || cbin == 9) padv1evenPt_final->SetRightMargin(0.02);
        if (cbin <= 4) padv1evenPt_final->SetTopMargin(0.1);
        if (cbin > 4) padv1evenPt_final->SetBottomMargin(0.25);

        TH1D * hv1evenPt_final = new TH1D(Form("hv1evenPt_final_%d",cbin), "", 50, 0, 12);
        hv1evenPt_final->SetXTitle("p_{T} (GeV/c)");
        hv1evenPt_final->SetYTitle("v_{1}^{even}");
        hv1evenPt_final->GetXaxis()->CenterTitle();
        hv1evenPt_final->GetYaxis()->CenterTitle();
        hv1evenPt_final->GetYaxis()->SetRangeUser(-0.05, 0.22);
        hv1evenPt_final->GetYaxis()->SetNdivisions(509);
        hv1evenPt_final->GetYaxis()->SetTitleSize(0.07);
        hv1evenPt_final->GetYaxis()->SetLabelSize(0.05);
        hv1evenPt_final->GetYaxis()->SetTitleOffset(1.20);
        hv1evenPt_final->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1evenPt_final->GetXaxis()->SetTitleSize(0.07);
            hv1evenPt_final->GetXaxis()->SetLabelSize(0.05);
            hv1evenPt_final->GetXaxis()->SetTitleOffset(1.00);
            hv1evenPt_final->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1evenPt_final->GetXaxis()->SetTitleSize(0.08);
            hv1evenPt_final->GetXaxis()->SetLabelSize(0.06);
            hv1evenPt_final->GetXaxis()->SetTitleOffset(0.83);
            hv1evenPt_final->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1evenPt_final->Draw();

        gN1MC22SUB3_final_pt[cbin]->SetMarkerColor(kBlue);
        gN1MC22SUB3_final_pt[cbin]->SetLineColor(kBlue);
        gN1MC22SUB3_final_pt[cbin]->SetMarkerStyle(21);
        gN1MC22SUB3_final_pt[cbin]->SetMarkerSize(1.1);
        gN1MC22SUB3_final_pt[cbin]->SetFillColor(kGray+1);
        gN1MC22SUB3_final_pt[cbin]->Draw("same []2");

        N1MC22SUB3_Sym_pt[cbin]->Draw("same");

        TPaveText * txv1evenPt_final_cent;
        if (cbin == 0) txv1evenPt_final_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1evenPt_final_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1evenPt_final_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1evenPt_final_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1evenPt_final_cent, 17);
        txv1evenPt_final_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1evenPt_final_cent->Draw();
    }
    cv1evenPt_final->cd(1);
    TPaveText * txv1evenPt_final_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1evenPt_final_CMS, 16);
    txv1evenPt_final_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenPt_final_CMS->Draw();

    TPaveText * txv1evenPt_final_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1evenPt_final_label, 16);
    txv1evenPt_final_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenPt_final_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1evenPt_final_label->Draw();

    cv1evenPt->Print("figures/integralVN/systematics/v1_final_syst_N1MC22SUB3_pt.pdf","pdf");


}
