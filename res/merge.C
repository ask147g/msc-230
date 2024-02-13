#include "TROOT.h"

void merge() {

    double time1, time2, time3, time4, time5;
    double energy1, energy2, energy3, energy4, energy5;

    TFile* file = new TFile("energy/msc-230_20_1.root");
    TTree* tr = (TTree*)file->Get("neutron");
    tr->SetBranchAddress("t", &time1);
    tr->SetBranchAddress("e", &energy1);
    int entr1 = tr->GetEntries();
    

    TFile* file2 = new TFile("energy/msc-230_20_2.root");
    TTree* tr2 = (TTree*)file2->Get("neutron");
    tr2->SetBranchAddress("t", &time2);
    tr2->SetBranchAddress("e", &energy2);
    int entr2 = tr2->GetEntries();

    TFile* file3 = new TFile("energy/msc-230_50.root");
    TTree* tr3 = (TTree*)file3->Get("neutron");
    tr3->SetBranchAddress("t", &time3);
    tr3->SetBranchAddress("e", &energy3);
    int entr3 = tr3->GetEntries();

    TFile* file4 = new TFile("energy/msc-230_50e_2.root");
    TTree* tr4 = (TTree*)file4->Get("neutron");
    tr4->SetBranchAddress("t", &time4);
    tr4->SetBranchAddress("e", &energy4);
    int entr4 = tr4->GetEntries();

    TFile* file5 = new TFile("energy/msc-230_20_3.root");
    TTree* tr5 = (TTree*)file5->Get("neutron");
    tr5->SetBranchAddress("t", &time5);
    tr5->SetBranchAddress("e", &energy5);
    int entr5 = tr5->GetEntries();

    TFile fout("energy/msc-230r.root","recreate");
    TTree trR("T","");

    Float_t nt;
    Float_t ne;
    trR.Branch("nt",&nt,"nt/F");
    trR.Branch("ne",&ne,"ne/F");

    for (int i = 0; i < entr1; i++) {
        tr->GetEntry(i);
        nt = time1; // mus
        ne = energy1;
        trR.Fill();
    }
    
    for (int i = 0; i < entr2; i++) {
        tr2->GetEntry(i);
        nt = time2; // mus
        ne = energy2;
        trR.Fill();
    }

    for (int i = 0; i < entr3; i++) {
        tr3->GetEntry(i);
        nt = time3; // mus
        ne = energy3;
        trR.Fill();
    }

    for (int i = 0; i < entr4; i++) {
        tr4->GetEntry(i);
        nt = time4; // mus
        ne = energy4;
        trR.Fill();
    }

    for (int i = 0; i < entr5; i++) {
        tr5->GetEntry(i);
        nt = time5; // mus
        ne = energy5;
        trR.Fill();
    }

    trR.Write();

}