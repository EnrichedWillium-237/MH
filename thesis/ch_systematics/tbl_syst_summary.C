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

static const int ntypes = 5;
TString type[ntypes] = {"N1HFgSUB3", "N112ASUB3", "N1HFgSUB3_decor", "N1EVENSUB3", "N1EVENSUB3_decor"};
TString erange[ntypes] = {"0.0_2.0", "0.0_2.0", "1.2_1.6", "0.4_2.4", "1.2_1.6"};
double fitmin = 0.3;
double fitmax = 3.0;

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

TGraphErrors * N1SUB3_eta[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_loose[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_Diff_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_Diff_loose[ntypes][ncbins];

TGraphErrors * N1SUB3_eta_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_wide[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_Diff_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_Diff_wide[ntypes][ncbins];

TGraphErrors * N1SUB3_eta_trkCut[ntypes][ncbins];
TGraphErrors * N1SUB3_eta_vtxCut[ntypes][ncbins];

TGraphErrors * N1SUB3_pt[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_loose[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_loose[ntypes][ncbins];

TGraphErrors * N1SUB3_pt_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_wide[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_wide[ntypes][ncbins];

TGraphErrors * N1SUB3_pt_trkCut[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_vtxCut[ntypes][ncbins];

TF1 * fitTrkCut_eta[ntypes][ncbins];
TF1 * fitVtxCut_eta[ntypes][ncbins];
TF1 * fitTrkCut_pt[ntypes][ncbins];
TF1 * fitVtxCut_pt[ntypes][ncbins];

TGraphErrors * gN1_eta_trkCut[ntypes];
TGraphErrors * gN1_eta_vtxCut[ntypes];
TGraphErrors * gN1_pt_trkCut[ntypes];
TGraphErrors * gN1_pt_vtxCut[ntypes];

void tbl_syst_summary() {

    for (int i = 0; i<ntypes; i++) {
        for (int cbin = 0; cbin<ncbins; cbin++) {
            N1SUB3_eta[i][cbin] = (TGraphErrors *) fin->Get(Form("default/%s/%s/%d_%d/gint",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            N1SUB3_eta_tight[i][cbin] = (TGraphErrors *) fin->Get(Form("tight2/%s/%s/%d_%d/gint",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            N1SUB3_eta_loose[i][cbin] = (TGraphErrors *) fin->Get(Form("loose/%s/%s/%d_%d/gint",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            N1SUB3_eta_narrow[i][cbin] = (TGraphErrors *) fin->Get(Form("narrow/%s/%s/%d_%d/gint",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            N1SUB3_eta_wide[i][cbin] = (TGraphErrors *) fin->Get(Form("wide/%s/%s/%d_%d/gint",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            if (i <= 2) {
                N1SUB3_eta[i][cbin]->RemovePoint(0);
                N1SUB3_eta[i][cbin]->RemovePoint(N1SUB3_eta[i][cbin]->GetN()-1);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(0);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(N1SUB3_eta_tight[i][cbin]->GetN()-1);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(0);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(N1SUB3_eta_loose[i][cbin]->GetN()-1);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(0);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(N1SUB3_eta_narrow[i][cbin]->GetN()-1);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(0);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(N1SUB3_eta_wide[i][cbin]->GetN()-1);
            } else if (i == 3) {
                N1SUB3_eta[i][cbin]->RemovePoint(5);
                N1SUB3_eta[i][cbin]->RemovePoint(5);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(5);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(5);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(5);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(5);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(5);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(5);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(5);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(5);
            } else if (i == 4) {
                N1SUB3_eta[i][cbin]->RemovePoint(4);
                N1SUB3_eta[i][cbin]->RemovePoint(4);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(4);
                N1SUB3_eta_tight[i][cbin]->RemovePoint(4);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(4);
                N1SUB3_eta_loose[i][cbin]->RemovePoint(4);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(4);
                N1SUB3_eta_narrow[i][cbin]->RemovePoint(4);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(4);
                N1SUB3_eta_wide[i][cbin]->RemovePoint(4);
            }

            if (i <= 2) {
                N1SUB3_pt[i][cbin] = (TGraphErrors *) fin->Get(Form("default/%s/%s/%d_%d/g",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_tight[i][cbin] = (TGraphErrors *) fin->Get(Form("tight2/%s/%s/%d_%d/g",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_loose[i][cbin] = (TGraphErrors *) fin->Get(Form("loose/%s/%s/%d_%d/g",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_narrow[i][cbin] = (TGraphErrors *) fin->Get(Form("narrow/%s/%s/%d_%d/g",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_wide[i][cbin] = (TGraphErrors *) fin->Get(Form("wide/%s/%s/%d_%d/g",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            } else if (i == 3 || i == 4) {
                N1SUB3_pt[i][cbin] = (TGraphErrors *) fin->Get(Form("default/%s/%s/%d_%d/gA",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_tight[i][cbin] = (TGraphErrors *) fin->Get(Form("tight2/%s/%s/%d_%d/gA",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_loose[i][cbin] = (TGraphErrors *) fin->Get(Form("loose/%s/%s/%d_%d/gA",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_narrow[i][cbin] = (TGraphErrors *) fin->Get(Form("narrow/%s/%s/%d_%d/gA",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
                N1SUB3_pt_wide[i][cbin] = (TGraphErrors *) fin->Get(Form("wide/%s/%s/%d_%d/gA",type[i].Data(),erange[i].Data(),cmin[cbin],cmax[cbin]));
            }

            // compute differences
            double x[50], y[50], yt[50], yl[50], yn[50], yw[50];
            double ye[50], yte[50], yle[50], yne[50], ywe[50];
            int numE = N1SUB3_eta[i][cbin]->GetN();
            for (int j = 0; j<numE; j++) {
                N1SUB3_eta[i][cbin]->GetPoint(j, x[j], y[j]);
                N1SUB3_eta_tight[i][cbin]->GetPoint(j, x[j], yt[j]);
                N1SUB3_eta_loose[i][cbin]->GetPoint(j, x[j], yl[j]);
                N1SUB3_eta_narrow[i][cbin]->GetPoint(j, x[j], yn[j]);
                N1SUB3_eta_wide[i][cbin]->GetPoint(j, x[j], yw[j]);

                ye[j] = N1SUB3_eta[i][cbin]->GetErrorY(j);
                yte[j] = N1SUB3_eta_tight[i][cbin]->GetErrorY(j);
                yle[j] = N1SUB3_eta_loose[i][cbin]->GetErrorY(j);
                yne[j] = N1SUB3_eta_narrow[i][cbin]->GetErrorY(j);
                ywe[j] = N1SUB3_eta_wide[i][cbin]->GetErrorY(j);

                yt[j] = fabs(yt[j] - y[j]) * 1000.;
                yl[j] = fabs(yl[j] - y[j]) * 1000.;
                yn[j] = fabs(yn[j] - y[j]) * 1000.;
                yw[j] = fabs(yw[j] - y[j]) * 1000.;
                // yt[j] = fabs(yt[j] - y[j]);
                // yl[j] = fabs(yl[j] - y[j]);
                // yn[j] = fabs(yn[j] - y[j]);
                // yw[j] = fabs(yw[j] - y[j]);

                if (pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yt[j]/y[j]>0) {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yt[j]/y[j];
                } else if (pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(yte[j],2)/yt[j]/y[j]>0) {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(yte[j],2)/yt[j]/y[j];
                } else {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yl[j]/y[j]>0) {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yl[j]/y[j];
                } else if (pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(yle[j],2)/yl[j]/y[j]>0) {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(yle[j],2)/yl[j]/y[j];
                } else {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yn[j]/y[j]>0) {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yn[j]/y[j];
                } else if (pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(yne[j],2)/yn[j]/y[j]>0) {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(yne[j],2)/yn[j]/y[j];
                } else {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yw[j]/y[j]>0) {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yw[j]/y[j];
                } else if (pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ywe[j],2)/yw[j]/y[j]>0) {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ywe[j],2)/yw[j]/y[j];
                } else {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2);
                }

                yte[j] = sqrt( yte[j] );
                yle[j] = sqrt( yle[j] );
                yne[j] = sqrt( yne[j] );
                ywe[j] = sqrt( ywe[j] );
            }
            N1SUB3_eta_Diff_tight[i][cbin] = new TGraphErrors(numE, x, yt, 0, yte);
            N1SUB3_eta_Diff_loose[i][cbin] = new TGraphErrors(numE, x, yl, 0, yle);
            N1SUB3_eta_Diff_narrow[i][cbin] = new TGraphErrors(numE, x, yn, 0, yne);
            N1SUB3_eta_Diff_wide[i][cbin] = new TGraphErrors(numE, x, yw, 0, ywe);

            double ytrk[50], yvtx[50], ytrkerr[50], yvtxerr[50];
            for (int j = 0; j<numE; j++) {
                ytrk[j] = 0.5*(yt[j] + yl[j]);
                yvtx[j] = 0.5*(yn[j] + yw[j]);
                ytrkerr[j] = sqrt( pow(yte[j],2) + pow(yle[j],2) );
                yvtxerr[j] = sqrt( pow(yne[j],2) + pow(ywe[j],2) );
            }
            N1SUB3_eta_trkCut[i][cbin] = new TGraphErrors(numE, x, ytrk, 0, ytrkerr);
            N1SUB3_eta_vtxCut[i][cbin] = new TGraphErrors(numE, x, yvtx, 0, yvtxerr);

            //-- pT-dependence

            int numP = N1SUB3_pt[i][cbin]->GetN();
            for (int j = 0; j<numP; j++) {
                N1SUB3_pt[i][cbin]->GetPoint(j, x[j], y[j]);
                N1SUB3_pt_tight[i][cbin]->GetPoint(j, x[j], yt[j]);
                N1SUB3_pt_loose[i][cbin]->GetPoint(j, x[j], yl[j]);
                N1SUB3_pt_narrow[i][cbin]->GetPoint(j, x[j], yn[j]);
                N1SUB3_pt_wide[i][cbin]->GetPoint(j, x[j], yw[j]);

                ye[j] = N1SUB3_pt[i][cbin]->GetErrorY(j);
                yte[j] = N1SUB3_pt_tight[i][cbin]->GetErrorY(j);
                yle[j] = N1SUB3_pt_loose[i][cbin]->GetErrorY(j);
                yne[j] = N1SUB3_pt_narrow[i][cbin]->GetErrorY(j);
                ywe[j] = N1SUB3_pt_wide[i][cbin]->GetErrorY(j);

                yt[j] = fabs(yt[j] - y[j]) * 1000.;
                yl[j] = fabs(yl[j] - y[j]) * 1000.;
                yn[j] = fabs(yn[j] - y[j]) * 1000.;
                yw[j] = fabs(yw[j] - y[j]) * 1000.;
                // yt[j] = fabs(yt[j] - y[j]);
                // yl[j] = fabs(yl[j] - y[j]);
                // yn[j] = fabs(yn[j] - y[j]);
                // yw[j] = fabs(yw[j] - y[j]);

                if (pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yt[j]/y[j]>0) {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yt[j]/y[j];
                } else if (pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(yte[j],2)/yt[j]/y[j]>0) {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2) - 2*pow(yte[j],2)/yt[j]/y[j];
                } else {
                    yte[j] = pow(yte[j]/yt[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yl[j]/y[j]>0) {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yl[j]/y[j];
                } else if (pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(yle[j],2)/yl[j]/y[j]>0) {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2) - 2*pow(yle[j],2)/yl[j]/y[j];
                } else {
                    yle[j] = pow(yle[j]/yl[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yn[j]/y[j]>0) {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yn[j]/y[j];
                } else if (pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(yne[j],2)/yn[j]/y[j]>0) {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2) - 2*pow(yne[j],2)/yn[j]/y[j];
                } else {
                    yne[j] = pow(yne[j]/yn[j],2) + pow(ye[j]/y[j],2);
                }

                if (pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yw[j]/y[j]>0) {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ye[j],2)/yw[j]/y[j];
                } else if (pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ywe[j],2)/yw[j]/y[j]>0) {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2) - 2*pow(ywe[j],2)/yw[j]/y[j];
                } else {
                    ywe[j] = pow(ywe[j]/yw[j],2) + pow(ye[j]/y[j],2);
                }

                yte[j] = sqrt( yte[j] );
                yle[j] = sqrt( yle[j] );
                yne[j] = sqrt( yne[j] );
                ywe[j] = sqrt( ywe[j] );
            }
            N1SUB3_pt_Diff_tight[i][cbin] = new TGraphErrors(numP, x, yt, 0, yte);
            N1SUB3_pt_Diff_loose[i][cbin] = new TGraphErrors(numP, x, yl, 0, yle);
            N1SUB3_pt_Diff_narrow[i][cbin] = new TGraphErrors(numP, x, yn, 0, yne);
            N1SUB3_pt_Diff_wide[i][cbin] = new TGraphErrors(numP, x, yw, 0, ywe);

            for (int j = 0; j<numP; j++) {
                ytrk[j] = 0.5*(yt[j] + yl[j]);
                yvtx[j] = 0.5*(yn[j] + yw[j]);
                ytrkerr[j] = sqrt( pow(yte[j],2) + pow(yle[j],2) );
                yvtxerr[j] = sqrt( pow(yne[j],2) + pow(ywe[j],2) );
            }
            N1SUB3_pt_trkCut[i][cbin] = new TGraphErrors(numP, x, ytrk, 0, ytrkerr);
            N1SUB3_pt_vtxCut[i][cbin] = new TGraphErrors(numP, x, yvtx, 0, yvtxerr);
        }
    }
    // N1SUB3_pt_trkCut[0][4]->Draw("alp");

    // now fit

    for (int i = 0; i<ntypes; i++) {
        for (int cbin = 0; cbin<ncbins; cbin++) {
            string tag = Form("%0.1f_%0.1f_%s_%d_%d",fitmin,fitmax,type[i].Data(),cmin[cbin],cmax[cbin]);
            if (i<=2) {
                fitTrkCut_eta[i][cbin] = new TF1(Form("fitTrkCut_eta_%s",tag.data()), "pol0", -2.0, 2.0);
                N1SUB3_eta_trkCut[i][cbin]->Fit(Form("fitTrkCut_eta_%s",tag.data()), "", "", -2.0, 2.0);
                fitVtxCut_eta[i][cbin] = new TF1(Form("fitVtxCut_eta_%s",tag.data()), "pol0", -2.0, 2.0);
                N1SUB3_eta_vtxCut[i][cbin]->Fit(Form("fitVtxCut_eta_%s",tag.data()), "", "", -2.0, 2.0);
            } else if (i == 3 || i == 4) {
                fitTrkCut_eta[i][cbin] = new TF1(Form("fitTrkCut_eta_%s",tag.data()), "pol0", -2.4, 2.4);
                N1SUB3_eta_trkCut[i][cbin]->Fit(Form("fitTrkCut_eta_%s",tag.data()), "", "", -2.4, 2.4);
                fitVtxCut_eta[i][cbin] = new TF1(Form("fitVtxCut_eta_%s",tag.data()), "pol0", -2.4, 2.4);
                N1SUB3_eta_vtxCut[i][cbin]->Fit(Form("fitVtxCut_eta_%s",tag.data()), "", "", -2.4, 2.4);
            }

            fitTrkCut_pt[i][cbin] = new TF1(Form("fitTrkCut_pt_%s",tag.data()), "pol0", fitmin, fitmax);
            N1SUB3_pt_trkCut[i][cbin]->Fit(Form("fitTrkCut_pt_%s",tag.data()), "", "", fitmin, fitmax);
            fitVtxCut_pt[i][cbin] = new TF1(Form("fitVtxCut_pt_%s",tag.data()), "pol0", fitmin, fitmax);
            N1SUB3_pt_vtxCut[i][cbin]->Fit(Form("fitVtxCut_pt_%s",tag.data()), "", "", fitmin, fitmax);
        }
    }
    cout<<"\n\n----------------------------------\n\n"<<endl;
    cout<<"Systematics summary by centrality bin "<<endl;
    cout<<"\n track cuts\tvertex cuts"<<endl;
    for (int i = 0; i<ntypes; i++) {
        cout<<"\n"<<type[i].Data()<<"\n eta-dependence"<<endl;
        for (int cbin = 0; cbin<ncbins; cbin++) {
            cout<<fitTrkCut_eta[i][cbin]->GetParameter(0)<<"\t"<<fitVtxCut_eta[i][cbin]->GetParameter(0)<<endl;
        }
        cout<<"\n pT-dependence ("<<fitmin<<" to "<<fitmax<<" GeV/c)"<<endl;
        for (int cbin = 0; cbin<ncbins; cbin++) {
            cout<<fitTrkCut_pt[i][cbin]->GetParameter(0)<<"\t"<<fitVtxCut_pt[i][cbin]->GetParameter(0)<<endl;
        }
        cout<<"\n"<<endl;
    }


    //--

    for (int i = 0; i<ntypes; i++) {
        double x[50], y[50], yerr[50];
        for (int cbin = 0; cbin<ncbins; cbin++) {
            x[cbin] = (cmin[cbin]+cmax[cbin])/2;
            y[cbin] = fitTrkCut_eta[i][cbin]->GetParameter(0);
            yerr[cbin] = fitTrkCut_eta[i][cbin]->GetParError(0);
        }
        gN1_eta_trkCut[i] = new TGraphErrors(ncbins, x, y, 0, yerr);
        for (int cbin = 0; cbin<ncbins; cbin++) {
            x[cbin] = (cmin[cbin]+cmax[cbin])/2;
            y[cbin] = fitVtxCut_eta[i][cbin]->GetParameter(0);
            yerr[cbin] = fitVtxCut_eta[i][cbin]->GetParError(0);
        }
        gN1_eta_vtxCut[i] = new TGraphErrors(ncbins, x, y, 0, yerr);
        for (int cbin = 0; cbin<ncbins; cbin++) {
            x[cbin] = (cmin[cbin]+cmax[cbin])/2;
            y[cbin] = fitTrkCut_pt[i][cbin]->GetParameter(0);
            yerr[cbin] = fitTrkCut_pt[i][cbin]->GetParError(0);
        }
        gN1_pt_trkCut[i] = new TGraphErrors(ncbins, x, y, 0, yerr);
        for (int cbin = 0; cbin<ncbins; cbin++) {
            x[cbin] = (cmin[cbin]+cmax[cbin])/2;
            y[cbin] = fitVtxCut_pt[i][cbin]->GetParameter(0);
            yerr[cbin] = fitVtxCut_pt[i][cbin]->GetParError(0);
        }
        gN1_pt_vtxCut[i] = new TGraphErrors(ncbins, x, y, 0, yerr);

        gN1_eta_trkCut[i]->SetMarkerStyle(20);
        gN1_eta_trkCut[i]->SetMarkerSize(1.3);
        gN1_eta_trkCut[i]->SetMarkerColor(kGreen+2);
        gN1_eta_trkCut[i]->SetLineColor(kGreen+2);

        gN1_eta_vtxCut[i]->SetMarkerStyle(24);
        gN1_eta_vtxCut[i]->SetMarkerSize(1.3);
        gN1_eta_vtxCut[i]->SetMarkerColor(kRed);
        gN1_eta_vtxCut[i]->SetLineColor(kRed);

        gN1_pt_trkCut[i]->SetMarkerStyle(20);
        gN1_pt_trkCut[i]->SetMarkerSize(1.3);
        gN1_pt_trkCut[i]->SetMarkerColor(kGreen+2);
        gN1_pt_trkCut[i]->SetLineColor(kGreen+2);

        gN1_pt_vtxCut[i]->SetMarkerStyle(24);
        gN1_pt_vtxCut[i]->SetMarkerSize(1.3);
        gN1_pt_vtxCut[i]->SetMarkerColor(kRed);
        gN1_pt_vtxCut[i]->SetLineColor(kRed);
    }


    TCanvas * c0_e = new TCanvas("c0_e", "c0_e", 600, 550);
    c0_e->cd();
    TH1D * h0_e = new TH1D("h0_e", "", 100, 0, 70);
    h0_e->SetXTitle("Centrality (%)");
    h0_e->GetXaxis()->CenterTitle();
    h0_e->GetXaxis()->SetTitleFont(43);
    h0_e->GetXaxis()->SetTitleSize(26);
    h0_e->GetXaxis()->SetTitleOffset(1.3);
    h0_e->SetYTitle("Absolute systematic #times 1000");
    h0_e->GetYaxis()->CenterTitle();
    h0_e->GetYaxis()->SetTitleFont(43);
    h0_e->GetYaxis()->SetTitleSize(26);
    h0_e->GetYaxis()->SetTitleOffset(1.6);
    h0_e->GetYaxis()->SetRangeUser(-0.1, 0.9);
    h0_e->Draw();
    gN1_eta_trkCut[0]->Draw("same p");
    gN1_eta_vtxCut[0]->Draw("same p");
    TLegend * leg0_e = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg0_e, 20);
    leg0_e->SetHeader("v_{1}^{odd}(#eta)  #eta_{C} = 0");
    leg0_e->AddEntry(gN1_eta_trkCut[0], "Track quality", "p");
    leg0_e->AddEntry(gN1_eta_vtxCut[0], "Vertex selection", "p");
    leg0_e->Draw();
    c0_e->Print("../figures/fig_syst_summary_N1HFgSUB3_eta.pdf","pdf");


    TCanvas * c0_p = new TCanvas("c0_p", "c0_p", 600, 550);
    c0_p->cd();
    TH1D * h0_p = (TH1D *) h0_e->Clone("h0_p");
    h0_p->GetYaxis()->SetRangeUser(0, 0.8);
    h0_p->Draw();
    gN1_pt_trkCut[0]->Draw("same p");
    gN1_pt_vtxCut[0]->Draw("same p");
    TLegend * leg0_p = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg0_p, 20);
    leg0_p->SetHeader(Form("v_{1}^{even}(p_{T})  #eta_{C} = 0  %0.1f < p_{T} < %0.1f",fitmin,fitmax));
    leg0_p->AddEntry(gN1_eta_trkCut[1], "Track quality", "p");
    leg0_p->AddEntry(gN1_eta_vtxCut[1], "Vertex selection", "p");
    leg0_p->Draw();
    c0_p->Print("../figures/fig_syst_summary_N1HFgSUB3_pT.pdf","pdf");


    TCanvas * c1_e = new TCanvas("c1_e", "c1_e", 600, 550);
    c1_e->cd();
    TH1D * h1_e = (TH1D *) h0_e->Clone("h1_e");
    h1_e->GetYaxis()->SetRangeUser(-1.5, 4);
    h1_e->Draw();
    gN1_eta_vtxCut[1]->Draw("same p");
    gN1_eta_trkCut[1]->Draw("same p");
    TLegend * leg1_e = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg1_e, 20);
    leg1_e->SetHeader("v_{1}^{odd}(#eta)  mixed");
    leg1_e->AddEntry(gN1_eta_trkCut[1], "Track quality", "p");
    leg1_e->AddEntry(gN1_eta_vtxCut[1], "Vertex selection", "p");
    leg1_e->Draw();
    c1_e->Print("../figures/fig_syst_summary_N112ASUB3_eta.pdf","pdf");


    TCanvas * c1_p = new TCanvas("c1_p", "c1_p", 600, 550);
    c1_p->cd();
    TH1D * h1_p = (TH1D *) h0_p->Clone("h1_p");
    h1_p->GetYaxis()->SetRangeUser(0, 6);
    h1_p->Draw();
    gN1_pt_vtxCut[1]->Draw("same p");
    gN1_pt_trkCut[1]->Draw("same p");
    TLegend * leg1_p = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg1_p, 20);
    leg1_p->SetHeader(Form("v_{1}^{even}(p_{T})  mixed  %0.1f < p_{T} < %0.1f",fitmin,fitmax));
    leg1_p->AddEntry(gN1_pt_trkCut[1], "Track quality", "p");
    leg1_p->AddEntry(gN1_pt_vtxCut[1], "Vertex selection", "p");
    leg1_p->Draw();
    c1_p->Print("../figures/fig_syst_summary_N112ASUB3_pT.pdf","pdf");


    TCanvas * c2_e = new TCanvas("c2_e", "c2_e", 600, 550);
    c2_e->cd();
    TH1D * h2_e = (TH1D *) h0_e->Clone("h2_e");
    h2_e->GetYaxis()->SetRangeUser(-1, 2.5);
    h2_e->Draw();
    gN1_eta_vtxCut[2]->Draw("same p");
    gN1_eta_trkCut[2]->Draw("same p");
    TLegend * leg2_e = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg2_e, 20);
    leg2_e->SetHeader("v_{1}^{odd}(#eta)  #eta_{C} = #eta_{ROI}");
    leg2_e->AddEntry(gN1_eta_trkCut[2], "Track quality", "p");
    leg2_e->AddEntry(gN1_eta_vtxCut[2], "Vertex selection", "p");
    leg2_e->Draw();
    c2_e->Print("../figures/fig_syst_summary_N1HFgSUB3_decor_eta.pdf","pdf");


    TCanvas * c2_p = new TCanvas("c2_p", "c2_p", 600, 550);
    c2_p->cd();
    TH1D * h2_p = (TH1D *) h0_p->Clone("h2_p");
    h2_p->GetYaxis()->SetRangeUser(-0.3, 3);
    h2_p->Draw();
    gN1_pt_vtxCut[2]->Draw("same p");
    gN1_pt_trkCut[2]->Draw("same p");
    TLegend * leg2_p = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg2_p, 20);
    leg2_p->SetHeader(Form("v_{1}^{even}(p_{T})  #eta_{C} = #eta_{ROI}  %0.1f < p_{T} < %0.1f",fitmin,fitmax));
    leg2_p->AddEntry(gN1_pt_trkCut[2], "Track quality", "p");
    leg2_p->AddEntry(gN1_pt_vtxCut[2], "Vertex selection", "p");
    leg2_p->Draw();
    c2_p->Print("../figures/fig_syst_summary_N1HFgSUB3_decor_pT.pdf","pdf");


    TCanvas * c3_e = new TCanvas("c3_e", "c3_e", 600, 550);
    c3_e->cd();
    TH1D * h3_e = (TH1D *) h0_e->Clone("h3_e");
    h3_e->GetYaxis()->SetRangeUser(0, 4);
    h3_e->Draw();
    gN1_eta_vtxCut[3]->Draw("same p");
    gN1_eta_trkCut[3]->Draw("same p");
    TLegend * leg3_e = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg3_e, 20);
    leg3_e->SetHeader("v_{1}^{even}(#eta)  #eta_{C} = 0");
    leg3_e->AddEntry(gN1_eta_trkCut[3], "Track quality", "p");
    leg3_e->AddEntry(gN1_eta_vtxCut[3], "Vertex selection", "p");
    leg3_e->Draw();
    c3_e->Print("../figures/fig_syst_summary_N1EVENSUB3_eta.pdf","pdf");


    TCanvas * c3_p = new TCanvas("c3_p", "c3_p", 600, 550);
    c3_p->cd();
    TH1D * h3_p = (TH1D *) h0_p->Clone("h3_p");
    h3_p->GetYaxis()->SetRangeUser(0, 8);
    h3_p->Draw();
    gN1_pt_vtxCut[3]->Draw("same p");
    gN1_pt_trkCut[3]->Draw("same p");
    TLegend * leg3_p = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg3_p, 20);
    leg3_p->SetHeader(Form("v_{1}^{even}(p_{T})  #eta_{C} = 0  %0.1f < p_{T} < %0.1f",fitmin,fitmax));
    leg3_p->AddEntry(gN1_pt_trkCut[2], "Track quality", "p");
    leg3_p->AddEntry(gN1_pt_vtxCut[2], "Vertex selection", "p");
    leg3_p->Draw();
    c3_p->Print("../figures/fig_syst_summary_N1EVENSUB3_pT.pdf","pdf");


    TCanvas * c4_e = new TCanvas("c4_e", "c4_e", 600, 550);
    c4_e->cd();
    TH1D * h4_e = (TH1D *) h0_e->Clone("h4_e");
    h4_e->GetYaxis()->SetRangeUser(0, 7);
    h4_e->Draw();
    gN1_eta_vtxCut[4]->Draw("same p");
    gN1_eta_trkCut[4]->Draw("same p");
    TLegend * leg4_e = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg4_e, 20);
    leg4_e->SetHeader("v_{1}^{even}(#eta)  #eta_{C} = #eta_{ROI}");
    leg4_e->AddEntry(gN1_eta_trkCut[4], "Track quality", "p");
    leg4_e->AddEntry(gN1_eta_vtxCut[4], "Vertex selection", "p");
    leg4_e->Draw();
    c4_e->Print("../figures/fig_syst_summary_N1EVENSUB3_decor_eta.pdf","pdf");


    TCanvas * c4_p = new TCanvas("c4_p", "c4_p", 600, 550);
    c4_p->cd();
    TH1D * h4_p = (TH1D *) h0_p->Clone("h4_p");
    h4_p->GetYaxis()->SetRangeUser(0, 30);
    h4_p->Draw();
    gN1_pt_vtxCut[4]->Draw("same p");
    gN1_pt_trkCut[4]->Draw("same p");
    TLegend * leg4_p = new TLegend(0.21, 0.72, 0.41, 0.91);
    SetLegend(leg4_p, 20);
    leg4_p->SetHeader(Form("v_{1}^{even}(p_{T})  #eta_{C} = #eta_{ROI}  %0.1f < p_{T} < %0.1f",fitmin,fitmax));
    leg4_p->AddEntry(gN1_pt_trkCut[4], "Track quality", "p");
    leg4_p->AddEntry(gN1_pt_vtxCut[4], "Vertex selection", "p");
    leg4_p->Draw();
    c4_p->Print("../figures/fig_syst_summary_N1EVENSUB3_decor_pT.pdf","pdf");




}
