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
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
static const double etaMid[] = {-2.2, -1.8, -1.4, -1.0, -0.6, -0.2,  0.2,  0.6,  1.0,  1.4,  1.8,  2.2};
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};

TGraphErrors * gN1MCm22SUB2_pt[ncentbins];
TGraphErrors * gN1MCp22SUB2_pt[ncentbins];
TGraphErrors * gN1SUB2_pt[ncentbins];
TGraphErrors * gN1MCm22SUB3_pt[ncentbins];
TGraphErrors * gN1MCp22SUB3_pt[ncentbins];
TGraphErrors * gN1SUB3_pt[ncentbins];

TGraphErrors * gN1MCm22SUB2_eta[ncentbins];
TGraphErrors * gN1MCp22SUB2_eta[ncentbins];
TGraphErrors * gN1SUB2_eta[ncentbins];
TGraphErrors * gN1MCm22SUB3_eta[ncentbins];
TGraphErrors * gN1MCp22SUB3_eta[ncentbins];
TGraphErrors * gN1SUB3_eta[ncentbins];

TH1D * hN1SUB2_pt[ncentbins];
TH1D * hN1SUB3_pt[ncentbins];
TH1D * hN1MCm22SUB2_pt[ncentbins];
TH1D * hN1MCp22SUB2_pt[ncentbins];
TH1D * hN1MCm22SUB3_pt[ncentbins];
TH1D * hN1MCp22SUB3_pt[ncentbins];
TH1D * hN1MC22SUB2_pt[ncentbins];
TH1D * hN1MC22SUB3_pt[ncentbins];

TH1D * hN1SUB2_eta[ncentbins];
TH1D * hN1SUB3_eta[ncentbins];
TH1D * hN1MCm22SUB2_eta[ncentbins];
TH1D * hN1MCp22SUB2_eta[ncentbins];
TH1D * hN1MCm22SUB3_eta[ncentbins];
TH1D * hN1MCp22SUB3_eta[ncentbins];
TH1D * hN1MC22SUB2_eta[ncentbins];
TH1D * hN1MC22SUB3_eta[ncentbins];


TFile * tfin;
TFile * tfout;

TDirectory * tdir;

bool isNominal = true;
bool istight = false;
bool isWide = false;
bool isNarrow = false;

void GetDists( TString input = "MH" )
{
    isNominal = true;
    istight = false;
    isWide = false;
    isNarrow = false;
    if (input.Contains("tight")) istight = true;
    if (input.Contains("wide")) isWide = true;
    if (input.Contains("narrow")) isNarrow = true;
    if (istight) {
        tfin = new TFile("hists/MH_tight_hists.root","read");
        tdir = (TDirectory *) tfout->mkdir("MH_tight");
    } else if (isWide) {
        tfin = new TFile("hists/MH_wide_hists.root","read");
        tdir = (TDirectory *) tfout->mkdir("MH_wide");
    } else if (isNarrow) {
        tfin = new TFile("hists/MH_narrow_hists.root","read");
        tdir = (TDirectory *) tfout->mkdir("MH_narrow");
    } else {
        tfin = new TFile("hists/MH_hists.root","read");
        tdir = (TDirectory *) tfout->mkdir("MH_nominal");
    }

    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TString mtag = Form("%d_%d",cminCENT[cbin],cmaxCENT[cbin]);
        gN1SUB2_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1SUB2/0_20/%s/g",mtag.Data()));
        gN1SUB3_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1SUB3/0_20/%s/g",mtag.Data()));
        gN1MCm22SUB2_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCm22SUB2/4_24/%s/gA",mtag.Data()));
        gN1MCp22SUB2_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCp22SUB2/-24_-4/%s/gA",mtag.Data()));
        gN1MCm22SUB3_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCm22SUB3/4_24/%s/gA",mtag.Data()));
        gN1MCp22SUB3_pt[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCp22SUB2/-24_-4/%s/gA",mtag.Data()));

        gN1SUB2_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1SUB2/-24_24/%s/sum_N1SUB2",mtag.Data()));
        gN1SUB3_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1SUB3/-24_24/%s/sum_N1SUB3",mtag.Data()));
        gN1MCm22SUB2_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCm22SUB2/4_24/%s/A_N1MCm22SUB2",mtag.Data()));
        gN1MCp22SUB2_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCp22SUB2/-24_-4/%s/A_N1MCp22SUB2",mtag.Data()));
        gN1MCm22SUB3_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCm22SUB3/4_24/%s/A_N1MCm22SUB3",mtag.Data()));
        gN1MCp22SUB3_eta[cbin] = (TGraphErrors *) tfin->Get(Form("N1MCp22SUB2/-24_-4/%s/A_N1MCp22SUB2",mtag.Data()));
    }

    if (istight) cout << "Accessing hists/MH_tight_hists.root... " << endl;
    else if (isWide) cout << "Accessing hists/MH_wide_hists.root... " << endl;
    else if (isNarrow) cout << "Accessing hists/MH_narrow_hists.root... " << endl;
    else cout << "Accessing hists/MH_hists.root... " << endl;

    for (int cbin = 0; cbin<ncentbins; cbin++) {
        TDirectory * tdcbin = (TDirectory *) tdir->mkdir(Form("%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        tdcbin->cd();

        hN1SUB2_eta[cbin] = new TH1D(Form("hN1SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]), "", netabins, etabins);
        hN1SUB2_eta[cbin]->SetStats(0);
        hN1SUB2_eta[cbin]->SetXTitle("#eta");
        hN1SUB2_eta[cbin]->SetYTitle("v_{1}");

        hN1SUB3_eta[cbin] = (TH1D *) hN1SUB2_eta[cbin]->Clone(Form("hN1SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCm22SUB2_eta[cbin] = (TH1D *) hN1SUB2_eta[cbin]->Clone(Form("hN1MCm22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCp22SUB2_eta[cbin] = (TH1D *) hN1SUB2_eta[cbin]->Clone(Form("hN1MCp22SUB2_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCm22SUB3_eta[cbin] = (TH1D *) hN1SUB2_eta[cbin]->Clone(Form("hN1MCm22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCp22SUB3_eta[cbin] = (TH1D *) hN1SUB2_eta[cbin]->Clone(Form("hN1MCp22SUB3_eta_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));

        hN1SUB2_pt[cbin] = new TH1D(Form("hN1SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]), "", nptbins, ptbins);
        hN1SUB2_pt[cbin]->SetStats(0);
        hN1SUB2_pt[cbin]->SetXTitle("p_{T} (GeV/c)");
        hN1SUB2_pt[cbin]->SetYTitle("v_{1}");

        hN1SUB3_pt[cbin] = (TH1D *) hN1SUB2_pt[cbin]->Clone(Form("hN1SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCm22SUB2_pt[cbin] = (TH1D *) hN1SUB2_pt[cbin]->Clone(Form("hN1MCm22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCp22SUB2_pt[cbin] = (TH1D *) hN1SUB2_pt[cbin]->Clone(Form("hN1MCp22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCm22SUB3_pt[cbin] = (TH1D *) hN1SUB2_pt[cbin]->Clone(Form("hN1MCm22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));
        hN1MCp22SUB3_pt[cbin] = (TH1D *) hN1SUB2_pt[cbin]->Clone(Form("hN1MCp22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]));


        // convert TGraphErrors to TH1Ds
        GraphToHist( gN1SUB2_pt[cbin], hN1SUB2_pt[cbin] );
        GraphToHist( gN1SUB3_pt[cbin], hN1SUB3_pt[cbin] );
        GraphToHist( gN1MCm22SUB2_pt[cbin], hN1MCm22SUB2_pt[cbin] );
        GraphToHist( gN1MCp22SUB2_pt[cbin], hN1MCp22SUB2_pt[cbin] );
        GraphToHist( gN1MCm22SUB3_pt[cbin], hN1MCm22SUB3_pt[cbin] );
        GraphToHist( gN1MCp22SUB3_pt[cbin], hN1MCp22SUB3_pt[cbin] );

        GraphToHist( gN1SUB2_eta[cbin], hN1SUB2_eta[cbin] );
        GraphToHist( gN1SUB3_eta[cbin], hN1SUB3_eta[cbin] );
        GraphToHist( gN1MCm22SUB2_eta[cbin], hN1MCm22SUB2_eta[cbin] );
        GraphToHist( gN1MCp22SUB2_eta[cbin] , hN1MCp22SUB2_eta[cbin] );
        GraphToHist( gN1MCm22SUB3_eta[cbin], hN1MCm22SUB3_eta[cbin] );
        GraphToHist( gN1MCp22SUB3_eta[cbin], hN1MCp22SUB3_eta[cbin] );


        // combine sides of eta for N1MC measurement
        hN1MC22SUB2_pt[cbin] = new TH1D(Form("N1MC22SUB2_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]), "", netabins, etabins);
        hN1MC22SUB3_pt[cbin] = new TH1D(Form("N1MC22SUB3_pt_%d_%d",cminCENT[cbin],cmaxCENT[cbin]), "", netabins, etabins);



        // write histograms to output file
        hN1SUB2_pt[cbin]->Write();
        hN1SUB3_pt[cbin]->Write();
        hN1MCm22SUB2_pt[cbin]->Write();
        hN1MCp22SUB2_pt[cbin]->Write();
        hN1MCm22SUB3_pt[cbin]->Write();
        hN1MCp22SUB3_pt[cbin]->Write();

        hN1SUB2_eta[cbin]->Write();
        hN1SUB3_eta[cbin]->Write();
        hN1MCm22SUB2_eta[cbin]->Write();
        hN1MCp22SUB2_eta[cbin]->Write();
        hN1MCm22SUB3_eta[cbin]->Write();
        hN1MCp22SUB3_eta[cbin]->Write();


        // clean up histograms
        hN1SUB2_pt[cbin]->Delete();
        hN1SUB3_pt[cbin]->Delete();
        hN1MCm22SUB2_pt[cbin]->Delete();
        hN1MCp22SUB2_pt[cbin]->Delete();
        hN1MCm22SUB3_pt[cbin]->Delete();
        hN1MCp22SUB3_pt[cbin]->Delete();

        hN1SUB2_eta[cbin]->Delete();
        hN1SUB3_eta[cbin]->Delete();
        hN1MCm22SUB2_eta[cbin]->Delete();
        hN1MCp22SUB2_eta[cbin]->Delete();
        hN1MCm22SUB3_eta[cbin]->Delete();
        hN1MCp22SUB3_eta[cbin]->Delete();
    }

    tfin->Close();

}

void combine() {

    TH1::SetDefaultSumw2();
    cout << "Combining eta distributions from source files... " << endl;

    tfout = new TFile("hists/MH_combined.root","recreate");

    GetDists( "MH_hists" );
    GetDists( "MH_tight_hists" );
    GetDists( "MH_wide_hists" );
    GetDists( "MH_narrow_hists" );

    cout << "Distributions saved to hists/MH_combined.root \n" << endl;
    //tfout->Close();

}
