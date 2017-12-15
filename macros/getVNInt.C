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
TH1D * N1SUB3_eta[ncbins];

TH1D * vnA_pt[nanals][ncbins];
TH1D * vnB_pt[nanals][ncbins];
TH1D * vnAB_pt[nanals][ncbins];
TH1D * N1SUB3_pt[ncbins];

TFile * tfin;

void getVNInt()
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

    //-- average N1SUB3
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB3_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB3][cbin]->Clone(Form("N1SUB3_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_eta[cbin]->Add(vnAB_eta[N1BSUB3][cbin]);
        N1SUB3_eta[cbin]->Scale(0.5);
        N1SUB3_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB3][cbin]->Clone(Form("N1SUB3_pt_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_pt[cbin]->Add(vnAB_pt[N1BSUB3][cbin]);
        N1SUB3_pt[cbin]->Scale(0.5);
    }


    //-- previous CMS results for v2 comparison
    # include "data/HIN-10-002.h"
    TH1D * v2HIN_10_002_eta[12];
    for (int cbin = 0; cbin<12; cbin++) {
        v2HIN_10_002_eta[cbin] = new TH1D(Form("v2HIN_10_002_eta_%d",cbin), "", netabins, etabins);
    }
    for (int ebin = 0; ebin<netabins; ebin++) {
        v2HIN_10_002_eta[0]->SetBinContent(ebin+1, v2Ecent0to5[ebin]);
        v2HIN_10_002_eta[0]->SetBinError(ebin+1, v2Ecent0to5Err[ebin]);
        v2HIN_10_002_eta[1]->SetBinContent(ebin+1, v2Ecent5to10[ebin]);
        v2HIN_10_002_eta[1]->SetBinError(ebin+1, v2Ecent5to10Err[ebin]);
        v2HIN_10_002_eta[2]->SetBinContent(ebin+1, v2Ecent10to15[ebin]);
        v2HIN_10_002_eta[2]->SetBinError(ebin+1, v2Ecent10to15Err[ebin]);
        v2HIN_10_002_eta[3]->SetBinContent(ebin+1, v2Ecent15to20[ebin]);
        v2HIN_10_002_eta[3]->SetBinError(ebin+1, v2Ecent15to20Err[ebin]);
        v2HIN_10_002_eta[4]->SetBinContent(ebin+1, v2Ecent20to25[ebin]);
        v2HIN_10_002_eta[4]->SetBinError(ebin+1, v2Ecent20to25Err[ebin]);
        v2HIN_10_002_eta[5]->SetBinContent(ebin+1, v2Ecent25to30[ebin]);
        v2HIN_10_002_eta[5]->SetBinError(ebin+1, v2Ecent25to30Err[ebin]);
        v2HIN_10_002_eta[6]->SetBinContent(ebin+1, v2Ecent30to35[ebin]);
        v2HIN_10_002_eta[6]->SetBinError(ebin+1, v2Ecent30to35Err[ebin]);
        v2HIN_10_002_eta[7]->SetBinContent(ebin+1, v2Ecent35to40[ebin]);
        v2HIN_10_002_eta[7]->SetBinError(ebin+1, v2Ecent35to40Err[ebin]);
        v2HIN_10_002_eta[8]->SetBinContent(ebin+1, v2Ecent40to50[ebin]);
        v2HIN_10_002_eta[8]->SetBinError(ebin+1, v2Ecent40to50Err[ebin]);
        v2HIN_10_002_eta[9]->SetBinContent(ebin+1, v2Ecent50to60[ebin]);
        v2HIN_10_002_eta[9]->SetBinError(ebin+1, v2Ecent50to60Err[ebin]);
        v2HIN_10_002_eta[10]->SetBinContent(ebin+1, v2Ecent60to70[ebin]);
        v2HIN_10_002_eta[10]->SetBinError(ebin+1, v2Ecent60to70Err[ebin]);
    }

    TLine * lnEta = new TLine(-2.4, 0.0, 2.4, 0.0);
    TLine * lnPt  = new TLine(0.0, 0.0, 12.0, 0.0);

    if (!fopen("figures/integralVN","r")) system("mkdir figures/integralVN");
    if (!fopen("figures/integralVN/data","r")) system("mkdir figures/integralVN/data");



    //-- centrality dependence of integral v1^odd(eta) with both 2-and 3-subevent methods
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

        N1SUB3_eta[cbin]->SetMarkerColor(kBlue);
        N1SUB3_eta[cbin]->SetLineColor(kBlue);
        N1SUB3_eta[cbin]->SetMarkerStyle(21);
        N1SUB3_eta[cbin]->SetMarkerSize(1.1);
        N1SUB3_eta[cbin]->Draw("same");

        vnAB_eta[N1ASUB2][cbin]->SetMarkerColor(kRed);
        vnAB_eta[N1ASUB2][cbin]->SetLineColor(kRed);
        vnAB_eta[N1ASUB2][cbin]->SetMarkerStyle(25);
        vnAB_eta[N1ASUB2][cbin]->SetMarkerSize(1.1);
        vnAB_eta[N1ASUB2][cbin]->Draw("same");

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

    TLegend * legv1oddEta = new TLegend(0.23, 0.05, 0.60, 0.23);
    SetLegend(legv1oddEta, 16);
    legv1oddEta->AddEntry(vnAB_eta[N1ASUB2][0],"v_{1}^{odd}{SUB2}","p");
    legv1oddEta->AddEntry(N1SUB3_eta[0],"v_{1}^{odd}{SUB3}","p");
    legv1oddEta->Draw();

    cv1oddEta->Print("figures/integralVN/v1odd_eta_SUB2_SUB3.pdf","pdf");



    //-- centrality dependence of integral v1^odd(eta) with just the 3-subevent methods
    TCanvas * cv1oddEtaSUB3 = new TCanvas("cv1oddEtaSUB3", "cv1oddEtaSUB3", 1300, 650);
    cv1oddEtaSUB3->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1oddEtaSUB3 = (TPad *) cv1oddEtaSUB3->cd(cbin+1);
        if (gridlines) padv1oddEtaSUB3->SetGrid();
        if (cbin == 4 || cbin == 9) padv1oddEtaSUB3->SetRightMargin(0.02);
        if (cbin <= 4) padv1oddEtaSUB3->SetTopMargin(0.1);
        if (cbin > 4) padv1oddEtaSUB3->SetBottomMargin(0.25);

        TH1D * hv1oddEtaSUB3 = new TH1D(Form("hv1oddEtaSUB3_%d",cbin), "", 50, -2.8, 2.8);
        hv1oddEtaSUB3->SetXTitle("#eta");
        hv1oddEtaSUB3->SetYTitle("v_{1}^{odd}");
        hv1oddEtaSUB3->GetXaxis()->CenterTitle();
        hv1oddEtaSUB3->GetYaxis()->CenterTitle();
        hv1oddEtaSUB3->GetYaxis()->SetRangeUser(-0.022, 0.022);
        hv1oddEtaSUB3->GetYaxis()->SetNdivisions(509);
        hv1oddEtaSUB3->GetYaxis()->SetTitleSize(0.07);
        hv1oddEtaSUB3->GetYaxis()->SetLabelSize(0.05);
        hv1oddEtaSUB3->GetYaxis()->SetTitleOffset(1.20);
        hv1oddEtaSUB3->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1oddEtaSUB3->GetXaxis()->SetTitleSize(0.07);
            hv1oddEtaSUB3->GetXaxis()->SetLabelSize(0.05);
            hv1oddEtaSUB3->GetXaxis()->SetTitleOffset(1.00);
            hv1oddEtaSUB3->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1oddEtaSUB3->GetXaxis()->SetTitleSize(0.08);
            hv1oddEtaSUB3->GetXaxis()->SetLabelSize(0.06);
            hv1oddEtaSUB3->GetXaxis()->SetTitleOffset(0.83);
            hv1oddEtaSUB3->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1oddEtaSUB3->Draw();

        N1SUB3_eta[cbin]->SetMarkerColor(kBlue);
        N1SUB3_eta[cbin]->SetLineColor(kBlue);
        N1SUB3_eta[cbin]->SetMarkerStyle(21);
        N1SUB3_eta[cbin]->SetMarkerSize(1.1);
        N1SUB3_eta[cbin]->Draw("same");

        TPaveText * txv1oddEtaSUB3_cent;
        if (cbin == 0) txv1oddEtaSUB3_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1oddEtaSUB3_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1oddEtaSUB3_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1oddEtaSUB3_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1oddEtaSUB3_cent, 17);
        txv1oddEtaSUB3_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1oddEtaSUB3_cent->Draw();
    }
    cv1oddEtaSUB3->cd(1);
    TPaveText * txv1oddEtaSUB3_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1oddEtaSUB3_CMS, 16);
    txv1oddEtaSUB3_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1oddEtaSUB3_CMS->Draw();

    TPaveText * txv1oddEtaSUB3_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1oddEtaSUB3_label, 16);
    txv1oddEtaSUB3_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1oddEtaSUB3_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1oddEtaSUB3_label->Draw();

    cv1oddEtaSUB3->Print("figures/integralVN/v1odd_eta_SUB3.pdf","pdf");



    //-- centrality dependence of integral v1(eta) using just HF+ and HF-
    TCanvas * cv1pmEta = new TCanvas("cv1pmEta", "cv1pmEta", 1300, 650);
    cv1pmEta->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1pmEta = (TPad *) cv1pmEta->cd(cbin+1);
        if (gridlines) padv1pmEta->SetGrid();
        if (cbin == 4 || cbin == 9) padv1pmEta->SetRightMargin(0.02);
        if (cbin <= 4) padv1pmEta->SetTopMargin(0.1);
        if (cbin > 4) padv1pmEta->SetBottomMargin(0.25);

        TH1D * hv1pmEta = new TH1D(Form("hv1pmEta_%d",cbin), "", 50, -2.8, 2.8);
        hv1pmEta->SetXTitle("#eta");
        hv1pmEta->SetYTitle("v_{1}");
        hv1pmEta->GetXaxis()->CenterTitle();
        hv1pmEta->GetYaxis()->CenterTitle();
        hv1pmEta->GetYaxis()->SetRangeUser(-0.09, 0.09);
        hv1pmEta->GetYaxis()->SetNdivisions(509);
        hv1pmEta->GetYaxis()->SetTitleSize(0.07);
        hv1pmEta->GetYaxis()->SetLabelSize(0.05);
        hv1pmEta->GetYaxis()->SetTitleOffset(1.20);
        hv1pmEta->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1pmEta->GetXaxis()->SetTitleSize(0.07);
            hv1pmEta->GetXaxis()->SetLabelSize(0.05);
            hv1pmEta->GetXaxis()->SetTitleOffset(1.00);
            hv1pmEta->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1pmEta->GetXaxis()->SetTitleSize(0.08);
            hv1pmEta->GetXaxis()->SetLabelSize(0.06);
            hv1pmEta->GetXaxis()->SetTitleOffset(0.83);
            hv1pmEta->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1pmEta->Draw();

        vnA_eta[N1ASUB3][cbin]->SetMarkerColor(kMagenta);
        vnA_eta[N1ASUB3][cbin]->SetLineColor(kMagenta);
        vnA_eta[N1ASUB3][cbin]->SetMarkerStyle(28);
        vnA_eta[N1ASUB3][cbin]->SetMarkerSize(1.2);
        vnA_eta[N1ASUB3][cbin]->Draw("same");

        vnA_eta[N1BSUB3][cbin]->SetMarkerColor(kCyan+2);
        vnA_eta[N1BSUB3][cbin]->SetLineColor(kCyan+2);
        vnA_eta[N1BSUB3][cbin]->SetMarkerStyle(28);
        vnA_eta[N1BSUB3][cbin]->SetMarkerSize(1.2);
        vnA_eta[N1BSUB3][cbin]->Draw("same");

        TPaveText * txv1pmEta_cent;
        if (cbin == 0) txv1pmEta_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1pmEta_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1pmEta_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1pmEta_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1pmEta_cent, 17);
        txv1pmEta_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1pmEta_cent->Draw();
    }
    cv1pmEta->cd(1);
    TPaveText * txv1pmEta_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1pmEta_CMS, 16);
    txv1pmEta_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1pmEta_CMS->Draw();

    TPaveText * txv1pmEta_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1pmEta_label, 16);
    txv1pmEta_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1pmEta_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1pmEta_label->Draw();

    TLegend * legv1pmEta = new TLegend(0.23, 0.05, 0.60, 0.23);
    SetLegend(legv1pmEta, 16);
    legv1pmEta->AddEntry(vnA_eta[N1ASUB3][0],"v_{1}{HF+ only}","p");
    legv1pmEta->AddEntry(vnA_eta[N1BSUB3][0],"v_{1}{HF- only}","p");
    legv1pmEta->Draw();

    cv1pmEta->Print("figures/integralVN/v1pm_eta_SUB3.pdf","pdf");



    //-- centrality dependence of integral v1^even(pT)
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
        hv1evenPt->GetYaxis()->SetRangeUser(-0.025, 0.195);
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

        vnAB_pt[N1MCp22SUB3][cbin]->SetMarkerColor(kBlue);
        vnAB_pt[N1MCp22SUB3][cbin]->SetLineColor(kBlue);
        vnAB_pt[N1MCp22SUB3][cbin]->SetMarkerStyle(21);
        vnAB_pt[N1MCp22SUB3][cbin]->SetMarkerSize(1.1);
        vnAB_pt[N1MCp22SUB3][cbin]->Draw("same");

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
    SetTPaveTxt(txv1evenPt_CMS, 18);
    txv1evenPt_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenPt_CMS->Draw();

    TPaveText * txv1evenPt_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1evenPt_label, 16);
    txv1evenPt_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenPt_label->AddText("|#eta| < 2.4");
    txv1evenPt_label->Draw();

    cv1evenPt->Print("figures/integralVN/v1even_pt_N1MC22SUB3.pdf","pdf");



    //-- centrality dependence of integral v1^even(pT)
    TCanvas * cv1evenEta = new TCanvas("cv1evenEta", "cv1evenEta", 1300, 650);
    cv1evenEta->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padv1evenEta = (TPad *) cv1evenEta->cd(cbin+1);
        if (gridlines) padv1evenEta->SetGrid();
        if (cbin == 4 || cbin == 9) padv1evenEta->SetRightMargin(0.02);
        if (cbin <= 4) padv1evenEta->SetTopMargin(0.1);
        if (cbin > 4) padv1evenEta->SetBottomMargin(0.25);

        TH1D * hv1evenEta = new TH1D(Form("hv1evenEta_%d",cbin), "", 50, -2.8, 2.8);
        hv1evenEta->SetXTitle("#eta");
        hv1evenEta->SetYTitle("v_{1}^{even}");
        hv1evenEta->GetXaxis()->CenterTitle();
        hv1evenEta->GetYaxis()->CenterTitle();
        hv1evenEta->GetYaxis()->SetRangeUser(-0.045, 0.02);
        hv1evenEta->GetYaxis()->SetNdivisions(509);
        hv1evenEta->GetYaxis()->SetTitleSize(0.07);
        hv1evenEta->GetYaxis()->SetLabelSize(0.05);
        hv1evenEta->GetYaxis()->SetTitleOffset(1.20);
        hv1evenEta->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hv1evenEta->GetXaxis()->SetTitleSize(0.07);
            hv1evenEta->GetXaxis()->SetLabelSize(0.05);
            hv1evenEta->GetXaxis()->SetTitleOffset(1.00);
            hv1evenEta->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hv1evenEta->GetXaxis()->SetTitleSize(0.08);
            hv1evenEta->GetXaxis()->SetLabelSize(0.06);
            hv1evenEta->GetXaxis()->SetTitleOffset(0.83);
            hv1evenEta->GetXaxis()->SetLabelOffset(0.011);
        }

        hv1evenEta->Draw();

        vnAB_eta[N1MCp22SUB3][cbin]->SetMarkerColor(kBlue);
        vnAB_eta[N1MCp22SUB3][cbin]->SetLineColor(kBlue);
        vnAB_eta[N1MCp22SUB3][cbin]->SetMarkerStyle(21);
        vnAB_eta[N1MCp22SUB3][cbin]->SetMarkerSize(1.1);
        vnAB_eta[N1MCp22SUB3][cbin]->Draw("same");

        vnA_eta[N1MCp22SUB3][cbin]->SetMarkerColor(kMagenta);
        vnA_eta[N1MCp22SUB3][cbin]->SetLineColor(kMagenta);
        vnA_eta[N1MCp22SUB3][cbin]->SetMarkerStyle(28);
        vnA_eta[N1MCp22SUB3][cbin]->SetMarkerSize(1.4);
        vnA_eta[N1MCp22SUB3][cbin]->Draw("same");

        vnB_eta[N1MCp22SUB3][cbin]->SetMarkerColor(kCyan+2);
        vnB_eta[N1MCp22SUB3][cbin]->SetLineColor(kCyan+2);
        vnB_eta[N1MCp22SUB3][cbin]->SetMarkerStyle(28);
        vnB_eta[N1MCp22SUB3][cbin]->SetMarkerSize(1.4);
        vnB_eta[N1MCp22SUB3][cbin]->Draw("same");

        // vnAB_eta[N1MCm22SUB3][cbin]->SetMarkerColor(kBlue);
        // vnAB_eta[N1MCm22SUB3][cbin]->SetLineColor(kBlue);
        // vnAB_eta[N1MCm22SUB3][cbin]->SetMarkerStyle(21);
        // vnAB_eta[N1MCm22SUB3][cbin]->SetMarkerSize(1.1);
        // vnAB_eta[N1MCm22SUB3][cbin]->Draw("same");
        //
        // vnA_eta[N1MCm22SUB3][cbin]->SetMarkerColor(kMagenta);
        // vnA_eta[N1MCm22SUB3][cbin]->SetLineColor(kMagenta);
        // vnA_eta[N1MCm22SUB3][cbin]->SetMarkerStyle(28);
        // vnA_eta[N1MCm22SUB3][cbin]->SetMarkerSize(1.4);
        // vnA_eta[N1MCm22SUB3][cbin]->Draw("same");
        //
        // vnB_eta[N1MCm22SUB3][cbin]->SetMarkerColor(kCyan+2);
        // vnB_eta[N1MCm22SUB3][cbin]->SetLineColor(kCyan+2);
        // vnB_eta[N1MCm22SUB3][cbin]->SetMarkerStyle(28);
        // vnB_eta[N1MCm22SUB3][cbin]->SetMarkerSize(1.4);
        // vnB_eta[N1MCm22SUB3][cbin]->Draw("same");

        TPaveText * txv1evenEta_cent;
        if (cbin == 0) txv1evenEta_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txv1evenEta_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txv1evenEta_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txv1evenEta_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txv1evenEta_cent, 17);
        txv1evenEta_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txv1evenEta_cent->Draw();
    }
    cv1evenEta->cd(1);
    TPaveText * txv1evenEta_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txv1evenEta_CMS, 18);
    txv1evenEta_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txv1evenEta_CMS->Draw();

    TPaveText * txv1evenEta_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txv1evenEta_label, 16);
    txv1evenEta_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txv1evenEta_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txv1evenEta_label->Draw();

    TLegend * legv1evenEta = new TLegend(0.23, 0.05, 0.60, 0.23);
    SetLegend(legv1evenEta, 16);
    legv1evenEta->AddEntry(vnA_eta[N1MCp22SUB3][0],"Track+ only","p");
    legv1evenEta->AddEntry(vnB_eta[N1MCp22SUB3][0],"Track- only","p");
    legv1evenEta->AddEntry(vnAB_eta[N1MCp22SUB3][0],"N1MCp22SUB3","p");

    legv1evenEta->Draw();

    cv1evenEta->Print("figures/integralVN/v1even_eta_N1MC22SUB3.pdf","pdf");


}
