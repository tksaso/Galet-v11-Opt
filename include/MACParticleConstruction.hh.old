//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ParticleConstruction.hh
//
// [Description]
//   Physics list to define particles for the P152 (NIRS) experiment.
//
// [Histoy]
//   8 April, 2003, K. Amako : The 1st version created.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef MACParticleConstruction_h
#define MACParticleConstruction_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

/******************************************************************************/
 class MACParticleConstruction: public G4VPhysicsConstructor
/******************************************************************************/
{
  public: 
    MACParticleConstruction();
    virtual ~MACParticleConstruction();

  public: 
    // Particle constructors should be defined in this methods
    virtual void ConstructParticle();
 
    // This method should be dummied because the current class is only
    // for particle constructions
    virtual void ConstructProcess() {};

 };

#endif








