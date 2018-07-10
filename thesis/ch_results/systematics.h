
static const int cminCent[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 20};
static const int cmaxCent[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 20, 60};

// Total systematic uncertainty
// Uncertainty binned in the following: 0 - 30%, 30 - 60%, 60 - 70%, with two extra bins for 20 - 60% and 5 - 80%
// Two sets of pt-dependent systematics: pT0 (pT<3), and pt1 (pT>3)
//

static const double syst_N1HFgSUB3_eta[] = {2.286E-04, 3.735E-04, 6.773E-04,  3.011E-04,  4.265E-04};
static const double syst_N1HFgSUB3_pt0[] = {2.553E-04, 3.692E-04, 5.209E-04,  3.123E-04,  3.818E-04};
static const double syst_N1HFgSUB3_pt1[] = {1.124E-03, 1.915E-03, 3.538E-03,  1.519E-03,  2.192E-03};

static const double syst_N112ASUB3_eta[] = {4.011E-04, 6.163E-04, 1.278E-03,  5.087E-04,  7.650E-04};
static const double syst_N112ASUB3_pt0[] = {5.586E-04, 1.363E-03, 4.210E-03,  9.609E-04,  2.044E-03};
static const double syst_N112ASUB3_pt1[] = {2.850E-03, 4.767E-03, 1.036E-02,  3.808E-03,  5.991E-03};

static const double syst_N1HFgSUB3_decor_eta[] = {2.082E-04, 2.943E-04, 4.986E-04,  2.512E-04,  3.337E-04};
static const double syst_N1HFgSUB3_decor_pt0[] = {6.522E-04, 1.030E-03, 1.169E-03,  8.412E-04,  9.506E-04};
static const double syst_N1HFgSUB3_decor_pt1[] = {2.538E-03, 1.048E-02, 2.533E-02,  6.510E-03,  1.278E-02};

static const double syst_N1EVENSUB3_eta[] = {7.814E-04, 1.145E-03, 2.522E-03,  9.633E-04,  1.483E-03};
static const double syst_N1EVENSUB3_pt0[] = {9.856E-04, 1.313E-03, 6.482E-03,  1.149E-03,  2.927E-03};
static const double syst_N1EVENSUB3_pt1[] = {3.754E-03, 6.552E-03, 1.358E-02,  5.153E-03,  7.963E-03};

static const double syst_N1EVENSUB3_decor_eta[] = {8.695E-04, 1.423E-03, 5.707E-03,  1.146E-03,  2.666E-03};
static const double syst_N1EVENSUB3_decor_pt0[] = {1.287E-03, 4.710E-03, 2.496E-02,  2.998E-03,  1.032E-02};
static const double syst_N1EVENSUB3_decor_pt1[] = {5.225E-03, 2.089E-02, 4.508E-02,  1.306E-02,  2.373E-02};

double getSyst( TString type, string dep, int centbin ) {
    double syst = 0;
    int x = 0;
    if (cminCent[centbin]>31) x = 1;
    if (cminCent[centbin]>61) x = 2;
    if (type.Contains("N1HFg") && !type.Contains("decor")) {
        if (dep == "eta") syst = syst_N1HFgSUB3_eta[x];
        if (dep == "pt0") syst = syst_N1HFgSUB3_pt0[x];
        if (dep == "pt1") syst = syst_N1HFgSUB3_pt1[x];
    }
    if (type.Contains("N1HFg") && type.Contains("decor")) {
        if (dep == "eta") syst = syst_N1HFgSUB3_decor_eta[x];
        if (dep == "pt0") syst = syst_N1HFgSUB3_decor_pt0[x];
        if (dep == "pt1") syst = syst_N1HFgSUB3_decor_pt1[x];
    }
    if (type.Contains("N112A") ) {
        if (dep == "eta") syst = syst_N112ASUB3_eta[x];
        if (dep == "pt0") syst = syst_N112ASUB3_pt0[x];
        if (dep == "pt1") syst = syst_N112ASUB3_pt1[x];
    }
    if (type.Contains("N1EVEN") && !type.Contains("decor")) {
        if (dep == "eta") syst = syst_N1EVENSUB3_eta[x];
        if (dep == "pt0") syst = syst_N1EVENSUB3_pt0[x];
        if (dep == "pt1") syst = syst_N1EVENSUB3_pt1[x];
    }
    if (type.Contains("N1EVEN") && type.Contains("decor")) {
        if (dep == "eta") syst = syst_N1EVENSUB3_decor_eta[x];
        if (dep == "pt0") syst = syst_N1EVENSUB3_decor_pt0[x];
        if (dep == "pt1") syst = syst_N1EVENSUB3_decor_pt1[x];
    }
    return syst;
}
