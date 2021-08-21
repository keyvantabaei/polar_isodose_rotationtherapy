#include "Parametrisation.hh"


#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Tubs.hh"
Parametrisation::Parametrisation(G4double r,G4double phi,G4double z,std::vector<G4Material*>& mat):
G4VNestedParameterisation(),dr(r),dphi(phi),dz(z)
{

fMat=mat;
}

Parametrisation::~Parametrisation(){}

void Parametrisation::ComputeTransformation(const G4int copyNo,G4VPhysicalVolume* pv) const
{
  // G4ThreeVector origin(0,0,0);
  // pv->SetTranslation(origin);
  // pv->SetRotation(0);
}
void Parametrisation::ComputeDimensions (G4Tubs& tube,const G4int copyNo, const G4VPhysicalVolume*) const
{
tube.SetInnerRadius(copyNo*dr);
tube.SetOuterRadius(copyNo*dr+dr) ;
tube.SetZHalfLength(dz/2);
tube.SetStartPhiAngle(0);
tube.SetDeltaPhiAngle(dphi);

}






G4Material* Parametrisation::ComputeMaterial(G4VPhysicalVolume* /*currentVol*/, const G4int copyNo, const G4VTouchable* parentTouch)
{
  if(parentTouch==0) return fMat[0]; // protection for initialization and
  //                                    // vis at idle state
  // // Copy number of voxels. 
  // // Copy number of X and Y are obtained from replication number.
  // // Copy nymber of Z is the copy number of current voxel.
  // G4int ix = parentTouch->GetReplicaNumber(0);
  // G4int iy = parentTouch->GetReplicaNumber(1);
  // G4int iz = copyNo;
  // // For demonstration purpose,a couple of materials are chosen alternately.
  // G4Material* mat=0;
  // if ( ix%2 == 0 && iy%2 == 0 && iz%2 == 0 ) mat = fMat[0];
  // else mat = fMat[1];

  return fMat[0];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//  Number of Materials
//  Material scanner is required for preparing physics tables and so on before 
//  stating simulation, so that G4 has to know number of materials.
G4int Parametrisation::GetNumberOfMaterials() const{
  return fMat.size();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// GetMaterial
//  This is needed for material scanner and realizing geometry.
//
G4Material* Parametrisation::GetMaterial(G4int i) const{
  return fMat[0];
}