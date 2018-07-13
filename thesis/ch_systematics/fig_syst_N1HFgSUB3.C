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

static const int ncbins = 22;
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

TF1 * fg_tight[ncbins];
TF1 * fg_narrow[ncbins];

TF1 * fgint_tight[ncbins];
TF1 * fgint_narrow[ncbins];

void fig_syst_N1HFgSUB3() {

    TString tag = "/default/N1HFgSUB3/0.0_2.0/";

    int minc = 0;
    int maxc = 11;
    // int maxc = ncbins;

    // differential results, track quality
    for (int cbin = minc; cbin<maxc; cbin++) {
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

        fg_tight[cbin] = new TF1(Form("fg_tight_%d",cbin), "pol0", 0.3, 3);
        g_tight[cbin]->Fit(fg_tight[cbin], "QRN0+");
        // cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fg_tight[cbin]->GetParameter(0)<<"\t"<<fg_tight[cbin]->GetParError(0)<<endl;
        cout<<fg_tight[cbin]->GetParameter(0)<<endl;
    }
    cout<<"\n...differential results, track quality: done"<<endl;

    // differential results, vtx cut
    for (int cbin = minc; cbin<maxc; cbin++) {
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

        fg_narrow[cbin] = new TF1(Form("fg_narrow_%d",cbin), "pol0", 0.3, 3);
        g_narrow[cbin]->Fit(fg_narrow[cbin], "QRN0+");
        // cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fg_narrow[cbin]->GetParameter(0)<<"\t"<<fg_narrow[cbin]->GetParError(0)<<endl;
        cout<<fg_narrow[cbin]->GetParameter(0)<<endl;
    }
    cout<<"\n...differential results, vtx cut: done"<<endl;

    // integral results, track quality
    for (int cbin = minc; cbin<maxc; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_gint_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/gint_trackQuality",tag.Data()));
        TList * list_c =  c_gint_trackQuality[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        gint_loose[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(4);
        gint_default[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(5);
        gint_tight[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(6);

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

        fgint_tight[cbin] = new TF1(Form("fgint_tight_%d",cbin), "pol0", 0.3, 3);
        gint_tight[cbin]->Fit(fgint_tight[cbin], "QRN0+");
        // cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fgint_tight[cbin]->GetParameter(0)<<"\t"<<fgint_tight[cbin]->GetParError(0)<<endl;
        cout<<fgint_tight[cbin]->GetParameter(0)<<endl;
    }
    cout<<"\n...integral results, track quality: done"<<endl;

    // integral results, vtx cut
    for (int cbin = minc; cbin<maxc; cbin++) {
        TString tag = Form("/default/N1HFgSUB3/0.0_2.0/%d_%d/systematics",cmin[cbin],cmax[cbin]);

        c_gint_vtxRange[cbin] = (TCanvas *) fin->Get(Form("%s/gint_vtxRange",tag.Data()));
        TList * list_c =  c_gint_vtxRange[cbin]->GetListOfPrimitives();
        TList & list_c_0 = list_c[0];
        TPad * list_c_0_pad0 = (TPad *) list_c_0.At(0);
        TList & list_c_0_pad0_0 = list_c_0_pad0->GetListOfPrimitives()[0];
        gint_wide[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(4);
        gint_narrow[cbin] = (TGraphErrors *) list_c_0_pad0_0.At(6);

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

        fgint_narrow[cbin] = new TF1(Form("fgint_narrow_%d",cbin), "pol0", 0.3, 3);
        gint_narrow[cbin]->Fit(fgint_narrow[cbin], "QRN0+");
        // cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fgint_narrow[cbin]->GetParameter(0)<<"\t"<<fgint_narrow[cbin]->GetParError(0)<<endl;
        cout<<fgint_narrow[cbin]->GetParameter(0)<<endl;
    }
    cout<<"\n...integral results, vtx cut: done"<<endl;


    int setbin = 4;

    TCanvas * c0 = new TCanvas("c0", "c0", 550, 800);
    c0->Divide(1,3,0,0);
    TPad * pad0_1 = (TPad *) c0->cd(1);
    pad0_1->SetRightMargin(0.01);
    TH1D * h0 = new TH1D("h0", "", 500, -2.4, 8);
    h0->GetXaxis()->SetRangeUser(0, 8);
    h0->SetStats(0);
    h0->SetXTitle("p_{T} (GeV/c)");
    h0->SetYTitle("v_{1}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(18);
    h0->GetXaxis()->SetTitleOffset(3.45);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(16);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(18);
    h0->GetYaxis()->SetTitleOffset(3);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(15);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.044, 0.029);
    h0->Draw();
    g_default[setbin]->Draw("p0");
    g_loose[setbin]->Draw("p0");
    g_tight[setbin]->Draw("p0");
    TLegend * leg0 = new TLegend(0.79, 0.67, 0.95, 0.95);
    SetLegend(leg0, 20);
    leg0->AddEntry(g_loose[setbin], " loose", "p0");
    leg0->AddEntry(g_tight[setbin], " tight", "p0");
    leg0->AddEntry(g_default[setbin], " default", "p0");
    leg0->Draw();
    TPaveText * tx0 = new TPaveText(0.23, 0.64, 0.38, 0.95, "NDC");
    SetTPaveTxt(tx0, 18);
    tx0->AddText("v_{1}^{odd}(p_{T}) #eta_{C} = 0");
    tx0->AddText("|#eta| < 2.0");
    tx0->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    tx0->Draw();

    TPad * pad0_2 = (TPad *) c0->cd(2);
    pad0_2->SetRightMargin(0.01);
    pad0_2->SetGrid();
    TH1D * h0_1 = (TH1D *) h0->Clone();
    h0_1->SetYTitle("v_{1} - v_{1}{default} (#times 1000)");
    h0_1->GetYaxis()->SetRangeUser(-3.4, 3.4);
    h0_1->Draw();
    gd_loose[setbin]->Draw("p0");
    gd_tight[setbin]->Draw("p0");

    TPad * pad0_3 = (TPad *) c0->cd(3);
    pad0_3->SetRightMargin(0.01);
    pad0_3->SetGrid();
    TH1D * h0_2 = (TH1D *) h0->Clone();
    h0_2->SetYTitle("Absolute uncertainty (#times 1000)");
    h0_2->GetYaxis()->SetRangeUser(-0.7, 0.7);
    h0_2->Draw();
    gabs_loose_gshade[setbin]->Draw("f");
    gabs_loose_gmin[setbin]->Draw("l");
    gabs_loose_gmax[setbin]->Draw("l");
    gabs_tight_gshade[setbin]->Draw("f");
    gabs_tight_gmin[setbin]->Draw("l");
    gabs_tight_gmax[setbin]->Draw("l");

    c0->Print("../figures/fig_syst_N1HFgSUB3_pt_trkQuality.pdf","pdf");



    TCanvas * c1 = new TCanvas("c1", "c1", 550, 800);
    c1->Divide(1,3,0,0);
    TPad * pad1_1 = (TPad *) c1->cd(1);
    pad1_1->SetRightMargin(0.01);
    TH1D * h1_0 = (TH1D *) h0->Clone("h1_0");
    h1_0->GetXaxis()->SetRangeUser(-2.4, 2.4);
    h1_0->GetYaxis()->SetRangeUser(-0.014, 0.014);
    h1_0->Draw();
    gint_default[setbin]->Draw("p0");
    gint_loose[setbin]->Draw("p0");
    gint_tight[setbin]->Draw("p0");
    TLegend * leg1 = new TLegend(0.79, 0.67, 0.95, 0.95);
    SetLegend(leg1, 20);
    leg1->AddEntry(gint_loose[setbin], " loose", "p0");
    leg1->AddEntry(gint_tight[setbin], " tight", "p0");
    leg1->AddEntry(gint_default[setbin], " default", "p0");
    leg1->Draw();
    TPaveText * tx1 = new TPaveText(0.24, 0.06, 0.39, 0.38, "NDC");
    SetTPaveTxt(tx1, 18);
    tx1->AddText("v_{1}^{odd}(#eta) #eta_{C} = 0");
    tx1->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx1->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    tx1->Draw();

    TPad * pad1_2 = (TPad *) c1->cd(2);
    pad1_2->SetRightMargin(0.01);
    pad1_2->SetGrid();
    TH1D * h1_1 = (TH1D *) h1_0->Clone();
    h1_1->SetYTitle("v_{1} - v_{1}{default} (#times 1000)");
    h1_1->GetYaxis()->SetRangeUser(-1.2, 1.2);
    h1_1->Draw();
    gintd_loose[setbin]->Draw("p0");
    gintd_tight[setbin]->Draw("p0");

    TPad * pad1_3 = (TPad *) c1->cd(3);
    pad1_3->SetRightMargin(0.01);
    pad1_3->SetGrid();
    TH1D * h1_2 = (TH1D *) h1_0->Clone();
    h1_2->SetYTitle("Absolute uncertainty (#times 1000)");
    h1_2->GetYaxis()->SetRangeUser(-0.7, 0.7);
    h1_2->Draw();
    gintabs_loose_gshade[setbin]->Draw("f");
    gintabs_loose_gmin[setbin]->Draw("l");
    gintabs_loose_gmax[setbin]->Draw("l");
    gintabs_tight_gshade[setbin]->Draw("f");
    gintabs_tight_gmin[setbin]->Draw("l");
    gintabs_tight_gmax[setbin]->Draw("l");

    c1->Print("../figures/fig_syst_N1HFgSUB3_eta_trkQuality.pdf","pdf");



    TCanvas * c2 = new TCanvas("c2", "c2", 550, 800);
    c2->Divide(1,3,0,0);
    TPad * pad2_1 = (TPad *) c2->cd(1);
    pad2_1->SetRightMargin(0.01);
    TH1D * h2_0 = (TH1D *) h0->Clone("h2_0");
    h2_0->GetYaxis()->SetRangeUser(-0.052, 0.035);
    h2_0->Draw();
    g_default[setbin]->Draw("p0");
    g_wide[setbin]->Draw("p0");
    g_narrow[setbin]->Draw("p0");
    TLegend * leg2 = new TLegend(0.79, 0.67, 0.95, 0.95);
    SetLegend(leg2, 20);
    leg2->AddEntry(g_wide[setbin], " wide", "p0");
    leg2->AddEntry(g_narrow[setbin], " narrow", "p0");
    leg2->AddEntry(g_default[setbin], " default", "p0");
    leg2->Draw();
    TPaveText * tx2 = new TPaveText(0.23, 0.64, 0.38, 0.95, "NDC");
    SetTPaveTxt(tx2, 18);
    tx2->AddText("v_{1}^{odd}(p_{T}) #eta_{C} = 0");
    tx2->AddText("|#eta| < 2.0");
    tx2->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    tx2->Draw();

    TPad * pad2_2 = (TPad *) c2->cd(2);
    pad2_2->SetRightMargin(0.01);
    pad2_2->SetGrid();
    TH1D * h2_1 = (TH1D *) h0_1->Clone();
    h2_1->SetYTitle("v_{1} - v_{1}{default} (#times 1000)");
    h2_1->GetYaxis()->SetRangeUser(-4.4, 4.4);
    h2_1->Draw();
    gd_wide[setbin]->Draw("p0");
    gd_narrow[setbin]->Draw("p0");

    TPad * pad2_3 = (TPad *) c2->cd(3);
    pad2_3->SetRightMargin(0.01);
    pad2_3->SetGrid();
    TH1D * h2_2 = (TH1D *) h0_2->Clone();
    h2_2->SetYTitle("Absolute uncertainty (#times 1000)");
    h2_2->GetYaxis()->SetRangeUser(-1.2, 1.2);
    h2_2->Draw();
    gabs_wide_gshade[setbin]->Draw("f");
    gabs_wide_gmin[setbin]->Draw("l");
    gabs_wide_gmax[setbin]->Draw("l");
    gabs_narrow_gshade[setbin]->Draw("f");
    gabs_narrow_gmin[setbin]->Draw("l");
    gabs_narrow_gmax[setbin]->Draw("l");

    c2->Print("../figures/fig_syst_N1HFgSUB3_pt_vtxRange.pdf","pdf");



    TCanvas * c3 = new TCanvas("c3", "c3", 550, 800);
    c3->Divide(1,3,0,0);
    TPad * pad3_1 = (TPad *) c3->cd(1);
    pad3_1->SetRightMargin(0.01);
    TH1D * h3_0 = (TH1D *) h0->Clone("h3_0");
    h3_0->GetXaxis()->SetRangeUser(-2.4, 2.4);
    h3_0->GetYaxis()->SetRangeUser(-0.014, 0.014);
    h3_0->Draw();
    gint_default[setbin]->Draw("p0");
    gint_wide[setbin]->Draw("p0");
    gint_narrow[setbin]->Draw("p0");
    TLegend * leg3 = new TLegend(0.79, 0.67, 0.95, 0.95);
    SetLegend(leg3, 20);
    leg3->AddEntry(gint_wide[setbin], " wide", "p0");
    leg3->AddEntry(gint_narrow[setbin], " narrow", "p0");
    leg3->AddEntry(gint_default[setbin], " default", "p0");
    leg3->Draw();
    TPaveText * tx3 = new TPaveText(0.24, 0.06, 0.39, 0.38, "NDC");
    SetTPaveTxt(tx3, 18);
    tx3->AddText("v_{1}^{odd}(#eta) #eta_{C} = 0");
    tx3->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx3->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    tx3->Draw();

    TPad * pad3_2 = (TPad *) c3->cd(2);
    pad3_2->SetRightMargin(0.01);
    pad3_2->SetGrid();
    TH1D * h3_1 = (TH1D *) h1_0->Clone();
    h3_1->SetYTitle("v_{1} - v_{1}{default} (#times 1000)");
    h3_1->GetYaxis()->SetRangeUser(-1.8, 1.8);
    h3_1->Draw();
    gintd_wide[setbin]->Draw("p0");
    gintd_narrow[setbin]->Draw("p0");

    TPad * pad3_3 = (TPad *) c3->cd(3);
    pad3_3->SetRightMargin(0.01);
    pad3_3->SetGrid();
    TH1D * h3_2 = (TH1D *) h1_0->Clone();
    h3_2->SetYTitle("Absolute uncertainty (#times 1000)");
    h3_2->GetYaxis()->SetRangeUser(-1.2, 1.2);
    h3_2->Draw();
    gintabs_wide_gshade[setbin]->Draw("f");
    gintabs_wide_gmin[setbin]->Draw("l");
    gintabs_wide_gmax[setbin]->Draw("l");
    gintabs_narrow_gshade[setbin]->Draw("f");
    gintabs_narrow_gmin[setbin]->Draw("l");
    gintabs_narrow_gmax[setbin]->Draw("l");

    c3->Print("../figures/fig_syst_N1HFgSUB3_eta_vtxRange.pdf","pdf");


}
