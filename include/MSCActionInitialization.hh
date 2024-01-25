/// \file include/ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef MSCAction_h
#define MSCAction_h 1

#include "G4VUserActionInitialization.hh"

#include "MSCPrimaryGenerator.hh"
#include "MSCRunAction.hh"
#include "MSCHistoManager.hh"
#include "MSCSteppingAction.hh"
#include "MSCEventAction.hh"

class MSCActionInitialization : public G4VUserActionInitialization {
public:
    MSCActionInitialization();
    ~MSCActionInitialization();

    // one-thread processes from the base class
	virtual void Build() const;
	// multithreading processes from the base class
	virtual void BuildForMaster() const;
};

#endif