# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "Riostream.h"
# include <iostream>

using namespace std;

# include "src/style.h"

static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20,  60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60, 100};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int nadbins = 6;
static const double adbins[] = {0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};

TFile * fin;
TFile * fout;
TGraphErrors * gintN1HFfSUB3[ncbins];
TGraphErrors * absdiffN1HFfSUB3[ncbins];

void testSymmetry() {

    fin = new TFile("hists/MH_hists_master.root","read");

    fout = new TFile("hists/data_symmetry.root","recreate");
    TDirectory * dirN1HFfSUB3 = (TDirectory *) fout->mkdir("N1HFfSUB3");
    dirN1HFfSUB3->cd();

    for (int cbin = 0; cbin<ncbins; cbin++) {
        gintN1HFfSUB3[cbin] = (TGraphErrors *) fin->Get(Form("N1HFfSUB3/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));

        Double_t xval[30], yval[30], yerr[30];
        int num = gintN1HFfSUB3[cbin]->GetN();
        for (int j = 0; j<num; j++) {
            gintN1HFfSUB3[cbin]->GetPoint(j, xval[j], yval[j]);
            yerr[j] = gintN1HFfSUB3[cbin]->GetErrorY(j);
            // if (cbin == 10) cout<<yerr[j]<<endl;
        }
        Double_t xad[30], yad[30], yaderr[30];
        for (int j = 0; j<6; j++) {
            xad[j] = xval[j+6];
            double yneg = yval[j];
            double ynegErr = yerr[j];
            double ypos = yval[11-j];
            double yposErr = yerr[11-j];
            yad[j] = fabs(ypos) - fabs(yneg);
            yaderr[j] = sqrt( pow(yposErr,2) + pow(ynegErr,2) );
            //if (cbin == 12) cout<<xval[j]<<"\t"<<xad[j]<<"\t"<<yneg<<"\t"<<ypos<<"\t"<<yad[j]<<"\t"<<yerr[j]<<"\t"<<yaderr[j]<<endl;
        }
        absdiffN1HFfSUB3[cbin] = new TGraphErrors(6, xad, yad, 0, yaderr);
        absdiffN1HFfSUB3[cbin]->SetMarkerStyle(20);
        absdiffN1HFfSUB3[cbin]->SetMarkerSize(1.3);
        absdiffN1HFfSUB3[cbin]->SetMarkerColor(kBlack);
        absdiffN1HFfSUB3[cbin]->SetLineColor(kBlack);
        absdiffN1HFfSUB3[cbin]->SetName(Form("gint_%d_%d",cmin[cbin],cmax[cbin]));
        absdiffN1HFfSUB3[cbin]->Write();
    }


    TCanvas * c0 = new TCanvas("c0", "c0", 700, 800);
    c0->Divide(3,4,0,0);
    TH1D * h0 = new TH1D("h0", "h0", 100, 0, 2.0);
    h0->SetStats(0);
    h0->GetYaxis()->SetRangeUser(-0.0045, 0.0045);
    h0->SetXTitle("|#eta|");
    h0->GetXaxis()->SetNdivisions(504);
    h0->GetXaxis()->SetTitleSize(0.08);
    h0->GetXaxis()->CenterTitle();
    h0->GetXaxis()->SetLabelSize(0.07);
    h0->GetYaxis()->SetNdivisions(504);
    h0->GetYaxis()->SetDecimals(3);
    h0->GetYaxis()->SetLabelSize(0.07);
    for (int cbin = 0; cbin<11; cbin++) {
        TPad * pad0 = (TPad *) c0->cd(cbin+1);
        if (cbin == 8) pad0->SetBottomMargin(0.01);
        if (cbin == 2 || cbin == 5 || cbin == 8 || cbin == 10) pad0->SetRightMargin(0.02);
        h0->Draw();
        absdiffN1HFfSUB3[cbin]->Draw("same p");
        TPaveText * tx0 = new TPaveText(0.56, 0.71, 0.82, 0.91, "NDC");
        SetTPaveTxt(tx0, 20);
        tx0->AddText(Form("%d-%d%%",cmin[cbin],cmax[cbin]));
        tx0->Draw();
    }
    c0->cd(12);
    TPaveText * tx1 = new TPaveText(0.12, 0.39, 0.71, 0.80, "NDC");
    SetTPaveTxt(tx1, 22);
    tx1->AddText("#eta_{C} = 0");
    tx1->AddText("|v_{1}^{odd}{+#eta}| - |v_{1}^{odd}{-#eta}|");
    tx1->Draw();
    dirN1HFfSUB3->cd();
    c0->Write();

}
