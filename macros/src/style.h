// style.h
// little plotting classes to make Will's life easier

# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLegend.h"
# include "TPaveText.h"

// void bug() {
//     cout << " !!! " << __LINE__ << " !!! " << endl;
// }
// need to work on this one some more

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

void GraphToHist( TGraphErrors * gin, TH1D * hout ) {
    int num = gin->GetN();
    Double_t x[400], y[400], yerr[400];
    for (int i = 0; i<num; i++) {
        gin->GetPoint(i, x[i], y[i]);
        yerr[i] = gin->GetErrorY(i);
        hout->SetBinContent(i+1, y[i]);
        hout->SetBinError(i+1, yerr[i]);
    }
}

// propagate errors of ratios for partially correlated uncertainties
double ErrRatCalc( double x, double y, double delx, double dely ) {
    double f = x;
    f/=y;
    double delf = f*sqrt( pow(delx/x,2) + pow(dely/y,2) - 2*(delx/x)*(dely/y) );
    return delf;
}

// propagate errors of differences for partially correlated uncertainties
double ErrDiffCalc( double x, double y, double delx, double dely ) {
    double f = x;
    f-=y;
    double delf = sqrt( fabs(delx*delx - dely*dely) );
    return delf;
}
