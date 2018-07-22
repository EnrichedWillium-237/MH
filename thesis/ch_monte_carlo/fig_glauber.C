# include "TAttAxis.h"
# include "TAttFill.h"
# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraph.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TLine.h"
# include "TPaveText.h"
# include "TString.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

using namespace std;

static const int ncbins = 20;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95,100};

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

void SetTPaveTxt2( TPaveText * txtemplate, int txtsize ) {
    txtemplate->SetFillColor(0);
    txtemplate->SetBorderSize(0);
    txtemplate->SetTextFont(43);
    txtemplate->SetTextSize(txtsize);
}

TFile * fin = new TFile("../../data/glauber_minorAxes.root","read");

TH2D * xy1[ncbins];
TH2D * xy2[ncbins];
TH2D * xy3[ncbins];
TH2D * xy4[ncbins];
TH2D * xy5[ncbins];
TH2D * xy6[ncbins];

void fig_glauber() {

    int centbin = 5;

    for (int cbin = 0; cbin<ncbins; cbin++) {
        xy1[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy1_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
        xy2[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy2_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
        xy3[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy3_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
        xy4[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy4_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
        xy5[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy5_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
        xy6[cbin] = (TH2D *) fin->Get(Form("moments/%d-%d/x_vs_y/xy6_%d-%d",cmin[cbin],cmax[cbin],cmin[cbin],cmax[cbin]));
    }

    cout<<"\nPrinting results for centrality bin "<<cmin[centbin]<<"-"<<cmax[centbin]<<"%: \n"<<endl;

    TCanvas * c_v1 = new TCanvas("c_v1", "c_v1", 500, 500);
    TPad * pad_v1 = (TPad *) c_v1->cd();
    pad_v1->SetTopMargin(0);
    pad_v1->SetBottomMargin(0);
    pad_v1->SetLeftMargin(0);
    pad_v1->SetRightMargin(0);
    xy1[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy1[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy1[centbin]->Draw("CONT1 AH");
    c_v1->Print("../figures/fig_glauber_v1.pdf","pdf");

    TCanvas * c_v2 = new TCanvas("c_v2", "c_v2", 500, 500);
    TPad * pad_v2 = (TPad *) c_v2->cd();
    pad_v2->SetTopMargin(0);
    pad_v2->SetBottomMargin(0);
    pad_v2->SetLeftMargin(0);
    pad_v2->SetRightMargin(0);
    xy2[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy2[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy2[centbin]->Draw("CONT1 AH");
    c_v2->Print("../figures/fig_glauber_v2.pdf","pdf");

    TCanvas * c_v3 = new TCanvas("c_v3", "c_v3", 500, 500);
    TPad * pad_v3 = (TPad *) c_v3->cd();
    pad_v3->SetTopMargin(0);
    pad_v3->SetBottomMargin(0);
    pad_v3->SetLeftMargin(0);
    pad_v3->SetRightMargin(0);
    xy3[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy3[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy3[centbin]->Draw("CONT1 AH");
    c_v3->Print("../figures/fig_glauber_v3.pdf","pdf");

    TCanvas * c_v4 = new TCanvas("c_v4", "c_v4", 500, 500);
    TPad * pad_v4 = (TPad *) c_v4->cd();
    pad_v4->SetTopMargin(0);
    pad_v4->SetBottomMargin(0);
    pad_v4->SetLeftMargin(0);
    pad_v4->SetRightMargin(0);
    xy4[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy4[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy4[centbin]->Draw("CONT1 AH");
    c_v4->Print("../figures/fig_glauber_v4.pdf","pdf");

    TCanvas * c_v5 = new TCanvas("c_v5", "c_v5", 500, 500);
    TPad * pad_v5 = (TPad *) c_v5->cd();
    pad_v5->SetTopMargin(0);
    pad_v5->SetBottomMargin(0);
    pad_v5->SetLeftMargin(0);
    pad_v5->SetRightMargin(0);
    xy5[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy5[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy5[centbin]->Draw("CONT1 AH");
    c_v5->Print("../figures/fig_glauber_v5.pdf","pdf");

    TCanvas * c_v6 = new TCanvas("c_v6", "c_v6", 500, 500);
    TPad * pad_v6 = (TPad *) c_v6->cd();
    pad_v6->SetTopMargin(0);
    pad_v6->SetBottomMargin(0);
    pad_v6->SetLeftMargin(0);
    pad_v6->SetRightMargin(0);
    xy6[centbin]->GetXaxis()->SetRangeUser(-7, 7);
    xy6[centbin]->GetYaxis()->SetRangeUser(-7, 7);
    xy6[centbin]->Draw("CONT1 AH");
    c_v6->Print("../figures/fig_glauber_v6.pdf","pdf");

}
