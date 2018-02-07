double maxR(double val){
  double sign = 1.;
  if(val<0) sign = -1.;
  if(val==0) return 0.;
  val=abs(val);
  double scale = 1.25;
  double ex = trunc(log10(scale*val));
  double rem = log10(scale*val)- trunc(log10(scale*val));
  double rn = 0;
  double remck = rem;
  if(remck>0) {
    if(remck<log10(1)) {
      rn = log10(1);
    } else if (remck<log10(2)){
      rn = log10(2);
    } else if (remck<log10(4)){
      rn = log10(4);
    } else if (remck<log10(5)){
      rn = log10(5);
    } else if (remck<log10(10)){
      rn = log10(10);
    }
  } else {
    if(remck<log10(0.1)) {
      rn = log10(0.1);
    } else if (remck<log10(.2)){
      rn = log10(.2);
    } else if (remck<log10(.4)){
      rn = log10(.4);
    } else if (remck<log10(.5)){
      rn = log10(.5);
    } else if (remck<log10(1.)){
      rn = log10(1.0);
    }
  }
  double ret = sign*pow(10,ex+rn);
  return ret;
}
double setYmin(TGraphErrors * g, TGraphErrors * gA, TGraphErrors * gB){
  double ymin = 1.;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymin > g->GetY()[i]-g->GetEY()[i]) ymin = g->GetY()[i]-g->GetEY()[i];
    if(ymin > gA->GetY()[i]-gA->GetEY()[i]) ymin = gA->GetY()[i]-gA->GetEY()[i];
    if(ymin > gB->GetY()[i]-gB->GetEY()[i]) ymin = gB->GetY()[i]-gB->GetEY()[i];
  }
  if(ymin>0) return 0.;
  return maxR(ymin);
}
double setYmax(TGraphErrors * g, TGraphErrors * gA, TGraphErrors * gB){
  double ymax = -1;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymax < g->GetY()[i]+g->GetEY()[i])   ymax = g->GetY()[i]  + g->GetEY()[i];
    if(ymax < gA->GetY()[i]+gA->GetEY()[i]) ymax = gA->GetY()[i] + gA->GetEY()[i];
    if(ymax < gB->GetY()[i]+gB->GetEY()[i]) ymax = gB->GetY()[i] + gB->GetEY()[i];
  }
  if(ymax<0) return 0.;
  return maxR(ymax);
}
double setYmin(TGraphErrors * g, TGraphErrors * gA){
  double ymin = 1.;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymin > g->GetY()[i]-g->GetEY()[i]) ymin = g->GetY()[i]-g->GetEY()[i];
    if(ymin > gA->GetY()[i]-gA->GetEY()[i]) ymin = gA->GetY()[i]-gA->GetEY()[i];
  }
  if(ymin>0) return 0.;
  return maxR(ymin);
}
double setYmax(TGraphErrors * g, TGraphErrors * gA){
  double ymax = -1;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymax < g->GetY()[i]+g->GetEY()[i])   ymax = g->GetY()[i]  + g->GetEY()[i];
    if(ymax < gA->GetY()[i]+gA->GetEY()[i]) ymax = gA->GetY()[i] + gA->GetEY()[i];
  }
  if(ymax<0) return 0.;
  return maxR(ymax);
}
double setYmin(TGraphErrors * g){
  double ymin = 1.;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymin > g->GetY()[i]-g->GetEY()[i]) ymin = g->GetY()[i]-g->GetEY()[i];
  }
  if(ymin>0) return 0.;
  return maxR(ymin);
}
double setYmax(TGraphErrors * g){
  double ymax = -1;
  for (int i = 0; i<g->GetN(); i++) {
    if(ymax < g->GetY()[i]+g->GetEY()[i])   ymax = g->GetY()[i]  + g->GetEY()[i];
  }
  if(ymax<0) return 0.;
  return maxR(ymax);
}

double plotmin(double ymin) {
  if(ymin>0) ymin=0;
  return maxR(ymin);
}

double plotmax(double ymax) {
  if(ymax<0) ymax=0;
  return maxR(ymax);
}
