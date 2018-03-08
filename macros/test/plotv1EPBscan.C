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
TGraphErrors * g6A;
TGraphErrors * g7A;
TGraphErrors * g8A;
TGraphErrors * g1B;
TGraphErrors * g2B;
TGraphErrors * g3B;
TGraphErrors * g4B;
TGraphErrors * g5B;
TGraphErrors * g6B;
TGraphErrors * g7B;
TGraphErrors * g8B;
TGraphErrors * g1AB;
TGraphErrors * g2AB;
TGraphErrors * g3AB;
TGraphErrors * g4AB;
TGraphErrors * g5AB;
TGraphErrors * g6AB;
TGraphErrors * g7AB;
TGraphErrors * g8AB;

void plotv1EPBscan() {

    fin = new TFile("data_v1EPBscan.root");

    g1A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g1");
    g1A->RemovePoint(0);
    g1A->RemovePoint(g1A->GetN()-1);

    g2A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g2");
    g2A->RemovePoint(0);
    g2A->RemovePoint(g2A->GetN()-1);

    g3A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g3");
    g3A->RemovePoint(0);
    g3A->RemovePoint(g3A->GetN()-1);

    g4A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g4");
    g4A->RemovePoint(0);
    g4A->RemovePoint(g4A->GetN()-1);

    g5A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g5");
    g5A->RemovePoint(0);
    g5A->RemovePoint(g5A->GetN()-1);

    g6A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g6");
    g6A->RemovePoint(0);
    g6A->RemovePoint(g6A->GetN()-1);

    g7A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g7");
    g7A->RemovePoint(0);
    g7A->RemovePoint(g7A->GetN()-1);

    g8A = (TGraphErrors *) fin->Get("N1HFp1gSUB3/-2.0_2.0/20_60/g8");
    g8A->RemovePoint(0);
    g8A->RemovePoint(g8A->GetN()-1);

    g1B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g1");
    g1B->RemovePoint(0);
    g1B->RemovePoint(g1B->GetN()-1);

    g2B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g2");
    g2B->RemovePoint(0);
    g2B->RemovePoint(g2B->GetN()-1);

    g3B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g3");
    g3B->RemovePoint(0);
    g3B->RemovePoint(g3B->GetN()-1);

    g4B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g4");
    g4B->RemovePoint(0);
    g4B->RemovePoint(g4B->GetN()-1);

    g5B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g5");
    g5B->RemovePoint(0);
    g5B->RemovePoint(g5B->GetN()-1);

    g6B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g6");
    g6B->RemovePoint(0);
    g6B->RemovePoint(g6B->GetN()-1);

    g7B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g7");
    g7B->RemovePoint(0);
    g7B->RemovePoint(g7B->GetN()-1);

    g8B = (TGraphErrors *) fin->Get("N1HFm1gSUB3/-2.0_2.0/20_60/g8");
    g8B->RemovePoint(0);
    g8B->RemovePoint(g8B->GetN()-1);

    //-- average side to get v1odd

    int num = g1A->GetN();
    double xA[30],  yA[30],  yAerr[30];
    double xB[30],  yB[30],  yBerr[30];
    double xAB[30], yAB[30], yABerr[30];
    for (int i = 0; i<num; i++) {
        g1A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g1A->GetErrorY(i);
        g1B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g1B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g1AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g2A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g2A->GetErrorY(i);
        g2B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g2B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g2AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g3A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g3A->GetErrorY(i);
        g3B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g3B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g3AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g4A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g4A->GetErrorY(i);
        g4B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g4B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g4AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g5A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g5A->GetErrorY(i);
        g5B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g5B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g5AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g6A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g6A->GetErrorY(i);
        g6B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g6B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g6AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g7A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g7A->GetErrorY(i);
        g7B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g7B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g7AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    for (int i = 0; i<num; i++) {
        g8A->GetPoint(i, xA[i], yA[i]);
        yAerr[i] = g8A->GetErrorY(i);
        g8B->GetPoint(i, xB[i], yB[i]);
        yBerr[i] = g8B->GetErrorY(i);

        yAB[i] = 0.5*(yA[i] - yB[i]);
        // yABerr[i] = ErrDiffCalc(yA[i], yB[i], yAerr[i], yBerr[i]);
        yABerr[i] = 0.5*sqrt( pow(yAerr[i],2) + pow(yBerr[i],2) );
    }
    g8AB = new TGraphErrors(num, xA, yAB, 0, yABerr);

    g1AB->SetMarkerStyle(24);
    g1AB->SetMarkerSize(1.3);
    g1AB->SetMarkerColor(kBlack);
    g1AB->SetLineColor(kBlack);

    g2AB->SetMarkerStyle(20);
    g2AB->SetMarkerSize(1.3);
    g2AB->SetMarkerColor(kBlue);
    g2AB->SetLineColor(kBlue);

    g3AB->SetMarkerStyle(21);
    g3AB->SetMarkerSize(1.2);
    g3AB->SetMarkerColor(kGreen+2);
    g3AB->SetLineColor(kGreen+2);

    g4AB->SetMarkerStyle(25);
    g4AB->SetMarkerSize(1.2);
    g4AB->SetMarkerColor(kMagenta);
    g4AB->SetLineColor(kMagenta);

    g5AB->SetMarkerStyle(20);
    g5AB->SetMarkerSize(1.3);
    g5AB->SetMarkerColor(kOrange-3);
    g5AB->SetLineColor(kOrange-3);

    g6AB->SetMarkerStyle(28);
    g6AB->SetMarkerSize(1.6);
    g6AB->SetMarkerColor(kBlue-3);
    g6AB->SetLineColor(kBlue-3);

    g7AB->SetMarkerStyle(34);
    g7AB->SetMarkerSize(1.6);
    g7AB->SetMarkerColor(kRed-3);
    g7AB->SetLineColor(kRed-3);

    g8AB->SetMarkerStyle(33);
    g8AB->SetMarkerSize(1.7);
    g8AB->SetMarkerColor(kCyan+2);
    g8AB->SetLineColor(kCyan+2);


    TCanvas * cA = new TCanvas("cA", "cA", 620, 600);
    TPad * padA = (TPad *) cA->cd();
    padA->SetTopMargin(0.08);
    padA->SetLeftMargin(0.18);
    hA = new TH1D("hA", "", 100, -2.5, 2.5);
    hA->SetStats(0);
    hA->SetXTitle("#eta");
    hA->SetYTitle("v_{1}");
    hA->GetYaxis()->SetDecimals();
    hA->GetYaxis()->SetNdivisions(509);
    hA->GetXaxis()->CenterTitle();
    hA->GetYaxis()->CenterTitle();
    hA->GetXaxis()->SetTitleOffset(1.15);
    hA->GetYaxis()->SetTitleOffset(1.65);
    hA->GetYaxis()->SetRangeUser(-0.046, 0.0);
    hA->Draw();
    g1A->Draw("same p");
    g2A->Draw("same p");
    g3A->Draw("same p");
    g4A->Draw("same p");
    g5A->Draw("same p");
    g6A->Draw("same p");
    g7A->Draw("same p");
    g8A->Draw("same p");

    TPaveText * txA0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txA0, 20);
    txA0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    txA0->Draw();

    TPaveText * txA1 = new TPaveText(0.22, 0.74, 0.37, 0.88, "NDC");
    SetTPaveTxt(txA1, 22);
    txA1->AddText("20 - 60%");
    txA1->AddText("4.0 < #eta_{A} < 5.0");
    txA1->AddText("0.4 < #eta_{C} < 0.8");
    txA1->Draw();

    TLegend * legA = new TLegend(0.67, 0.56, 0.91, 0.88);
    SetLegend(legA, 18);
    legA->AddEntry(g1A,"-5.0 < #eta_{B} < -4.0","p");
    legA->AddEntry(g2A,"-5.0 < #eta_{B} < -4.5","p");
    legA->AddEntry(g3A,"-4.5 < #eta_{B} < -4.0","p");
    legA->AddEntry(g4A,"-4.0 < #eta_{B} < -3.5","p");
    legA->AddEntry(g5A,"-3.5 < #eta_{B} < -3.0","p");
    legA->AddEntry(g6A,"-2.4 < #eta_{B} < -2.0","p");
    legA->AddEntry(g7A,"-2.0 < #eta_{B} < -1.6","p");
    legA->AddEntry(g8A,"-1.6 < #eta_{B} < -1.2","p");
    legA->Draw();

    cA->Print("fig_v1EPBscanA.pdf","pdf");
    // cA->Print("fig_v1EPBscanA.png","png");


    //--  --//

    TCanvas * cB = new TCanvas("cB", "cB", 620, 600);
    TPad * padB = (TPad *) cB->cd();
    padB->SetTopMargin(0.08);
    padB->SetLeftMargin(0.18);
    hB = new TH1D("hB", "", 100, -2.5, 2.5);
    hB->SetStats(0);
    hB->SetXTitle("#eta");
    hB->SetYTitle("v_{1}");
    hB->GetYaxis()->SetDecimals();
    hB->GetYaxis()->SetNdivisions(509);
    hB->GetXaxis()->CenterTitle();
    hB->GetYaxis()->CenterTitle();
    hB->GetXaxis()->SetTitleOffset(1.15);
    hB->GetYaxis()->SetTitleOffset(1.65);
    hB->GetYaxis()->SetRangeUser(-0.046, 0.0);
    hB->Draw();
    g1B->Draw("same p");
    g2B->Draw("same p");
    g3B->Draw("same p");
    g4B->Draw("same p");
    g5B->Draw("same p");
    g6B->Draw("same p");
    g7B->Draw("same p");
    g8B->Draw("same p");

    TPaveText * txB0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txB0, 20);
    txB0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    //txB0->Draw();

    TPaveText * txB1 = new TPaveText(0.68, 0.74, 0.83, 0.88, "NDC");
    SetTPaveTxt(txB1, 22);
    txB1->AddText("20 - 60%");
    txB1->AddText("-5.0 < #eta_{A} < -4.0");
    txB1->AddText("-0.8 < #eta_{C} < -0.4");
    txB1->Draw();

    TLegend * legB = new TLegend(0.22, 0.56, 0.46, 0.88);
    SetLegend(legB, 18);
    legB->AddEntry(g1B,"4.0 < #eta_{B} < 5.0","p");
    legB->AddEntry(g2B,"4.5 < #eta_{B} < 5.0","p");
    legB->AddEntry(g3B,"4.0 < #eta_{B} < 4.5","p");
    legB->AddEntry(g4B,"3.5 < #eta_{B} < 4.0","p");
    legB->AddEntry(g5B,"3.0 < #eta_{B} < 3.5","p");
    legB->AddEntry(g6B,"2.0 < #eta_{B} < 2.4","p");
    legB->AddEntry(g7B,"1.6 < #eta_{B} < 2.0","p");
    legB->AddEntry(g8B,"1.2 < #eta_{B} < 1.6","p");
    legB->Draw();

    cB->Print("fig_v1EPBscanB.pdf","pdf");
    // cB->Print("fig_v1EPBscanB.png","png");


    //--  --//

    TCanvas * cAB = new TCanvas("cAB", "cAB", 620, 600);
    TPad * padAB = (TPad *) cAB->cd();
    padAB->SetTopMargin(0.08);
    padAB->SetLeftMargin(0.18);
    hAB = new TH1D("hAB", "", 100, -2.5, 2.5);
    hAB->SetStats(0);
    hAB->SetXTitle("#eta");
    hAB->SetYTitle("v_{1}^{odd}");
    hAB->GetYaxis()->SetDecimals();
    hAB->GetYaxis()->SetNdivisions(509);
    hAB->GetXaxis()->CenterTitle();
    hAB->GetYaxis()->CenterTitle();
    hAB->GetXaxis()->SetTitleOffset(1.15);
    hAB->GetYaxis()->SetTitleOffset(1.65);
    hAB->GetYaxis()->SetRangeUser(-0.022, 0.022);
    hAB->Draw();
    g1AB->Draw("same p");
    g2AB->Draw("same p");
    g3AB->Draw("same p");
    g4AB->Draw("same p");
    g5AB->Draw("same p");
    g6AB->Draw("same p");
    g7AB->Draw("same p");
    g8AB->Draw("same p");

    TPaveText * txAB0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txAB0, 20);
    txAB0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    txAB0->Draw();

    TPaveText * txAB1 = new TPaveText(0.64, 0.75, 0.79, 0.90, "NDC");
    SetTPaveTxt(txAB1, 22);
    txAB1->AddText("20 - 60%");
    txAB1->AddText("-5.0 < |#eta_{A}| < -4.0");
    txAB1->AddText("-0.8 < |#eta_{C}| < -0.4");
    txAB1->Draw();

    TLegend * legAB = new TLegend(0.22, 0.18, 0.46, 0.50);
    SetLegend(legAB, 18);
    legAB->AddEntry(g1AB,"4.0 < |#eta_{B}| < 5.0","p");
    legAB->AddEntry(g2AB,"4.5 < |#eta_{B}| < 5.0","p");
    legAB->AddEntry(g3AB,"4.0 < |#eta_{B}| < 4.5","p");
    legAB->AddEntry(g4AB,"3.5 < |#eta_{B}| < 4.0","p");
    legAB->AddEntry(g5AB,"3.0 < |#eta_{B}| < 3.5","p");
    legAB->AddEntry(g6AB,"2.0 < |#eta_{B}| < 2.4","p");
    legAB->AddEntry(g7AB,"1.6 < |#eta_{B}| < 2.0","p");
    legAB->AddEntry(g8AB,"1.2 < |#eta_{B}| < 1.6","p");
    legAB->Draw();

    cAB->Print("fig_v1EPBscanAB.pdf","pdf");
    // cAB->Print("fig_v1EPBscanAB.png","png");


}
