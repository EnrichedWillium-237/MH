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
static const int nanals = 10;
enum AnalType {
    N1MCm22SUB3, N1MCp22SUB3, N112ASUB2, N112ASUB3, N123ASUB2, N123ASUB3, N1SUB2, N1SUB3, N2SUB2, N2SUB3};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCp22SUB3", "N112ASUB2", "N112ASUB3", "N123ASUB2", "N123ASUB3", "N1SUB2", "N1SUB3", "N2SUB2", "N2SUB3"};
string ytitle[] = {
        "v_{1}\{#Psi_{1,MC}\} (-2.4<#eta<-2.0)", "v_{1}\{#Psi_{1,MC}\} (2.0<#eta<2.4)",
        "v_{1}\{#Psi_{1},#Psi_{2}\}",            "v_{1}\{#Psi_{1},#Psi_{2}\}",
        "v_{1}\{#Psi_{2},#Psi_{3}\}",            "v_{1}\{#Psi_{2},#Psi_{3}\}",
        "v_{1}\{#Psi_{1}\}",                     "v_{1}\{#Psi_{1}\}",
        "v_{2}\{#Psi_{2}\}",                     "v_{2}\{#Psi_{2}\}"
};

using namespace std;

//  track cut, analysis type, etabin,
TH1D * vnA[3][netabins][nanals];
TH1D * vnB[3][netabins][nanals];
TH1D * vnAB[3][netabins][nanals];

TH1D * vnArat[netabins][nanals];
TH1D * vnBrat[netabins][nanals];
TH1D * vnABrat[netabins][nanals];

TH1D * vnABrat_int[3][nanals];

TFile * tfin;

void pTratios()
{

    TH1::SetDefaultSumw2();

    int centbin = 2;

    for (int cut = 0; cut<3; cut++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            for (int anal = 0; anal<nanals; anal++) {
                string tag = "";
                if (cut == 0) tag = Form("useTight_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                if (cut == 1) tag = Form("useTightB_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                if (cut == 2) tag = Form("useLoose_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                tfin = new TFile(Form("../results/results_%s/%s.root",tag.data(),AnalNames[anal].data()));

                vnA[cut][ebin][anal] = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[centbin],cmax[centbin]));
                vnB[cut][ebin][anal] = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[centbin],cmax[centbin]));
                vnAB[cut][ebin][anal] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[centbin],cmax[centbin]));

                vnA[cut][ebin][anal]->SetMarkerColor(kMagenta);
                vnA[cut][ebin][anal]->SetLineColor(kMagenta);
                vnA[cut][ebin][anal]->SetMarkerStyle(28);
                vnA[cut][ebin][anal]->SetMarkerSize(1.3);
                vnA[cut][ebin][anal]->SetXTitle("p_{T} (GeV/c)");
                vnA[cut][ebin][anal]->SetYTitle(Form("%s",ytitle[anal].data()));
                if (anal<=1) vnA[cut][ebin][anal]->GetYaxis()->SetRangeUser(-0.04, 0.22);
                else vnA[cut][ebin][anal]->GetYaxis()->SetRangeUser(-0.2, 0.2);

                vnB[cut][ebin][anal]->SetMarkerColor(kCyan+2);
                vnB[cut][ebin][anal]->SetLineColor(kCyan+2);
                vnB[cut][ebin][anal]->SetMarkerStyle(28);
                vnB[cut][ebin][anal]->SetMarkerSize(1.3);
                vnB[cut][ebin][anal]->SetXTitle("p_{T} (GeV/c)");
                if (anal<=1) vnB[cut][ebin][anal]->SetYTitle(Form("%s",ytitle[anal].data()));
                else vnB[cut][ebin][anal]->GetYaxis()->SetRangeUser(-0.18, 0.18);

                vnAB[cut][ebin][anal]->SetMarkerColor(kBlue);
                vnAB[cut][ebin][anal]->SetLineColor(kBlue);
                vnAB[cut][ebin][anal]->SetMarkerStyle(21);
                vnAB[cut][ebin][anal]->SetMarkerSize(1.2);
                vnAB[cut][ebin][anal]->SetXTitle("p_{T} (GeV/c)");
                if (anal<=1) vnAB[cut][ebin][anal]->SetYTitle(Form("%s",ytitle[anal].data()));
                else vnAB[cut][ebin][anal]->GetYaxis()->SetRangeUser(-0.2, 0.2);
            }
        }
    }

    for (int ebin = 0; ebin<netabins; ebin++) {
        for (int anal = 0; anal<nanals; anal++) {
            vnArat[ebin][anal] = (TH1D *) vnA[0][ebin][anal]->Clone(Form("vnArat_%s_%1.1f_%1.1f",AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]));
            vnBrat[ebin][anal] = (TH1D *) vnB[0][ebin][anal]->Clone(Form("vnBrat_%s_%1.1f_%1.1f",AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]));
            vnABrat[ebin][anal] = (TH1D *) vnAB[0][ebin][anal]->Clone(Form("vnABrat_%s_%1.1f_%1.1f",AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]));

            vnArat[ebin][anal]->Divide(vnA[1][ebin][anal]);
            vnBrat[ebin][anal]->Divide(vnB[1][ebin][anal]);
            vnABrat[ebin][anal]->Divide(vnAB[1][ebin][anal]);

            vnArat[ebin][anal]->GetYaxis()->SetRangeUser(0.90, 1.1);
            vnBrat[ebin][anal]->GetYaxis()->SetRangeUser(0.90, 1.1);
            vnABrat[ebin][anal]->GetYaxis()->SetRangeUser(0.90, 1.1);

            vnArat[ebin][anal]->SetMarkerColor(kBlack);
            vnBrat[ebin][anal]->SetMarkerColor(kBlack);
            vnABrat[ebin][anal]->SetMarkerColor(kBlack);

            vnArat[ebin][anal]->SetLineColor(kBlack);
            vnBrat[ebin][anal]->SetLineColor(kBlack);
            vnABrat[ebin][anal]->SetLineColor(kBlack);

            vnArat[ebin][anal]->SetYTitle("v_{1}{tight}/v_{1}{tightB}");
            vnBrat[ebin][anal]->SetYTitle("v_{1}{tight}/v_{1}{tightB}");
            vnABrat[ebin][anal]->SetYTitle("v_{1}{tight}/v_{1}{tightB}");

            vnArat[ebin][anal]->GetYaxis()->SetTitleSize(0.06);
            vnBrat[ebin][anal]->GetYaxis()->SetTitleSize(0.06);
            vnABrat[ebin][anal]->GetYaxis()->SetTitleSize(0.06);

            vnArat[ebin][anal]->GetYaxis()->SetLabelSize(0.06);
            vnBrat[ebin][anal]->GetYaxis()->SetLabelSize(0.06);
            vnABrat[ebin][anal]->GetYaxis()->SetLabelSize(0.06);
        }
    }

    if (!fopen("figures","r")) system("mkdir figures");
    if (!fopen("figures/pT_spectra","r")) system("mkdir figures/pT_spectra");

    TLine * ln_pT = new TLine(0.0, 0.0, 12.0, 0.0);
    ln_pT->SetLineWidth(1);


    // TCanvas * ctest = new TCanvas("ctest","ctest",650,500);
    // TPad * padtest = (TPad *) ctest->cd();
    // padtest->SetGrid();
    // vnA[0][6][0]->Draw();
    // vnB[0][6][0]->Draw("same");
    // vnAB[0][6][0]->Draw("same");
    // ln_pT->Draw();
    // TLegend * legtest = new TLegend(0.63, 0.76, 0.92, 0.92);
    // SetLegend(legtest, 20);
    // legtest->AddEntry(vnAB[0][6][0],Form("%s",AnalNames[0].data()),"p");
    // legtest->AddEntry(vnA[0][6][0],"track+ only","p");
    // legtest->AddEntry(vnB[0][6][0],"track- only","p");
    // legtest->Draw();
    // TPaveText * txtest = new TPaveText(0.21, 0.79, 0.41, 0.93,"NDC");
    // SetTPaveTxt(txtest, 20);
    // txtest->AddText("5 - 10%");
    // txtest->AddText(Form("%1.1f < #eta < %1.1f",etabins[6],etabins[6+1]));
    // txtest->Draw();

    TCanvas * ctest = new TCanvas("ctest","ctest",650,500);
    TPad * padtest = (TPad *) ctest->cd();
    padtest->SetGrid();
    vnAB[0][0][9]->Draw();
    vnAB[1][0][9]->SetMarkerColor(kMagenta);
    vnAB[1][0][9]->SetLineColor(kMagenta);
    vnAB[1][0][9]->Draw("same");
    vnAB[2][0][9]->SetMarkerColor(kCyan+2);
    vnAB[2][0][9]->SetLineColor(kCyan+2);
    vnAB[2][0][9]->Draw("same");
    ln_pT->Draw();
    TLegend * legtest = new TLegend(0.63, 0.76, 0.92, 0.92);
    SetLegend(legtest, 20);
    legtest->AddEntry(vnAB[0][0][9],"Tight","p");
    legtest->AddEntry(vnAB[1][0][9],"TightB","p");
    legtest->AddEntry(vnAB[2][0][9],"Loose","p");
    legtest->Draw();
    TPaveText * txtest = new TPaveText(0.21, 0.79, 0.41, 0.93,"NDC");
    SetTPaveTxt(txtest, 20);
    txtest->AddText("5 - 10%");
    txtest->AddText(Form("%1.1f < #eta < %1.1f",etabins[0],etabins[0+1]));
    txtest->Draw();


/*
    //-- compare pos and neg sides
    for (int cut = 0; cut<3; cut++) {
        string ptag = "";
        if (cut == 0) ptag = "useTight";
        if (cut == 1) ptag = "useTightB";
        if (cut == 2) ptag = "useLoose";
        if (!fopen(Form("figures/pT_spectra/%s",ptag.data()),"r")) system(Form("mkdir figures/pT_spectra/%s",ptag.data()));
        for (int anal = 0; anal<nanals; anal++) {
            if (!fopen(Form("figures/pT_spectra/%s/%s",ptag.data(),AnalNames[anal].data()),"r")) {
                system(Form("mkdir figures/pT_spectra/%s/%s",ptag.data(),AnalNames[anal].data()));
            }
            for (int ebin = 0; ebin<netabins; ebin++) {
                TCanvas * cvnAB_pT = new TCanvas("cvnAB_pT","cvnAB_pT",650,500);
                TPad * padvnAB_pT = (TPad *) cvnAB_pT->cd();
                padvnAB_pT->SetGrid();
                vnA[cut][ebin][anal]->Draw();
                vnB[cut][ebin][anal]->Draw("same");
                vnAB[cut][ebin][anal]->Draw("same");
                ln_pT->Draw();
                TLegend * legvnAB_pT = new TLegend(0.63, 0.76, 0.92, 0.92);
                SetLegend(legvnAB_pT, 20);
                legvnAB_pT->AddEntry(vnAB[cut][ebin][anal],Form("%s",AnalNames[anal].data()),"p");
                if (anal <= 1) {
                    legvnAB_pT->AddEntry(vnA[cut][ebin][anal],"track+ only","p");
                    legvnAB_pT->AddEntry(vnB[cut][ebin][anal],"track- only","p");
                } else {
                    legvnAB_pT->AddEntry(vnA[cut][ebin][anal],"HF+ only","p");
                    legvnAB_pT->AddEntry(vnB[cut][ebin][anal],"HF- only","p");
                }
                legvnAB_pT->Draw();
                TPaveText * txvnAB_pT = new TPaveText(0.21, 0.79, 0.41, 0.93,"NDC");
                SetTPaveTxt(txvnAB_pT, 20);
                txvnAB_pT->AddText(Form("%d - %d%%",cmin[centbin],cmax[centbin]));
                txvnAB_pT->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
                txvnAB_pT->Draw();
                cvnAB_pT->Print(Form("figures/pT_spectra/%s/%s/vnAB_%1.1f_%1.1f.png",ptag.data(),AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]),"png");
                cvnAB_pT->Close();
            }
        }
    }
*/



    //-- ratios of v1(tight) / v1(tightB)
    if (!fopen("figures/pT_spectra/ratio_tight_tightB","r")) system("mkdir figures/pT_spectra/ratio_tight_tightB");
    TLine * ln_rat = new TLine(0.3, 1.0, 12.0, 1.0);

    TCanvas * cvnAB_pT_rat[nanals];
    TH1D * hvnAB_pT_rat[netabins][nanals];
    for (int anal = 0; anal<nanals; anal++) {
        cvnAB_pT_rat[anal] = new TCanvas(Form("vnAB_pT_rat_%s",AnalNames[anal].data()),Form("vnAB_pT_rat_%s",AnalNames[anal].data()),1100,700);
        cvnAB_pT_rat[anal]->Divide(4,3,0,0);
        for (int ebin = 0; ebin<netabins; ebin++) {
            TPad * padvnAB_pT_rat = (TPad *) cvnAB_pT_rat[anal]->cd(ebin+1);
            padvnAB_pT_rat->SetGrid();
            hvnAB_pT_rat[ebin][anal] = new TH1D(Form("hvnAB_pT_rat_e%d_a%d",ebin,anal), "", 40, 0, 12);
            if (anal == 0 || anal == 1) hvnAB_pT_rat[ebin][anal]->GetYaxis()->SetRangeUser(0.5, 1.5);
            else if (anal == 6) hvnAB_pT_rat[ebin][anal]->GetYaxis()->SetRangeUser(0.0, 2.0);
            else hvnAB_pT_rat[ebin][anal]->GetYaxis()->SetRangeUser(0.90, 1.1);
            hvnAB_pT_rat[ebin][anal]->SetMarkerColor(kBlack);
            hvnAB_pT_rat[ebin][anal]->SetLineColor(kBlack);
            hvnAB_pT_rat[ebin][anal]->SetYTitle("v_{1}{tight} / v_{1}{tightB}");
            hvnAB_pT_rat[ebin][anal]->GetYaxis()->SetTitleSize(0.06);
            hvnAB_pT_rat[ebin][anal]->GetYaxis()->SetLabelSize(0.06);
            hvnAB_pT_rat[ebin][anal]->Draw();
            vnABrat[ebin][anal]->Draw("same");
            ln_rat->Draw();
            TPaveText * txvnAB_pT_rat;
            if (ebin<8) txvnAB_pT_rat = new TPaveText(0.54, 0.07, 0.94, 0.19,"NDC");
            else txvnAB_pT_rat = new TPaveText(0.54, 0.19, 0.94, 0.30,"NDC");
            SetTPaveTxt(txvnAB_pT_rat, 18);
            txvnAB_pT_rat->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
            txvnAB_pT_rat->Draw();
        }
        cvnAB_pT_rat[anal]->cd(1);
        TPaveText * txcvnAB_pT_rat_anal = new TPaveText(0.25, 0.73, 0.67, 0.95,"NDC");
        SetTPaveTxt(txcvnAB_pT_rat_anal, 18);
        if (anal == 6) txcvnAB_pT_rat_anal->AddText("v_{1}^{odd}");
        else txcvnAB_pT_rat_anal->AddText(Form("%s",AnalNames[anal].data()));
        txcvnAB_pT_rat_anal->AddText(Form("%d - %d%%",cmin[centbin],cmax[centbin]));
        txcvnAB_pT_rat_anal->Draw();
        cvnAB_pT_rat[anal]->Print(Form("figures/pT_spectra/ratio_tight_tightB_%s_%d_%d.png",AnalNames[anal].data(),cmin[centbin],cmax[centbin]),"png");
        //cvnAB_pT_rat[anal]->Close();
    }


    TCanvas * cvnAB_pT_rat_even;
    TH1D * hvnAB_pT_rat_even[netabins];
    cvnAB_pT_rat_even = new TCanvas("vnAB_pT_rat_even","vnAB_pT_rat_even",1100,700);
    cvnAB_pT_rat_even->Divide(4,3,0,0);
    for (int ebin = 0; ebin<netabins; ebin++) {
        TPad * padvnAB_pT_rat_even = (TPad *) cvnAB_pT_rat_even->cd(ebin+1);
        padvnAB_pT_rat_even->SetGrid();
        hvnAB_pT_rat_even[ebin] = new TH1D(Form("hvnAB_pT_rat_even_e%d",ebin), "", 40, 0, 12);
        hvnAB_pT_rat_even[ebin]->GetYaxis()->SetRangeUser(0.5, 1.5);
        hvnAB_pT_rat_even[ebin]->SetMarkerColor(kBlack);
        hvnAB_pT_rat_even[ebin]->SetLineColor(kBlack);
        hvnAB_pT_rat_even[ebin]->SetYTitle("v_{1}{tight} / v_{1}{tightB}");
        hvnAB_pT_rat_even[ebin]->GetYaxis()->SetTitleSize(0.06);
        hvnAB_pT_rat_even[ebin]->GetYaxis()->SetLabelSize(0.06);
        hvnAB_pT_rat_even[ebin]->Draw();
        if (ebin<6) vnABrat[ebin][1]->Draw("same");
        if (ebin>=6) vnABrat[ebin][0]->Draw("same");
        ln_rat->Draw();
        TPaveText * txvnAB_pT_rat_even;
        if (ebin<8) txvnAB_pT_rat_even = new TPaveText(0.54, 0.07, 0.94, 0.19,"NDC");
        else txvnAB_pT_rat_even = new TPaveText(0.54, 0.19, 0.94, 0.30,"NDC");
        SetTPaveTxt(txvnAB_pT_rat_even, 18);
        txvnAB_pT_rat_even->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
        txvnAB_pT_rat_even->Draw();
    }
    cvnAB_pT_rat_even->cd(1);
    TPaveText * txcvnAB_pT_rat_even_anal = new TPaveText(0.25, 0.73, 0.67, 0.95,"NDC");
    SetTPaveTxt(txcvnAB_pT_rat_even_anal, 18);
    txcvnAB_pT_rat_even_anal->AddText("v_{1}^{even}");
    txcvnAB_pT_rat_even_anal->AddText(Form("%d - %d%%",cmin[centbin],cmax[centbin]));
    txcvnAB_pT_rat_even_anal->Draw();
    cvnAB_pT_rat_even->Print(Form("figures/pT_spectra/ratio_tight_tightB_even_%d_%d.png",cmin[centbin],cmax[centbin]),"png");
    //cvnAB_pT_rat_even->Close();



    //-- single plot comparing loose, tight, and tightB cuts
    TCanvas * cvnAB_pT_cuts[nanals];
    for (int anal = 1; anal<2; anal++) {
        TFile * tf0 = new TFile(Form("../results/results_useTight_-2.4_2.4/%s.root",AnalNames[anal].data()));
        TFile * tf1 = new TFile(Form("../results/results_useTightB_-2.4_2.4/%s.root",AnalNames[anal].data()));
        TFile * tf2 = new TFile(Form("../results/results_useLoose_-2.4_2.4/%s.root",AnalNames[anal].data()));

        vnABrat_int[0][anal] = (TH1D *) tf0->Get(Form("%d_%d/vnAB",cmin[centbin],cmax[centbin]));
        vnABrat_int[1][anal] = (TH1D *) tf1->Get(Form("%d_%d/vnAB",cmin[centbin],cmax[centbin]));
        vnABrat_int[2][anal] = (TH1D *) tf2->Get(Form("%d_%d/vnAB",cmin[centbin],cmax[centbin]));

        vnABrat_int[0][anal]->SetMarkerColor(kBlue);
        vnABrat_int[0][anal]->SetLineColor(kBlue);
        vnABrat_int[0][anal]->SetMarkerStyle(21);
        vnABrat_int[0][anal]->SetMarkerSize(1.2);

        vnABrat_int[1][anal]->SetMarkerColor(kMagenta);
        vnABrat_int[1][anal]->SetLineColor(kMagenta);
        vnABrat_int[1][anal]->SetMarkerStyle(24);
        vnABrat_int[1][anal]->SetMarkerSize(1.3);

        vnABrat_int[2][anal]->SetMarkerColor(kCyan+2);
        vnABrat_int[2][anal]->SetLineColor(kCyan+2);
        vnABrat_int[2][anal]->SetMarkerStyle(24);
        vnABrat_int[2][anal]->SetMarkerSize(1.3);

        cvnAB_pT_cuts[anal] = new TCanvas(Form("cvnAB_pT_cuts_%s",AnalNames[anal].data()),Form("cvnAB_pT_cuts_%s",AnalNames[anal].data()),650,500);
        TPad * padvnAB_pT_cuts = (TPad *) cvnAB_pT_cuts[anal]->cd();
        padvnAB_pT_cuts->SetGrid();
        TH1D * hvnAB_pT_cuts = new TH1D(Form("vnAB_pT_cuts_%s",AnalNames[anal].data()), "", 40, 0, 12);
        hvnAB_pT_cuts->SetXTitle("p_{T} (GeV/c)");
        hvnAB_pT_cuts->SetYTitle("v_{1}");
        hvnAB_pT_cuts->GetYaxis()->SetRangeUser(-0.02, 0.15);
        hvnAB_pT_cuts->Draw();
        vnABrat_int[0][anal]->Draw("same");
        vnABrat_int[1][anal]->Draw("same");
        vnABrat_int[2][anal]->Draw("same");
        ln_pT->Draw();
        TLegend * legvnAB_pT_cuts = new TLegend(0.63, 0.76, 0.92, 0.92);
        SetLegend(legvnAB_pT_cuts, 20);
        legvnAB_pT_cuts->AddEntry(vnABrat_int[0][anal],"Tight (default)","p");
        legvnAB_pT_cuts->AddEntry(vnABrat_int[1][anal],"TightB","p");
        legvnAB_pT_cuts->AddEntry(vnABrat_int[2][anal],"Loose","p");
        legvnAB_pT_cuts->Draw();

        TPaveText * txvnAB_pT_cuts = new TPaveText(0.20, 0.79, 0.40, 0.92,"NDC");
        SetTPaveTxt(txvnAB_pT_cuts, 20);
        txvnAB_pT_cuts->AddText(Form("%d - %d%%",cmin[centbin],cmax[centbin]));
        txvnAB_pT_cuts->AddText("-2.4 < #eta < 2.4");
        txvnAB_pT_cuts->Draw();
        cvnAB_pT_cuts[anal]->Print(Form("figures/pT_spectra/vnAB_cuts_%s_%d_%d.png",AnalNames[anal].data(),cmin[centbin],cmax[centbin]),"png");
        //cvnAB_pT_cuts[anal]->Close();
    }



    //-- systemmatic from cuts
    TH1D * Dv1even_Loose[ncentbins];
    TH1D * Dv1even_TightB[ncentbins];
    TH1D * Dv1even_num[ncentbins];
    TH1D * Dv1even_den[ncentbins];
    TFile * tfevenLoose = new TFile(Form("../results/results_useTight_-2.4_2.4/%s.root",AnalNames[1].data()));
    TFile * tfevenTight = new TFile(Form("../results/results_useTight_-2.4_2.4/%s.root",AnalNames[1].data()));
    TFile * tfevenTightB = new TFile(Form("../results/results_useTightB_-2.4_2.4/%s.root",AnalNames[1].data()));
    TF1 * fitSystDEven[ncentbins];
    TH1D * systv1even[ncentbins];
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        Dv1even_Loose[cbin] = (TH1D *) tfevenLoose->Get(Form("%d_%d/vnAB",centBins[cbin],centBins[cbin+1]));
        Dv1even_TightB[cbin] = (TH1D *) tfevenTightB->Get(Form("%d_%d/vnAB",centBins[cbin],centBins[cbin+1]));
        for (int i = 1; i<=Dv1even_Loose[cbin]->GetNbinsX(); i++){
            Dv1even_Loose[cbin]->SetBinContent(i, fabs(Dv1even_Loose[cbin]->GetBinContent(i)));
            Dv1even_TightB[cbin]->SetBinContent(i, fabs(Dv1even_TightB[cbin]->GetBinContent(i)));
        }
        Dv1even_num[cbin] = (TH1D *) Dv1even_Loose[cbin]->Clone(Form("Dv1even_num_%d_%d",centBins[cbin],centBins[cbin+1]));
        Dv1even_num[cbin]->Add(Dv1even_TightB[cbin],-1.);
        Dv1even_den[cbin] = (TH1D *) Dv1even_Loose[cbin]->Clone(Form("Dv1even_den_%d_%d",centBins[cbin],centBins[cbin+1]));
        Dv1even_den[cbin]->Add(Dv1even_TightB[cbin]);
        Dv1even_num[cbin]->Divide(Dv1even_den[cbin]);

        systv1even[cbin] = (TH1D *) tfevenTight->Get(Form("%d_%d/vnAB",centBins[cbin],centBins[cbin+1]));
    }

    TCanvas * cSystDEven = new TCanvas("cSystDEven","cSystDEven",1100,700);
    cSystDEven->Divide(4,3,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padSystDEven = (TPad *) cSystDEven->cd(cbin+1);
        padSystDEven->SetGrid();
        TH1D * hSystDEven = new TH1D(Form("hSystDEven_%d_%d",cmin[cbin],cmax[cbin]), "", 40, 0, 12);
        hSystDEven->GetYaxis()->SetRangeUser(-0.5, 0.5);
        hSystDEven->SetMarkerColor(kBlack);
        hSystDEven->SetLineColor(kBlack);
        hSystDEven->SetYTitle("#frac{|v_{1}^{loose}| - |v_{1}^{tightB}|}{|v_{1}^{loose}| + |v_{1}^{tightB}|}");
        hSystDEven->GetYaxis()->SetTitleSize(0.06);
        hSystDEven->GetYaxis()->SetLabelSize(0.06);
        hSystDEven->Draw();
        Dv1even_num[cbin]->Draw("same");

        TPaveText * txSystDEven_cent = new TPaveText(0.25, 0.82, 0.42, 0.95,"NDC");
        SetTPaveTxt(txSystDEven_cent, 18);
        txSystDEven_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txSystDEven_cent->Draw();

        fitSystDEven[cbin] = new TF1(Form("fitSystDEven_%d-%d",centBins[cbin],centBins[cbin+1]), "pol0", 0, 12);
        Dv1even_num[cbin]->Fit(fitSystDEven[cbin],"QR");
        double relv1even_num = fitSystDEven[cbin]->GetParameter(0);
        for (int i = 1; i<=systv1even[cbin]->GetNbinsX(); i++) {
            systv1even[cbin]->SetBinError(i, relv1even_num * systv1even[cbin]->GetBinContent(i));
        }

    }
    cSystDEven->cd(12);
    TPaveText * txSystDEven_cms = new TPaveText(0.2, 0.2, 0.42, 0.4,"NDC");
    SetTPaveTxt(txSystDEven_cms, 18);
    txSystDEven_cms->AddText("#bf{CMS} #it{Preliminary}");
    txSystDEven_cms->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txSystDEven_cms->Draw();
    cSystDEven->Print("figures/pT_spectra/Dmeanv1even_centscan.png","png");



    //-- v1even with syst errors
    TCanvas * cSystv1Even = new TCanvas("cSystv1Even","cSystv1Even",1100,700);
    cSystv1Even->Divide(4,3,0,0);
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TPad * padSystv1Even = (TPad *) cSystv1Even->cd(cbin+1);
        padSystv1Even->SetGrid();
        TH1D * hSystv1Even = new TH1D(Form("hSystv1Even_%d_%d",cmin[cbin],cmax[cbin]), "", 40, 0, 12);
        hSystv1Even->GetYaxis()->SetRangeUser(-0.05, 0.25);
        hSystv1Even->SetMarkerColor(kBlack);
        hSystv1Even->SetLineColor(kBlack);
        //hSystv1Even->SetYTitle("#frac{|v_{1}^{loose}| - |v_{1}^{tightB}|}{|v_{1}^{loose}| + |v_{1}^{tightB}|}");
        hSystv1Even->GetYaxis()->SetTitleSize(0.06);
        hSystv1Even->GetYaxis()->SetLabelSize(0.06);
        hSystv1Even->Draw();

        TPaveText * txSystv1Even_cent = new TPaveText(0.25, 0.82, 0.42, 0.95,"NDC");
        SetTPaveTxt(txSystv1Even_cent, 18);
        txSystv1Even_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txSystv1Even_cent->Draw();


        systv1even[cbin]->Draw("same");

    }
    cSystv1Even->cd(12);
    TPaveText * txSystv1Even_cms = new TPaveText(0.2, 0.2, 0.42, 0.4,"NDC");
    SetTPaveTxt(txSystv1Even_cms, 18);
    txSystv1Even_cms->AddText("#bf{CMS} #it{Preliminary}");
    txSystv1Even_cms->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txSystv1Even_cms->Draw();
    cSystv1Even->Print("figures/pT_spectra/v1evenSyst_centscan.png","png");




}
