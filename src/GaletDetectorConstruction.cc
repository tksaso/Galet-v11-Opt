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
// $Id: GaletDetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
// 
/// \file GaletDetectorConstruction.cc
/// \brief Implementation of the GaletDetectorConstruction class

#include "GaletDetectorConstruction.hh"
#include "GaletSD.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4MMaterialFileConstruction.hh"
#include "G4Types.hh"

#include "GaletDetectorConstructionMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <fstream>
//
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GaletDetectorConstruction::GaletDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
  materialConstructor = new G4MMaterialFileConstruction;
  messenger = new GaletDetectorConstructionMessenger(this);
  //
  fVerbose = 0;
  //
  // Initialize parameters.                                                            
  InitOptEnum();
  InitUnit();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GaletDetectorConstruction::~GaletDetectorConstruction()
{ 
  delete materialConstructor;
  delete messenger;
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GaletDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GaletDetectorConstruction::DefineMaterials()
{ 
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GaletDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  G4double worldSizeX = 50.*cm;
  G4double worldSizeY = 30.*cm;
  G4double worldSizeZ  = 30.*cm; 
  //     
  // World Volume
  //
  G4VSolid* worldS 
    = new G4Box("WorldS",           // its name
                 worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size
                         
  G4LogicalVolume* worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 G4Material::GetMaterial("G4_AIR"),  // its material
                 "WorldLV");         // its name
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume
                 "WorldPV",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
  // Visualization attributes
  //worldLV->SetVisAttributes (G4VisAttributes::Invisible);

  //
  //  Thin Al layer (50 um thick)  
  //
  G4double AlSizeX = 20.0*cm;  // Both edges are open.
  G4double AlSizeY = 5.01*cm;
  G4double AlSizeZ = 2.01*cm;    

  G4VSolid* AlS 
    = new G4Box("AlS",           // its name
                 AlSizeX/2, AlSizeY/2, AlSizeZ/2); // its size
                         
  G4LogicalVolume* AlLV
    = new G4LogicalVolume(
                 AlS,           // its solid
                 G4Material::GetMaterial("G4_WATER"),  // its material
                 "AlLV");         // its name
                                   
  G4VPhysicalVolume* AlPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 AlLV,          // its logical volume
                 "AlPV",          // its name
                 worldLV,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

 
  //
  //  Certain Scintillator ( Now  G4_WATER )
  //
  G4double scintiSizeX = 20.0*cm;
  G4double scintiSizeY = 5.0*cm;
  G4double scintiSizeZ = 2.0*cm;
  
  G4VSolid* scintiS 
    = new G4Box("ScintiS",           // its name
                 scintiSizeX/2, scintiSizeY/2, scintiSizeZ/2); // its size
                         
  G4LogicalVolume* scintiLV
    = new G4LogicalVolume(
                 scintiS,           // its solid
                 G4Material::GetMaterial("G4_WATER"),  // its material
                 "ScintiLV");         // its name
                                   
  G4VPhysicalVolume* scintiPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 scintiLV,          // its logical volume
                 "ScintiPV",          // its name
                 AlLV,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
  
  //                               
  // PMT window
  //
  G4double PMTR = 2*cm;
  G4double PMTZ = 1*cm;  //
  //
  G4VSolid* PMTS 
    = new G4Tubs("PMTS",           // its name
                 0.*cm, PMTR, PMTZ/2.,0,twopi); // its size
                         
  G4LogicalVolume* PMTLV
    = new G4LogicalVolume(
                 PMTS,           // its solid
                 G4Material::GetMaterial("G4_GLASS_PLATE"),  // its material
                 "PMTLV");         // its name

  G4RotationMatrix* PMTrot = new G4RotationMatrix();
  PMTrot->rotateY(90.*degree);
  G4VPhysicalVolume* PMTPV
    = new G4PVPlacement(
                 PMTrot,                // no rotation
                 G4ThreeVector(scintiSizeX/2.+PMTZ/2.,0,0),  // at (0,0,0)
                 PMTLV,          // its logical volume
                 "PMTPV",          // its name
                 worldLV,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GaletDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  // Sensitive detectors
  //
  // Scinti                                                                              
  GaletSD* galetScintiSD = new GaletSD("galetScintiSD", "GaletScintiHitsCollection");
  G4String name_lv = "ScintiLV";
  SetSensitiveDetector(name_lv,galetScintiSD);
  G4SDManager::GetSDMpointer()->AddNewDetector(galetScintiSD);

  // PMT
  GaletSD* galetPMTSD  = new GaletSD("galetPMTSD", "GaletPMTHitsCollection");
  galetPMTSD->SetZeroEdep(false);
  galetPMTSD->StopOpticalPhoton(true);  
  name_lv = "PMTLV";
  G4SDManager::GetSDMpointer()->AddNewDetector(galetPMTSD);
  SetSensitiveDetector(name_lv,galetPMTSD);

}
/*----------------------------------------------------------------------------*/

void GaletDetectorConstruction::SetScintillationProperty(G4String& matname, 
                                                         G4String& filename){
  G4Material* mat = G4Material::GetMaterial(matname);
  G4MaterialPropertiesTable * MPT = mat->GetMaterialPropertiesTable();
  if ( !MPT ) {
    MPT = new G4MaterialPropertiesTable();
    mat->SetMaterialPropertiesTable(MPT);
  }
  std::ifstream fin;
  fin.open(filename.c_str());
  if ( !fin){
    G4String mes = "File Not Found " + filename;
    G4Exception("GaletDetectorConstruction:GetScintillationProperty()",
                "File00",
                FatalException,mes);
  }
  //
  const char ctrM = 0x0d;
  std::string buf;
  G4int ncount = 0;
  G4String KEY, unitName;
  G4double ETA;
  G4double KE, KEQE;
  std::vector<G4double> KEVec;
  std::vector<G4double> LVec;
  while ( fin && std::getline(fin,buf)){
    str_size nb = 0;
    while ( (nb=buf.find('\t',nb)) != std::string::npos){
      buf.replace(nb,1," ");
    }
    G4String sline(buf);
    sline = sline.strip(G4String::both);
    sline = sline.strip(G4String::trailing, ctrM);

    if ( sline[(size_t)0]=='#' ) continue;

    std::istringstream iss(sline);
    if ( ncount == 0 ) {
      iss >> KEY >> ETA >>  unitName;
      ETA *= G4UnitDefinition::GetValueOf(unitName);
    }else{
      iss >> KE >> KEQE;
      KE *= keV;
      KEQE *= keV;
      G4double ETAKEQE = ETA*KEQE;
      KEVec.push_back(KE);
      LVec.push_back(ETAKEQE);
    }
    ncount++;
  }
  //
  fin.close();
  //
  if ( MPT->GetProperty(KEY) ) {MPT->RemoveProperty(KEY);};
  (MPT->AddProperty(KEY,&(KEVec.front()),&(LVec.front()),KEVec.size()))
      ->SetSpline(true);
  //
  //
  //MPT->DumpTable(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
void GaletDetectorConstruction::SetMaterialProperty(G4String& matname, 
                                                         G4String& filename){
  G4Material* mat = G4Material::GetMaterial(matname);
  G4MaterialPropertiesTable * MPT = mat->GetMaterialPropertiesTable();
  if ( !MPT ) {
    MPT = new G4MaterialPropertiesTable();
    mat->SetMaterialPropertiesTable(MPT);
  }

  std::ifstream fin;
  fin.open(filename.c_str());
  if ( !fin){
    G4String mes = "File Not Found " + filename;
    G4Exception("GaletDetectorConstruction:GetMaterialProperty()","File00",
                FatalException,mes);
  }
  //
  G4String key;
  G4int Nconst;
  fin >> key >> Nconst;
  if ( fVerbose > 1 ) G4cout << key << " " << Nconst <<G4endl;
  //
  G4double value;
  G4String unitName;
  for ( G4int i = 0 ; i < Nconst ; i++){
    fin >> key >> value >> unitName;
    if ( fVerbose > 1 ) G4cout << key << " " << value <<" " << unitName << G4endl;
    if ( value < 0.0 ) continue;
    value *= G4UnitDefinition::GetValueOf(unitName);
    if ( key == "BIRKS" ){
      mat->GetIonisation()->SetBirksConstant(value);
    }else {
        MPT->AddConstProperty(key,value); 
    }
  }
  //
  //
  const G4int NparMax=5;
  G4int Npar;
  fin >> key >> Npar;  // Number of parameters.
  ///
  G4int Ndata;
  fin >> key >> Ndata; // Number of data lines.
  //
  G4String IDXNAME[NparMax];
  G4int idxABSL=-1;
  for ( G4int j = 0; j < Npar; j++){ 
    fin >> IDXNAME[j];
    if ( fVerbose > 1 ) G4cout << IDXNAME[j] << " " << G4endl;
    if ( IDXNAME[j] == "ABSLENGTH" ){
      idxABSL = j;
    }
    if ( MPT->GetProperty(IDXNAME[j]) ){
      MPT->RemoveProperty(IDXNAME[j]);
      if ( fVerbose > 0 ) {
        G4cout << " Remove property of "<< IDXNAME[j] 
               << "in " <<mat->GetName()<<G4endl;
      }
    }
  };
  //
  std::vector<G4double> IDXVALVEC[NparMax];
  for ( G4int i = 0; i < Ndata; i++ ){
    for ( G4int j = 0; j < Npar; j++){
      fin >> value;
      if ( fVerbose > 1 ) G4cout << value <<" ";
      if ( j == 0 ) {
        value *= eV;
      }else if ( j == idxABSL ){
        value *= cm;
      }
      IDXVALVEC[j].push_back(value);
    }
    if ( fVerbose > 1 ) G4cout << G4endl;
  }

  for ( G4int j = 1; j < Npar; j++){
    (MPT->AddProperty(IDXNAME[j],&(IDXVALVEC[0].front()),&(IDXVALVEC[j].front()),IDXVALVEC[j].size()))
      ->SetSpline(true);
  }
  //
  fin.close();
  //
  //MPT->DumpTable(); 
  //
}

/*----------------------------------------------------------------------------*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GaletDetectorConstruction::SetSkinProperty(G4String& logName, 
                                                G4String& filename){
  G4LogicalVolume* logical = G4LogicalVolumeStore::GetInstance()->GetVolume(logName);
  if ( logical ) {
    SetSkinProperty(logical, filename);
  }else{
    G4ExceptionDescription msg;
    msg << "logical volume not found.\n";
    G4Exception("GaletDetectorConstruction","SetSkinProperty",JustWarning,msg);
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GaletDetectorConstruction::SetSkinProperty(G4LogicalVolume* logical, 
                                                G4String& filename){
  //
  G4LogicalSkinSurface* skin = G4LogicalSkinSurface::GetSurface(logical);
  if ( skin ){
    G4String msg = "SkinProperty has already defined. ";
    G4Exception("GaletDetectorConstruction","SetSkinProperty",FatalException,msg);
  } 
  //
  G4String name = logical->GetName() + "Surface";
  G4OpticalSurface* opSurface = new G4OpticalSurface(name);
  G4Material* mat = logical->GetMaterial();
  G4MaterialPropertiesTable*  MPT = mat->GetMaterialPropertiesTable();
  opSurface->SetMaterialPropertiesTable(MPT);
  if ( fVerbose > 0 ) G4cout << " Create G4OpticalSurface : " << name << G4endl;
  //
  //
  SetOpticalSurface(opSurface,filename);
  //
  G4LogicalSkinSurface* logSurface =
    new G4LogicalSkinSurface(name,logical,opSurface);
  //
  G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
    (logSurface->GetSurface(logical)->GetSurfaceProperty());
  //
  if (opticalSurface) opticalSurface->DumpInfo();
}

/*----------------------------------------------------------------------------*/
void GaletDetectorConstruction::SetBorderProperty(G4String& phys1Name, 
                                                  G4String& phys2Name, 
                                                  G4String& filename){
  //
  G4VPhysicalVolume* phys1 = G4PhysicalVolumeStore::GetInstance()->GetVolume(phys1Name);
  G4VPhysicalVolume* phys2 = G4PhysicalVolumeStore::GetInstance()->GetVolume(phys2Name);
  //
  if ( !phys1  ) { 
    G4String msg = "phys1 is not defined. ";
    msg += phys1->GetName();
    G4Exception("GaletDetectorConstruction","FindPhysicalVolume",FatalException,msg);
  }
  if ( !phys2  ) { 
    G4String msg = "phys1 is not defined. ";
    msg += phys2->GetName();
    G4Exception("GaletDetectorConstruction","FindPhysicalVolume",FatalException,msg);
  }

  SetBorderProperty(phys1,phys2,filename);
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GaletDetectorConstruction::SetBorderProperty(G4VPhysicalVolume* phys1, 
                                                  G4VPhysicalVolume* phys2, 
                                                  G4String& filename){

  if ( fVerbose > 1 ) G4cout << phys1->GetName()<<" "<<phys2->GetName()<<G4endl;
  G4LogicalBorderSurface::DumpInfo();
  G4LogicalBorderSurface* border = G4LogicalBorderSurface::GetSurface(phys1,phys2);
  if ( border ){
    G4String msg = "BorderProperty has already defined. ";
    G4Exception("GaletDetectorConstruction","SetBorderProperty",FatalException,msg);
  }  

  G4OpticalSurface* opSurface = new G4OpticalSurface("Border");
  //
  SetOpticalSurface(opSurface,filename);
  //
  new G4LogicalBorderSurface("Border",phys1,phys2,opSurface);
  new G4LogicalBorderSurface("Border",phys2,phys1,opSurface);
  
}

/*----------------------------------------------------------------------------*/
void GaletDetectorConstruction::SetOpticalSurface(G4OpticalSurface* opSurface,
                                                  G4String& filename){
  std::ifstream fin;
  fin.open(filename.c_str());
  if ( !fin){
    G4String mes = "File Not Found " + filename;
    G4Exception("GaletDetectorConstruction:SetOpticalSurface()","File00",
                FatalException,mes);
  }
  //
  G4String key;
  G4int Nproperty;
  fin >> key >> Nproperty;
  if ( fVerbose > 1 ) G4cout << key << " " << Nproperty <<G4endl;
  //
  G4String svalue;
  for ( G4int i = 0 ; i < Nproperty ; i++){
    fin >> key >> svalue ;
    if ( fVerbose > 1 ) G4cout << key << " " << svalue << G4endl;
    if ( key == "TYPE" ){
      opSurface->SetType(fOpTypeMap[svalue]);
    }else if ( key == "MODEL" ){
      opSurface->SetModel(fOpModelMap[svalue]);
    }else if ( key == "FINISH" ){
      opSurface->SetFinish(fOpFinishMap[svalue]);
    }else if ( key == "SIGMAALPHA" ){
      G4cout << " SIGMAALPHA " << StoD(svalue)<<G4endl;
      opSurface->SetSigmaAlpha(StoD(svalue));
    }
  }
  fin.close();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GaletDetectorConstruction::DumpMPT(G4String& matName){
  G4Material* mat = G4Material::GetMaterial(matName);
  G4MaterialPropertiesTable * MPT = mat->GetMaterialPropertiesTable();
  if ( MPT ) {
    MPT->DumpTable(); 
  }
  G4cout << "BIRKS " <<  mat->GetIonisation()->GetBirksConstant()/(mm/MeV)
         << " mm/MeV "<<G4endl;
}
/*----------------------------------------------------------------------------*/
void GaletDetectorConstruction::InitUnit(){
  new G4UnitDefinition("/kev","/keV","/Energy",(1./keV));
  new G4UnitDefinition("none","none","none",1.);
  new G4UnitDefinition("um/keV","um/keV","Length/Energy",um/keV);
}
/*----------------------------------------------------------------------------*/
void GaletDetectorConstruction::InitOptEnum(){
  fOpTypeMap.clear();
  fOpFinishMap.clear();
  fOpModelMap.clear();

  //
  fOpTypeMap["dielectric_metal"]=dielectric_metal;
  fOpTypeMap["dielectric_dielectric"]=dielectric_dielectric;
  fOpTypeMap["dielectric_LUT"]=dielectric_LUT;
  fOpTypeMap["dielectric_dichroic"]=dielectric_dichroic;
  fOpTypeMap["firsov"]=firsov;
  fOpTypeMap["x_ray"]=x_ray;

  //
  fOpFinishMap["polished"]=polished;                          // smooth perfectly polished surface
  fOpFinishMap["polishedfrontpainted"]=polishedfrontpainted;  // smooth top-layer (front) paint
  fOpFinishMap["polishedbackpainted"]=polishedbackpainted;    // same is 'polished' but with a back-paint

  fOpFinishMap["ground"]=ground;                             // rough surface
  fOpFinishMap["groundfrontpainted"]=groundfrontpainted;     // rough top-layer (front) paint
  fOpFinishMap["groundbackpainted"]=groundbackpainted;       // same as 'ground' but with a back-paint

  fOpFinishMap["polishedlumirrorair"]=polishedlumirrorair;   // mechanically polished surface, with lumirror
  fOpFinishMap["polishedlumirrorglue"]=polishedlumirrorglue; // mechanically polished surface, with lumirror & meltmount
  fOpFinishMap["polishedair"]=polishedair;               // mechanically polished surface
  fOpFinishMap["polishedteflonair"]=polishedteflonair;   // mechanically polished surface, with teflon
  fOpFinishMap["polishedtioair"]=polishedtioair;         // mechanically polished surface, with tio paint
  fOpFinishMap["polishedtyvekair"]=polishedtyvekair;     // mechanically polished surface, with tyvek
  fOpFinishMap["polishedvm2000air"]=polishedvm2000air;   // mechanically polished surface, with esr film
  fOpFinishMap["polishedvm2000glue"]=polishedvm2000glue; // mechanically polished surface, with esr film & meltmount
  
  fOpFinishMap["etchedlumirrorair"]=polishedvm2000glue;  // chemically etched surface, with lumirror
  fOpFinishMap["etchedlumirrorglue"]=etchedlumirrorglue; // chemically etched surface, with lumirror & meltmount
  fOpFinishMap["etchedair"]=etchedair;                   // chemically etched surface
  fOpFinishMap["etchedteflonair"]=etchedteflonair;       // chemically etched surface, with teflon
  fOpFinishMap["etchedtioair"]=etchedtioair;             // chemically etched surface, with tio paint
  fOpFinishMap["etchedtyvekair"]=etchedtyvekair;         // chemically etched surface, with tyvek
  fOpFinishMap["etchedvm2000air"]=etchedvm2000air;       // chemically etched surface, with esr film
  fOpFinishMap["etchedvm2000glue"]=etchedvm2000glue;     // chemically etched surface, with esr film & meltmount

  fOpFinishMap["groundlumirrorair"]=groundlumirrorair;   // rough-cut surface, with lumirror
  fOpFinishMap["groundlumirrorglue"]=groundlumirrorglue; // rough-cut surface, with lumirror & meltmount
  fOpFinishMap["groundair"]=groundair;                   // rough-cut surface
  fOpFinishMap["groundteflonair"]=groundteflonair;       // rough-cut surface, with teflon
  fOpFinishMap["groundtioair"]=groundtioair;             // rough-cut surface, with tio paint
  fOpFinishMap["groundtyvekair"]=groundtyvekair;         // rough-cut surface, with tyvek
  fOpFinishMap["groundvm2000air"]=groundvm2000air;       // rough-cut surface, with esr film
  fOpFinishMap["groundvm2000glue"]=groundvm2000glue;     // rough-cut surface, with esr film & meltmount

  
  fOpModelMap["glisur"]=glisur;                  // original GEANT3 model
  fOpModelMap["unified"]=unified;                // UNIFIED model
  fOpModelMap["LUT"]=LUT;                        // Look-Up-Table model
  fOpModelMap["dichroic"]=dichroic;              // dichroic filter


}
//
G4double GaletDetectorConstruction::StoD(G4String str){
  G4double vl;
  const char* t = str;
  std::istringstream is(t);
  is >> vl;
  return vl;
}
