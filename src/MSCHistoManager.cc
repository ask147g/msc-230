/// \file src/HistoManager.cc
/// \brief Implementation of the HistoManager class

#include "MSCHistoManager.hh"

MSCHistoManager::MSCHistoManager() : fFactoryOn(false) {
}

MSCHistoManager::~MSCHistoManager() {
}

void MSCHistoManager::Book() {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if ( ! fFactoryOn ) {
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetVerboseLevel(1);
    // Only merge in MT mode to avoid warning when running in Sequential mode
  #ifdef G4MULTITHREADED
    analysisManager->SetNtupleMerging(true);
  #endif
  }

  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile("msc-230");
  if (! fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open "
           << analysisManager->GetFileName() << G4endl;
    return;
  }

  if ( ! fFactoryOn ) {
    analysisManager->CreateNtuple("neutron", "neutron");// column Id = 0
    analysisManager->CreateNtupleDColumn("t");
    analysisManager->CreateNtupleDColumn("e");
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("proton", "proton");// column Id = 1
    analysisManager->CreateNtupleDColumn("dt");
    analysisManager->FinishNtuple();

    fFactoryOn = true;
  }

  G4cout << "\n----> Output file is open in "
         << analysisManager->GetFileName() << "."
         << analysisManager->GetFileType() << G4endl;
}

void MSCHistoManager::Save() {
  if (!fFactoryOn) return;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

void MSCHistoManager::FillNtuple(G4double t, G4double e) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(0, 0, t);  
  analysisManager->FillNtupleDColumn(0, 1, e);  
  analysisManager->AddNtupleRow(0);
}

void MSCHistoManager::FillNtupleProtonDelta(G4double t) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(1, 0, t);  
  analysisManager->AddNtupleRow(1);
}