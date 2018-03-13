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

TFile * fin = new TFile("../MH.root","read");
TGraphErrors * N1track118SUB2;
TGraphErrors * N1track122SUB2;
TGraphErrors * N1trackm118SUB3;
TGraphErrors * N1trackp118SUB3;
TGraphErrors * N1trackm122SUB3;
TGraphErrors * N1trackp122SUB3;
TGraphErrors * N1HFcSUB2;
TGraphErrors * N1HFdSUB2;
TGraphErrors * N1HFeSUB2;
TGraphErrors * N1HFfSUB2;
TGraphErrors * N1HFgSUB2;
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

        qba = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",ctag.Data(),type.Data())))->GetBinContent(1);
        qca = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",ctag.Data(),type.Data())))->GetBinContent(1);
        qcb = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",ctag.Data(),type.Data())))->GetBinContent(1);
        qbacnt = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",ctag.Data(),type.Data())))->GetBinContent(1);
        qcacnt = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",ctag.Data(),type.Data())))->GetBinContent(1);
        qcbcnt = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",ctag.Data(),type.Data())))->GetBinContent(1);

        qbae = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBA",ctag.Data(),type.Data())))->GetBinError(1);
        qcae = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCA",ctag.Data(),type.Data())))->GetBinError(1);
        qcbe = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCB",ctag.Data(),type.Data())))->GetBinError(1);
        qbacnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qBAcnt",ctag.Data(),type.Data())))->GetBinError(1);
        qcacnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCAcnt",ctag.Data(),type.Data())))->GetBinError(1);
        qcbcnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/qCBcnt",ctag.Data(),type.Data())))->GetBinError(1);

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
            qbae = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBA_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcae = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCA_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcbe = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCB_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qbacnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qBAcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcacnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCAcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
            qcbcnte = ((TH1D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/SubEvents/qCBcnt_%d",ctag.Data(),type.Data(),k)))->GetBinContent(1);
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

    N1HFcSUB2 = getRes("N1HFm1c", N1HFcSUB2, true);
    N1HFcSUB2->SetMarkerStyle(20);
    N1HFcSUB2->SetMarkerSize(1.3);
    N1HFcSUB2->SetMarkerColor(kBlack);
    N1HFcSUB2->SetLineColor(kBlack);

    N1HFdSUB2 = getRes("N1HFm1d", N1HFdSUB2, true);
    N1HFdSUB2->SetMarkerStyle(25);
    N1HFdSUB2->SetMarkerSize(1.2);
    N1HFdSUB2->SetMarkerColor(kRed);
    N1HFdSUB2->SetLineColor(kRed);

    N1HFeSUB2 = getRes("N1HFm1e", N1HFeSUB2, true);
    N1HFeSUB2->SetMarkerStyle(21);
    N1HFeSUB2->SetMarkerSize(1.2);
    N1HFeSUB2->SetMarkerColor(kGreen+2);
    N1HFeSUB2->SetLineColor(kGreen+2);

    N1HFfSUB2 = getRes("N1HFm1f", N1HFfSUB2, true);
    N1HFfSUB2->SetMarkerStyle(24);
    N1HFfSUB2->SetMarkerSize(1.3);
    N1HFfSUB2->SetMarkerColor(kBlue);
    N1HFfSUB2->SetLineColor(kBlue);

    N1track118SUB2 = getRes("N1MCm18", N1track118SUB2, true);
    N1track118SUB2->SetMarkerStyle(28);
    N1track118SUB2->SetMarkerSize(1.6);
    N1track118SUB2->SetMarkerColor(kCyan+2);
    N1track118SUB2->SetLineColor(kCyan+2);

    N1track122SUB2 = getRes("N1MCm22", N1track122SUB2, true);
    N1track122SUB2->SetMarkerStyle(34);
    N1track122SUB2->SetMarkerSize(1.6);
    N1track122SUB2->SetMarkerColor(kMagenta);
    N1track122SUB2->SetLineColor(kMagenta);


    TCanvas * c0 = new TCanvas("c0", "c0", 650, 600);
    TPad * pad0 = (TPad *) c0->cd();
    h0 = new TH1D("h0", "h0", 100, 0, 80);
    h0->GetYaxis()->SetRangeUser(0, 0.045);
    h0->GetYaxis()->SetDecimals();
    h0->GetYaxis()->SetNdivisions(508);
    h0->SetXTitle("Centrality (%)");
    h0->SetYTitle("Scalar-product denomenator");
    h0->Draw();
    N1HFcSUB2->Draw("same p");
    N1HFdSUB2->Draw("same p");
    N1HFeSUB2->Draw("same p");
    N1HFfSUB2->Draw("same p");
    // N1track118SUB2->Draw("same p");
    // N1track122SUB2->Draw("same p");
    TLegend * leg0 = new TLegend(0.20, 0.63, 0.47, 0.90);
    SetLegend(leg0, 20);
    leg0->SetHeader("2 subevent v_{1}");
    // leg0->AddEntry(N1track118SUB2,"1.6 < |#eta_{EP}| < 2.0","p");
    // leg0->AddEntry(N1track122SUB2,"2.0 < |#eta_{EP}| < 2.4","p");
    leg0->AddEntry(N1HFcSUB2,"3.0 < |#eta_{EP}| < 3.5","p");
    leg0->AddEntry(N1HFdSUB2,"3.5 < |#eta_{EP}| < 4.0","p");
    leg0->AddEntry(N1HFeSUB2,"4.0 < |#eta_{EP}| < 4.5","p");
    leg0->AddEntry(N1HFfSUB2,"4.5 < |#eta_{EP}| < 5.0","p");
    leg0->Draw();
    c0->Print("resPlot.png","png");


}
