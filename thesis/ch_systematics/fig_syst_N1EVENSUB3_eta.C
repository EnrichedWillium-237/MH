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

static const int ncbins = 11;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const double ebinmid[] = {-2.2, -1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2};

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
TH1D * h0;
TH1D * h1;
TH1D * h2;
TH1D * h3;
TGraphErrors * N1EVENSUB3[ncbins];
TGraphErrors * N1EVENSUB3_tight[ncbins];
TGraphErrors * N1EVENSUB3_loose[ncbins];
TGraphErrors * N1EVENSUB3_Diff_tight[ncbins];
TGraphErrors * N1EVENSUB3_Diff_loose[ncbins];

TGraphErrors * N1EVENSUB3_narrow[ncbins];
TGraphErrors * N1EVENSUB3_wide[ncbins];
TGraphErrors * N1EVENSUB3_Diff_narrow[ncbins];
TGraphErrors * N1EVENSUB3_Diff_wide[ncbins];

void fig_syst_N1EVENSUB3_eta() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1EVENSUB3[cbin] = (TGraphErrors *) fin->Get(Form("default/N1EVENSUB3/0.4_2.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3[cbin]->SetMarkerStyle(21);
        N1EVENSUB3[cbin]->SetMarkerSize(1.2);
        N1EVENSUB3[cbin]->SetMarkerColor(kBlue);
        N1EVENSUB3[cbin]->SetLineColor(kBlue);
        N1EVENSUB3[cbin]->RemovePoint(5);
        N1EVENSUB3[cbin]->RemovePoint(5);

        N1EVENSUB3_tight[cbin] = (TGraphErrors *) fin->Get(Form("tight2/N1EVENSUB3/0.4_2.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3_tight[cbin]->SetMarkerStyle(20);
        N1EVENSUB3_tight[cbin]->SetMarkerSize(1.3);
        N1EVENSUB3_tight[cbin]->SetMarkerColor(kGreen+2);
        N1EVENSUB3_tight[cbin]->SetLineColor(kGreen+2);
        N1EVENSUB3_tight[cbin]->RemovePoint(5);
        N1EVENSUB3_tight[cbin]->RemovePoint(5);

        N1EVENSUB3_loose[cbin] = (TGraphErrors *) fin->Get(Form("loose/N1EVENSUB3/0.4_2.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3_loose[cbin]->SetMarkerStyle(25);
        N1EVENSUB3_loose[cbin]->SetMarkerSize(1.2);
        N1EVENSUB3_loose[cbin]->SetMarkerColor(kRed);
        N1EVENSUB3_loose[cbin]->SetLineColor(kRed);
        N1EVENSUB3_loose[cbin]->RemovePoint(5);
        N1EVENSUB3_loose[cbin]->RemovePoint(5);

        N1EVENSUB3_narrow[cbin] = (TGraphErrors *) fin->Get(Form("narrow/N1EVENSUB3/0.4_2.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3_narrow[cbin]->SetMarkerStyle(20);
        N1EVENSUB3_narrow[cbin]->SetMarkerSize(1.3);
        N1EVENSUB3_narrow[cbin]->SetMarkerColor(kGreen+2);
        N1EVENSUB3_narrow[cbin]->SetLineColor(kGreen+2);
        N1EVENSUB3_narrow[cbin]->RemovePoint(05);
        N1EVENSUB3_narrow[cbin]->RemovePoint(05);

        N1EVENSUB3_wide[cbin] = (TGraphErrors *) fin->Get(Form("wide/N1EVENSUB3/0.4_2.4/%d_%d/gint",cmin[cbin],cmax[cbin]));
        N1EVENSUB3_wide[cbin]->SetMarkerStyle(25);
        N1EVENSUB3_wide[cbin]->SetMarkerSize(1.2);
        N1EVENSUB3_wide[cbin]->SetMarkerColor(kRed);
        N1EVENSUB3_wide[cbin]->SetLineColor(kRed);
        N1EVENSUB3_wide[cbin]->RemovePoint(5);
        N1EVENSUB3_wide[cbin]->RemovePoint(5);

        // compute differences
        int num = N1EVENSUB3[cbin]->GetN();
        double xval[50], y0[50], y1[50], y2[50], y0e[50], y1e[50], y2e[50];
        double y3[50], y4[50], y3e[50], y4e[50];
        for (int i = 0; i<num; i++) {
            N1EVENSUB3[cbin]->GetPoint(i, xval[i], y0[i]);
            N1EVENSUB3_tight[cbin]->GetPoint(i, xval[i], y1[i]);
            N1EVENSUB3_loose[cbin]->GetPoint(i, xval[i], y2[i]);
            N1EVENSUB3_narrow[cbin]->GetPoint(i, xval[i], y3[i]);
            N1EVENSUB3_wide[cbin]->GetPoint(i, xval[i], y4[i]);

            y0e[i] = N1EVENSUB3[cbin]->GetErrorY(i);
            y1e[i] = N1EVENSUB3_tight[cbin]->GetErrorY(i);
            y2e[i] = N1EVENSUB3_loose[cbin]->GetErrorY(i);
            y3e[i] = N1EVENSUB3_narrow[cbin]->GetErrorY(i);
            y4e[i] = N1EVENSUB3_wide[cbin]->GetErrorY(i);

            y1[i] = fabs(y1[i] - y0[i]) * 1000.;
            y2[i] = fabs(y2[i] - y0[i]) * 1000.;
            y3[i] = fabs(y3[i] - y0[i]) * 1000.;
            y4[i] = fabs(y4[i] - y0[i]) * 1000.;
            // y1e[i] = fabs(pow(y0e[i],2) - pow(y1e[i],2));
            // y2e[i] = fabs(pow(y0e[i],2) - pow(y2e[i],2));
            // y3e[i] = fabs(pow(y0e[i],2) - pow(y3e[i],2));
            // y4e[i] = fabs(pow(y0e[i],2) - pow(y4e[i],2));

            if (pow(y1e[i]/y1[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y1[i]/y0[i]>0) {
                y1e[i] = pow(y1e[i]/y1[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y1[i]/y0[i];
            } else if (pow(y1e[i]/y1[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y1e[i],2)/y1[i]/y0[i]>0) {
                y1e[i] = pow(y1e[i]/y1[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y1e[i],2)/y1[i]/y0[i];
            } else {
                y1e[i] = pow(y1e[i]/y1[i],2) + pow(y0e[i]/y0[i],2);
            }

            if (pow(y2e[i]/y2[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y2[i]/y0[i]>0) {
                y2e[i] = pow(y2e[i]/y2[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y2[i]/y0[i];
            } else if (pow(y2e[i]/y2[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y2e[i],2)/y2[i]/y0[i]>0) {
                y2e[i] = pow(y2e[i]/y2[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y2e[i],2)/y2[i]/y0[i];
            } else {
                y2e[i] = pow(y2e[i]/y2[i],2) + pow(y0e[i]/y0[i],2);
            }

            if (pow(y3e[i]/y3[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y3[i]/y0[i]>0) {
                y3e[i] = pow(y3e[i]/y3[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y3[i]/y0[i];
            } else if (pow(y3e[i]/y3[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y3e[i],2)/y3[i]/y0[i]>0) {
                y3e[i] = pow(y3e[i]/y3[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y3e[i],2)/y3[i]/y0[i];
            } else {
                y3e[i] = pow(y3e[i]/y3[i],2) + pow(y0e[i]/y0[i],2);
            }

            if (pow(y4e[i]/y4[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y4[i]/y0[i]>0) {
                y4e[i] = pow(y4e[i]/y4[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y0e[i],2)/y4[i]/y0[i];
            } else if (pow(y4e[i]/y4[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y4e[i],2)/y4[i]/y0[i]>0) {
                y4e[i] = pow(y4e[i]/y4[i],2) + pow(y0e[i]/y0[i],2) - 2*pow(y4e[i],2)/y4[i]/y0[i];
            } else {
                y4e[i] = pow(y4e[i]/y4[i],2) + pow(y0e[i]/y0[i],2);
            }

            y1e[i] = sqrt( y1e[i] );
            y2e[i] = sqrt( y2e[i] );
            y3e[i] = sqrt( y3e[i] );
            y4e[i] = sqrt( y4e[i] );
        }
        N1EVENSUB3_Diff_tight[cbin] = new TGraphErrors(num, xval, y1, 0, y1e);
        N1EVENSUB3_Diff_tight[cbin]->SetMarkerStyle(20);
        N1EVENSUB3_Diff_tight[cbin]->SetMarkerSize(1.3);
        N1EVENSUB3_Diff_tight[cbin]->SetMarkerColor(kGreen+2);
        N1EVENSUB3_Diff_tight[cbin]->SetLineColor(kGreen+2);

        N1EVENSUB3_Diff_loose[cbin] = new TGraphErrors(num, xval, y2, 0, y2e);
        N1EVENSUB3_Diff_loose[cbin]->SetMarkerStyle(25);
        N1EVENSUB3_Diff_loose[cbin]->SetMarkerSize(1.2);
        N1EVENSUB3_Diff_loose[cbin]->SetMarkerColor(kRed);
        N1EVENSUB3_Diff_loose[cbin]->SetLineColor(kRed);

        N1EVENSUB3_Diff_narrow[cbin] = new TGraphErrors(num, xval, y3, 0, y3e);
        N1EVENSUB3_Diff_narrow[cbin]->SetMarkerStyle(20);
        N1EVENSUB3_Diff_narrow[cbin]->SetMarkerSize(1.3);
        N1EVENSUB3_Diff_narrow[cbin]->SetMarkerColor(kGreen+2);
        N1EVENSUB3_Diff_narrow[cbin]->SetLineColor(kGreen+2);

        N1EVENSUB3_Diff_wide[cbin] = new TGraphErrors(num, xval, y4, 0, y4e);
        N1EVENSUB3_Diff_wide[cbin]->SetMarkerStyle(25);
        N1EVENSUB3_Diff_wide[cbin]->SetMarkerSize(1.2);
        N1EVENSUB3_Diff_wide[cbin]->SetMarkerColor(kRed);
        N1EVENSUB3_Diff_wide[cbin]->SetLineColor(kRed);
    }

    int setbin = 4;
    double fitmin = -2.4;
    double fitmax = 2.4;


    TCanvas * c0 = new TCanvas("c0", "c0", 550, 720);
    c0->cd();
    TPad * pad0 = new TPad("pad0", "pad0", 0.0, 0.4, 1.0, 1.0);
    pad0->SetBottomMargin(0);
    pad0->Draw();

    c0->cd();
    TPad * pad1 = new TPad("pad1", "pad1", 0.0, 0.0, 1.0, 0.4);
    pad1->SetTopMargin(0);
    pad1->SetBottomMargin(0.25);
    pad1->SetGrid();
    pad1->Draw();

    h0 = new TH1D("h0", "h0", 100, -2.8, 2.8);
    h0->SetStats(0);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}^{even}");
    h0->GetYaxis()->SetDecimals();
    h0->GetXaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetXaxis()->SetTitleFont(43);
    h0->GetXaxis()->SetTitleSize(26);
    h0->GetXaxis()->SetTitleOffset(2.5);
    h0->GetXaxis()->SetLabelFont(43);
    h0->GetXaxis()->SetLabelSize(20);
    h0->GetXaxis()->SetLabelOffset(0.018);
    h0->GetYaxis()->SetTitleFont(43);
    h0->GetYaxis()->SetTitleSize(26);
    h0->GetYaxis()->SetTitleOffset(2.15);
    h0->GetYaxis()->SetLabelFont(43);
    h0->GetYaxis()->SetLabelSize(19);
    h0->GetYaxis()->SetLabelOffset(0.010);
    h0->GetYaxis()->SetRangeUser(-0.014, 0.01);

    pad0->cd();
    h0->Draw();
    N1EVENSUB3[setbin]->Draw("same p");
    N1EVENSUB3_tight[setbin]->Draw("same p");
    N1EVENSUB3_loose[setbin]->Draw("same p");
    TLegend * leg0 = new TLegend(0.73, 0.71, 0.90, 0.91);
    SetLegend(leg0, 20);
    leg0->AddEntry(N1EVENSUB3_loose[setbin]," loose","p");
    leg0->AddEntry(N1EVENSUB3_tight[setbin]," tight","p");
    leg0->AddEntry(N1EVENSUB3[setbin]," default","p");
    leg0->Draw();
    TPaveText * txt0_0 = new TPaveText(0.21, 0.77, 0.41, 0.90, "NDC");
    SetTPaveTxt(txt0_0, 22);
    txt0_0->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txt0_0->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    txt0_0->Draw();

    pad1->cd();
    h1 = (TH1D *) h0->Clone("h1");
    h1->SetYTitle("v_{1} - v_{1}{default} #times 1000");
    h1->GetYaxis()->SetTitleSize(22);
    h1->GetYaxis()->SetTitleOffset(2.45);
    h1->GetYaxis()->SetRangeUser(-2.8, 2.8);
    h1->Draw();
    N1EVENSUB3_Diff_tight[setbin]->Draw("same p");
    N1EVENSUB3_Diff_loose[setbin]->Draw("same p");
    TF1 * ftight = new TF1("ftight", "pol0", fitmin, fitmax);
    N1EVENSUB3_Diff_tight[setbin]->Fit(ftight, "0");
    TF1 * floose = new TF1("floose", "pol0", fitmin, fitmax);
    N1EVENSUB3_Diff_loose[setbin]->Fit(floose, "0");
    TPaveText * txt0_1 = new TPaveText(0.19, 0.27, 0.53, 0.54, "NDC");
    SetTPaveTxt(txt0_1, 18);
    txt0_1->AddText("pol0 fits");
    txt0_1->AddText(Form("loose: %0.3f #pm %0.3f",floose->GetParameter(0),floose->GetParError(0)));
    txt0_1->AddText(Form("tight: %0.3f #pm %0.3f",ftight->GetParameter(0),ftight->GetParError(0)));
    txt0_1->Draw();

    c0->Print("../figures/fig_syst_N1EVENSUB3_trkCuts_eta.pdf","pdf");


    //--

    TCanvas * c1 = new TCanvas("c1", "c1", 550, 720);
    c1->cd();
    TPad * pad2 = new TPad("pad2", "pad2", 0.0, 0.4, 1.0, 1.0);
    pad2->SetBottomMargin(0);
    pad2->Draw();

    c1->cd();
    TPad * pad3 = new TPad("pad3", "pad3", 0.0, 0.0, 1.0, 0.4);
    pad3->SetTopMargin(0);
    pad3->SetBottomMargin(0.25);
    pad3->SetGrid();
    pad3->Draw();

    pad2->cd();
    h2 = (TH1D *) h0->Clone("h2");
    h2->Draw();
    N1EVENSUB3[setbin]->Draw("same p");
    N1EVENSUB3_narrow[setbin]->Draw("same p");
    N1EVENSUB3_wide[setbin]->Draw("same p");
    TLegend * leg1 = new TLegend(0.73, 0.71, 0.90, 0.91);
    SetLegend(leg1, 20);
    leg1->AddEntry(N1EVENSUB3_wide[setbin]," wide","p");
    leg1->AddEntry(N1EVENSUB3_narrow[setbin]," narrow","p");
    leg1->AddEntry(N1EVENSUB3[setbin]," default","p");
    leg1->Draw();
    TPaveText * txt1_0 = new TPaveText(0.21, 0.77, 0.41, 0.90, "NDC");
    SetTPaveTxt(txt1_0, 22);
    txt1_0->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txt1_0->AddText(Form("%d - %d%%",cmin[setbin],cmax[setbin]));
    txt1_0->Draw();

    pad3->cd();
    h3 = (TH1D *) h1->Clone("h3");
    h3->Draw();
    N1EVENSUB3_Diff_narrow[setbin]->Draw("same p");
    N1EVENSUB3_Diff_wide[setbin]->Draw("same p");
    TF1 * fnarrow = new TF1("fnarrow", "pol0", fitmin, fitmax);
    N1EVENSUB3_Diff_narrow[setbin]->Fit(fnarrow, "0");
    TF1 * fwide = new TF1("fwide", "pol0", fitmin, fitmax);
    N1EVENSUB3_Diff_wide[setbin]->Fit(fwide, "0");
    TPaveText * txt1_1 = new TPaveText(0.19, 0.27, 0.53, 0.54, "NDC");
    SetTPaveTxt(txt1_1, 18);
    txt1_1->AddText("pol0 fits");
    txt1_1->AddText(Form("wide: %0.3f #pm %0.3f",fwide->GetParameter(0),fwide->GetParError(0)));
    txt1_1->AddText(Form("narrow: %0.3f #pm %0.3f",fnarrow->GetParameter(0),fnarrow->GetParError(0)));
    txt1_1->Draw();

    c1->Print("../figures/fig_syst_N1EVENSUB3_vtxCuts_eta.pdf","pdf");



    //-- print out fit parameters
    TGraphErrors * gfit_tight[ncbins];
    TGraphErrors * gfit_loose[ncbins];
    TGraphErrors * gfit_narrow[ncbins];
    TGraphErrors * gfit_wide[ncbins];
    TF1 * ffit_tight[ncbins];
    TF1 * ffit_loose[ncbins];
    TF1 * ffit_narrow[ncbins];
    TF1 * ffit_wide[ncbins];
    for (int cbin = 0; cbin<ncbins; cbin++) {
        gfit_tight[cbin] = (TGraphErrors *) N1EVENSUB3_Diff_tight[cbin]->Clone();
        ffit_tight[cbin] = new TF1(Form("ffit_tight_%d",cbin), "pol0", fitmin, fitmax);
        gfit_tight[cbin]->Fit(Form("ffit_tight_%d",cbin));
        gfit_tight[cbin]->Delete();

        gfit_loose[cbin] = (TGraphErrors *) N1EVENSUB3_Diff_loose[cbin]->Clone();
        ffit_loose[cbin] = new TF1(Form("ffit_loose_%d",cbin), "pol0", fitmin, fitmax);
        gfit_loose[cbin]->Fit(Form("ffit_loose_%d",cbin));
        gfit_loose[cbin]->Delete();

        gfit_narrow[cbin] = (TGraphErrors *) N1EVENSUB3_Diff_narrow[cbin]->Clone();
        ffit_narrow[cbin] = new TF1(Form("ffit_narrow_%d",cbin), "pol0", fitmin, fitmax);
        gfit_narrow[cbin]->Fit(Form("ffit_narrow_%d",cbin));
        gfit_narrow[cbin]->Delete();

        gfit_wide[cbin] = (TGraphErrors *) N1EVENSUB3_Diff_wide[cbin]->Clone();
        ffit_wide[cbin] = new TF1(Form("ffit_wide_%d",cbin), "pol0", fitmin, fitmax);
        gfit_wide[cbin]->Fit(Form("ffit_wide_%d",cbin));
        gfit_wide[cbin]->Delete();
    }
    cout<<"\n\n----------------------------------\n\n"<<endl;
    cout<<"Systematics summary of N1EVENSUB3 by centrality bin "<<endl;
    cout<<"\n tight cuts: \n"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"-"<<cmax[cbin]<<"\t"<<ffit_tight[cbin]->GetParameter(0)<<"\t"<<ffit_tight[cbin]->GetParError(0)<<endl;
    }
    cout<<"\n loose cuts: \n"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"-"<<cmax[cbin]<<"\t"<<ffit_loose[cbin]->GetParameter(0)<<"\t"<<ffit_loose[cbin]->GetParError(0)<<endl;
    }
    cout<<"\n narrow cuts: \n"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"-"<<cmax[cbin]<<"\t"<<ffit_narrow[cbin]->GetParameter(0)<<"\t"<<ffit_narrow[cbin]->GetParError(0)<<endl;
    }
    cout<<"\n wide cuts: \n"<<endl;
    for (int cbin = 0; cbin<ncbins; cbin++) {
        cout<<cmin[cbin]<<"-"<<cmax[cbin]<<"\t"<<ffit_wide[cbin]->GetParameter(0)<<"\t"<<ffit_wide[cbin]->GetParError(0)<<endl;
    }
    cout<<"\n"<<endl;

}
