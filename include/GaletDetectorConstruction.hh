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
// $Id: GaletDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file GaletDetectorConstruction.hh
/// \brief Definition of the GaletDetectorConstruction class

#ifndef GaletDetectorConstruction_h
#define GaletDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4OpticalSurface.hh"
#include "G4SurfaceProperty.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;
class G4MMaterialFileConstruction;
class GaletDetectorConstructionMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of GaletCalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class GaletDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    GaletDetectorConstruction();
    virtual ~GaletDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetScintillationProperty(G4String& matname, G4String& filename);
    void SetMaterialProperty(G4String& matname, G4String& filename);
  //
    void SetSkinProperty(G4String& logName, G4String& filename);
    void SetSkinProperty(G4LogicalVolume* logical, G4String& filename);
  //
    void SetBorderProperty(G4String& phys1Name, G4String& phys2Name,G4String& filename);
    void SetBorderProperty(G4VPhysicalVolume* phys1, G4VPhysicalVolume* phys2, G4String& filename);

    void SetOpticalSurface(G4OpticalSurface* opSurface, G4String& filename);
  //
    void DumpMPT(G4String& matName);
    void InitOptEnum();
    void InitUnit();
      
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    G4double StoD(G4String str);

  private:  
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    G4int   fVerbose;
  
    G4MMaterialFileConstruction* materialConstructor;
    GaletDetectorConstructionMessenger* messenger;

  private:
  // Enum map in optical surface.
  std::map<G4String,G4SurfaceType,std::less<G4String>> fOpTypeMap;
  std::map<G4String,G4OpticalSurfaceFinish,std::less<G4String>> fOpFinishMap;
  std::map<G4String,G4OpticalSurfaceModel,std::less<G4String>> fOpModelMap;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

