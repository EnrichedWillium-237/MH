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
TGraphErrors * gint_N1HFgSUB2_tight[ncbins];
TGraphErrors * gint_N1HFgSUB2_loose[ncbins];

TGraphErrors * ratio_gint_N1HFgSUB2_narrow[ncbins];
TGraphErrors * ratio_gint_N1HFgSUB2_wide[ncbins];
TGraphErrors * ratio_gint_N1HFgSUB2_tight[ncbins];
TGraphErrors * ratio_gint_N1HFgSUB2_loose[ncbins];

TGraphErrors * diff_gint_N1HFgSUB2_narrow[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_wide[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_tight[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_loose[ncbins];

TGraphErrors * g_N1HFgSUB2[ncbins];
TGraphErrors * g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * g_N1HFgSUB2_wide[ncbins];
TGraphErrors * g_N1HFgSUB2_tight[ncbins];
TGraphErrors * g_N1HFgSUB2_loose[ncbins];

TGraphErrors * ratio_g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * ratio_g_N1HFgSUB2_wide[ncbins];
TGraphErrors * ratio_g_N1HFgSUB2_tight[ncbins];
TGraphErrors * ratio_g_N1HFgSUB2_loose[ncbins];

TGraphErrors * diff_g_N1HFgSUB2_narrow[ncbins];
TGraphErrors * diff_g_N1HFgSUB2_wide[ncbins];
TGraphErrors * diff_g_N1HFgSUB2_tight[ncbins];
TGraphErrors * diff_g_N1HFgSUB2_loose[ncbins];

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

void plotSyst_N1HFgSUB2() {

    Double_t fitLoose_rat_p0[ncbins];
    Double_t fitTight_rat_p0[ncbins];
    Double_t fitLoose_diff_p0[ncbins];
    Double_t fitLoose_diff_p1[ncbins];
    Double_t fitTight_diff_p0[ncbins];
    Double_t fitTight_diff_p1[ncbins];

    Double_t fitWide_rat_p0[ncbins];
    Double_t fitNarrow_rat_p0[ncbins];
    Double_t fitWide_diff_p0[ncbins];
    Double_t fitWide_diff_p1[ncbins];
    Double_t fitNarrow_diff_p0[ncbins];
    Double_t fitNarrow_diff_p1[ncbins];

    for (int cbin = 0; cbin<ncbins; cbin++) {
        string tag = Form("default/N1HFgSUB2/-2.0_2.0/%d_%d",cmin[cbin],cmax[cbin]);

        // cN1HFgSUB2_gint_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/syserr_N1HFgSUB2_gint_-2.0_2.0_%d_%d_trackQuality",tag.data(),cmin[cbin],cmax[cbin]));

        gint_N1HFgSUB2[cbin] = (TGraphErrors *) fin->Get(Form("%s/gint",tag.data()));
        gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("narrow/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("wide/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        gint_N1HFgSUB2_tight[cbin] = (TGraphErrors *) fin->Get(Form("tight2/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));
        gint_N1HFgSUB2_loose[cbin] = (TGraphErrors *) fin->Get(Form("loose/N1HFgSUB2/-2.0_2.0/%d_%d/gint",cmin[cbin],cmax[cbin]));

        ratio_gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_narrow_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_wide_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_tight[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_tight2_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_loose[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_loose_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));

        diff_gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_narrow_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        diff_gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_wide_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        diff_gint_N1HFgSUB2_tight[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_tight2_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        diff_gint_N1HFgSUB2_loose[cbin] = (TGraphErrors *) fin->Get(Form("%s/Difference_loose_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));

        // g_N1HFgSUB2[cbin] = (TGraphErrors *) fin->Get(Form("%s/g",tag.data()));)
        // g_N1HFgSUB2_narrow[ncbins];
        // g_N1HFgSUB2_wide[ncbins];
        // g_N1HFgSUB2_tight[ncbins];
        // g_N1HFgSUB2_loose[ncbins];
        //
        // ratio_g_N1HFgSUB2_narrow[ncbins];
        // ratio_g_N1HFgSUB2_wide[ncbins];
        // ratio_g_N1HFgSUB2_tight[ncbins];
        // ratio_g_N1HFgSUB2_loose[ncbins];
        //
        // diff_g_N1HFgSUB2_narrow[ncbins];
        // diff_g_N1HFgSUB2_wide[ncbins];
        // diff_g_N1HFgSUB2_tight[ncbins];
        // diff_g_N1HFgSUB2_loose[ncbins];

        gint_N1HFgSUB2[cbin]->SetMarkerStyle(25);
        gint_N1HFgSUB2[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2[cbin]->SetMarkerColor(kRed);
        gint_N1HFgSUB2[cbin]->SetLineColor(kRed);
        gint_N1HFgSUB2[cbin]->RemovePoint(0);
        gint_N1HFgSUB2[cbin]->RemovePoint(gint_N1HFgSUB2[cbin]->GetN()-1);

        gint_N1HFgSUB2_loose[cbin]->SetMarkerStyle(20);
        gint_N1HFgSUB2_loose[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2_loose[cbin]->SetMarkerColor(kBlue);
        gint_N1HFgSUB2_loose[cbin]->SetLineColor(kBlue);
        gint_N1HFgSUB2_loose[cbin]->RemovePoint(0);
        gint_N1HFgSUB2_loose[cbin]->RemovePoint(gint_N1HFgSUB2_loose[cbin]->GetN()-1);

        gint_N1HFgSUB2_tight[cbin]->SetMarkerStyle(20);
        gint_N1HFgSUB2_tight[cbin]->SetMarkerSize(1.0);
        gint_N1HFgSUB2_tight[cbin]->SetMarkerColor(kGreen+2);
        gint_N1HFgSUB2_tight[cbin]->SetLineColor(kGreen+2);
        gint_N1HFgSUB2_tight[cbin]->RemovePoint(0);
        gint_N1HFgSUB2_tight[cbin]->RemovePoint(gint_N1HFgSUB2_tight[cbin]->GetN()-1);

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

        ratio_gint_N1HFgSUB2_tight[cbin]->SetMarkerStyle(20);
        ratio_gint_N1HFgSUB2_tight[cbin]->SetMarkerSize(1.0);
        ratio_gint_N1HFgSUB2_tight[cbin]->SetMarkerColor(kGreen+2);
        ratio_gint_N1HFgSUB2_tight[cbin]->SetLineColor(kGreen+2);
        ratio_gint_N1HFgSUB2_tight[cbin]->RemovePoint(0);
        ratio_gint_N1HFgSUB2_tight[cbin]->RemovePoint(ratio_gint_N1HFgSUB2_tight[cbin]->GetN()-1);

        ratio_gint_N1HFgSUB2_loose[cbin]->SetMarkerStyle(20);
        ratio_gint_N1HFgSUB2_loose[cbin]->SetMarkerSize(1.0);
        ratio_gint_N1HFgSUB2_loose[cbin]->SetMarkerColor(kBlue);
        ratio_gint_N1HFgSUB2_loose[cbin]->SetLineColor(kBlue);
        ratio_gint_N1HFgSUB2_loose[cbin]->RemovePoint(0);
        ratio_gint_N1HFgSUB2_loose[cbin]->RemovePoint(ratio_gint_N1HFgSUB2_loose[cbin]->GetN()-1);


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

        diff_gint_N1HFgSUB2_tight[cbin]->SetMarkerStyle(20);
        diff_gint_N1HFgSUB2_tight[cbin]->SetMarkerSize(1.0);
        diff_gint_N1HFgSUB2_tight[cbin]->SetMarkerColor(kGreen+2);
        diff_gint_N1HFgSUB2_tight[cbin]->SetLineColor(kGreen+2);
        diff_gint_N1HFgSUB2_tight[cbin]->RemovePoint(0);
        diff_gint_N1HFgSUB2_tight[cbin]->RemovePoint(diff_gint_N1HFgSUB2_tight[cbin]->GetN()-1);

        diff_gint_N1HFgSUB2_loose[cbin]->SetMarkerStyle(20);
        diff_gint_N1HFgSUB2_loose[cbin]->SetMarkerSize(1.0);
        diff_gint_N1HFgSUB2_loose[cbin]->SetMarkerColor(kBlue);
        diff_gint_N1HFgSUB2_loose[cbin]->SetLineColor(kBlue);
        diff_gint_N1HFgSUB2_loose[cbin]->RemovePoint(0);
        diff_gint_N1HFgSUB2_loose[cbin]->RemovePoint(diff_gint_N1HFgSUB2_loose[cbin]->GetN()-1);


        string mtag = Form("N1HFgSUB2_%d_%d",cmin[cbin],cmax[cbin]);

        cN1HFgSUB2_gint_trackQuality[cbin] = new TCanvas(Form("c%s_trackQuality",mtag.data()), Form("c%s_trackQuality",mtag.data()), 600, 900);
        cN1HFgSUB2_gint_trackQuality[cbin]->Divide(1,3,0,0);
        TPad * pad1 = (TPad *) cN1HFgSUB2_gint_trackQuality[cbin]->cd(1);
        pad1->SetRightMargin(0.03);
        TH1D * h1 = new TH1D(Form("h1%s",mtag.data()), "", 100, -2.3, 2.3);
        h1->GetYaxis()->SetRangeUser(-0.019, 0.019);
        if (cbin == 9) h1->GetYaxis()->SetRangeUser(-0.029, 0.029);
        if (cbin == 10) h1->GetYaxis()->SetRangeUser(-0.039, 0.039);
        h1->SetYTitle("v_{1}");
        h1->GetYaxis()->SetLabelSize(0.07);
        h1->GetYaxis()->SetTitleSize(0.09);
        h1->GetYaxis()->SetTitleOffset(0.9);
        h1->GetYaxis()->CenterTitle();
        h1->GetYaxis()->SetDecimals();
        h1->Draw();
        gint_N1HFgSUB2_loose[cbin]->Draw("same p");
        gint_N1HFgSUB2_tight[cbin]->Draw("same p");
        gint_N1HFgSUB2[cbin]->Draw("same p");
        TPaveText * text = new TPaveText(0.52, 0.83, 0.73, 0.94, "NDC");
        SetTPaveTxt(text, 24);
        text->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        text->Draw();
        TLegend * leg = new TLegend(0.73, 0.65, 0.91, 0.93);
        SetLegend(leg, 24);
        leg->AddEntry(gint_N1HFgSUB2_loose[cbin],"loose","p");
        leg->AddEntry(gint_N1HFgSUB2_tight[cbin],"tight","p");
        leg->AddEntry(gint_N1HFgSUB2[cbin],"nominal","p");
        leg->Draw();

        TPad * pad2 = (TPad *) cN1HFgSUB2_gint_trackQuality[cbin]->cd(2);
        pad2->SetRightMargin(0.03);
        TH1D * h2 = (TH1D *) h1->Clone(Form("h2%s",mtag.data()));
        h2->GetYaxis()->SetRangeUser(0.75, 1.25);
        h2->SetYTitle("v_{1}/v_{1}{nominal}");
        h2->GetYaxis()->SetDecimals();
        h2->GetYaxis()->SetNdivisions(509);
        gPad->SetGrid(1,1);
        h2->Draw();
        TLine * lnrat = new TLine(-2.3, 1.0, 2.3, 1.0);
        lnrat->Draw();
        ratio_gint_N1HFgSUB2_loose[cbin]->Draw("same p");
        ratio_gint_N1HFgSUB2_tight[cbin]->Draw("same p");
        TF1 * fit_rat_loose = new TF1("fir_rat_loose", "pol0", -2, 2);
        TGraphErrors * tmp_rat_loose = (TGraphErrors *) ratio_gint_N1HFgSUB2_loose[cbin]->Clone();
        cout<<"\ncrange: "<<cmin[cbin]<<"\t"<<cmax[cbin]<<endl;
        cout<<"loose ratio: "<<endl;
        tmp_rat_loose->Fit(fit_rat_loose);
        TF1 * fit_rat_tight = new TF1("fir_rat_tight", "pol0", -2, 2);
        TGraphErrors * tmp_rat_tight = (TGraphErrors *) ratio_gint_N1HFgSUB2_tight[cbin]->Clone();
        cout<<"tight ratio: "<<endl;
        tmp_rat_tight->Fit(fit_rat_tight);
        fitLoose_rat_p0[cbin] = fit_rat_loose->GetParameter(0);
        fitTight_rat_p0[cbin] = fit_rat_tight->GetParameter(0);

        TPad * pad3 = (TPad *) cN1HFgSUB2_gint_trackQuality[cbin]->cd(3);
        pad3->SetRightMargin(0.03);
        TH1D * h3 = (TH1D *) h1->Clone(Form("h3%s",mtag.data()));
        h3->GetYaxis()->SetRangeUser(-1.05, 1.05);
        if (cbin==8) h3->GetYaxis()->SetRangeUser(-1.15, 1.15);
        if (cbin==9) h3->GetYaxis()->SetRangeUser(-1.55, 1.55);
        if (cbin==10) h3->GetYaxis()->SetRangeUser(-3.95,3.95);
        h3->SetXTitle("#eta");
        h3->GetXaxis()->SetLabelSize(0.06);
        h3->GetXaxis()->SetTitleSize(0.08);
        h3->GetXaxis()->SetTitleOffset(0.95);
        h3->SetYTitle("v_{1} - v_{1}{nominal} (#times 1000)");
        h3->GetYaxis()->SetLabelSize(0.06);
        h3->GetYaxis()->SetTitleSize(0.08);
        h3->GetYaxis()->SetTitleOffset(1.00);
        h3->GetYaxis()->SetDecimals();
        h3->GetYaxis()->SetNdivisions(508);
        gPad->SetGrid(1,1);
        h3->Draw();
        TLine * lndiff = new TLine(-2.3, 0.0, 2.3, 0.0);
        lndiff->Draw();
        diff_gint_N1HFgSUB2_loose[cbin]->Draw("same p");
        diff_gint_N1HFgSUB2_tight[cbin]->Draw("same p");
        TF1 * fit_diff_loose = new TF1("fir_diff_loose", "pol1", -2, 2);
        TGraphErrors * tmp_diff_loose = (TGraphErrors *) diff_gint_N1HFgSUB2_loose[cbin]->Clone();
        cout<<"\ncrange: "<<cmin[cbin]<<"\t"<<cmax[cbin]<<endl;
        cout<<"loose difference: "<<endl;
        tmp_diff_loose->Fit(fit_diff_loose);
        TF1 * fit_diff_tight = new TF1("fir_diff_tight", "pol1", -2, 2);
        TGraphErrors * tmp_diff_tight = (TGraphErrors *) diff_gint_N1HFgSUB2_tight[cbin]->Clone();
        cout<<"tight difference: "<<endl;
        tmp_diff_tight->Fit(fit_diff_tight);
        fitLoose_diff_p0[cbin] = 0.001 * fit_diff_loose->GetParameter(0);
        fitLoose_diff_p1[cbin] = 0.001 * fit_diff_loose->GetParameter(1);
        fitTight_diff_p0[cbin] = 0.001 * fit_diff_tight->GetParameter(0);
        fitTight_diff_p1[cbin] = 0.001 * fit_diff_tight->GetParameter(1);

        cN1HFgSUB2_gint_trackQuality[cbin]->Print(Form("plots/N1HFgSUB2/cN1HFgSUB2_gint_trackQuality_%d_%d.pdf",cmin[cbin],cmax[cbin]),"pdf");


        cN1HFgSUB2_gint_vtxRange[cbin] = new TCanvas(Form("c%s_vtxRange",mtag.data()), Form("c%s_vtxRange",mtag.data()), 600, 900);
        cN1HFgSUB2_gint_vtxRange[cbin]->Divide(1,3,0,0);
        TPad * pad1a = (TPad *) cN1HFgSUB2_gint_vtxRange[cbin]->cd(1);
        pad1a->SetRightMargin(0.03);
        TH1D * h1a = new TH1D(Form("h1%s",mtag.data()), "", 100, -2.3, 2.3);
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
        TH1D * h2a = (TH1D *) h1->Clone(Form("h2%s",mtag.data()));
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
        TH1D * h3a = (TH1D *) h1->Clone(Form("h3%s",mtag.data()));
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
        fitWide_diff_p1[cbin] = 0.001 * fit_diff_wide->GetParameter(1);
        fitNarrow_diff_p0[cbin] = 0.001 * fit_diff_narrow->GetParameter(0);
        fitNarrow_diff_p1[cbin] = 0.001 * fit_diff_narrow->GetParameter(1);

        cN1HFgSUB2_gint_vtxRange[cbin]->Print(Form("plots/N1HFgSUB2/cN1HFgSUB2_gint_vtxRange_%d_%d.pdf",cmin[cbin],cmax[cbin]),"pdf");
    }

    cout<<"cmin\tcmax\twide rat p0\tnarrow ratp0\twide diff p0\twide diff p1\tnarrow diff p0\tnarrow diff p1"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"\t"<<cmax[cbin]<<"\t"<<fitWide_rat_p0[cbin]<<"\t"<<fitNarrow_rat_p0[cbin]<<"\t"<<fitWide_diff_p0[cbin]<<"\t"<<fitWide_diff_p1[cbin]<<"\t"<<fitNarrow_diff_p0[cbin]<<"\t"<<fitNarrow_diff_p1[cbin]<<endl;
    }



    //-- --//


}
