# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TLegend.h"
# include "TLine.h"
# include "TList.h"
# include "TPaveText.h"
# include "TString.h"
# include <iostream>

using namespace std;

static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,   0, 20,  60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70,  20, 60, 100};

TFile * fin = new TFile("../MH_hists_master.root","read");

TGraphErrors * gint_N1HFgSUB2[ncbins];
TGraphErrors * gint_N1HFgSUB2_narrow[ncbins];
TGraphErrors * gint_N1HFgSUB2_wide[ncbins];

TGraphErrors * ratio_gint_N1HFgSUB2_narrow[ncbins];
TGraphErrors * ratio_gint_N1HFgSUB2_wide[ncbins];

TGraphErrors * diff_gint_N1HFgSUB2_narrow[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_wide[ncbins];

TGraphErrors * g_N1HFgSUB2[ncbins];
TGraphErrors * g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * g_N1HFgSUB2_wide[ncbins];

TGraphErrors * ratio_g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * ratio_g_N1HFgSUB2_wide[ncbins];

TGraphErrors * diff_g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * diff_g_N1HFgSUB2_wide[ncbins];

TCanvas * cN1HFgSUB2_gint_trackQuality[ncbins];
TCanvas * cN1HFgSUB2_gint_vtxRange[ncbins];

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

void plotSyst_N1HFgSUB2_vtxRange() {

    Double_t fitWide_rat_p0[ncbins];
    Double_t fitNarrow_rat_p0[ncbins];
    Double_t fitWide_diff_p0[ncbins];
    Double_t fitWide_diff_p1[ncbins];
    Double_t fitNarrow_diff_p0[ncbins];
    Double_t fitNarrow_diff_p1[ncbins];
    Double_t fitWide_diff_p0_err[ncbins];
    Double_t fitWide_diff_p1_err[ncbins];
    Double_t fitNarrow_diff_p0_err[ncbins];
    Double_t fitNarrow_diff_p1_err[ncbins];

    for (int cbin = 0; cbin<ncbins; cbin++) {
        string tag = Form("default/N1HFgSUB2/-2.0_2.0/%d_%d",cmin[cbin],cmax[cbin]);

        gint_N1HFgSUB2[cbin] = (TGraphErrors *) fin->Get(Form("%s/gint",tag.data()));
        gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("narrow/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("wide/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));\

        ratio_gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_narrow_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_wide_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));

        diff_gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_narrow_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        diff_gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_wide_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));

        gint_N1HFgSUB2[cbin]->SetMarkerStyle(25);
        gint_N1HFgSUB2[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2[cbin]->SetMarkerColor(kRed);
        gint_N1HFgSUB2[cbin]->SetLineColor(kRed);
        gint_N1HFgSUB2[cbin]->RemovePoint(0);
        gint_N1HFgSUB2[cbin]->RemovePoint(gint_N1HFgSUB2[cbin]->GetN()-1);

        gint_N1HFgSUB2_wide[cbin]->SetMarkerStyle(20);
        gint_N1HFgSUB2_wide[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2_wide[cbin]->SetMarkerColor(kBlue);
        gint_N1HFgSUB2_wide[cbin]->SetLineColor(kBlue);
        gint_N1HFgSUB2_wide[cbin]->RemovePoint(0);
        gint_N1HFgSUB2_wide[cbin]->RemovePoint(gint_N1HFgSUB2_wide[cbin]->GetN()-1);

        gint_N1HFgSUB2_narrow[cbin]->SetMarkerStyle(20);
        gint_N1HFgSUB2_narrow[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2_narrow[cbin]->SetMarkerColor(kGreen+2);
        gint_N1HFgSUB2_narrow[cbin]->SetLineColor(kGreen+2);
        gint_N1HFgSUB2_narrow[cbin]->RemovePoint(0);
        gint_N1HFgSUB2_narrow[cbin]->RemovePoint(gint_N1HFgSUB2_narrow[cbin]->GetN()-1);

        ratio_gint_N1HFgSUB2_narrow[cbin]->SetMarkerStyle(20);
        ratio_gint_N1HFgSUB2_narrow[cbin]->SetMarkerSize(1.0);
        ratio_gint_N1HFgSUB2_narrow[cbin]->SetMarkerColor(kGreen+2);
        ratio_gint_N1HFgSUB2_narrow[cbin]->SetLineColor(kGreen+2);
        ratio_gint_N1HFgSUB2_narrow[cbin]->RemovePoint(0);
        ratio_gint_N1HFgSUB2_narrow[cbin]->RemovePoint(ratio_gint_N1HFgSUB2_narrow[cbin]->GetN()-1);

        ratio_gint_N1HFgSUB2_wide[cbin]->SetMarkerStyle(20);
        ratio_gint_N1HFgSUB2_wide[cbin]->SetMarkerSize(1.0);
        ratio_gint_N1HFgSUB2_wide[cbin]->SetMarkerColor(kBlue);
        ratio_gint_N1HFgSUB2_wide[cbin]->SetLineColor(kBlue);
        ratio_gint_N1HFgSUB2_wide[cbin]->RemovePoint(0);
        ratio_gint_N1HFgSUB2_wide[cbin]->RemovePoint(ratio_gint_N1HFgSUB2_wide[cbin]->GetN()-1);


        diff_gint_N1HFgSUB2_narrow[cbin]->SetMarkerStyle(20);
        diff_gint_N1HFgSUB2_narrow[cbin]->SetMarkerSize(1.0);
        diff_gint_N1HFgSUB2_narrow[cbin]->SetMarkerColor(kGreen+2);
        diff_gint_N1HFgSUB2_narrow[cbin]->SetLineColor(kGreen+2);
        diff_gint_N1HFgSUB2_narrow[cbin]->RemovePoint(0);
        diff_gint_N1HFgSUB2_narrow[cbin]->RemovePoint(diff_gint_N1HFgSUB2_narrow[cbin]->GetN()-1);

        diff_gint_N1HFgSUB2_wide[cbin]->SetMarkerStyle(20);
        diff_gint_N1HFgSUB2_wide[cbin]->SetMarkerSize(1.0);
        diff_gint_N1HFgSUB2_wide[cbin]->SetMarkerColor(kBlue);
        diff_gint_N1HFgSUB2_wide[cbin]->SetLineColor(kBlue);
        diff_gint_N1HFgSUB2_wide[cbin]->RemovePoint(0);
        diff_gint_N1HFgSUB2_wide[cbin]->RemovePoint(diff_gint_N1HFgSUB2_wide[cbin]->GetN()-1);


        string mtag = Form("N1HFgSUB2_%d_%d",cmin[cbin],cmax[cbin]);


        cN1HFgSUB2_gint_vtxRange[cbin] = new TCanvas(Form("c%s_vtxRange",mtag.data()), Form("c%s_vtxRange",mtag.data()), 600, 900);
        cN1HFgSUB2_gint_vtxRange[cbin]->Divide(1,3,0,0);
        TPad * pad1a = (TPad *) cN1HFgSUB2_gint_vtxRange[cbin]->cd(1);
        pad1a->SetRightMargin(0.03);
        TH1D * h1a = new TH1D(Form("h1%s",mtag.data()), "", 100, -2.6, 2.6);
        h1a->GetYaxis()->SetRangeUser(-0.019, 0.019);
        if (cbin == 9) h1a->GetYaxis()->SetRangeUser(-0.029, 0.029);
        if (cbin == 10) h1a->GetYaxis()->SetRangeUser(-0.039, 0.039);
        h1a->SetYTitle("v_{1}");
        h1a->GetYaxis()->SetLabelSize(0.07);
        h1a->GetYaxis()->SetTitleSize(0.09);
        h1a->GetYaxis()->SetTitleOffset(0.9);
        h1a->GetYaxis()->CenterTitle();
        h1a->GetYaxis()->SetDecimals();
        h1a->Draw();
        gint_N1HFgSUB2_wide[cbin]->Draw("same p");
        gint_N1HFgSUB2_narrow[cbin]->Draw("same p");
        gint_N1HFgSUB2[cbin]->Draw("same p");
        TPaveText * texta = new TPaveText(0.52, 0.83, 0.73, 0.94, "NDC");
        SetTPaveTxt(texta, 24);
        texta->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        texta->Draw();
        TLegend * lega = new TLegend(0.73, 0.65, 0.91, 0.93);
        SetLegend(lega, 24);
        lega->AddEntry(gint_N1HFgSUB2_wide[cbin],"wide","p");
        lega->AddEntry(gint_N1HFgSUB2_narrow[cbin],"narrow","p");
        lega->AddEntry(gint_N1HFgSUB2[cbin],"nominal","p");
        lega->Draw();

        TPad * pad2a = (TPad *) cN1HFgSUB2_gint_vtxRange[cbin]->cd(2);
        pad2a->SetRightMargin(0.03);
        TH1D * h2a = (TH1D *) h1a->Clone(Form("h2%s",mtag.data()));
        h2a->GetYaxis()->SetRangeUser(0.75, 1.25);
        h2a->SetYTitle("v_{1}/v_{1}{nominal}");
        h2a->GetYaxis()->SetDecimals();
        h2a->GetYaxis()->SetNdivisions(509);
        gPad->SetGrid(1,1);
        h2a->Draw();
        TLine * lnrata = new TLine(-2.3, 1.0, 2.3, 1.0);
        lnrata->Draw();
        ratio_gint_N1HFgSUB2_wide[cbin]->Draw("same p");
        ratio_gint_N1HFgSUB2_narrow[cbin]->Draw("same p");
        TF1 * fit_rat_wide = new TF1("fir_rat_wide", "pol0", -2, 2);
        TGraphErrors * tmp_rat_wide = (TGraphErrors *) ratio_gint_N1HFgSUB2_wide[cbin]->Clone();
        cout<<"\ncrange: "<<cmin[cbin]<<"\t"<<cmax[cbin]<<endl;
        cout<<"wide ratio: "<<endl;
        tmp_rat_wide->Fit(fit_rat_wide);
        TF1 * fit_rat_narrow = new TF1("fir_rat_narrow", "pol0", -2, 2);
        TGraphErrors * tmp_rat_narrow = (TGraphErrors *) ratio_gint_N1HFgSUB2_narrow[cbin]->Clone();
        cout<<"narrow ratio: "<<endl;
        tmp_rat_narrow->Fit(fit_rat_narrow);
        fitWide_rat_p0[cbin] = fit_rat_wide->GetParameter(0);
        fitNarrow_rat_p0[cbin] = fit_rat_narrow->GetParameter(0);

        TPad * pad3a = (TPad *) cN1HFgSUB2_gint_vtxRange[cbin]->cd(3);
        pad3a->SetRightMargin(0.03);
        TH1D * h3a = (TH1D *) h1a->Clone(Form("h3%s",mtag.data()));
        h3a->GetYaxis()->SetRangeUser(-1.05, 1.05);
        if (cbin==8) h3a->GetYaxis()->SetRangeUser(-1.15, 1.15);
        if (cbin==9) h3a->GetYaxis()->SetRangeUser(-1.55, 1.55);
        if (cbin==10) h3a->GetYaxis()->SetRangeUser(-3.95,3.95);
        h3a->SetXTitle("#eta");
        h3a->GetXaxis()->SetLabelSize(0.06);
        h3a->GetXaxis()->SetTitleSize(0.08);
        h3a->GetXaxis()->SetTitleOffset(0.95);
        h3a->SetYTitle("v_{1} - v_{1}{nominal} (#times 1000)");
        h3a->GetYaxis()->SetLabelSize(0.06);
        h3a->GetYaxis()->SetTitleSize(0.08);
        h3a->GetYaxis()->SetTitleOffset(1.00);
        h3a->GetYaxis()->SetDecimals();
        h3a->GetYaxis()->SetNdivisions(508);
        gPad->SetGrid(1,1);
        h3a->Draw();
        TLine * lndiffa = new TLine(-2.3, 0.0, 2.3, 0.0);
        lndiffa->Draw();
        diff_gint_N1HFgSUB2_wide[cbin]->Draw("same p");
        diff_gint_N1HFgSUB2_narrow[cbin]->Draw("same p");
        TF1 * fit_diff_wide = new TF1("fir_diff_wide", "pol1", -2, 2);
        TGraphErrors * tmp_diff_wide = (TGraphErrors *) diff_gint_N1HFgSUB2_wide[cbin]->Clone();
        cout<<"\ncrange: "<<cmin[cbin]<<"\t"<<cmax[cbin]<<endl;
        cout<<"wide difference: "<<endl;
        tmp_diff_wide->Fit(fit_diff_wide);
        TF1 * fit_diff_narrow = new TF1("fir_diff_narrow", "pol1", -2, 2);
        TGraphErrors * tmp_diff_narrow = (TGraphErrors *) diff_gint_N1HFgSUB2_narrow[cbin]->Clone();
        cout<<"narrow difference: "<<endl;
        tmp_diff_narrow->Fit(fit_diff_narrow);
        fitWide_diff_p0[cbin] = 0.001 * fit_diff_wide->GetParameter(0);
        fitWide_diff_p0_err[cbin] = 0.001 * fit_diff_wide->GetParError(0);
        fitWide_diff_p1[cbin] = 0.001 * fit_diff_wide->GetParameter(1);
        fitWide_diff_p1_err[cbin] = 0.001 * fit_diff_wide->GetParError(1);
        fitNarrow_diff_p0[cbin] = 0.001 * fit_diff_narrow->GetParameter(0);
        fitNarrow_diff_p0_err[cbin] = 0.001 * fit_diff_narrow->GetParError(0);
        fitNarrow_diff_p1[cbin] = 0.001 * fit_diff_narrow->GetParameter(1);
        fitNarrow_diff_p1_err[cbin] = 0.001 * fit_diff_narrow->GetParError(1);

        cN1HFgSUB2_gint_vtxRange[cbin]->Print(Form("plots/N1HFgSUB2/cN1HFgSUB2_gint_vtxRange_%d_%d.pdf",cmin[cbin],cmax[cbin]),"pdf");
        cN1HFgSUB2_gint_vtxRange[cbin]->Close();
    }

    cout<<"cmin\tcmax\twide diff p0\t\twide diff p1\t\tnarrow diff p0\t\tnarrow diff p1"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fitWide_diff_p0[cbin]<<" +/- "<<fitWide_diff_p0_err[cbin]<<"\t"
        <<fitWide_diff_p1[cbin]<<" +/- "<<fitWide_diff_p1_err[cbin]<<"\t"
        <<fitNarrow_diff_p0[cbin]<<" +/- "<<fitNarrow_diff_p0_err[cbin]<<"\t"
        <<fitNarrow_diff_p1[cbin]<<" +/- "<<fitNarrow_diff_p1_err[cbin]<<"\t"<<endl;
    }



    TCanvas * c0 = new TCanvas("c0", "c0", 1200, 600);
    c0->Divide(4,2,0,0);
    c0->cd(1);
    TH1D * h0_1 = new TH1D("h0_1", "", 100, -2.6, 2.6);
    h0_1->GetYaxis()->SetRangeUser(-0.022, 0.022);
    h0_1->SetYTitle("v_{1}^{odd}");
    h0_1->GetYaxis()->SetLabelSize(0.07);
    h0_1->GetYaxis()->SetTitleSize(0.09);
    h0_1->GetYaxis()->SetTitleOffset(1.05);
    h0_1->GetYaxis()->CenterTitle();
    h0_1->GetYaxis()->SetDecimals();
    h0_1->GetYaxis()->SetNdivisions(507);
    h0_1->Draw();
    gint_N1HFgSUB2_narrow[0]->Draw("same p");
    gint_N1HFgSUB2_wide[0]->Draw("same p");
    gint_N1HFgSUB2[0]->Draw("same p");
    TPaveText * txt0_1 = new TPaveText(0.50, 0.84, 0.70, 0.93, "NDC");
    SetTPaveTxt(txt0_1, 24);
    txt0_1->AddText("0 - 5%");
    txt0_1->Draw();
    TLegend * leg0 = new TLegend(0.26, 0.06, 0.46, 0.40);
    SetLegend(leg0, 24);
    leg0->AddEntry(gint_N1HFgSUB2_narrow[0],"narrow","p");
    leg0->AddEntry(gint_N1HFgSUB2_wide[0],"wide","p");
    leg0->AddEntry(gint_N1HFgSUB2[0],"nominal","p");
    leg0->Draw();
    c0->cd(2);
    TH1D * h0_2 = (TH1D *) h0_1->Clone("h0_2");
    h0_2->Draw();
    gint_N1HFgSUB2_narrow[1]->Draw("same p");
    gint_N1HFgSUB2_wide[1]->Draw("same p");
    gint_N1HFgSUB2[1]->Draw("same p");
    TPaveText * txt0_2 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt0_2, 24);
    txt0_2->AddText("5 - 10%");
    txt0_2->Draw();
    c0->cd(3);
    TH1D * h0_3 = (TH1D *) h0_1->Clone("h0_3");
    h0_3->Draw();
    gint_N1HFgSUB2_narrow[2]->Draw("same p");
    gint_N1HFgSUB2_wide[2]->Draw("same p");
    gint_N1HFgSUB2[2]->Draw("same p");
    TPaveText * txt0_3 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt0_3, 24);
    txt0_3->AddText("10 - 15%");
    txt0_3->Draw();
    TPad * pad0_4 = (TPad *) c0->cd(4);
    pad0_4->SetRightMargin(0.02);
    TH1D * h0_4 = (TH1D *) h0_1->Clone("h0_4");
    h0_4->Draw();
    gint_N1HFgSUB2_narrow[3]->Draw("same p");
    gint_N1HFgSUB2_wide[3]->Draw("same p");
    gint_N1HFgSUB2[3]->Draw("same p");
    TPaveText * txt0_4 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt0_4, 24);
    txt0_4->AddText("15 - 20%");
    txt0_4->Draw();

    c0->cd(5);
    gPad->SetGrid(1,1);
    TH1D * h0_5 = (TH1D *) h0_1->Clone("h0_5");
    h0_5->SetYTitle("v_{1} - v_{1}{nominal} (#times 1000)");
    h0_5->GetYaxis()->SetRangeUser(-2.2, 2.2);
    h0_5->SetXTitle("#eta");
    h0_5->GetXaxis()->CenterTitle();
    h0_5->GetXaxis()->SetLabelSize(0.06);
    h0_5->GetXaxis()->SetTitleSize(0.08);
    h0_5->GetXaxis()->SetTitleOffset(0.90);
    h0_5->GetYaxis()->SetLabelSize(0.06);
    h0_5->GetYaxis()->SetTitleSize(0.07);
    h0_5->GetYaxis()->SetTitleOffset(1.20);
    h0_5->GetYaxis()->SetNdivisions(507);
    h0_5->Draw();
    diff_gint_N1HFgSUB2_narrow[0]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[0]->Draw("same p");
    c0->cd(6);
    gPad->SetGrid(1,1);
    TH1D * h0_6 = (TH1D *) h0_5->Clone("h0_6");
    h0_6->Draw();
    diff_gint_N1HFgSUB2_narrow[1]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[1]->Draw("same p");
    c0->cd(7);
    gPad->SetGrid(1,1);
    TH1D * h0_7 = (TH1D *) h0_5->Clone("h0_7");
    h0_7->Draw();
    diff_gint_N1HFgSUB2_narrow[2]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[2]->Draw("same p");
    TPad * pad0_8 = (TPad *) c0->cd(8);
    pad0_8->SetRightMargin(0.02);
    gPad->SetGrid(1,1);
    TH1D * h0_8 = (TH1D *) h0_5->Clone("h0_8");
    h0_8->Draw();
    diff_gint_N1HFgSUB2_wide[3]->Draw("same p");
    diff_gint_N1HFgSUB2_narrow[3]->Draw("same p");

    c0->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_0_20.pdf","pdf");
    c0->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_0_20.png","png");


    //-- --//


    TCanvas * c1 = new TCanvas("c1", "c1", 1200, 600);
    c1->Divide(4,2,0,0);
    c1->cd(1);
    TH1D * h1_1 = new TH1D("h1_1", "", 100, -2.6, 2.6);
    h1_1->GetYaxis()->SetRangeUser(-0.022, 0.022);
    h1_1->SetYTitle("v_{1}^{odd}");
    h1_1->GetYaxis()->SetLabelSize(0.07);
    h1_1->GetYaxis()->SetTitleSize(0.09);
    h1_1->GetYaxis()->SetTitleOffset(1.05);
    h1_1->GetYaxis()->CenterTitle();
    h1_1->GetYaxis()->SetDecimals();
    h1_1->GetYaxis()->SetNdivisions(507);
    h1_1->Draw();
    gint_N1HFgSUB2_narrow[4]->Draw("same p");
    gint_N1HFgSUB2_wide[4]->Draw("same p");
    gint_N1HFgSUB2[4]->Draw("same p");
    TPaveText * txt1_1 = new TPaveText(0.50, 0.84, 0.70, 0.93, "NDC");
    SetTPaveTxt(txt1_1, 24);
    txt1_1->AddText("20 - 25%");
    txt1_1->Draw();
    TLegend * leg1 = new TLegend(0.26, 0.06, 0.46, 0.40);
    SetLegend(leg1, 24);
    leg1->AddEntry(gint_N1HFgSUB2_wide[4],"wide","p");
    leg1->AddEntry(gint_N1HFgSUB2_narrow[4],"narrow","p");
    leg1->AddEntry(gint_N1HFgSUB2[4],"nominal","p");
    leg1->Draw();
    c1->cd(2);
    TH1D * h1_2 = (TH1D *) h1_1->Clone("h1_2");
    h1_2->Draw();
    gint_N1HFgSUB2_narrow[5]->Draw("same p");
    gint_N1HFgSUB2_wide[5]->Draw("same p");
    gint_N1HFgSUB2[5]->Draw("same p");
    TPaveText * txt1_2 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt1_2, 24);
    txt1_2->AddText("25 - 30%");
    txt1_2->Draw();
    c1->cd(3);
    TH1D * h1_3 = (TH1D *) h1_1->Clone("h1_3");
    h1_3->Draw();
    gint_N1HFgSUB2_narrow[6]->Draw("same p");
    gint_N1HFgSUB2_wide[6]->Draw("same p");
    gint_N1HFgSUB2[6]->Draw("same p");
    TPaveText * txt1_3 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt1_3, 24);
    txt1_3->AddText("30 - 35%");
    txt1_3->Draw();
    TPad * pad1_4 = (TPad *) c1->cd(4);
    pad1_4->SetRightMargin(0.02);
    TH1D * h1_4 = (TH1D *) h1_1->Clone("h1_4");
    h1_4->Draw();
    gint_N1HFgSUB2_narrow[7]->Draw("same p");
    gint_N1HFgSUB2_wide[7]->Draw("same p");
    gint_N1HFgSUB2[7]->Draw("same p");
    TPaveText * txt1_4 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt1_4, 24);
    txt1_4->AddText("35 - 40%");
    txt1_4->Draw();

    c1->cd(5);
    gPad->SetGrid(1,1);
    TH1D * h1_5 = (TH1D *) h1_1->Clone("h1_5");
    h1_5->SetYTitle("v_{1} - v_{1}{nominal} (#times 1000)");
    h1_5->GetYaxis()->SetRangeUser(-3.5, 3.5);
    h1_5->SetXTitle("#eta");
    h1_5->GetXaxis()->CenterTitle();
    h1_5->GetXaxis()->SetLabelSize(0.06);
    h1_5->GetXaxis()->SetTitleSize(0.08);
    h1_5->GetXaxis()->SetTitleOffset(0.90);
    h1_5->GetYaxis()->SetLabelSize(0.06);
    h1_5->GetYaxis()->SetTitleSize(0.07);
    h1_5->GetYaxis()->SetTitleOffset(1.20);
    h1_5->GetYaxis()->SetNdivisions(507);
    h1_5->Draw();
    diff_gint_N1HFgSUB2_narrow[4]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[4]->Draw("same p");
    c1->cd(6);
    gPad->SetGrid(1,1);
    TH1D * h1_6 = (TH1D *) h1_5->Clone("h1_6");
    h1_6->Draw();
    diff_gint_N1HFgSUB2_narrow[5]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[5]->Draw("same p");
    c1->cd(7);
    gPad->SetGrid(1,1);
    TH1D * h1_7 = (TH1D *) h1_5->Clone("h1_7");
    h1_7->Draw();
    diff_gint_N1HFgSUB2_narrow[6]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[6]->Draw("same p");
    TPad * pad1_8 = (TPad *) c1->cd(8);
    pad1_8->SetRightMargin(0.02);
    gPad->SetGrid(1,1);
    TH1D * h1_8 = (TH1D *) h1_5->Clone("h1_8");
    h1_8->Draw();
    diff_gint_N1HFgSUB2_narrow[7]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[7]->Draw("same p");

    c1->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_20_40.pdf","pdf");
    c1->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_20_40.png","png");


    //-- --//


    TCanvas * c2 = new TCanvas("c2", "c2", 900, 600);
    c2->Divide(3,2,0,0);
    c2->cd(1);
    TH1D * h2_1 = new TH1D("h2_1", "", 100, -2.6, 2.6);
    h2_1->GetYaxis()->SetRangeUser(-0.042, 0.042);
    h2_1->SetYTitle("v_{1}^{odd}");
    h2_1->GetYaxis()->SetLabelSize(0.07);
    h2_1->GetYaxis()->SetTitleSize(0.09);
    h2_1->GetYaxis()->SetTitleOffset(1.05);
    h2_1->GetYaxis()->CenterTitle();
    h2_1->GetYaxis()->SetDecimals();
    h2_1->GetYaxis()->SetNdivisions(507);
    h2_1->Draw();
    gint_N1HFgSUB2_narrow[8]->Draw("same p");
    gint_N1HFgSUB2_wide[8]->Draw("same p");
    gint_N1HFgSUB2[8]->Draw("same p");
    TPaveText * txt2_1 = new TPaveText(0.50, 0.84, 0.70, 0.93, "NDC");
    SetTPaveTxt(txt2_1, 24);
    txt2_1->AddText("40 - 50%");
    txt2_1->Draw();
    TLegend * leg2_1 = new TLegend(0.26, 0.06, 0.46, 0.40);
    SetLegend(leg2_1, 24);
    leg2_1->AddEntry(gint_N1HFgSUB2_wide[8],"wide","p");
    leg2_1->AddEntry(gint_N1HFgSUB2_narrow[8],"narrow","p");
    leg2_1->AddEntry(gint_N1HFgSUB2[8],"nominal","p");
    leg2_1->Draw();
    c2->cd(2);
    TH1D * h2_2 = (TH1D *) h2_1->Clone("h2_2");
    h2_2->Draw();
    gint_N1HFgSUB2_narrow[9]->Draw("same p");
    gint_N1HFgSUB2_wide[9]->Draw("same p");
    gint_N1HFgSUB2[9]->Draw("same p");
    TPaveText * txt2_2 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt2_2, 24);
    txt2_2->AddText("50 - 60%");
    txt2_2->Draw();
    TPad * pad2_3 = (TPad *) c2->cd(3);
    pad2_3->SetRightMargin(0.02);
    TH1D * h2_3 = (TH1D *) h2_1->Clone("h2_3");
    h2_3->Draw();
    gint_N1HFgSUB2_narrow[10]->Draw("same p");
    gint_N1HFgSUB2_wide[10]->Draw("same p");
    gint_N1HFgSUB2[10]->Draw("same p");
    TPaveText * txt2_3 = new TPaveText(0.40, 0.84, 0.60, 0.93, "NDC");
    SetTPaveTxt(txt2_3, 24);
    txt2_3->AddText("60 - 70%");
    txt2_3->Draw();

    c2->cd(4);
    gPad->SetGrid(1,1);
    TH1D * h2_5 = (TH1D *) h2_1->Clone("h2_5");
    h2_5->SetYTitle("v_{1} - v_{1}{nominal} (#times 1000)");
    h2_5->GetYaxis()->SetRangeUser(-5.8, 5.8);
    h2_5->SetXTitle("#eta");
    h2_5->GetXaxis()->CenterTitle();
    h2_5->GetXaxis()->SetLabelSize(0.06);
    h2_5->GetXaxis()->SetTitleSize(0.08);
    h2_5->GetXaxis()->SetTitleOffset(0.90);
    h2_5->GetYaxis()->SetLabelSize(0.06);
    h2_5->GetYaxis()->SetTitleSize(0.07);
    h2_5->GetYaxis()->SetTitleOffset(1.20);
    h2_5->GetYaxis()->SetNdivisions(507);
    h2_5->Draw();
    diff_gint_N1HFgSUB2_narrow[8]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[8]->Draw("same p");
    c2->cd(5);
    gPad->SetGrid(1,1);
    TH1D * h2_6 = (TH1D *) h2_5->Clone("h2_6");
    h2_6->Draw();
    diff_gint_N1HFgSUB2_narrow[9]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[9]->Draw("same p");
    c2->cd(6);
    gPad->SetGrid(1,1);
    TH1D * h2_7 = (TH1D *) h2_5->Clone("h2_7");
    h2_7->Draw();
    diff_gint_N1HFgSUB2_narrow[10]->Draw("same p");
    diff_gint_N1HFgSUB2_wide[10]->Draw("same p");
    TPad * pad2_8 = (TPad *) c2->cd(7);
    pad2_8->SetRightMargin(0.02);
    gPad->SetGrid(1,1);

    c2->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_40_70.pdf","pdf");
    c2->Print("plots/N1HFgSUB2/N1HFgSUB2_vtxRange_40_70.png","png");




}
