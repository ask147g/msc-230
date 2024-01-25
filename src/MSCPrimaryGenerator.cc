/// \file src/PrimaryGenerator.cc
/// \brief Implementation of the PrimaryGenerator class

#include "MSCPrimaryGenerator.hh"

MSCPrimaryGenerator::MSCPrimaryGenerator() 
	: gun(new G4GeneralParticleSource) {
}

MSCPrimaryGenerator::~MSCPrimaryGenerator() {
	delete gun;
}

void MSCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	gun->GeneratePrimaryVertex(anEvent);
}