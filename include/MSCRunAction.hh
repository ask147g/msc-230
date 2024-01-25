/// \file include/RunAction.hh
/// \brief Definition of the RunAction class

#ifndef MSCRunAction_h
#define MSCRunAction_h 1

#include "G4UserRunAction.hh"

#include "MSCHistoManager.hh"

class G4Run;

class MSCRunAction : public G4UserRunAction {
public:
    MSCRunAction(MSCHistoManager* histo);
    ~MSCRunAction();

    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);
private:
    MSCHistoManager* fHistoManager;
};

#endif