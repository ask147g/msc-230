#include "TROOT.h"

void merge() {

    double time1, time2, time3;

    TFile* file = new TFile("msc-230_20_11.root");
    TTree* tr = (TTree*)file->Get("neutron");
    tr->SetBranchAddress("t", &time1);
    int entr1 = tr->GetEntries();
    

    TFile* file2 = new TFile("msc-230_50_1.root");
    TTree* tr2 = (TTree*)file2->Get("neutron");
    tr2->SetBranchAddress("t", &time2);
    int entr2 = tr2->GetEntries();

    TFile* file3 = new TFile("msc-230_50_2.root");
    TTree* tr3 = (TTree*)file3->Get("neutron");
    tr3->SetBranchAddress("t", &time3);
    int entr3 = tr3->GetEntries();

    TFile fout("msc-230r.root","recreate");
    TTree trR("T","");

    Float_t nt;
    trR.Branch("nt",&nt,"nt/F");

    for (int i = 0; i < entr1; i++) {
        tr->GetEntry(i);
        nt = time1; // mus
        trR.Fill();
    }
    
    for (int i = 0; i < entr2; i++) {
        tr2->GetEntry(i);
        nt = time2; // mus
        trR.Fill();
    }

    for (int i = 0; i < entr3; i++) {
        tr3->GetEntry(i);
        nt = time3; // mus
        trR.Fill();
    }

    trR.Write();



}