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

TGraphErrors * diff_gint_N1HFgSUB2_trackQuality[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_wide[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_tight[ncbins];
TGraphErrors * diff_gint_N1HFgSUB2_loose[ncbins];

TCanvas * cN1HFgSUB2_gint_trackQuality[ncbins];

void plotSyst() {

    for (int cbin = 0; cbin<ncbins; cbin++) {
        string tag = Form("default/N1HFgSUB2/-2.0_2.0/%d_%d",cmin[cbin],cmax[cbin]);

        // cN1HFgSUB2_gint_trackQuality[cbin] = (TCanvas *) fin->Get(Form("%s/syserr_N1HFgSUB2_gint_-2.0_2.0_%d_%d_trackQuality",tag.data(),cmin[cbin],cmax[cbin]));

        ratio_gint_N1HFgSUB2_narrow[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_narrow_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_wide[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_wide_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_tight[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_tight_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));
        ratio_gint_N1HFgSUB2_loose[cbin] = (TGraphErrors *) fin->Get(Form("%s/Ratio_loose_N1HFgSUB2_-2.0_2.0_%d_%d_gint",tag.data(),cmin[cbin],cmax[cbin]));

    }

}
