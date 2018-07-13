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

TGraphErrors * gd_loose[ncbins];
TGraphErrors * gd_tight[ncbins];
TGraphErrors * gd_narrow[ncbins];
TGraphErrors * gd_wide[ncbins];

TGraph * gabs_loose_gshade[ncbins];
TGraph * gabs_loose_gmin[ncbins];
TGraph * gabs_loose_gmax[ncbins];
TGraph * gabs_tight_gshade[ncbins];
TGraph * gabs_tight_gmin[ncbins];
TGraph * gabs_tight_gmax[ncbins];
TGraph * gabs_narrow_gshade[ncbins];
TGraph * gabs_narrow_gmin[ncbins];
TGraph * gabs_narrow_gmax[ncbins];
TGraph * gabs_wide_gshade[ncbins];
TGraph * gabs_wide_gmin[ncbins];
TGraph * gabs_wide_gmax[ncbins];


TGraphErrors * gint_default[ncbins];
TGraphErrors * gint_loose[ncbins];
TGraphErrors * gint_tight[ncbins];
TGraphErrors * gint_narrow[ncbins];
TGraphErrors * gint_wide[ncbins];

TGraphErrors * gintd_loose[ncbins];
TGraphErrors * gintd_tight[ncbins];
TGraphErrors * gintd_narrow[ncbins];
TGraphErrors * gintd_wide[ncbins];

TGraph * gintabs_loose_gshade[ncbins];
TGraph * gintabs_loose_gmin[ncbins];
TGraph * gintabs_loose_gmax[ncbins];
TGraph * gintabs_tight_gshade[ncbins];
TGraph * gintabs_tight_gmin[ncbins];
TGraph * gintabs_tight_gmax[ncbins];
TGraph * gintabs_narrow_gshade[ncbins];
TGraph * gintabs_narrow_gmin[ncbins];
TGraph * gintabs_narrow_gmax[ncbins];
TGraph * gintabs_wide_gshade[ncbins];
TGraph * gintabs_wide_gmin[ncbins];
TGraph * gintabs_wide_gmax[ncbins];

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
        TList * list_c =  c_g_trackQuality[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        g_loose[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(5);
        g_default[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(6);
        g_tight[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(7);

        TPad * list_c_0_pad4 = (TPad *) list_c_0.At(4);
        TList & list_c_0_pad4_0 = list_c_0_pad4->GetListOfPrimitives()[0];
        gd_loose[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(2);
        gd_tight[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(3);

        TPad * list_c_0_pad5 = (TPad *) list_c_0.At(5);
        TList & list_c_0_pad5_0 = list_c_0_pad5->GetListOfPrimitives()[0];
        gabs_loose_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(2);
        gabs_loose_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(3);
        gabs_loose_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(4);
        gabs_tight_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(5);
        gabs_tight_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(6);
        gabs_tight_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(7);
    }

    // differential results, vtx cut
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_g_vtxRange[cbin] = (TCanvas *) fin->Get(Form("%s/g_vtxRange",tag.Data()));
        TList * list_c =  c_g_vtxRange[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        g_wide[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(5);
        g_narrow[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(7);

        TPad * list_c_0_pad4 = (TPad *) list_c_0.At(4);
        TList & list_c_0_pad4_0 = list_c_0_pad4->GetListOfPrimitives()[0];
        gd_wide[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(2);
        gd_narrow[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(3);

        TPad * list_c_0_pad5 = (TPad *) list_c_0.At(5);
        TList & list_c_0_pad5_0 = list_c_0_pad5->GetListOfPrimitives()[0];
        gabs_wide_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(2);
        gabs_wide_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(3);
        gabs_wide_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(4);
        gabs_narrow_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(5);
        gabs_narrow_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(6);
        gabs_narrow_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(7);
    }

    // integral results, track quality
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_gint_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/gint_trackQuality",tag.Data()));
        TList * list_c =  c_gint_trackQuality[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        gint_loose[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(5);
        gint_default[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(6);
        gint_tight[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(7);

        TPad * list_c_0_pad4 = (TPad *) list_c_0.At(4);
        TList & list_c_0_pad4_0 = list_c_0_pad4->GetListOfPrimitives()[0];
        gintd_loose[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(2);
        gintd_tight[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(3);

        TPad * list_c_0_pad5 = (TPad *) list_c_0.At(5);
        TList & list_c_0_pad5_0 = list_c_0_pad5->GetListOfPrimitives()[0];
        gintabs_loose_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(2);
        gintabs_loose_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(3);
        gintabs_loose_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(4);
        gintabs_tight_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(5);
        gintabs_tight_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(6);
        gintabs_tight_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(7);
    }

    // integral results, vtx cut
    for (int cbin = 0; cbin<1; cbin++) {
    // for (int cbin = 0; cbin<ncbins; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_gint_vtxRange[cbin] = (TCanvas *) fin->Get(Form("%s/gint_vtxRange",tag.Data()));
        TList * list_c =  c_gint_vtxRange[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        gint_wide[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(5);
        gint_narrow[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(7);

        TPad * list_c_0_pad4 = (TPad *) list_c_0.At(4);
        TList & list_c_0_pad4_0 = list_c_0_pad4->GetListOfPrimitives()[0];
        gintd_wide[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(2);
        gintd_narrow[cbin] = (TGraphErrors *) list_c_0_pad4_0.At(3);

        TPad * list_c_0_pad5 = (TPad *) list_c_0.At(5);
        TList & list_c_0_pad5_0 = list_c_0_pad5->GetListOfPrimitives()[0];
        gintabs_wide_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(2);
        gintabs_wide_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(3);
        gintabs_wide_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(4);
        gintabs_narrow_gshade[cbin] = (TGraph *) list_c_0_pad5_0.At(5);
        gintabs_narrow_gmin[cbin] = (TGraph *) list_c_0_pad5_0.At(6);
        gintabs_narrow_gmax[cbin] = (TGraph *) list_c_0_pad5_0.At(7);
    }

    // TCanvas * c0 = new TCanvas("c0","c0",500,500);
    // gintabs_loose_gshade[0]->Draw("af");
    // gintabs_loose_gmin[0]->Draw("l");
    // gintabs_loose_gmax[0]->Draw("l");
    // gintabs_tight_gshade[0]->Draw("f");
    // gintabs_tight_gmin[0]->Draw("l");
    // gintabs_tight_gmax[0]->Draw("l");
    TCanvas * c0 = new TCanvas("c0","c0",500,500);
    gintabs_wide_gshade[0]->Draw("af");
    gintabs_wide_gmin[0]->Draw("l");
    gintabs_wide_gmax[0]->Draw("l");
    gintabs_narrow_gshade[0]->Draw("f");
    gintabs_narrow_gmin[0]->Draw("l");
    gintabs_narrow_gmax[0]->Draw("l");
    // gint_loose[0]->Draw("alp");
    // gint_default[0]->Draw("lp");
    // gint_tight[0]->Draw("lp");

}
