//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: GaletScoreId.hh,v 1.4 2001/07/11 10:08:17 gunter Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
//
//---------------------------------------------------------------
//
// GaletScoreId.hh
//
// Class Description:
//
//  2015-12-14  T.ASO
//  2016-01-21  T.Aso ParentTrkId
//  2016-01-21  T.Aso ParentPID, TriggerBit
//  2016-04-12  T.Aso Trigger Position
//
//---------------------------------------------------------------

#ifndef GaletScoreId_h
#define GaletScoreId_h 1

enum GaletScoreId
{
  // 0 
  EvnoScId,
  TrkScId,
  PidScId,
  EdepScId,
  DoseScId,
  StepLScId,
  XidScId,
  YidScId,
  ZidScId,
  ModidScId,
  SecidScId,
  WeigtScId,
  ProcScId,
  KinEScId,
  XpointScId,
  YpointScId,
  ZpointScId,
  PxScId,
  PyScId,
  PzScId,
  TimeScId,
  XvtxScId,
  YvtxScId,
  ZvtxScId,
  ParentTrkScId,
  ParentPidScId,
  TrigbitScId,
  TrigPosXScId,
  TrigPosYScId,
  TrigPosZScId
};
#endif


