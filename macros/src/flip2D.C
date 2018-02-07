TH2D * flip2D(TH2D * h) {
  if(sTrackReaction!=pPb) return h;
  if(sTrackOrientation==Type_Pbp) return h;
  int nx = h->GetNbinsX();
  int ny = h->GetNbinsY();
  for(int j = 1; j<=ny/2; j++) {
    for(int i = 1; i<=nx; i++) {
      double hold = h->GetBinContent(i,j);
      double holde = h->GetBinError(i,j);
      h->SetBinContent(i,j,h->GetBinContent(i,ny+1-j));
      h->SetBinError(i,j,h->GetBinError(i,ny+1-j));
      h->SetBinContent(i,ny+1-j,hold);
      h->SetBinError(i,ny+1-j,holde);
    }
  } 
  return h;
}
