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

TFile * tfin;

void pTratios()
{

    TH1::SetDefaultSumw2();

    for (int cut = 0; cut<3; cut++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            for (int anal = 0; anal<nanals; anal++) {
                string tag = "";
                if (cut == 0) tag = Form("useTight_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                if (cut == 1) tag = Form("useTightB_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                if (cut == 2) tag = Form("useLoose_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]);
                tfin = new TFile(Form("../results/results_%s/%s.root",tag.data(),AnalNames[anal].data()));

                vnA[cut][ebin][anal] = (TH1D *) tfin->Get("30_50/vnA");
                vnB[cut][ebin][anal] = (TH1D *) tfin->Get("30_50/vnB");
                vnAB[cut][ebin][anal] = (TH1D *) tfin->Get("30_50/vnAB");

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
            vnBrat[ebin][anal] = (TH1D *) vnB[0][ebin][anal]->Clone(Form("vnArat_%s_%1.1f_%1.1f",AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]));
            vnABrat[ebin][anal] = (TH1D *) vnAB[0][ebin][anal]->Clone(Form("vnArat_%s_%1.1f_%1.1f",AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]));

            vnArat[ebin][anal]->Divide(vnA[1][ebin][anal]);
            vnBrat[ebin][anal]->Divide(vnA[1][ebin][anal]);
            vnABrat[ebin][anal]->Divide(vnA[1][ebin][anal]);

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
        }
    }

    if (!fopen("figures","r")) system("mkdir figures");
    if (!fopen("figures/pT_spectra","r")) system("mkdir figures/pT_spectra");

    TLine * ln_pT = new TLine(0.0, 0.0, 12.0, 0.0);
    ln_pT->SetLineWidth(1);


    TCanvas * ctest = new TCanvas("ctest","ctest",650,500);
    TPad * padtest = (TPad *) ctest->cd();
    padtest->SetGrid();
    vnA[0][6][0]->Draw();
    vnB[0][6][0]->Draw("same");
    vnAB[0][6][0]->Draw("same");
    ln_pT->Draw();
    TLegend * legtest = new TLegend(0.63, 0.76, 0.92, 0.92);
    SetLegend(legtest, 20);
    legtest->AddEntry(vnAB[0][6][0],Form("%s",AnalNames[0].data()),"p");
    legtest->AddEntry(vnA[0][6][0],"track+ only","p");
    legtest->AddEntry(vnB[0][6][0],"track- only","p");
    legtest->Draw();
    TPaveText * txtest = new TPaveText(0.21, 0.79, 0.41, 0.93,"NDC");
    SetTPaveTxt(txtest, 20);
    txtest->AddText("30 - 50%");
    txtest->AddText(Form("%1.1f < #eta < %1.1f",etabins[6],etabins[6+1]));
    txtest->Draw();


    //-- compare pos and neg sides
    // for (int cut = 0; cut<3; cut++) {
    //     string ptag = "";
    //     if (cut == 0) ptag = "useTight";
    //     if (cut == 1) ptag = "useTightB";
    //     if (cut == 2) ptag = "useLoose";
    //     if (!fopen(Form("figures/pT_spectra/%s",ptag.data()),"r")) system(Form("mkdir figures/pT_spectra/%s",ptag.data()));
    //     for (int anal = 0; anal<nanals; anal++) {
    //         if (!fopen(Form("figures/pT_spectra/%s/%s",ptag.data(),AnalNames[anal].data()),"r")) {
    //             system(Form("mkdir figures/pT_spectra/%s/%s",ptag.data(),AnalNames[anal].data()));
    //         }
    //         for (int ebin = 0; ebin<netabins; ebin++) {
    //             TCanvas * cvnAB_pT = new TCanvas("cvnAB_pT","cvnAB_pT",650,500);
    //             TPad * padvnAB_pT = (TPad *) cvnAB_pT->cd();
    //             padvnAB_pT->SetGrid();
    //             vnA[cut][ebin][anal]->Draw();
    //             vnB[cut][ebin][anal]->Draw("same");
    //             vnAB[cut][ebin][anal]->Draw("same");
    //             ln_pT->Draw();
    //             TLegend * legvnAB_pT = new TLegend(0.63, 0.76, 0.92, 0.92);
    //             SetLegend(legvnAB_pT, 20);
    //             legvnAB_pT->AddEntry(vnAB[cut][ebin][anal],Form("%s",AnalNames[anal].data()),"p");
    //             if (anal <= 1) {
    //                 legvnAB_pT->AddEntry(vnA[cut][ebin][anal],"track+ only","p");
    //                 legvnAB_pT->AddEntry(vnB[cut][ebin][anal],"track- only","p");
    //             } else {
    //                 legvnAB_pT->AddEntry(vnA[cut][ebin][anal],"HF+ only","p");
    //                 legvnAB_pT->AddEntry(vnB[cut][ebin][anal],"HF- only","p");
    //             }
    //             legvnAB_pT->Draw();
    //             TPaveText * txvnAB_pT = new TPaveText(0.21, 0.79, 0.41, 0.93,"NDC");
    //             SetTPaveTxt(txvnAB_pT, 20);
    //             txvnAB_pT->AddText("30 - 50%");
    //             txvnAB_pT->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
    //             txvnAB_pT->Draw();
    //             cvnAB_pT->Print(Form("figures/pT_spectra/%s/%s/vnAB_%1.1f_%1.1f.png",ptag.data(),AnalNames[anal].data(),etabins[ebin],etabins[ebin+1]),"png");
    //             cvnAB_pT->Close();
    //         }
    //     }
    // }


    //-- ratios of v1(tight)/v1(tightB)
    if (!fopen("figures/pT_spectra/ratio_tight_tightB","r")) system("mkdir figures/pT_spectra/ratio_tight_tightB");
    TLine * ln_rat = new TLine(0.0, 1.0, 12.0, 1.0);

    TCanvas * cvnAB_pT_rat[nanals];
    for (int anal = 0; anal<nanals; anal++) {
        cvnAB_pT_rat[anal] = new TCanvas(Form("vnAB_pT_rat_%s",AnalNames[anal].data()),Form("vnAB_pT_rat_%s",AnalNames[anal].data()),1100,700);
        cvnAB_pT_rat[anal]->Divide(4,3,0,0);
        for (int ebin = 0; ebin<netabins; ebin++) {
            TPad * padvnAB_pT_rat = (TPad *) cvnAB_pT_rat[anal]->cd(ebin+1);
            padvnAB_pT_rat->SetGrid();
            vnABrat[ebin][anal]->Draw();
            ln_rat->Draw();
            TPaveText * txvnAB_pT_rat = new TPaveText(0.54, 0.07, 0.94, 0.19,"NDC");
            SetTPaveTxt(txvnAB_pT_rat, 18);
            txvnAB_pT_rat->AddText(Form("%1.1f < #eta < %1.1f",etabins[ebin],etabins[ebin+1]));
            txvnAB_pT_rat->Draw();
        }
        cvnAB_pT_rat[anal]->cd(1);
        TPaveText * txcvnAB_pT_rat_anal = new TPaveText(0.24, 0.07, 0.52, 0.29,"NDC");
        SetTPaveTxt(txcvnAB_pT_rat_anal, 18);
        txcvnAB_pT_rat_anal->AddText(Form("%s",AnalNames[anal].data()));
        txcvnAB_pT_rat_anal->AddText("30 - 50%");
        txcvnAB_pT_rat_anal->Draw();
        cvnAB_pT_rat[anal]->Print(Form("figures/pT_spectra/ratio_tight_tightB_%s.png",AnalNames[anal].data()),"png");
        //cvnAB_pT_rat[anal]->Close();
    }

}
