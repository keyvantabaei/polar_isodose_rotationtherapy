#include "HistoManager.hh"
#include "G4Run.hh"
#include "Run.hh"
#include "G4DataVector.hh"
#include "G4SystemOfUnits.hh"
#include "k1DC.hh"
#include "G4RunManager.hh"
Run::Run():G4Run()
{
   const k1DC* _detConstruction= static_cast<const k1DC*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  voxels=new G4double[_detConstruction->GetVoxelNB()];
    for(int i=0; i<_detConstruction->GetVoxelNB(); i++) voxels[i] =0;
}
Run::~Run(){}
void Run::Merge(const G4Run* run)
{
  const Run* localRun = static_cast<const Run*>(run);
  for(int i=0; i<(int)sizeof(voxels); i++) voxels[i] += localRun->voxels[i];
  G4Run::Merge(run);
}

void Run::EndOfRun()
{

}
void Run::AddData(G4double dose,G4int cn)
{
  voxels[cn]+=dose;
  // G4cout<<"-----------------------------------------____>> ;:::::::::::::::::"<<voxels[cn]<<G4endl;
}
