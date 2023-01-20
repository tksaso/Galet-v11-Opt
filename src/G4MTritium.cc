//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id$
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      History: first implementation, based on object model of
//      4 Dec. 98 by H.Kurashige
// ----------------------------------------------------------------------
//  New impelemenataion as an utility class  M.Asai, 26 July 2004
// ----------------------------------------------------------------------

#include "G4MTritium.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"

// ######################################################################
// ###                           GenericIon                           ###
// ######################################################################
G4MTritium* G4MTritium::theInstance = 0;

G4MTritium* G4MTritium::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "tritium";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4Ions* anInstance = reinterpret_cast<G4Ions*>(pTable->FindParticle(name));
  if (anInstance ==0)
  {
  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding
  //             excitation   
//!!!!
//!!!! this particle should not be used for tracking
//!!!! all properties except name and type are meaningless
//!!!!
    G4double  year = 31.536000e06 * second;
    anInstance = new G4Ions(
                 name,    2.808921*GeV,       0.0*MeV,  +1.0*eplus,
                    1,              +1,             0,
                    0,               0,             0,
            "nucleus",               0,            +3, 1000010030,
                false,      12.32*year,          NULL,
		false,        "generic",             0, 
                  0.0
              );
 
    // Magnetic Moment
    G4double mN = eplus*hbar_Planck/2./(proton_mass_c2 /c_squared);
    anInstance->SetPDGMagneticMoment( 2.97896248 * mN);
   }
  anInstance->SetAntiPDGEncoding(0);

  //G4IonTable* iTable =  pTable->GetIonTable();
  //iTable->Insert(anInstance);

  theInstance = reinterpret_cast<G4MTritium*>(anInstance);
  return theInstance;
}

G4MTritium*  G4MTritium::TritiumDefinition()
{ 
  return Definition();
}

G4MTritium*  G4MTritium::Tritium()
{ 
  return Definition();
}

