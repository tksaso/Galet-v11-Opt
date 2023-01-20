#ifndef GaletSD_HH
#define GaletSD_HH

#include "G4VSensitiveDetector.hh"
#include "GaletHit.hh"
#include "G4MProcessType.hh"
#include "G4ThreeVector.hh"
#include <map>


//========================================================================
//
// (Modification)
// 2017-08-20
//========================================================================

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class GaletSD : public G4VSensitiveDetector {
public:
  GaletSD(const G4String &name,
          const G4String &colname="HitsCollection",
          G4int verb=0);

  ~GaletSD();

  void Initialize(G4HCofThisEvent * HCE);
  G4bool ProcessHits(G4Step * aStep, G4TouchableHistory * ROhist);
  void EndOfEvent(G4HCofThisEvent * HCE);
  void clear();
  void DrawAll();
  void PrintAll();

  G4bool IsNewEntry();
  G4bool IsEndOfEntry();

  void SetZeroEdep(G4bool b = true) { bEdep = b; }; 
  G4bool GetZeroEdep() { return bEdep; }; 
  void SetCheckTrackID(G4bool b = true) { bCheckTrackID = b; }; 
  G4bool GetCheckTrackID() { return bCheckTrackID; };

  void StopOpticalPhoton(G4bool b = true){ bOpticalPhotonStop = b; };

  void SetVerbose(G4int v=0) { verbose = v; }; 
  G4int GetVerbose() { return verbose; }; 

  void SetDepth(G4int d_x, G4int d_y, G4int d_z,  G4int d_m=0, G4int d_s=0) 
  { fDepth[0] = d_x; fDepth[1] = d_y;  fDepth[2] = d_z;
    fDepth[3] = d_m; fDepth[4] = d_s; }; 
  G4int GetDepth(G4int i)
  { return fDepth[i];};

  void SetSaveStep(G4bool flg=true){  bStep = flg; }
  G4bool GetSaveStep(){ return  bStep; }

  void SetNxyzMod(G4int nx, G4int ny, G4int nz)
  { NxyzMod[0] = nx; NxyzMod[1] = ny; NxyzMod[2] = nz; };
  G4int GetNxyzMod(G4int i) const { return NxyzMod[i]; };

private:
  G4int    HCID;
  G4String SDName;
  GaletHitsCollection * HCollection;

  GaletHit *       currentHit;
  G4Track *           track;
  G4VPhysicalVolume * currentPV;

  G4int fDepth[5];

  G4int PID;
  G4int theAtomicNumber;
  G4int theAtomicMass;
  G4int unitXID;
  G4int unitYID;
  G4int unitZID;
  G4int unitModID;
  G4int unitSecID;
  //
  G4int NxyzMod[3];
  //
  G4int trackID;
  G4int parentTrkID;

  G4StepPoint *        preStepPoint;
  G4StepPoint *        postStepPoint;
  G4TouchableHistory * touchable;
  G4double             EDeposit;
  G4double time;
  G4ThreeVector        hitPoint;
  G4ThreeVector        postPoint;
  G4ThreeVector        unitPoint;
  G4ThreeVector        primVertex;
  G4ThreeVector        momentum;
  G4double             incidentKinE;

  G4double  weight;

  G4double dose;

  G4double stepL;
  G4int    stepNumber;

  G4VUserTrackInformation* trackInfo;

  std::map<G4String, GaletHit *> hitmap;
  G4String key;

  G4bool bEdep;
  G4bool bStep;
  G4bool bCheckTrackID;
  G4int verbose;

  G4bool bOpticalPhotonStop;
  
private:
  void getStepInfo(G4Step * aStep);
  void createNewHit();
  void updateHit();
  void StoreHit(GaletHit * ahit);

};

#endif
