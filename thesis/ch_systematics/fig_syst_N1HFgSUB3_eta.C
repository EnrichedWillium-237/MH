# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include <iostream>

using namespace std;

static const int ncbins = 23;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70,   0, 10, 20, 30,  10, 10,  0,  40,   0, 20,   5};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80,  10, 20, 30, 40,  60, 70, 40,  80,  20, 60,  80};

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

TFile * fin = new TFile("../../data/vnPlots.root","read");

TGraphErrors * g_default[ncbins];
TGraphErrors * g_loose[ncbins];
TGraphErrors * g_tight[ncbins];
TGraphErrors * g_narrow[ncbins];
TGraphErrors * g_wide[ncbins];

TGraphErrors * gd_default[ncbins];
TGraphErrors * gd_loose[ncbins];
TGraphErrors * gd_tight[ncbins];
TGraphErrors * gd_narrow[ncbins];
TGraphErrors * gd_wide[ncbins];

TGraphErrors * gabs_default[ncbins];
TGraphErrors * gabs_loose[ncbins];
TGraphErrors * gabs_tight[ncbins];
TGraphErrors * gabs_narrow[ncbins];
TGraphErrors * gabs_wide[ncbins];

TGraphErrors * gint_default[ncbins];
TGraphErrors * gint_loose[ncbins];
TGraphErrors * gint_tight[ncbins];
TGraphErrors * gint_narrow[ncbins];
TGraphErrors * gint_wide[ncbins];

TGraphErrors * gintd_default[ncbins];
TGraphErrors * gintd_loose[ncbins];
TGraphErrors * gintd_tight[ncbins];
TGraphErrors * gintd_narrow[ncbins];
TGraphErrors * gintd_wide[ncbins];

TGraphErrors * gintabs_default[ncbins];
TGraphErrors * gintabs_loose[ncbins];
TGraphErrors * gintabs_tight[ncbins];
TGraphErrors * gintabs_narrow[ncbins];
TGraphErrors * gintabs_wide[ncbins];

TCanvas * c_g_trackQuality[ncbins];
TCanvas * c_g_vtxRange[ncbins];
TCanvas * c_gint_trackQuality[ncbins];
TCanvas * c_gint_vtxRange[ncbins];

void fig_syst_N1HFgSUB3_eta() {

    TString tag = "/default/N1HFgSUB3/0.0_2.0/";

    // differential results, track quality
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_g_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/g_trackQuality",tag.Data()));
        TList * list0_0 = c_g_trackQuality[cbin]->GetListOfPrimitives();
        TList & list0_1 = list0_0[0];
        TPad * list0_2 = (TPad *) list0_1.At(0);
        TList & list0_3 = list0_2->GetListOfPrimitives()[0];

        g_loose[cbin] = (TGraphErrors *) list0_3.At(5);
        g_default[cbin] = (TGraphErrors *) list0_3.At(6);
        g_tight[cbin] = (TGraphErrors *) list0_3.At(7);
    }

    // differential results, vtx cut
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_g_vtxRange[cbin] = (TCanvas *) fin->Get(Form("%s/g_vtxRange",tag.Data()));
        TList * list0_0 = c_g_vtxRange[cbin]->GetListOfPrimitives();
        TList & list0_1 = list0_0[0];
        TPad * list0_2 = (TPad *) list0_1.At(0);
        TList & list0_3 = list0_2->GetListOfPrimitives()[0];

        g_wide[cbin] = (TGraphErrors *) list0_3.At(5);
        g_narrow[cbin] = (TGraphErrors *) list0_3.At(7);

        TPad * list0_4 = (TPad *) list0_1.At(3);
        TList & list0_5 = list0_4->GetListOfPrimitives();
    }

    // integral results, track quality
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_gint_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/gint_trackQuality",tag.Data()));
        TList * list0_0 = c_gint_trackQuality[cbin]->GetListOfPrimitives();
        TList & list0_1 = list0_0[0];
        TPad * list0_2 = (TPad *) list0_1.At(0);
        TList & list0_3 = list0_2->GetListOfPrimitives()[0];

        gint_loose[cbin] = (TGraphErrors *) list0_3.At(5);
        gint_default[cbin] = (TGraphErrors *) list0_3.At(6);
        gint_tight[cbin] = (TGraphErrors *) list0_3.At(7);
    }

    // integral results, vtx cut
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

    }

    TCanvas * c0 = new TCanvas("c0","c0",500,500);
    g_narrow[0]->Draw("alp");

}
