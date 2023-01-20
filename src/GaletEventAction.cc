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
// $Id: GaletEventAction.cc 89037 2015-03-18 09:25:01Z gcosmo $
// 
/// \file GaletEventAction.cc
/// \brief Implementation of the GaletEventAction class

#include "GaletEventAction.hh"
#include "GaletSD.hh"
#include "GaletHit.hh"
#include "GaletAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GaletEventAction::GaletEventAction()
 : G4UserEventAction(),
   fHCScintiID(-1), fHCPMTID(-1)
{
  fMessenger = new GaletEventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GaletEventAction::~GaletEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GaletHitsCollection* 
GaletEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  GaletHitsCollection* hitsCollection 
    = static_cast<GaletHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("GaletEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GaletEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GaletEventAction::EndOfEventAction(const G4Event* event)
{  
  // Print per event (modulo n)
  //
  //  UI:  /run/printProgress <n>
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     
  }  

  //---------------
  // Scintillator
  //---------------
  //
  // Get hits collections IDs (only once)
  if ( fHCScintiID == -1 ) {
    fHCScintiID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("GaletScintiHitsCollection");
  }
  // Skip following code by return if no hits collection
  //
  if ( fHCScintiID < 0 ) return;
  //
  // Get hits collections
  GaletHitsCollection* ScintiHC = GetHitsCollection(fHCScintiID, event);
  //
  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  // Loop over the hits of Scintillator
  //
  G4cout << "===== Scintillator Hits=======" <<G4endl;
  G4double totalE = 0.0;
  for ( G4int i = 0; i < (G4int)(ScintiHC->entries()) ; i++){
    GaletHit* Hit = (*ScintiHC)[i];
    G4double  de  = Hit->GetEnergyDeposit()/keV;
    G4int     trackID  = Hit->GetTrackID();
    totalE += de;
    G4cout << "Event: "<<eventID
           <<" trackID: "<< trackID
           <<" EnergyDep(keV): " << de 
           <<" totalE(keV): " << totalE 
           <<G4endl;
  }
  //
  // fill histograms
  if ( totalE > 0 ) {
    analysisManager->FillH1(1, totalE);
  }

  //---------------
  // PMT
  //--------------
  //
  // Get hits collections IDs (only once)
  if ( fHCPMTID == -1 ) {
    fHCPMTID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("GaletPMTHitsCollection");
  }
  //
  // Skip following code by return if no hits collection
  //
  if ( fHCPMTID < 0 ) return;
  //
  // Get hits collections
  GaletHitsCollection* PMTHC = GetHitsCollection(fHCPMTID, event);
  
  G4cout << "===== PMT Hits=======" <<G4endl;  
  for ( G4int i = 0; i < (G4int)(PMTHC->entries()) ; i++){
    GaletHit* Hit = (*PMTHC)[i];
    G4int     trackID  = Hit->GetTrackID();
    G4int     PID  = Hit->GetPID();
    G4double  ke  = Hit->GetIncidentKinE()/eV;
    G4double  time = Hit->GetGlobalTime()/ns;
    G4cout << "Event: "<<eventID
           <<" trackID: "<< trackID
           <<" PID: "<< PID      
           <<" kinetic Energy(eV): " << ke
           <<" Global time (ns): " << time       
           <<G4endl;
  }
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
