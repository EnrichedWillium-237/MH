# include "TCanvas.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TPaveText.h"
# include <iostream>

# include "/mnt/c/Users/willj/macros/v1flow/2015_PbPb/MH/macros/src/HiEvtPlaneList.h"

using namespace std;
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

TFile * fin;

void q1q2( string rootfile = "/mnt/c/Users/willj/macros/v1flow/2015_PbPb/MH/MH.root", string Q2 = "track222", int cmin = 25, int cmax = 30 ) {

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    bool mh = true;
    bool ampt = false;
    string tag = "";
    if (rootfile == "/mnt/c/Users/willj/macros/v1flow/2015_PbPb/MH/MH.root") {
        tag+="default";
        mh = true;
        ampt = false;
    }
    if (rootfile == "/mnt/c/Users/willj/macros/v1flow/2015_PbPb/MH/MH_AMPT.root") {
        tag+="AMPT";
        mh = false;
        ampt = true;
    }
    if (Q2 == "track222") tag+="_track222";
    else tag+="_HF2";

    TString cent = Form("%d_%d",cmin,cmax);
    fin = new TFile(rootfile.data(),"read");
    TH2D * res12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/res12",cent.Data()));
    TH2D * resw12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resw12",cent.Data()));
    res12->Divide(resw12);
    // res12->Draw("colz");
    TH1D * prjA;
    TH1D * prjB;
    if (Q2 == "track222") {
        prjA = res12->ProjectionX("prjA", trackp222-HFm2+1, trackp222-HFm2+1);
        prjB = res12->ProjectionX("prjB", trackm222-HFm2+1, trackm222-HFm2+1);
    }
    else {
        prjA = res12->ProjectionX("prjA", HFp2-HFm2+1, HFp2-HFm2+1);
        prjB = res12->ProjectionX("prjB", HFm2-HFm2+1, HFm2-HFm2+1);
    }

    TCanvas * c0 = new TCanvas(Form("c0_%s",cent.Data()), Form("c0_%s",cent.Data()), 600, 550);
    c0->cd();
    double xA[12], yA[12], yAerr[12], xB[12], yB[12], yBerr[12];
    for (int i = 0; i<12; i++) {
        xA[i] = -2.2 + i*0.4;
        yA[i] = prjA->GetBinContent(trackm122 + i + 1);
        yAerr[i] = prjA->GetBinError(trackm122 + i + 1);
        xB[i] = -2.2 + i*0.4;
        yB[i] = prjB->GetBinContent(trackm122 + i + 1);
        yBerr[i] = prjB->GetBinError(trackm122 + i + 1);
    }
    TGraphErrors * gA = new TGraphErrors(12, xA, yA, 0, yAerr);
    gA->SetMarkerStyle(20);
    gA->SetMarkerSize(1.3);
    gA->SetMarkerColor(kRed);
    gA->SetLineColor(kRed);
    gA->RemovePoint(0);
    gA->RemovePoint(gA->GetN()-1);

    TGraphErrors * gB = new TGraphErrors(12, xB, yB, 0, yBerr);
    gB->SetMarkerStyle(20);
    gB->SetMarkerSize(1.3);
    gB->SetMarkerColor(kBlue);
    gB->SetLineColor(kBlue);
    gB->RemovePoint(0);
    gB->RemovePoint(gB->GetN()-1);

    TH1D * h0 = new TH1D("h0", "h0", 100, -2.4, 2.4);
    h0->SetXTitle("#eta");
    h0->SetYTitle("<Q_{1}^{2}Q_{2}^{*}>");
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(28);
    h0->GetYaxis()->SetTitleSize(28);
    h0->GetXaxis()->SetTitleOffset(1.10);
    h0->GetYaxis()->SetTitleOffset(1.55);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(21);
    h0->GetYaxis()->SetLabelSize(21);
    h0->GetYaxis()->SetRangeUser(0, 0.00035);
    if (mh && Q2 == "HF") h0->GetYaxis()->SetRangeUser(0, 0.00035);
    if (ampt && Q2 == "track222") h0->GetYaxis()->SetRangeUser(0, 0.00010);
    if (ampt && Q2 == "HF") h0->GetYaxis()->SetRangeUser(0, 0.000035);
    h0->Draw();
    gA->Draw("same p");
    gB->Draw("same p");

    TLegend * leg0 = new TLegend(0.58, 0.78, 0.82, 0.90);
    SetLegend(leg0, 20);
    if (Q2 == "track222") {
        leg0->AddEntry(gA, " Q_{2} (2 < #eta < 2.4)", "p");
        leg0->AddEntry(gB, " Q_{2} (-2.4 < #eta < -2.0)", "p");
    } else {
        leg0->AddEntry(gA, " Q_{2} (3 < #eta < 5)", "p");
        leg0->AddEntry(gB, " Q_{2} (-5 < #eta < -3)", "p");
    }
    leg0->Draw();

    TPaveText * tx0 = new TPaveText(0.23, 0.78, 0.39, 0.90, "NDC");
    SetTPaveTxt(tx0, 22);
    if (mh) tx0->AddText("#bf{CMS} PbPb");
    if (ampt) tx0->AddText("AMPT");
    tx0->AddText(Form("%d - %d%%",cmin,cmax));
    tx0->Draw();

    c0->Print(Form("../figures/q1q2corr_%s_%d_%d.pdf",tag.data(),cmin,cmax),"pdf");

}
