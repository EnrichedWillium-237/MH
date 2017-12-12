# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

# include "style.h"

using namespace std;

static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,
                     0.4,  0.8,  1.2,  1.6, 2.0,  2.4};
static const int ncentbins = 11;
static const int centBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const double centRefBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const int ncbins = 14;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 30,  50};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 30, 50, 100};
static const int nanals = 22;
enum AnalType {
    N1MCm22SUB3, N1MCm18SUB3, N1MCm14SUB3, N1MCm10SUB3, N1MCm06SUB3, N1MCm02SUB3,
    N1MCp22SUB3, N1MCp18SUB3, N1MCp14SUB3, N1MCp10SUB3, N1MCp06SUB3, N1MCp02SUB3,
    N112ASUB2,   N112ASUB3,   N123ASUB2,   N123ASUB3,   N1SUB2,      N1SUB3,
    N2SUB2,      N2SUB3,      N3SUB2,      N3SUB3,      LAST};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCm18SUB3", "N1MCm14SUB3", "N1MCm10SUB3", "N1MCm06SUB3", "N1MCm02SUB3",
    "N1MCp22SUB3", "N1MCp18SUB3", "N1MCp14SUB3", "N1MCp10SUB3", "N1MCp06SUB3", "N1MCp02SUB3",
    "N112ASUB2",   "N112ASUB3",   "N123ASUB2",   "N123ASUB3",   "N1SUB2",      "N1SUB3",
    "N2SUB2",      "N2SUB3",      "N3SUB2",      "N3SUB3",      "LAST"};

using namespace std;

TFile * tfinNew;
TH2D * qxtrk1;
TH2D * qytrk1;
TH2D * qxtrk2;
TH2D * qytrk2;
TH2D * qcnt;

TFile * tfinOld;
TH2D * qxav1;
TH2D * qyav1;
TH2D * qxycnt;

TH2D * qnA;
TH2D * qnB;
TH2D * qnAB;
TH2D * wnA;
TH2D * wnB;

TH1D * v1A;
TH1D * v1B;
TH1D * v1AB;
TH1D * w1A;
TH1D * w1B;

void checkQtrks()
{

    TH2::SetDefaultSumw2();

    tfinNew = new TFile("../../MH.root","read");

    qxtrk1 = (TH2D *) tfinNew->Get("vnanalyzer/qxtrk1");
    qytrk1 = (TH2D *) tfinNew->Get("vnanalyzer/qytrk1");
    qxtrk2 = (TH2D *) tfinNew->Get("vnanalyzer/qxtrk2");
    qytrk2 = (TH2D *) tfinNew->Get("vnanalyzer/qytrk2");
    qcnt   = (TH2D *) tfinNew->Get("vnanalyzer/qcnt");
    qxtrk1->Divide(qcnt);
    qytrk1->Divide(qcnt);
    qxtrk2->Divide(qcnt);
    qytrk2->Divide(qcnt);

    qnA = (TH2D *) tfinNew->Get("vnanalyzer/Harmonics/35_40/N1/qA");
    qnB = (TH2D *) tfinNew->Get("vnanalyzer/Harmonics/35_40/N1/qB");
    wnA = (TH2D *) tfinNew->Get("vnanalyzer/Harmonics/35_40/N1/wnA");
    wnB = (TH2D *) tfinNew->Get("vnanalyzer/Harmonics/35_40/N1/wnB");
    cout<<qnA->GetXaxis()->FindBin(0.3+0.001)<<"\t"<<qnA->GetXaxis()->FindBin(3.0-0.001)<<endl;
    cout<<qnA->GetXaxis()->GetBinCenter(qnA->GetXaxis()->FindBin(0.3))<<"\t"<<qnA->GetXaxis()->GetBinCenter(qnA->GetXaxis()->FindBin(3.0-0.001))<<endl;

    tfinOld = new TFile("../../../GenerateV1/outputs/raw_outputs/results/v1SP_mid.root");
    qxav1 = (TH2D *) tfinOld->Get("30-40/qxav1_3");
    qyav1 = (TH2D *) tfinOld->Get("30-40/qyav1_3");
    qxycnt = (TH2D *) tfinOld->Get("30-40/qxycnt_3");
    qxav1->Divide(qxycnt);
    qyav1->Divide(qxycnt);


    v1A = (TH1D *) qnA->ProjectionY("v1A",qnA->GetXaxis()->FindBin(0.3),qnA->GetXaxis()->FindBin(3.0));
    v1B = (TH1D *) qnB->ProjectionY("v1B",qnB->GetXaxis()->FindBin(0.3),qnA->GetXaxis()->FindBin(3.0));
    w1A = (TH1D *) wnA->ProjectionY("w1A",wnA->GetXaxis()->FindBin(0.3),qnA->GetXaxis()->FindBin(3.0));
    w1B = (TH1D *) wnB->ProjectionY("w1B",wnB->GetXaxis()->FindBin(0.3),qnA->GetXaxis()->FindBin(3.0));
    v1A->Divide(w1A);
    v1B->Divide(w1B);
    v1AB = (TH1D *) v1A->Clone("v1AB");
    v1AB->Divide(v1B);
    v1AB->Scale(0.5);



    TCanvas * cqxtrk1 = new TCanvas("cqxtrk1","cqxtrk1",800,600);
    TPad * padqxtrk1 = (TPad *) cqxtrk1->cd();
    qxtrk1->SetXTitle("p_{T} (GeV/c)");
    qxtrk1->SetYTitle("#eta {qxtrk1}");
    qxtrk1->GetYaxis()->SetTitleOffset(1.00);
    qxtrk1->GetXaxis()->SetRangeUser(0.301, 12);
    padqxtrk1->SetRightMargin(0.15);
    qxtrk1->Draw("colz");
    cqxtrk1->Print("qxtrk1.png","png");


    TCanvas * cqytrk1 = new TCanvas("cqytrk1","cqytrk1",800,600);
    TPad * padqytrk1 = (TPad *) cqytrk1->cd();
    qytrk1->SetXTitle("p_{T} (GeV/c)");
    qytrk1->SetYTitle("#eta {qytrk1}");
    qytrk1->GetYaxis()->SetTitleOffset(1.00);
    qytrk1->GetXaxis()->SetRangeUser(0.301, 12);
    padqytrk1->SetRightMargin(0.15);
    qytrk1->Draw("colz");
    cqytrk1->Print("qytrk1.png","png");


    TCanvas * cqxtrk2 = new TCanvas("cqxtrk2","cqxtrk2",800,600);
    TPad * padqxtrk2 = (TPad *) cqxtrk2->cd();
    qxtrk2->SetXTitle("p_{T} (GeV/c)");
    qxtrk2->SetYTitle("#eta {qxtrk2}");
    qxtrk2->GetYaxis()->SetTitleOffset(1.00);
    qxtrk2->GetXaxis()->SetRangeUser(0.301, 12);
    padqxtrk2->SetRightMargin(0.15);
    qxtrk2->Draw("colz");
    cqxtrk2->Print("qxtrk2.png","png");


    TCanvas * cqytrk2 = new TCanvas("cqytrk2","cqytrk2",800,600);
    TPad * padqytrk2 = (TPad *) cqytrk2->cd();
    qytrk2->SetXTitle("p_{T} (GeV/c)");
    qytrk2->SetYTitle("#eta {qytrk2}");
    qytrk2->GetYaxis()->SetTitleOffset(1.00);
    qytrk2->GetXaxis()->SetRangeUser(0.301, 12);
    padqytrk2->SetRightMargin(0.15);
    qytrk2->Draw("colz");
    cqytrk2->Print("qytrk2.png","png");


    TCanvas * cqxav1 = new TCanvas("cqxav1","cqxav1",800,600);
    TPad * padqxav1 = (TPad *) cqxav1->cd();
    qxav1->SetXTitle("p_{T} (GeV/c)");
    qxav1->SetYTitle("#eta {qxtrk1}");
    qxav1->GetYaxis()->SetTitleOffset(1.00);
    qxav1->GetXaxis()->SetRangeUser(0.301, 12);
    padqxav1->SetRightMargin(0.15);
    qxav1->Draw("colz");
    cqxav1->Print("qxav1.png","png");


    TCanvas * cqyav1 = new TCanvas("cqyav1","cqyav1",800,600);
    TPad * padqyav1 = (TPad *) cqyav1->cd();
    qyav1->SetXTitle("p_{T} (GeV/c)");
    qyav1->SetYTitle("#eta {qytrk1}");
    qyav1->GetYaxis()->SetTitleOffset(1.00);
    qyav1->GetXaxis()->SetRangeUser(0.301, 12);
    padqyav1->SetRightMargin(0.15);
    qyav1->Draw("colz");
    cqyav1->Print("qyav1.png","png");


}
