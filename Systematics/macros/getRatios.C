# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "Riostream.h"
# include <iostream>

using namespace std;

# include "src/HiEvtPlaneList.h"
# include "src/style.h"

using namespace hi;
static const int ncentbins = 13;
static const int cminCENT[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20,  60};
static const int cmaxCENT[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60, 100};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const int nbinsETA = 14;
static const double eminETA[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0, -2.4,  0.0};
static const double emaxETA[] = {-2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4,  0.0,  2.4};
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};

# include "src/getRatios.h"

TFile * fin;
TFile * fout;

void getRatios()
{
    TH1::SetDefaultSumw2();

    fin = new TFile("hists/MH_combined.root","read");

    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TString mtag = Form("%d_%d",cminCENT[cbin],cmaxCENT[cbin]);

        hN1SUB2_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCm22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCp22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCm22SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_pt[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCp22SUB3_pt_%s",mtag.Data(),mtag.Data()));

        hN1SUB2_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCm22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCp22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCm22SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_eta[cbin] = (TH1D *) fin->Get(Form("MH_nominal/%s/hN1MCp22SUB3_eta_%s",mtag.Data(),mtag.Data()));


        hN1SUB2_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCm22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCp22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCm22SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_tight_pt[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCp22SUB3_pt_%s",mtag.Data(),mtag.Data()));

        hN1SUB2_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCm22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCp22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCm22SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_tight_eta[cbin] = (TH1D *) fin->Get(Form("MH_tight/%s/hN1MCp22SUB3_eta_%s",mtag.Data(),mtag.Data()));


        hN1SUB2_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCm22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCp22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCm22SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_wide_pt[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCp22SUB3_pt_%s",mtag.Data(),mtag.Data()));

        hN1SUB2_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCm22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCp22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCm22SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_wide_eta[cbin] = (TH1D *) fin->Get(Form("MH_wide/%s/hN1MCp22SUB3_eta_%s",mtag.Data(),mtag.Data()));


        hN1SUB2_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCm22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCp22SUB2_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCm22SUB3_pt_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_narrow_pt[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCp22SUB3_pt_%s",mtag.Data(),mtag.Data()));

        hN1SUB2_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1SUB3_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB2_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCm22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB2_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCp22SUB2_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCm22SUB3_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCm22SUB3_eta_%s",mtag.Data(),mtag.Data()));
        hN1MCp22SUB3_narrow_eta[cbin] = (TH1D *) fin->Get(Form("MH_narrow/%s/hN1MCp22SUB3_eta_%s",mtag.Data(),mtag.Data()));
    }

    // nominal vs. tight
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        rat_tight_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_tight_pt[cbin]->Clone(Form("rat_tight_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1SUB3_pt[cbin] = (TH1D *) hN1SUB3_tight_pt[cbin]->Clone(Form("rat_tight_N1SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB3_pt[cbin]->Divide(hN1SUB3_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1SUB3_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1SUB3_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_tight_pt[cbin]->Clone(Form("rat_tight_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCm22SUB2_pt[cbin] = (TH1D *) hN1MCm22SUB2_tight_pt[cbin]->Clone(Form("rat_tight_N1MCm22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCm22SUB2_pt[cbin]->Divide(hN1MCm22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1MCm22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1MCm22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCp22SUB2_pt[cbin] = (TH1D *) hN1MCp22SUB2_tight_pt[cbin]->Clone(Form("rat_tight_N1MCp22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCp22SUB2_pt[cbin]->Divide(hN1MCp22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1MCp22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1MCp22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCm22SUB3_pt[cbin] = (TH1D *) hN1MCm22SUB3_tight_pt[cbin]->Clone(Form("rat_tight_N1MCm22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCm22SUB3_pt[cbin]->Divide(hN1MCm22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1MCm22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1MCm22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCp22SUB3_pt[cbin] = (TH1D *) hN1MCp22SUB3_tight_pt[cbin]->Clone(Form("rat_tight_N1MCp22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCp22SUB3_pt[cbin]->Divide(hN1MCp22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_tight_N1MCp22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_tight_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_tight_pt[cbin]->GetBinError(k);
            rat_tight_N1MCp22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_tight_eta[cbin]->Clone(Form("rat_tight_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1SUB3_eta[cbin] = (TH1D *) hN1SUB3_tight_eta[cbin]->Clone(Form("rat_tight_N1SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB3_eta[cbin]->Divide(hN1SUB3_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1SUB3_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1SUB3_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_tight_eta[cbin]->Clone(Form("rat_tight_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCm22SUB2_eta[cbin] = (TH1D *) hN1MCm22SUB2_tight_eta[cbin]->Clone(Form("rat_tight_N1MCm22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCm22SUB2_eta[cbin]->Divide(hN1MCm22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1MCm22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1MCm22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCp22SUB2_eta[cbin] = (TH1D *) hN1MCp22SUB2_tight_eta[cbin]->Clone(Form("rat_tight_N1MCp22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCp22SUB2_eta[cbin]->Divide(hN1MCp22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1MCp22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1MCp22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCm22SUB3_eta[cbin] = (TH1D *) hN1MCm22SUB3_tight_eta[cbin]->Clone(Form("rat_tight_N1MCm22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCm22SUB3_eta[cbin]->Divide(hN1MCm22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1MCm22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1MCm22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_tight_N1MCp22SUB3_eta[cbin] = (TH1D *) hN1MCp22SUB3_tight_eta[cbin]->Clone(Form("rat_tight_N1MCp22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_tight_N1MCp22SUB3_eta[cbin]->Divide(hN1MCp22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_tight_N1MCp22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_tight_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_tight_eta[cbin]->GetBinError(k);
            rat_tight_N1MCp22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }
    }

    // nominal vs. wide
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        rat_wide_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_wide_pt[cbin]->Clone(Form("rat_wide_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1SUB3_pt[cbin] = (TH1D *) hN1SUB3_wide_pt[cbin]->Clone(Form("rat_wide_N1SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB3_pt[cbin]->Divide(hN1SUB3_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1SUB3_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1SUB3_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_wide_pt[cbin]->Clone(Form("rat_wide_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCm22SUB2_pt[cbin] = (TH1D *) hN1MCm22SUB2_wide_pt[cbin]->Clone(Form("rat_wide_N1MCm22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCm22SUB2_pt[cbin]->Divide(hN1MCm22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1MCm22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1MCm22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCp22SUB2_pt[cbin] = (TH1D *) hN1MCp22SUB2_wide_pt[cbin]->Clone(Form("rat_wide_N1MCp22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCp22SUB2_pt[cbin]->Divide(hN1MCp22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1MCp22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1MCp22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCm22SUB3_pt[cbin] = (TH1D *) hN1MCm22SUB3_wide_pt[cbin]->Clone(Form("rat_wide_N1MCm22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCm22SUB3_pt[cbin]->Divide(hN1MCm22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1MCm22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1MCm22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCp22SUB3_pt[cbin] = (TH1D *) hN1MCp22SUB3_wide_pt[cbin]->Clone(Form("rat_wide_N1MCp22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCp22SUB3_pt[cbin]->Divide(hN1MCp22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_wide_N1MCp22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_wide_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_wide_pt[cbin]->GetBinError(k);
            rat_wide_N1MCp22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_wide_eta[cbin]->Clone(Form("rat_wide_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1SUB3_eta[cbin] = (TH1D *) hN1SUB3_wide_eta[cbin]->Clone(Form("rat_wide_N1SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB3_eta[cbin]->Divide(hN1SUB3_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1SUB3_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1SUB3_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_wide_eta[cbin]->Clone(Form("rat_wide_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCm22SUB2_eta[cbin] = (TH1D *) hN1MCm22SUB2_wide_eta[cbin]->Clone(Form("rat_wide_N1MCm22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCm22SUB2_eta[cbin]->Divide(hN1MCm22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1MCm22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1MCm22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCp22SUB2_eta[cbin] = (TH1D *) hN1MCp22SUB2_wide_eta[cbin]->Clone(Form("rat_wide_N1MCp22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCp22SUB2_eta[cbin]->Divide(hN1MCp22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1MCp22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1MCp22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCm22SUB3_eta[cbin] = (TH1D *) hN1MCm22SUB3_wide_eta[cbin]->Clone(Form("rat_wide_N1MCm22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCm22SUB3_eta[cbin]->Divide(hN1MCm22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1MCm22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1MCm22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_wide_N1MCp22SUB3_eta[cbin] = (TH1D *) hN1MCp22SUB3_wide_eta[cbin]->Clone(Form("rat_wide_N1MCp22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_wide_N1MCp22SUB3_eta[cbin]->Divide(hN1MCp22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_wide_N1MCp22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_wide_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_wide_eta[cbin]->GetBinError(k);
            rat_wide_N1MCp22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }
    }

    // nominal vs. narrow
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        rat_narrow_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_narrow_pt[cbin]->Clone(Form("rat_narrow_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1SUB3_pt[cbin] = (TH1D *) hN1SUB3_narrow_pt[cbin]->Clone(Form("rat_narrow_N1SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB3_pt[cbin]->Divide(hN1SUB3_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1SUB3_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1SUB3_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1SUB2_pt[cbin] = (TH1D *) hN1SUB2_narrow_pt[cbin]->Clone(Form("rat_narrow_N1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB2_pt[cbin]->Divide(hN1SUB2_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1SUB2_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1SUB2_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCm22SUB2_pt[cbin] = (TH1D *) hN1MCm22SUB2_narrow_pt[cbin]->Clone(Form("rat_narrow_N1MCm22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCm22SUB2_pt[cbin]->Divide(hN1MCm22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCm22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1MCm22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCp22SUB2_pt[cbin] = (TH1D *) hN1MCp22SUB2_narrow_pt[cbin]->Clone(Form("rat_narrow_N1MCp22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCp22SUB2_pt[cbin]->Divide(hN1MCp22SUB2_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCp22SUB2_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1MCp22SUB2_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCm22SUB3_pt[cbin] = (TH1D *) hN1MCm22SUB3_narrow_pt[cbin]->Clone(Form("rat_narrow_N1MCm22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCm22SUB3_pt[cbin]->Divide(hN1MCm22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCm22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1MCm22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCp22SUB3_pt[cbin] = (TH1D *) hN1MCp22SUB3_narrow_pt[cbin]->Clone(Form("rat_narrow_N1MCp22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCp22SUB3_pt[cbin]->Divide(hN1MCp22SUB3_pt[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCp22SUB3_pt[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_pt[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_narrow_pt[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_pt[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_narrow_pt[cbin]->GetBinError(k);
            rat_narrow_N1MCp22SUB3_pt[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_narrow_eta[cbin]->Clone(Form("rat_narrow_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1SUB3_eta[cbin] = (TH1D *) hN1SUB3_narrow_eta[cbin]->Clone(Form("rat_narrow_N1SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB3_eta[cbin]->Divide(hN1SUB3_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1SUB3_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1SUB3_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1SUB2_eta[cbin] = (TH1D *) hN1SUB2_narrow_eta[cbin]->Clone(Form("rat_narrow_N1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1SUB2_eta[cbin]->Divide(hN1SUB2_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1SUB2_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1SUB2_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCm22SUB2_eta[cbin] = (TH1D *) hN1MCm22SUB2_narrow_eta[cbin]->Clone(Form("rat_narrow_N1MCm22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCm22SUB2_eta[cbin]->Divide(hN1MCm22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCm22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB2_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB2_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1MCm22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCp22SUB2_eta[cbin] = (TH1D *) hN1MCp22SUB2_narrow_eta[cbin]->Clone(Form("rat_narrow_N1MCp22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCp22SUB2_eta[cbin]->Divide(hN1MCp22SUB2_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCp22SUB2_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB2_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB2_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB2_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB2_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1MCp22SUB2_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCm22SUB3_eta[cbin] = (TH1D *) hN1MCm22SUB3_narrow_eta[cbin]->Clone(Form("rat_narrow_N1MCm22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCm22SUB3_eta[cbin]->Divide(hN1MCm22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCm22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCm22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCm22SUB3_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1MCm22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCm22SUB3_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1MCm22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }

        rat_narrow_N1MCp22SUB3_eta[cbin] = (TH1D *) hN1MCp22SUB3_narrow_eta[cbin]->Clone(Form("rat_narrow_N1MCp22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        rat_narrow_N1MCp22SUB3_eta[cbin]->Divide(hN1MCp22SUB3_eta[cbin]);
        for (int k = 1; k<=rat_narrow_N1MCp22SUB3_eta[cbin]->GetNbinsX(); k++) {
            double x = hN1MCp22SUB3_eta[cbin]->GetBinContent(k);
            double y = hN1MCp22SUB3_narrow_eta[cbin]->GetBinContent(k);
            double xe = hN1MCp22SUB3_eta[cbin]->GetBinError(k);
            double ye = hN1MCp22SUB3_narrow_eta[cbin]->GetBinError(k);
            rat_narrow_N1MCp22SUB3_eta[cbin]->SetBinError(k, ErrRatCalc( x, y, xe, ye ));
        }
    }


    fout = new TFile("hists/MH_ratios.root","recreate");
    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TDirectory * tdcent = (TDirectory *) fout->mkdir(Form("%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        TDirectory * tdPt = (TDirectory *) tdcent->mkdir("vn_pt");
        tdPt->cd();

        rat_tight_N1SUB2_pt[cbin]->Write();
        rat_tight_N1SUB3_pt[cbin]->Write();
        rat_tight_N1MCm22SUB2_pt[cbin]->Write();
        rat_tight_N1MCp22SUB2_pt[cbin]->Write();
        rat_tight_N1MCm22SUB3_pt[cbin]->Write();
        rat_tight_N1MCp22SUB3_pt[cbin]->Write();

        rat_wide_N1SUB2_pt[cbin]->Write();
        rat_wide_N1SUB3_pt[cbin]->Write();
        rat_wide_N1MCm22SUB2_pt[cbin]->Write();
        rat_wide_N1MCp22SUB2_pt[cbin]->Write();
        rat_wide_N1MCm22SUB3_pt[cbin]->Write();
        rat_wide_N1MCp22SUB3_pt[cbin]->Write();

        rat_narrow_N1SUB2_pt[cbin]->Write();
        rat_narrow_N1SUB3_pt[cbin]->Write();
        rat_narrow_N1MCm22SUB2_pt[cbin]->Write();
        rat_narrow_N1MCp22SUB2_pt[cbin]->Write();
        rat_narrow_N1MCm22SUB3_pt[cbin]->Write();
        rat_narrow_N1MCp22SUB3_pt[cbin]->Write();

        TDirectory * tdEta = (TDirectory *) tdcent->mkdir("vn_eta");
        tdEta->cd();

        rat_tight_N1SUB2_eta[cbin]->Write();
        rat_tight_N1SUB3_eta[cbin]->Write();
        rat_tight_N1MCm22SUB2_eta[cbin]->Write();
        rat_tight_N1MCp22SUB2_eta[cbin]->Write();
        rat_tight_N1MCm22SUB3_eta[cbin]->Write();
        rat_tight_N1MCp22SUB3_eta[cbin]->Write();

        rat_wide_N1SUB2_eta[cbin]->Write();
        rat_wide_N1SUB3_eta[cbin]->Write();
        rat_wide_N1MCm22SUB2_eta[cbin]->Write();
        rat_wide_N1MCp22SUB2_eta[cbin]->Write();
        rat_wide_N1MCm22SUB3_eta[cbin]->Write();
        rat_wide_N1MCp22SUB3_eta[cbin]->Write();

        rat_narrow_N1SUB2_eta[cbin]->Write();
        rat_narrow_N1SUB3_eta[cbin]->Write();
        rat_narrow_N1MCm22SUB2_eta[cbin]->Write();
        rat_narrow_N1MCp22SUB2_eta[cbin]->Write();
        rat_narrow_N1MCm22SUB3_eta[cbin]->Write();
        rat_narrow_N1MCp22SUB3_eta[cbin]->Write();

    }

    // fout->Close();

    cout << "vn cut ratios written out to hists/MH_ratios.root \n" << endl;

}
