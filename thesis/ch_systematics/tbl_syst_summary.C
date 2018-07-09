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

TGraphErrors * N1SUB3_pt[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_loose[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_tight[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_loose[ntypes][ncbins];

TGraphErrors * N1SUB3_pt_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_wide[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_narrow[ntypes][ncbins];
TGraphErrors * N1SUB3_pt_Diff_wide[ntypes][ncbins];

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
        }
    }
    N1SUB3_pt_wide[3][3]->Draw("alp");


}
