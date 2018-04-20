# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TGaxis.h"
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

double N1HFgSUB2_loose[] = {-0.00015, -0.00017, -0.00021, -0.00020, -0.00018, -0.00028, -0.00029, -0.00032, -0.00031, -0.00044, -0.00075, -0.00017, -0.00025};
double N1HFgSUB2_loose_err[] = {0.00003, 0.00003, 0.00003, 0.00005, 0.00004, 0.00004, 0.00006, 0.00005, 0.00004, 0.00012, 0.00011, 0.00002, 0.00002};

double N1HFgSUB2_tight[] = {0.00016, 0.00018, 0.00015, 0.00019, 0.00022, 0.00023, 0.00024, 0.00031, 0.00032, 0.00042, 0.00058, 0.00016, 0.00023};
double N1HFgSUB2_tight_err[] = {0.00003, 0.00003, 0.00003, 0.00004, 0.00003, 0.00006, 0.00006, 0.00009, 0.00006, 0.00010, 0.00014, 0.00002, 0.00004};

double N1HFgSUB2_wide[] = {0.00016, 0.00018, 0.00015, 0.00019, 0.00022, 0.00023, 0.00024, 0.00031, 0.00032, 0.00042, 0.00058, 0.00016, 0.00023};
double N1HFgSUB2_wide_err[] = {0.00003, 0.00003, 0.00003, 0.00004, 0.00003, 0.00006, 0.00006, 0.00009, 0.00006, 0.00010, 0.00014, 0.00002, 0.00004};

double N1HFgSUB2_narrow[] = {-0.00012, -0.00010, -0.00002, -0.00015, 0.00001, -0.00020, 0.00010, -0.00029, 0.00023, -0.00005, -0.00051, -0.00008, -0.00003};
double N1HFgSUB2_narrow_err[] = {0.00018, 0.00021, 0.00023, 0.00027, 0.00028, 0.00033, 0.00036, 0.00044, 0.00040, 0.00061, 0.00089, 0.00012, 0.00017};



double N1HFgSUB2_pt_loose[] = {-0.00002, -0.00003, 0.00011, -0.00004, 0.00005, -0.00011, -0.00005, -0.00029, -0.00003, -0.00005, 0.00011, 0.00001, 0.00001};
double N1HFgSUB2_pt_loose_err[] = {0.00004, 0.00012, 0.00009, 0.00007, 0.00010, 0.00003, 0.00011, 0.00008, 0.00009, 0.00018, 0.00008, 0.00004, 0.00005};

double N1HFgSUB2_pt_tight[] = {-0.00001, -0.00004, 0.00010, -0.00003, 0.00015, 0.00001, -0.00006, -0.00013, 0.00004, -0.00002, 0.00006, 0.00002, 0.00002};
double N1HFgSUB2_pt_tight_err[] = {0.00010, 0.00007, 0.00007, 0.00010, 0.00009, 0.00010, 0.00009, 0.00012, 0.00012, 0.00012, 0.00014, 0.00004, 0.00004};

double N1HFgSUB2_pt_wide[] = {-0.00001, -0.00004, 0.00010, -0.00003, 0.00015, 0.00001, -0.00006, -0.00013, 0.00004, -0.00002, 0.00006, 0.00002, 0.00002};
double N1HFgSUB2_pt_wide_err[] = {0.00010, 0.00007, 0.00007, 0.00010, 0.00009, 0.00010, 0.00009, 0.00012, 0.00012, 0.00012, 0.00014, 0.00004, 0.00004};

double N1HFgSUB2_pt_narrow[] = {0.00079, 0.00048, -0.00033, -0.00071, 0.00024, -0.00043, -0.00066, -0.00075, -0.00025, -0.00038, -0.00147, 0.00025, -0.00019};
double N1HFgSUB2_pt_narrow_err[] = {0.00013, 0.00026, 0.00027, 0.00034, 0.00032, 0.00046, 0.00038, 0.00064, 0.00045, 0.00054, 0.00087, 0.00017, 0.00019};


double N1EVENSUB2_loose[] = {0.00068, 0.00080, 0.00075, 0.00104, 0.00116, 0.00103, 0.00107, 0.00130, 0.00121, 0.00200, 0.00279, 0.00089, 0.00116};
double N1EVENSUB2_loose_err[] = {0.00004, 0.00005, 0.00003, 0.00001, 0.00007, 0.00007, 0.00010, 0.00013, 0.00008, 0.00021, 0.00076, 0.00003, 0.00004};

double N1EVENSUB2_tight[] = {-0.00056, -0.00075, -0.00079, -0.00097, -0.00100, -0.00108, -0.00110, -0.00121, -0.00120, -0.00141, -0.00144, -0.00063, -0.00111};
double N1EVENSUB2_tight_err[] = {0.00004, 0.00003, 0.00007, 0.00008, 0.00010, 0.00010, 0.00014, 0.00014, 0.00015, 0.00028, 0.00087, 0.00002, 0.00005};

double N1EVENSUB2_wide[] = {-0.00056, -0.00075, -0.00079, -0.00097, -0.00100, -0.00108, -0.00110, -0.00121, -0.00120, -0.00141, -0.00144, -0.00063, -0.00111};
double N1EVENSUB2_wide_err[] = {0.00004, 0.00003, 0.00007, 0.00008, 0.00010, 0.00010, 0.00014, 0.00014, 0.00015, 0.00028, 0.00087, 0.00002, 0.00005};

double N1EVENSUB2_narrow[] = {0.00119, 0.00077, 0.00103, 0.00095, 0.00050, 0.00052, 0.00073, 0.00047, 0.00019, 0.00107, 0.00150, 0.00104, 0.00048};
double N1EVENSUB2_narrow_err[] = {0.00032, 0.00031, 0.00034, 0.00038, 0.00044, 0.00052, 0.00061, 0.00069, 0.00069, 0.00184, 0.00558, 0.00017, 0.00024};


double N1EVENSUB2_pt_loose[] = {0.00006, 0.00000, -0.00010, 0.00001, -0.00015, 0.00005, -0.00007, 0.00011, 0.00030, -0.00022, 0.00149, -0.00005, -0.00001};
double N1EVENSUB2_pt_loose_err[] = {0.00004, 0.00011, 0.00007, 0.00007, 0.00010, 0.00007, 0.00012, 0.00012, 0.00022, 0.00037, 0.00110, 0.00006, 0.00008};

double N1EVENSUB2_pt_tight[] = {0.00007, -0.00010, -0.00009, 0.00000, -0.00003, -0.00002, -0.00005, -0.00019, 0.00001, -0.00027, 0.00102, -0.00005, -0.00006};
double N1EVENSUB2_pt_tight_err[] = {0.00003, 0.00007, 0.00009, 0.00009, 0.00011, 0.00011, 0.00018, 0.00016, 0.00006, 0.00044, 0.00083, 0.00005, 0.00005};

double N1EVENSUB2_pt_wide[] = {0.00007, -0.00010, -0.00009, 0.00000, -0.00003, -0.00002, -0.00005, -0.00019, 0.00001, -0.00027, 0.00102, -0.00005, -0.00006};
double N1EVENSUB2_pt_wide_err[] = {0.00003, 0.00007, 0.00009, 0.00009, 0.00011, 0.00011, 0.00018, 0.00016, 0.00006, 0.00044, 0.00083, 0.00005, 0.00005};

double N1EVENSUB2_pt_narrow[] = {0.00034, 0.00020, 0.00058, 0.00124, 0.00084, -0.00012, -0.00011, 0.00098, 0.00108, 0.00099, -0.00590, 0.00044, 0.00036};
double N1EVENSUB2_pt_narrow_err[] = {0.00027, 0.00021, 0.00029, 0.00031, 0.00031, 0.00043, 0.00050, 0.00041, 0.00057, 0.00182, 0.00645, 0.00013, 0.00016};

TGraphErrors * gN1HFgSUB2_loose;
TGraphErrors * gN1HFgSUB2_tight;
TGraphErrors * gN1HFgSUB2_wide;
TGraphErrors * gN1HFgSUB2_narrow;

TGraphErrors * gN1HFgSUB2_pt_loose;
TGraphErrors * gN1HFgSUB2_pt_tight;
TGraphErrors * gN1HFgSUB2_pt_wide;
TGraphErrors * gN1HFgSUB2_pt_narrow;

TGraphErrors * gN1EVENSUB2_loose;
TGraphErrors * gN1EVENSUB2_tight;
TGraphErrors * gN1EVENSUB2_wide;
TGraphErrors * gN1EVENSUB2_narrow;

TGraphErrors * gN1EVENSUB2_pt_loose;
TGraphErrors * gN1EVENSUB2_pt_tight;
TGraphErrors * gN1EVENSUB2_pt_wide;
TGraphErrors * gN1EVENSUB2_pt_narrow;

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

void fig_syst_fits() {

    double xval[] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 45, 55, 65};

    for (int i = 0; i<ncbins; i++) {
        if (N1HFgSUB2_loose[i]<0) N1HFgSUB2_loose[i]*=-1.;
        if (N1HFgSUB2_tight[i]<0) N1HFgSUB2_tight[i]*=-1.;
        if (N1HFgSUB2_wide[i]<0) N1HFgSUB2_wide[i]*=-1.;
        if (N1HFgSUB2_narrow[i]<0) N1HFgSUB2_narrow[i]*=-1.;
        if (N1HFgSUB2_pt_loose[i]<0) N1HFgSUB2_pt_loose[i]*=-1.;
        if (N1HFgSUB2_pt_tight[i]<0) N1HFgSUB2_pt_tight[i]*=-1.;
        if (N1HFgSUB2_pt_wide[i]<0) N1HFgSUB2_pt_wide[i]*=-1.;
        if (N1HFgSUB2_pt_narrow[i]<0) N1HFgSUB2_pt_narrow[i]*=-1.;
        if (N1EVENSUB2_loose[i]<0) N1EVENSUB2_loose[i]*=-1.;
        if (N1EVENSUB2_tight[i]<0) N1EVENSUB2_tight[i]*=-1.;
        if (N1EVENSUB2_wide[i]<0) N1EVENSUB2_wide[i]*=-1.;
        if (N1EVENSUB2_narrow[i]<0) N1EVENSUB2_narrow[i]*=-1.;
        if (N1EVENSUB2_pt_loose[i]<0) N1EVENSUB2_pt_loose[i]*=-1.;
        if (N1EVENSUB2_pt_tight[i]<0) N1EVENSUB2_pt_tight[i]*=-1.;
        if (N1EVENSUB2_pt_wide[i]<0) N1EVENSUB2_pt_wide[i]*=-1.;
        if (N1EVENSUB2_pt_narrow[i]<0) N1EVENSUB2_pt_narrow[i]*=-1.;
    }


    gN1HFgSUB2_loose = new TGraphErrors(11, xval, N1HFgSUB2_loose, 0, N1HFgSUB2_loose_err);
    gN1HFgSUB2_tight = new TGraphErrors(11, xval, N1HFgSUB2_tight, 0, N1HFgSUB2_tight_err);
    gN1HFgSUB2_wide = new TGraphErrors(11, xval, N1HFgSUB2_wide, 0, N1HFgSUB2_wide_err);
    gN1HFgSUB2_narrow = new TGraphErrors(11, xval, N1HFgSUB2_narrow, 0, N1HFgSUB2_narrow_err);

    gN1HFgSUB2_pt_loose = new TGraphErrors(11, xval, N1HFgSUB2_pt_loose, 0, N1HFgSUB2_pt_loose_err);
    gN1HFgSUB2_pt_tight = new TGraphErrors(11, xval, N1HFgSUB2_pt_tight, 0, N1HFgSUB2_pt_tight_err);
    gN1HFgSUB2_pt_wide = new TGraphErrors(11, xval, N1HFgSUB2_pt_wide, 0, N1HFgSUB2_pt_wide_err);
    gN1HFgSUB2_pt_narrow = new TGraphErrors(11, xval, N1HFgSUB2_pt_narrow, 0, N1HFgSUB2_pt_narrow_err);

    gN1EVENSUB2_loose = new TGraphErrors(11, xval, N1EVENSUB2_loose, 0, N1EVENSUB2_loose_err);
    gN1EVENSUB2_tight = new TGraphErrors(11, xval, N1EVENSUB2_tight, 0, N1EVENSUB2_tight_err);
    gN1EVENSUB2_wide = new TGraphErrors(11, xval, N1EVENSUB2_wide, 0, N1EVENSUB2_wide_err);
    gN1EVENSUB2_narrow = new TGraphErrors(11, xval, N1EVENSUB2_narrow, 0, N1EVENSUB2_narrow_err);

    gN1EVENSUB2_pt_loose = new TGraphErrors(11, xval, N1EVENSUB2_pt_loose, 0, N1EVENSUB2_pt_loose_err);
    gN1EVENSUB2_pt_tight = new TGraphErrors(11, xval, N1EVENSUB2_pt_tight, 0, N1EVENSUB2_pt_tight_err);
    gN1EVENSUB2_pt_wide = new TGraphErrors(11, xval, N1EVENSUB2_pt_wide, 0, N1EVENSUB2_pt_wide_err);
    gN1EVENSUB2_pt_narrow = new TGraphErrors(11, xval, N1EVENSUB2_pt_narrow, 0, N1EVENSUB2_pt_narrow_err);


    gN1HFgSUB2_loose->SetMarkerStyle(20);
    gN1HFgSUB2_loose->SetMarkerSize(1.3);
    gN1HFgSUB2_loose->SetMarkerColor(kBlue);
    gN1HFgSUB2_loose->SetLineColor(kBlue);

    gN1HFgSUB2_tight->SetMarkerStyle(25);
    gN1HFgSUB2_tight->SetMarkerSize(1.2);
    gN1HFgSUB2_tight->SetMarkerColor(kGreen+2);
    gN1HFgSUB2_tight->SetLineColor(kGreen+2);

    gN1HFgSUB2_wide->SetMarkerStyle(20);
    gN1HFgSUB2_wide->SetMarkerSize(1.3);
    gN1HFgSUB2_wide->SetMarkerColor(kBlue);
    gN1HFgSUB2_wide->SetLineColor(kBlue);

    gN1HFgSUB2_narrow->SetMarkerStyle(25);
    gN1HFgSUB2_narrow->SetMarkerSize(1.2);
    gN1HFgSUB2_narrow->SetMarkerColor(kGreen+2);
    gN1HFgSUB2_narrow->SetLineColor(kGreen+2);


    gN1HFgSUB2_pt_loose->SetMarkerStyle(20);
    gN1HFgSUB2_pt_loose->SetMarkerSize(1.3);
    gN1HFgSUB2_pt_loose->SetMarkerColor(kBlue);
    gN1HFgSUB2_pt_loose->SetLineColor(kBlue);

    gN1HFgSUB2_pt_tight->SetMarkerStyle(25);
    gN1HFgSUB2_pt_tight->SetMarkerSize(1.2);
    gN1HFgSUB2_pt_tight->SetMarkerColor(kGreen+2);
    gN1HFgSUB2_pt_tight->SetLineColor(kGreen+2);

    gN1HFgSUB2_pt_wide->SetMarkerStyle(20);
    gN1HFgSUB2_pt_wide->SetMarkerSize(1.3);
    gN1HFgSUB2_pt_wide->SetMarkerColor(kBlue);
    gN1HFgSUB2_pt_wide->SetLineColor(kBlue);

    gN1HFgSUB2_pt_narrow->SetMarkerStyle(25);
    gN1HFgSUB2_pt_narrow->SetMarkerSize(1.2);
    gN1HFgSUB2_pt_narrow->SetMarkerColor(kGreen+2);
    gN1HFgSUB2_pt_narrow->SetLineColor(kGreen+2);


    gN1EVENSUB2_loose->SetMarkerStyle(20);
    gN1EVENSUB2_loose->SetMarkerSize(1.3);
    gN1EVENSUB2_loose->SetMarkerColor(kBlue);
    gN1EVENSUB2_loose->SetLineColor(kBlue);

    gN1EVENSUB2_tight->SetMarkerStyle(25);
    gN1EVENSUB2_tight->SetMarkerSize(1.2);
    gN1EVENSUB2_tight->SetMarkerColor(kGreen+2);
    gN1EVENSUB2_tight->SetLineColor(kGreen+2);

    gN1EVENSUB2_wide->SetMarkerStyle(20);
    gN1EVENSUB2_wide->SetMarkerSize(1.3);
    gN1EVENSUB2_wide->SetMarkerColor(kBlue);
    gN1EVENSUB2_wide->SetLineColor(kBlue);

    gN1EVENSUB2_narrow->SetMarkerStyle(25);
    gN1EVENSUB2_narrow->SetMarkerSize(1.2);
    gN1EVENSUB2_narrow->SetMarkerColor(kGreen+2);
    gN1EVENSUB2_narrow->SetLineColor(kGreen+2);


    gN1EVENSUB2_pt_loose->SetMarkerStyle(20);
    gN1EVENSUB2_pt_loose->SetMarkerSize(1.3);
    gN1EVENSUB2_pt_loose->SetMarkerColor(kBlue);
    gN1EVENSUB2_pt_loose->SetLineColor(kBlue);

    gN1EVENSUB2_pt_tight->SetMarkerStyle(25);
    gN1EVENSUB2_pt_tight->SetMarkerSize(1.2);
    gN1EVENSUB2_pt_tight->SetMarkerColor(kGreen+2);
    gN1EVENSUB2_pt_tight->SetLineColor(kGreen+2);

    gN1EVENSUB2_pt_wide->SetMarkerStyle(20);
    gN1EVENSUB2_pt_wide->SetMarkerSize(1.3);
    gN1EVENSUB2_pt_wide->SetMarkerColor(kBlue);
    gN1EVENSUB2_pt_wide->SetLineColor(kBlue);

    gN1EVENSUB2_pt_narrow->SetMarkerStyle(25);
    gN1EVENSUB2_pt_narrow->SetMarkerSize(1.2);
    gN1EVENSUB2_pt_narrow->SetMarkerColor(kGreen+2);
    gN1EVENSUB2_pt_narrow->SetLineColor(kGreen+2);


    TCanvas * c0 = new TCanvas("c0", "c0", 1000, 600);
    c0->Divide(2,1,0,0);
    TPad * pad0_1 = (TPad *) c0->cd(1);
    pad0_1->SetTopMargin(0.05);
    TH1D * h0 = new TH1D("h0", "", 200, 0, 79);
    h0->GetYaxis()->SetRangeUser(-0.0006, 0.0016);
    h0->GetYaxis()->SetNdivisions(508);
    h0->GetYaxis()->SetDecimals();
    h0->SetXTitle("Centrality (%)");
    h0->SetYTitle("|v_{1}^{odd}(#eta)  pol1 fit|");
    h0->GetXaxis()->SetTitleOffset(1.10);
    h0->GetXaxis()->CenterTitle();
    h0->GetYaxis()->CenterTitle();
    h0->GetYaxis()->SetTitleSize(0.06);
    h0->GetYaxis()->SetTitleOffset(1.4);
    TGaxis::SetMaxDigits(3);
    h0->Draw();
    gN1HFgSUB2_tight->Draw("same p");
    gN1HFgSUB2_loose->Draw("same p");
    TLegend * leg0_0 = new TLegend(0.26, 0.75, 0.47, 0.89);
    SetLegend(leg0_0, 24);
    leg0_0->AddEntry(gN1HFgSUB2_loose, "loose", "p");
    leg0_0->AddEntry(gN1HFgSUB2_tight, "tight", "p");
    leg0_0->Draw();

    TPad * pad0_2 = (TPad *) c0->cd(2);
    pad0_2->SetTopMargin(0.05);
    pad0_2->SetRightMargin(0.02);
    TH1D * h0_2 = (TH1D *) h0->Clone("h0_2");
    h0_2->GetXaxis()->SetRangeUser(0.5, 79);
    h0_2->GetYaxis()->SetLabelSize(0);
    h0_2->GetXaxis()->SetTitleSize(0.07);
    h0_2->GetXaxis()->SetTitleOffset(0.87);
    h0_2->GetXaxis()->SetLabelSize(0.06);
    h0_2->GetXaxis()->SetLabelOffset(0.0);
    h0_2->Draw();
    gN1HFgSUB2_narrow->Draw("same p");
    gN1HFgSUB2_wide->Draw("same p");
    TLegend * leg0_1 = new TLegend(0.06, 0.75, 0.27, 0.89);
    SetLegend(leg0_1, 24);
    leg0_1->AddEntry(gN1HFgSUB2_wide, "wide", "p");
    leg0_1->AddEntry(gN1HFgSUB2_narrow, "narrow", "p");
    leg0_1->Draw();

    c0->Print("../fig_syst_fits_v1odd_eta.pdf","pdf");


    TCanvas * c1 = new TCanvas("c1", "c1", 1000, 600);
    c1->Divide(2,1,0,0);
    TPad * pad1_1 = (TPad *) c1->cd(1);
    pad1_1->SetTopMargin(0.05);
    TH1D * h1 = new TH1D("h1", "", 200, 0, 79);
    h1->GetYaxis()->SetRangeUser(-0.0006, 0.0026);
    h1->GetYaxis()->SetNdivisions(508);
    h1->GetYaxis()->SetDecimals();
    h1->SetXTitle("Centrality (%)");
    h1->SetYTitle("|v_{1}^{odd}(p_{T})  pol0 fit|");
    h1->GetXaxis()->SetTitleOffset(1.10);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetYaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleOffset(1.4);
    TGaxis::SetMaxDigits(3);
    h1->Draw();
    gN1HFgSUB2_pt_tight->Draw("same p");
    gN1HFgSUB2_pt_loose->Draw("same p");
    TLegend * leg1_0 = new TLegend(0.26, 0.75, 0.47, 0.89);
    SetLegend(leg1_0, 24);
    leg1_0->AddEntry(gN1HFgSUB2_pt_loose, "loose", "p");
    leg1_0->AddEntry(gN1HFgSUB2_pt_tight, "tight", "p");
    leg1_0->Draw();

    TPad * pad1_2 = (TPad *) c1->cd(2);
    pad1_2->SetTopMargin(0.05);
    pad1_2->SetRightMargin(0.02);
    TH1D * h1_2 = (TH1D *) h1->Clone("h1_2");
    h1_2->GetXaxis()->SetRangeUser(0.5, 79);
    h1_2->GetYaxis()->SetLabelSize(0);
    h1_2->GetXaxis()->SetTitleSize(0.07);
    h1_2->GetXaxis()->SetTitleOffset(0.87);
    h1_2->GetXaxis()->SetLabelSize(0.06);
    h1_2->GetXaxis()->SetLabelOffset(0.0);
    h1_2->Draw();
    gN1HFgSUB2_pt_narrow->Draw("same p");
    gN1HFgSUB2_pt_wide->Draw("same p");
    TLegend * leg1_1 = new TLegend(0.06, 0.75, 0.27, 0.89);
    SetLegend(leg1_1, 24);
    leg1_1->AddEntry(gN1HFgSUB2_pt_wide, "wide", "p");
    leg1_1->AddEntry(gN1HFgSUB2_pt_narrow, "narrow", "p");
    leg1_1->Draw();

    c1->Print("../fig_syst_fits_v1odd_pt.pdf","pdf");




    TCanvas * c2 = new TCanvas("c2", "c2", 1000, 600);
    c2->Divide(2,1,0,0);
    TPad * pad2_1 = (TPad *) c2->cd(1);
    pad2_1->SetTopMargin(0.05);
    TH1D * h2 = new TH1D("h2", "", 200, 0, 79);
    h2->GetYaxis()->SetRangeUser(-0.0048, 0.0082);
    h2->GetYaxis()->SetNdivisions(508);
    h2->GetYaxis()->SetDecimals();
    h2->SetXTitle("Centrality (%)");
    h2->SetYTitle("|v_{1}^{even}(#eta)  pol0 fit|");
    h2->GetXaxis()->SetTitleOffset(1.10);
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->CenterTitle();
    h2->GetYaxis()->SetTitleSize(0.06);
    h2->GetYaxis()->SetTitleOffset(1.4);
    TGaxis::SetMaxDigits(3);
    h2->Draw();
    gN1EVENSUB2_tight->Draw("same p");
    gN1EVENSUB2_loose->Draw("same p");
    leg0_0->Draw();

    TPad * pad2_2 = (TPad *) c2->cd(2);
    pad2_2->SetTopMargin(0.05);
    pad2_2->SetRightMargin(0.02);
    TH1D * h2_2 = (TH1D *) h2->Clone("h2_2");
    h2_2->GetXaxis()->SetRangeUser(0.5, 79);
    h2_2->GetYaxis()->SetLabelSize(0);
    h2_2->GetXaxis()->SetTitleSize(0.07);
    h2_2->GetXaxis()->SetTitleOffset(0.87);
    h2_2->GetXaxis()->SetLabelSize(0.06);
    h2_2->GetXaxis()->SetLabelOffset(0.0);
    h2_2->Draw();
    gN1EVENSUB2_narrow->Draw("same p");
    gN1EVENSUB2_wide->Draw("same p");
    leg0_1->Draw();

    c2->Print("../fig_syst_fits_v1even_eta.pdf","pdf");


    TCanvas * c3 = new TCanvas("c3", "c3", 1000, 600);
    c3->Divide(2,1,0,0);
    TPad * pad3_1 = (TPad *) c3->cd(1);
    pad3_1->SetTopMargin(0.05);
    TH1D * h3 = new TH1D("h3", "", 200, 0, 79);
    h3->GetYaxis()->SetRangeUser(-0.0011, 0.0032);
    h3->GetYaxis()->SetNdivisions(508);
    h3->GetYaxis()->SetDecimals();
    h3->SetXTitle("Centrality (%)");
    h3->SetYTitle("|v_{1}^{even}(p_{T})  pol0 fit|");
    h3->GetXaxis()->SetTitleOffset(1.10);
    h3->GetXaxis()->CenterTitle();
    h3->GetYaxis()->CenterTitle();
    h3->GetYaxis()->SetTitleSize(0.06);
    h3->GetYaxis()->SetTitleOffset(1.4);
    TGaxis::SetMaxDigits(3);
    h3->Draw();
    gN1EVENSUB2_pt_tight->Draw("same p");
    gN1EVENSUB2_pt_loose->Draw("same p");
    leg1_0->Draw();

    TPad * pad3_2 = (TPad *) c3->cd(2);
    pad3_2->SetTopMargin(0.05);
    pad3_2->SetRightMargin(0.02);
    TH1D * h3_2 = (TH1D *) h3->Clone("h3_2");
    h3_2->GetXaxis()->SetRangeUser(0.5, 79);
    h3_2->GetYaxis()->SetLabelSize(0);
    h3_2->GetXaxis()->SetTitleSize(0.07);
    h3_2->GetXaxis()->SetTitleOffset(0.87);
    h3_2->GetXaxis()->SetLabelSize(0.06);
    h3_2->GetXaxis()->SetLabelOffset(0.0);
    h3_2->Draw();
    gN1EVENSUB2_pt_narrow->Draw("same p");
    gN1EVENSUB2_pt_wide->Draw("same p");
    leg1_1->Draw();

    c3->Print("../fig_syst_fits_v1even_pt.pdf","pdf");

}
