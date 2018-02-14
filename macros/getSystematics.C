# include "TDirectory.h"
# include "TFile.h"
# include "TH1.h"
# include <iostream>

using namespace std;



TFile * fout;

void getSystematics() {

    fout = new TFile("data_systematics.root","recreate");

}
