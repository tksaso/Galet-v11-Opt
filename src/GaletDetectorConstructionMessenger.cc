// ----------------------------------------------------------------------------
//
//
//    GaletDetectorConstructionMessenger
//
//  (Description)
//    2015 T.ASO 
//
// ----------------------------------------------------------------------------
#include "GaletDetectorConstructionMessenger.hh"
#include "GaletDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4Tokenizer.hh"

GaletDetectorConstructionMessenger::
GaletDetectorConstructionMessenger(GaletDetectorConstruction * det)
:fDet(det)
{  
 listDir = new G4UIdirectory("/Galet/det/");

 // Dump MPT                                                                          
 dumpMPTCmd = new G4UIcmdWithAString("/Galet/det/dumpMPT",this);
 dumpMPTCmd->SetGuidance("Dump Material Property Table");
 dumpMPTCmd->SetParameterName("matname",false);
 dumpMPTCmd->AvailableForStates(G4State_Idle);
 //
 G4UIparameter* param = 0;
 //
 ScintiMatCmd = new G4UIcommand("/Galet/det/set/ScintiMaterial",this);
 ScintiMatCmd->SetGuidance("Set Optical Material Property");
 param = new G4UIparameter("matname",'s',false);
 ScintiMatCmd->SetParameter(param);
 param = new G4UIparameter("filename",'s',false);
 ScintiMatCmd->SetParameter(param);
 ScintiMatCmd->AvailableForStates(G4State_Idle);
 //
 OptMatCmd = new G4UIcommand("/Galet/det/set/OptMaterial",this);
 OptMatCmd->SetGuidance("Set Optical Material Property");
 param = new G4UIparameter("matname",'s',false);
 OptMatCmd->SetParameter(param);
 param = new G4UIparameter("filename",'s',false);
 OptMatCmd->SetParameter(param);
 OptMatCmd->AvailableForStates(G4State_Idle);
 //                                                                                   
 OptSkinCmd = new G4UIcommand("/Galet/det/set/OptSkin",this);
 OptSkinCmd->SetGuidance("Set Optical Skin Surface");
 param = new G4UIparameter("logname",'s',false);
 OptSkinCmd->SetParameter(param);
 param = new G4UIparameter("filename",'s',false);
 OptSkinCmd->SetParameter(param);
 OptSkinCmd->AvailableForStates(G4State_Idle);
 //                                                                                   
 OptBorderCmd= new G4UIcommand("/Galet/det/set/OptBorder",this);
 OptBorderCmd->SetGuidance("Set Optical Border Surface");
 param = new G4UIparameter("phys1name",'s',false);
 OptBorderCmd->SetParameter(param);
 param = new G4UIparameter("phys2name",'s',false);
 OptBorderCmd->SetParameter(param);
 param = new G4UIparameter("filename",'s',false);
 OptBorderCmd->SetParameter(param);
 OptBorderCmd->AvailableForStates(G4State_Idle);


}

GaletDetectorConstructionMessenger::~GaletDetectorConstructionMessenger()
{
  delete dumpMPTCmd;
  delete ScintiMatCmd;
  delete OptMatCmd;
  delete OptSkinCmd;
  delete OptBorderCmd;
  delete listDir;
}

void GaletDetectorConstructionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  G4cout << command->GetCommandName()<<" " <<newValue<<G4endl;
  if (command == dumpMPTCmd){
    fDet->DumpMPT(newValue);
  } else if ( command == ScintiMatCmd ){
    G4Tokenizer next(newValue);
    G4String matname = next();
    G4String filename = next();
    fDet->SetScintillationProperty(matname, filename);
    //                                                                                 
  } else if ( command == OptMatCmd ){
    G4Tokenizer next(newValue);
    G4String matname = next();
    G4String filename = next();
    fDet->SetMaterialProperty(matname, filename);
    //                                                                                 
  } else if ( command == OptSkinCmd ){
    G4Tokenizer next(newValue);
    G4String logname = next();
    G4String filename = next();
    fDet->SetSkinProperty(logname, filename);
    //                                                                                 
  } else if ( command == OptBorderCmd ){
    G4Tokenizer next(newValue);
    G4String phys1name = next();
    G4String phys2name = next();
    G4String filename = next();
    fDet->SetBorderProperty(phys1name, phys2name, filename);
  }
  
}
