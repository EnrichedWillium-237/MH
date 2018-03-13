# include "TCanvas.h"
# include "TFile.h"
# include "TGraph.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TPaveText.h"
# include "TString.h"
# include <iostream>

#include "src/HiEvtPlaneList.h"

static const int ncbins = 11;
static const int centbins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};

TFile * finRes = new TFile("../MH.root","read");
TFile * finNum = new TFile("MH_hists_NumOnly.root","read");
TFile * finSP = new TFile("vnPlots.root","read");
TGraphErrors * N1HFcSUB3;
TGraphErrors * N1HFdSUB3;
TGraphErrors * N1HFeSUB3;
TGraphErrors * N1HFfSUB3;
TGraphErrors * N1HFgSUB3;
TGraphErrors * N1mHFcSUB3;
TGraphErrors * N1pHFcSUB3;
TGraphErrors * N1mHFdSUB3;
TGraphErrors * N1pHFdSUB3;
TGraphErrors * N1mHFeSUB3;
TGraphErrors * N1pHFeSUB3;
TGraphErrors * N1mHFfSUB3;
TGraphErrors * N1pHFfSUB3;
TGraphErrors * N1mHFgSUB3;
TGraphErrors * N1pHFgSUB3;
TH1D * qBA;
TH1D * qCA;
TH1D * qCB;
TH1D * qBAcnt;
TH1D * qCAcnt;
TH1D * qCBcnt;
TH1D * h0;
TH1D * h1;
TH1D * h2;

using namespace hi;

void SetTPaveTxt( TPaveText * txtemplate, int txtsize ) {
    txtemplate->SetFillColor(0);
    txtemplate->SetBorderSize(0);
    txtemplate->SetTextFont(43);
    txtemplate->SetTextAlign(12);
    txtemplate->SetTextSize(txtsize);
}

void SetLegend( TLegend * legtemplate, int legsize ) {
    legtemplate->SetFillColor(0);
    legtemplate->SetBorderSize(0);
    legtemplate->SetTextFont(43);
    legtemplate->SetTextSize(legsize);
}

TGraphErrors * getRes( TString type, TGraphErrors * &g, bool sub2 ) {

    double qba, qca, qcb;
    double qbae, qcae, qcbe;
    double qbacnt, qcacnt, qcbcnt;
    double qbacnte, qcacnte, qcbcnte;
    double xval[30], resval[30], reserr[30];
    for (int cbin = 0; cbin<ncbins; cbin++) {
        TString ctag = Form("%d_%d",centbins[cbin],centbins[cbin+1]);
        xval[cbin] = 0.5*(centbins[cbin]+centbins[cbin+1]);

        qba = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",ctag.Data(),type.Data())))->GetBinContent(1);
        qca = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",ctag.Data(),type.Data())))->GetBinContent(1);
        qcb = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",ctag.Data(),type.Data())))->GetBinContent(1);
        qbacnt = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",ctag.Data(),type.Data())))->GetBinContent(1);
        qcacnt = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",ctag.Data(),type.Data())))->GetBinContent(1);
        qcbcnt = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",ctag.Data(),type.Data())))->GetBinContent(1);

        qbae = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",ctag.Data(),type.Data())))->GetBinError(1);
        qcae = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",ctag.Data(),type.Data())))->GetBinError(1);
        qcbe = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",ctag.Data(),type.Data())))->GetBinError(1);
        qbacnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",ctag.Data(),type.Data())))->GetBinError(1);
        qcacnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",ctag.Data(),type.Data())))->GetBinError(1);
        qcbcnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",ctag.Data(),type.Data())))->GetBinError(1);

        qba/=qbacnt;
        qca/=qcacnt;
        qcb/=qcbcnt;

        qbae = qba*sqrt( pow(qbae/qba,2) + pow(qbacnte/qbacnt,2) );
        qcae = qca*sqrt( pow(qcae/qca,2) + pow(qcacnte/qcacnt,2) );
        qcbe = qcb*sqrt( pow(qcbe/qcb,2) + pow(qcbcnte/qcbcnt,2) );

        if (sub2) {
            resval[cbin] = sqrt( fabs(qba) );
        }
        else {
            resval[cbin] = sqrt( fabs(qba*qca/qcb) );
        }

        double qbae = 0;
        double qcae = 0;
        double qcbe = 0;
        double qbacnte = 0;
        double qcacnte = 0;
        double qcbcnte = 0;
        double resm = 0;
        double res2 = 0;
        for (int k = 1; k<10; k++) {
            qbae = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBA_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcae = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCA_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcbe = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCB_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qbacnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBAcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcacnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCAcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcbcnte = ((TH1D *) finRes->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCBcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qbae/=qbacnte;
            qcae/=qcacnte;
            qcbe/=qcbcnte;
            if (sub2) {
                resm += sqrt( fabs(qbae) );
                res2 += pow(sqrt( fabs(qbae) ),2);
            } else {
                resm += sqrt( fabs(qbae*qcae/qcbe) );
                res2 += pow(sqrt( fabs(qbae*qcae/qcbe) ),2);
            }
        }
        reserr[cbin] = sqrt( (1/9.)*(res2 - pow(resm,2)) );
    }

    g = new TGraphErrors(ncbins, xval, resval, 0, reserr);
    return g;

}

void resolution() {

    N1HFcSUB3 = getRes("N1HFm1c", N1HFcSUB3, false);
    N1HFcSUB3->SetMarkerStyle(20);
    N1HFcSUB3->SetMarkerSize(1.3);
    N1HFcSUB3->SetMarkerColor(kBlack);
    N1HFcSUB3->SetLineColor(kBlack);

    N1HFdSUB3 = getRes("N1HFm1d", N1HFdSUB3, false);
    N1HFdSUB3->SetMarkerStyle(25);
    N1HFdSUB3->SetMarkerSize(1.2);
    N1HFdSUB3->SetMarkerColor(kRed);
    N1HFdSUB3->SetLineColor(kRed);

    N1HFeSUB3 = getRes("N1HFm1e", N1HFeSUB3, false);
    N1HFeSUB3->SetMarkerStyle(21);
    N1HFeSUB3->SetMarkerSize(1.2);
    N1HFeSUB3->SetMarkerColor(kGreen+2);
    N1HFeSUB3->SetLineColor(kGreen+2);

    N1HFfSUB3 = getRes("N1HFm1f", N1HFfSUB3, false);
    N1HFfSUB3->SetMarkerStyle(24);
    N1HFfSUB3->SetMarkerSize(1.3);
    N1HFfSUB3->SetMarkerColor(kBlue);
    N1HFfSUB3->SetLineColor(kBlue);


    TCanvas * c0 = new TCanvas("c0", "c0", 650, 600);
    TPad * pad0 = (TPad *) c0->cd();
    h0 = new TH1D("h0", "h0", 100, 0, 80);
    h0->GetYaxis()->SetRangeUser(0, 0.045);
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(508);
    h0->SetXTitle("Centrality (%)");
    h0->SetYTitle("Scalar-product denominator");
    h0->Draw();
    N1HFcSUB3->Draw("same p");
    N1HFdSUB3->Draw("same p");
    N1HFeSUB3->Draw("same p");
    N1HFfSUB3->Draw("same p");
    TLegend * leg0 = new TLegend(0.20, 0.63, 0.47, 0.90);
    SetLegend(leg0, 20);
    leg0->SetHeader("3 subevent v_{1}");
    leg0->AddEntry(N1HFcSUB3,"3.0 < |#eta_{EP}| < 3.5","p");
    leg0->AddEntry(N1HFdSUB3,"3.5 < |#eta_{EP}| < 4.0","p");
    leg0->AddEntry(N1HFeSUB3,"4.0 < |#eta_{EP}| < 4.5","p");
    leg0->AddEntry(N1HFfSUB3,"4.5 < |#eta_{EP}| < 5.0","p");
    leg0->Draw();
    c0->Print("resPlot.png","png");



    TGraphErrors * N1HFcSUB3_num = (TGraphErrors *) finNum->Get("default/N1HFcSUB3/-2.0_2.0/20_60/gintA");
    N1HFcSUB3_num->SetMarkerStyle(20);
    N1HFcSUB3_num->SetMarkerSize(1.3);
    N1HFcSUB3_num->SetMarkerColor(kBlack);
    N1HFcSUB3_num->SetLineColor(kBlack);
    N1HFcSUB3_num->RemovePoint(0);
    N1HFcSUB3_num->RemovePoint(N1HFcSUB3_num->GetN()-1);

    TGraphErrors * N1HFdSUB3_num = (TGraphErrors *) finNum->Get("default/N1HFdSUB3/-2.0_2.0/20_60/gintA");
    N1HFdSUB3_num->SetMarkerStyle(25);
    N1HFdSUB3_num->SetMarkerSize(1.2);
    N1HFdSUB3_num->SetMarkerColor(kRed);
    N1HFdSUB3_num->SetLineColor(kRed);
    N1HFdSUB3_num->RemovePoint(0);
    N1HFdSUB3_num->RemovePoint(N1HFdSUB3_num->GetN()-1);

    TGraphErrors * N1HFeSUB3_num = (TGraphErrors *) finNum->Get("default/N1HFeSUB3/-2.0_2.0/20_60/gintA");
    N1HFeSUB3_num->SetMarkerStyle(21);
    N1HFeSUB3_num->SetMarkerSize(1.2);
    N1HFeSUB3_num->SetMarkerColor(kGreen+2);
    N1HFeSUB3_num->SetLineColor(kGreen+2);
    N1HFeSUB3_num->RemovePoint(0);
    N1HFeSUB3_num->RemovePoint(N1HFeSUB3_num->GetN()-1);

    TGraphErrors * N1HFfSUB3_num = (TGraphErrors *) finNum->Get("default/N1HFfSUB3/-2.0_2.0/20_60/gintA");
    N1HFfSUB3_num->SetMarkerStyle(24);
    N1HFfSUB3_num->SetMarkerSize(1.3);
    N1HFfSUB3_num->SetMarkerColor(kBlue);
    N1HFfSUB3_num->SetLineColor(kBlue);
    N1HFfSUB3_num->RemovePoint(0);
    N1HFfSUB3_num->RemovePoint(N1HFfSUB3_num->GetN()-1);

    TCanvas * c1 = new TCanvas("c1", "c1", 650, 600);
    TPad * pad1 = (TPad *) c1->cd();
    h1 = new TH1D("h1", "h1", 100, -2.5, 2.5);
    h1->GetYaxis()->SetRangeUser(-0.0006, 0);
    h1->GetYaxis()->SetDecimals();
    h1->GetYaxis()->SetNdivisions(508);
    h1->SetXTitle("#eta");
    h1->GetXaxis()->CenterTitle();
    h1->SetYTitle("Scalar-product numerator");
    h1->Draw();
    N1HFcSUB3_num->Draw("same p");
    N1HFdSUB3_num->Draw("same p");
    N1HFeSUB3_num->Draw("same p");
    N1HFfSUB3_num->Draw("same p");
    TLegend * leg1 = new TLegend(0.61, 0.64, 0.88, 0.91);
    SetLegend(leg1, 20);
    leg1->SetHeader("20 - 60%");
    leg1->AddEntry(N1HFcSUB3_num,"3.0 < |#eta_{EP}| < 3.5","p");
    leg1->AddEntry(N1HFdSUB3_num,"3.5 < |#eta_{EP}| < 4.0","p");
    leg1->AddEntry(N1HFeSUB3_num,"4.0 < |#eta_{EP}| < 4.5","p");
    leg1->AddEntry(N1HFfSUB3_num,"4.5 < |#eta_{EP}| < 5.0","p");
    leg1->Draw();
    c1->Print("numPlot.png","png");



    TGraphErrors * gN1HFcSUB3 = (TGraphErrors *) finSP->Get("default/N1HFcSUB3/-2.0_2.0/20_60/gintA");
    gN1HFcSUB3->SetMarkerStyle(20);
    gN1HFcSUB3->SetMarkerSize(1.3);
    gN1HFcSUB3->SetMarkerColor(kBlack);
    gN1HFcSUB3->SetLineColor(kBlack);
    gN1HFcSUB3->RemovePoint(0);
    gN1HFcSUB3->RemovePoint(gN1HFcSUB3->GetN()-1);

    TGraphErrors * gN1HFdSUB3 = (TGraphErrors *) finSP->Get("default/N1HFdSUB3/-2.0_2.0/20_60/gintA");
    gN1HFdSUB3->SetMarkerStyle(25);
    gN1HFdSUB3->SetMarkerSize(1.2);
    gN1HFdSUB3->SetMarkerColor(kRed);
    gN1HFdSUB3->SetLineColor(kRed);
    gN1HFdSUB3->RemovePoint(0);
    gN1HFdSUB3->RemovePoint(gN1HFdSUB3->GetN()-1);

    TGraphErrors * gN1HFeSUB3 = (TGraphErrors *) finSP->Get("default/N1HFeSUB3/-2.0_2.0/20_60/gintA");
    gN1HFeSUB3->SetMarkerStyle(21);
    gN1HFeSUB3->SetMarkerSize(1.2);
    gN1HFeSUB3->SetMarkerColor(kGreen+2);
    gN1HFeSUB3->SetLineColor(kGreen+2);
    gN1HFeSUB3->RemovePoint(0);
    gN1HFeSUB3->RemovePoint(gN1HFeSUB3->GetN()-1);

    TGraphErrors * gN1HFfSUB3 = (TGraphErrors *) finSP->Get("default/N1HFfSUB3/-2.0_2.0/20_60/gintA");
    gN1HFfSUB3->SetMarkerStyle(24);
    gN1HFfSUB3->SetMarkerSize(1.3);
    gN1HFfSUB3->SetMarkerColor(kBlue);
    gN1HFfSUB3->SetLineColor(kBlue);
    gN1HFfSUB3->RemovePoint(0);
    gN1HFfSUB3->RemovePoint(gN1HFfSUB3->GetN()-1);

    TCanvas * c2 = new TCanvas("c2", "c2", 650, 600);
    TPad * pad2 = (TPad *) c2->cd();
    h2 = new TH1D("h2", "h2", 100, -2.5, 2.5);
    h2->GetYaxis()->SetRangeUser(-0.06, 0);
    h2->GetYaxis()->SetDecimals();
    h2->GetYaxis()->SetNdivisions(508);
    h2->SetXTitle("#eta");
    h2->GetXaxis()->CenterTitle();
    h2->SetYTitle("v_{1}{HF+} (3-subevent)");
    h2->Draw();
    gN1HFcSUB3->Draw("same p");
    gN1HFdSUB3->Draw("same p");
    gN1HFeSUB3->Draw("same p");
    gN1HFfSUB3->Draw("same p");
    TLegend * leg2 = new TLegend(0.61, 0.64, 0.88, 0.91);
    SetLegend(leg2, 20);
    leg2->SetHeader("20 - 60%");
    leg2->AddEntry(gN1HFcSUB3,"3.0 < |#eta_{EP}| < 3.5","p");
    leg2->AddEntry(gN1HFdSUB3,"3.5 < |#eta_{EP}| < 4.0","p");
    leg2->AddEntry(gN1HFeSUB3,"4.0 < |#eta_{EP}| < 4.5","p");
    leg2->AddEntry(gN1HFfSUB3,"4.5 < |#eta_{EP}| < 5.0","p");
    leg2->Draw();
    c2->Print("SPPlot.png","png");


}
