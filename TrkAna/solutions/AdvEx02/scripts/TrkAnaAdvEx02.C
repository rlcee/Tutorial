#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

#include <iostream>

#include "TrkDiag/inc/TrkInfo.hh"
#include "TrkDiag/inc/EventWeightInfo.hh"

void TrkAnaAdvEx02(std::string filename, std::string treename) {

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  mu2e::TrkInfo de;
  trkana->SetBranchAddress("de", &de);
  mu2e::TrkFitInfo deent;
  trkana->SetBranchAddress("deent", &deent);
  mu2e::TrkFitInfo demid;
  trkana->SetBranchAddress("demid", &demid);
  mu2e::EventWeightInfo evtwt;
  trkana->SetBranchAddress("evtwt", &evtwt);

  int n_entries = 10;
  for (int i_entry = 0; i_entry < n_entries; ++i_entry) {
    trkana->GetEntry(i_entry);
    if (i_entry % 10000 == 0) {
      std::cout << i_entry << " / " << n_entries << std::endl;
    }
    std::cout << "Track #" << i_entry << ": Status = " << de._status << ", p (ent) = " << deent._fitmom << " MeV/c, p (mid) = " << demid._fitmom << " MeV/c, PBI weight = " << evtwt._weights[0] << std::endl;
  }
}
