
//--------------- 6 by 1

TCanvas * c0 = new TCanvas("c0", "c0", 1350, 550);
TPad * pad0[12];
c0->cd();
pad0[0] = new TPad("pad0_0", "pad0_0", 0.0, 0.5, 0.20, 1.0);
pad0[0]->SetLeftMargin(0.25);
pad0[0]->SetTopMargin(0.18);
pad0[0]->SetBottomMargin(0);
pad0[0]->SetRightMargin(0);
pad0[0]->Draw();

c0->cd();
pad0[1] = new TPad("pad0_1", "pad0_1", 0.20, 0.5, 0.36, 1.0);
pad0[1]->SetLeftMargin(0);
pad0[1]->SetRightMargin(0);
pad0[1]->SetTopMargin(0.18);
pad0[1]->SetBottomMargin(0);
pad0[1]->Draw();

c0->cd();
pad0[2] = new TPad("pad0_2", "pad0_2", 0.36, 0.5, 0.52, 1.0);
pad0[2]->SetLeftMargin(0);
pad0[2]->SetRightMargin(0);
pad0[2]->SetTopMargin(0.18);
pad0[2]->SetBottomMargin(0);
pad0[2]->Draw();

c0->cd();
pad0[3] = new TPad("pad0_3", "pad0_3", 0.52, 0.5, 0.68, 1.0);
pad0[3]->SetLeftMargin(0);
pad0[3]->SetRightMargin(0);
pad0[3]->SetTopMargin(0.18);
pad0[3]->SetBottomMargin(0);
pad0[3]->Draw();

c0->cd();
pad0[4] = new TPad("pad0_4", "pad0_4", 0.68, 0.5, 0.84, 1.0);
pad0[4]->SetLeftMargin(0);
pad0[4]->SetRightMargin(0);
pad0[4]->SetTopMargin(0.18);
pad0[4]->SetBottomMargin(0);
pad0[4]->Draw();

c0->cd();
pad0[5] = new TPad("pad0_5", "pad0_5", 0.84, 0.5, 1.0, 1.0);
pad0[5]->SetLeftMargin(0);
pad0[5]->SetRightMargin(0.02);
pad0[5]->SetTopMargin(0.18);
pad0[5]->SetBottomMargin(0);
pad0[5]->Draw();

//-- lower row

c0->cd();
pad0[6] = new TPad("pad0_0", "pad0_0", 0.0, 0, 0.20, 0.5);
pad0[6]->SetLeftMargin(0.25);
pad0[6]->SetTopMargin(0);
pad0[6]->SetBottomMargin(0.23);
pad0[6]->SetRightMargin(0);
pad0[6]->SetGrid();
pad0[6]->Draw();

c0->cd();
pad0[7] = new TPad("pad0_1", "pad0_1", 0.20, 0, 0.36, 0.5);
pad0[7]->SetLeftMargin(0);
pad0[7]->SetRightMargin(0);
pad0[7]->SetTopMargin(0);
pad0[7]->SetBottomMargin(0.23);
pad0[7]->SetGrid();
pad0[7]->Draw();

c0->cd();
pad0[8] = new TPad("pad0_2", "pad0_2", 0.36, 0, 0.52, 0.5);
pad0[8]->SetLeftMargin(0);
pad0[8]->SetRightMargin(0);
pad0[8]->SetTopMargin(0);
pad0[8]->SetBottomMargin(0.23);
pad0[8]->SetGrid();
pad0[8]->Draw();

c0->cd();
pad0[9] = new TPad("pad0_3", "pad0_3", 0.52, 0, 0.68, 0.5);
pad0[9]->SetLeftMargin(0);
pad0[9]->SetRightMargin(0);
pad0[9]->SetTopMargin(0);
pad0[9]->SetBottomMargin(0.23);
pad0[9]->SetGrid();
pad0[9]->Draw();

c0->cd();
pad0[10] = new TPad("pad0_4", "pad0_4", 0.68, 0, 0.84, 0.5);
pad0[10]->SetLeftMargin(0);
pad0[10]->SetRightMargin(0);
pad0[10]->SetTopMargin(0);
pad0[10]->SetBottomMargin(0.23);
pad0[10]->SetGrid();
pad0[10]->Draw();

c0->cd();
pad0[11] = new TPad("pad0_5", "pad0_5", 0.84, 0, 1.0, 0.5);
pad0[11]->SetLeftMargin(0);
pad0[11]->SetRightMargin(0.02);
pad0[11]->SetTopMargin(0);
pad0[11]->SetBottomMargin(0.23);
pad0[11]->SetGrid();
pad0[11]->Draw();
