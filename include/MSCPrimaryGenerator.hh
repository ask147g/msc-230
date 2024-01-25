/// \file include/PrimaryGenerator.hh
/// \brief Definition of the PrimaryGenerator class

#ifndef MSCPrimaryGenerator_h
#define MSCPrimaryGenerator_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

/// Defines a particles source in volume from ".in"-file.

class MSCPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
	MSCPrimaryGenerator();
	~MSCPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
	
private:
	G4GeneralParticleSource *gun;
};

#endif