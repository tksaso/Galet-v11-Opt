//========================================================================
//
// Created by T.Aso
//
// (Modification)
//========================================================================
#ifndef GaletHit_h
#define GaletHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4MProcessType.hh"
#include "GaletScoreId.hh"
#include "GaletTrigBit.hh"
#include <vector>

#include "G4Version.hh"

class GaletHit : public G4VHit {
public:

  GaletHit();
  GaletHit(const GaletHit & right);
  ~GaletHit();

  const GaletHit & operator=(const GaletHit & right);
  G4int operator==(const GaletHit & right) const;

  inline void * operator new(size_t);
  inline void operator delete(void * aHit);

  void Draw();
  void Print();

#if G4VERSION_NUMBER >= 930
  const std::map<G4String,G4AttDef>* GetAttDefs() const;
  std::vector<G4AttValue>* CreateAttValues() const;
#endif

private:
  G4ThreeVector hitPoint;   // Identical to entering point.
  G4ThreeVector exitPoint;
  G4ThreeVector primVertex;
  G4ThreeVector unitPoint;

  G4ThreeVector momentum;
  G4double incidentKinE;
  G4double exitKinE;
  G4int PID;
  G4int theAtomicNumber; // for ions
  G4int theAtomicMass;   // for ions
  G4int trackID;
  G4int parentTrkID;
  G4int parentPID;
  //
  G4int unitXID;
  G4int unitYID;
  G4int unitZID;

  // 
  G4int unitModID;
  G4int unitSecID;

  G4double EDeposit;
  G4double time;
  G4double weight;

  G4double dose;

  G4double slength;

  G4MProcessType pType;

  GaletTrigBit   trigBit;
  G4ThreeVector trigPos;

  G4int stepNumber;
  std::vector<G4ThreeVector> StepPosVec;
  std::vector<G4double> StepDEVec;

#if G4VERSION_NUMBER >= 930
  static std::map<G4String,G4AttDef> fAttDefs; // for gMocrenFile driver
#endif

public:
  void SetEntry(const G4ThreeVector & _hitPoint){ hitPoint = _hitPoint;}
  G4ThreeVector GetEntry() const { return hitPoint;}

  void SetExit(const G4ThreeVector & _hitPoint){ exitPoint = _hitPoint; }
  G4ThreeVector GetExit() const { return exitPoint;}

  void AddStepEntry(const G4ThreeVector & _hitPoint){ StepPosVec.push_back(_hitPoint); };
  void AddStepEdep(G4double edep){ StepDEVec.push_back(edep); };

  const std::vector<G4ThreeVector>& GetStepPosVec(){ return StepPosVec; };
  const std::vector<G4double>& GetStepDEVec(){ return StepDEVec; };

  void SetHitPoint(const G4ThreeVector & _hitPoint);
  G4ThreeVector GetHitPoint() const;

  void SetUnitPoint(const G4ThreeVector & _unitPoint);
  G4ThreeVector GetUnitPoint() const;

  void SetPrimaryVertex(const G4ThreeVector & _primVertex);
  G4ThreeVector GetPrimaryVertex() const;

  void SetMomentum(const G4ThreeVector & _momentum);
  G4ThreeVector GetMomentum() const;
  void SetIncidentKinE(const G4double & _incidentKinE);
  G4double GetIncidentKinE() const;
  void SetExitKinE(const G4double & _exitKinE);
  G4double GetExitKinE() const;

  void SetPID(const G4int & _PID);
  G4int GetPID() const;

  void SetAtomicNumber(G4int z) { theAtomicNumber = z; }
  G4int GetAtomicNumber() const { return theAtomicNumber; }

  void SetAtomicMass(G4int a) { theAtomicMass = a; }
  G4int GetAtomicMass() const { return theAtomicMass; }

  void SetTrackID(const G4int & _trackID);
  G4int GetTrackID() const;

  void SetParentTrackID(const G4int & _parentTrkID);
  G4int GetParentTrackID() const;

  void SetParentPID(const G4int & _parentPID);
  G4int GetParentPID() const;

  void SetUnitID(const G4int & _unitXID,
                 const G4int & _unitYID,
                 const G4int & _unitZID);
  void SetUnitXID(const G4int & _unitXID);
  G4int GetUnitXID() const;
  void SetUnitYID(const G4int & _unitYID);
  G4int GetUnitYID() const;
  void SetUnitZID(const G4int & _unitZID);
  G4int GetUnitZID() const;
  //
  void SetUnitModID(const G4int & _unitModID)
  { unitModID = _unitModID; };
  G4int GetUnitModID() const { return unitModID;};
  //
  void SetUnitSecID(const G4int & _unitSecID)
  { unitSecID = _unitSecID; };
  G4int GetUnitSecID() const { return unitSecID;};

  //
  void SetEnergyDeposit(const G4double & _EDeposit);
  G4double GetEnergyDeposit() const;
  void AddEnergyDeposit(const GaletHit & _aHit);
  void AddEnergyDeposit(const G4double & _EDeposit);

  void SetGlobalTime(G4double time_) { time = time_; }
  G4double GetGlobalTime() const { return time; }

  void SetWeight(G4double w) { weight = w; }
  G4double GetWeight() const { return weight; }
  
  void SetDose(G4double d) { dose = d; }
  G4double GetDose() const { return dose; }
  void AddDose(const GaletHit & _aHit) {dose += _aHit.GetDose();}
  void AddDose(const G4double & _dose) {dose += _dose;}

  void SetStepLength(G4double sl){slength = sl;}
  G4double GetStepLength(){return slength; }
  void AddStepLength(const G4double sl){ slength += sl; }

  void SetStepNumber(G4int n) { stepNumber = n; }
  G4int GetStepNumber()const { return stepNumber; }

  void SetCreatorProcessType(const G4MProcessType type);
  G4MProcessType GetCreatorProcessType()const;

  void SetTrigBit(const GaletTrigBit& tbit){ trigBit = tbit;};
  const GaletTrigBit& GetTrigBit()const{return trigBit;};
  unsigned long  GetTriggerBitByULong(){ return trigBit.to_ulong(); };
  void SetTrigPos(const G4ThreeVector& pos){ trigPos = pos; };
  const G4ThreeVector& GetTrigPos(){ return trigPos; };

  G4double GetByScId(G4int scid, const G4double unit=1.0, const G4int evno=0);
  G4int    GetByScIdI(G4int scid, const G4int evno=0);

};

typedef G4THitsCollection<GaletHit> GaletHitsCollection;

extern G4ThreadLocal G4Allocator<GaletHit>* GaletHitAllocator;

inline void * GaletHit::operator new(size_t)
{
  if ( !GaletHitAllocator ){
    GaletHitAllocator = new G4Allocator<GaletHit>;
  }
  void * aHit;
  aHit = (void *) GaletHitAllocator->MallocSingle();
  return aHit;
}

inline void GaletHit::operator delete(void * aHit)
{
  if ( !GaletHitAllocator ){
    GaletHitAllocator = new G4Allocator<GaletHit>;
  }
  GaletHitAllocator->FreeSingle((GaletHit *) aHit);
}

#endif
