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

#include <vector>

#include "GaletDigitizer.hh"
#include "GaletDigi.hh"
#include "GaletDigitizerMessenger.hh"

#include "GaletHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GaletDigitizer::GaletDigitizer(G4String name)
  :G4VDigitizerModule(name)
{
  G4String colName = "DigitsCollection";
  collectionName.push_back(colName);

//create a messenger for this class
  digiMessenger = new GaletDigitizerMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GaletDigitizer::~GaletDigitizer()
{
  delete digiMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GaletDigitizer::Digitize()
{
  //
  DigitsCollection = new GaletDigitsCollection
        ("GaletDigitizer","DigitsCollection"); // to create the Digi Collection
  
  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();

  G4int HCID; 

  //  Hits collection
  HCID = DigiMan->GetHitsCollectionID("GaletHitsCollection");
  GaletHitsCollection* HC = 0;
  HC = (GaletHitsCollection*)(DigiMan->GetHitsCollection(HCID));

  G4double totalDE=0.0;
  if (HC)
    {
      G4int n_hit = HC->entries();
      for (G4int i=0;i<n_hit;i++){
        totalDE += (*HC)[i]->GetEnergyDeposit();
      }
      GaletDigi* Digi = new GaletDigi();
      Digi->SetDetE( totalDE );
      //
      DigitsCollection->insert(Digi);
      //
    }
  //
  StoreDigiCollection(DigitsCollection);
  //
  //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
