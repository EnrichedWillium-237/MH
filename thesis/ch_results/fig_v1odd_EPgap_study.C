# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGaxis.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include <iostream>

using namespace std;

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

double ErrDiffCalc( double x, double y, double delx, double dely ) {
    double f = x;
    f-=y;
    double delf = sqrt( fabs(delx*delx - dely*dely) );
    return delf;
}

TFile * fin;
TH1D * hA;
TH1D * hB;
TH1D * hAB;
TGraphErrors * g1A;
TGraphErrors * g2A;
TGraphErrors * g3A;
TGraphErrors * g4A;
TGraphErrors * g5A;
TGraphErrors * g1B;
TGraphErrors * g2B;
TGraphErrors * g3B;
TGraphErrors * g4B;
TGraphErrors * g5B;
TGraphErrors * g1AB;
TGraphErrors * g2AB;
TGraphErrors * g3AB;
TGraphErrors * g4AB;
TGraphErrors * g5AB;

void fig_v1odd_EPgap_study() {

    fin = new TFile("../../data/vnPlots.root");

    g1AB = (TGraphErrors *) fin->Get("default/N1HFcSUB3/-2.0_0.0/20_60/gint");
    // g1AB->RemovePoint(0);
    // g1AB->RemovePoint(g1AB->GetN()-1);

    g2AB = (TGraphErrors *) fin->Get("default/N1HFdSUB3/-2.0_0.0/20_60/gint");
    // g2AB->RemovePoint(0);
    // g2AB->RemovePoint(g2AB->GetN()-1);

    g3AB = (TGraphErrors *) fin->Get("default/N1HFeSUB3/-2.0_0.0/20_60/gint");
    // g3AB->RemovePoint(0);
    // g3AB->RemovePoint(g3AB->GetN()-1);

    g4AB = (TGraphErrors *) fin->Get("default/N1HFfSUB3/-2.0_0.0/20_60/gint");
    // g4AB->RemovePoint(0);
    // g4AB->RemovePoint(g4AB->GetN()-1);


    g1AB->SetMarkerStyle(25);
    g1AB->SetMarkerSize(1.3);
    g1AB->SetMarkerColor(kBlack);
    g1AB->SetLineColor(kBlack);

    g2AB->SetMarkerStyle(20);
    g2AB->SetMarkerSize(1.3);
    g2AB->SetMarkerColor(kRed);
    g2AB->SetLineColor(kRed);

    g3AB->SetMarkerStyle(24);
    g3AB->SetMarkerSize(1.2);
    g3AB->SetMarkerColor(kGreen+2);
    g3AB->SetLineColor(kGreen+2);

    g4AB->SetMarkerStyle(21);
    g4AB->SetMarkerSize(1.2);
    g4AB->SetMarkerColor(kBlue);
    g4AB->SetLineColor(kBlue);


    //--  --//

    TCanvas * cAB = new TCanvas("cAB", "cAB", 620, 600);
    TPad * padAB = (TPad *) cAB->cd();
    padAB->SetTopMargin(0.08);
    padAB->SetLeftMargin(0.18);
    hAB = new TH1D("hAB", "", 100, -2.8, 2.8);
    hAB->SetStats(0);
    hAB->SetXTitle("#eta");
    hAB->SetYTitle("v_{1}^{odd}");
    hAB->GetYaxis()->SetDecimals();
    hAB->GetYaxis()->SetNdivisions(509);
    hAB->GetXaxis()->CenterTitle();
    hAB->GetYaxis()->CenterTitle();
    hAB->GetXaxis()->SetTitleOffset(1.15);
    hAB->GetYaxis()->SetTitleOffset(1.70);
    hAB->GetYaxis()->SetRangeUser(-0.02, 0.02);
    hAB->Draw();
    g1AB->Draw("same p");
    g2AB->Draw("same p");
    g3AB->Draw("same p");
    g4AB->Draw("same p");

    TPaveText * txAB0 = new TPaveText(0.178, 0.933, 0.420, 0.978, "NDC");
    SetTPaveTxt(txAB0, 20);
    txAB0->AddText("#bf{CMS},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    txAB0->Draw();

    TPaveText * txAB1 = new TPaveText(0.49, 0.75, 0.64, 0.87, "NDC");
    SetTPaveTxt(txAB1, 22);
    txAB1->AddText("#eta_{C} = 0");
    txAB1->AddText("20 - 60%");
    txAB1->Draw();

    TLegend * legAB = new TLegend(0.38, 0.19, 0.62, 0.40);
    SetLegend(legAB, 22);
    legAB->AddEntry(g4AB,"4.5 < |#eta_{A,B}| < 5.0","p");
    legAB->AddEntry(g3AB,"4.0 < |#eta_{A,B}| < 4.5","p");
    legAB->AddEntry(g2AB,"3.5 < |#eta_{A,B}| < 4.0","p");
    legAB->AddEntry(g1AB,"3.0 < |#eta_{A,B}| < 3.5","p");
    legAB->Draw();

    cAB->Print("../figures/fig_v1odd_EPgap_study.pdf","pdf");

}
