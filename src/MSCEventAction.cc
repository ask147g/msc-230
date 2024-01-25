/// \file src/EventAction.cc
/// \brief Implementation of the EventAction class

#include "MSCEventAction.hh"

MSCEventAction::MSCEventAction(MSCHistoManager* histo) : fHistoManager(histo) {
}

MSCEventAction::~MSCEventAction() = default;

void MSCEventAction::BeginOfEventAction(const G4Event* evt) {
  //minTime = 1000000;
  //maxTime = 0;
  evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) {
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
  }
}

void MSCEventAction::EndOfEventAction(const G4Event*) {
  //G4double dt = maxTime - minTime;
  //fHistoManager->FillNtupleProtonDelta(evtNb, dt);
}