/// \file include/EventAction.hh
/// \brief Definition of the EventAction class

#ifndef MSCEventAction_h
#define MSCEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "MSCHistoManager.hh"

/// Defines an alghorithms with particles per Event.
///
/// Used to event notifications.
class MSCEventAction : public G4UserEventAction {
public:
  MSCEventAction(MSCHistoManager* histo);
  ~MSCEventAction() override;

  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event*) override;

  G4int GetEventNumber() {return evtNb;};
  G4int GetMaxValue() {return maxTime;};
  G4int GetMinValue() {return minTime;};
  void SetMinValue(G4double time)  {minTime = time;}; 
  void SetMaxValue(G4double time) {maxTime = time;}; 
private:
  // defines notification frequency of event number
  G4int fPrintModulo = 10000;
  G4int evtNb;
  G4double minTime = 1000000;
  G4double maxTime = 0;

  MSCHistoManager* fHistoManager  = nullptr;
};

#endif