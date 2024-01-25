#include "MSCRunAction.hh"

MSCRunAction::MSCRunAction(MSCHistoManager* histo) : fHistoManager(histo) {
}

MSCRunAction::~MSCRunAction() {
}

void MSCRunAction::BeginOfRunAction(const G4Run* aRun) {
    fHistoManager->Book();
}

void MSCRunAction::EndOfRunAction(const G4Run* aRun) {
    fHistoManager->Save();
}