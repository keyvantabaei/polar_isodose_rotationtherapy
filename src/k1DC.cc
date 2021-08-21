
#include "k1DC.hh"
#include "G4SDManager.hh"
#include "k1Geometery.cc"
#include "phantomSD.hh"
#include "G4UnionSolid.hh"

k1DC::k1DC():G4VUserDetectorConstruction(),_phantom_size(G4ThreeVector(0,0,0))
{
}
k1DC::~k1DC()
{
}

G4VPhysicalVolume* k1DC::Construct()
{
          Geometery geo;
          Struct _world =geo.Box("world","vaccum",G4ThreeVector(1.5*m,1.5*m,1.5*m),G4ThreeVector(),0);

          
          G4double r0=0;
          G4double r=GetVoxelRadius()*_rad_nb;
          G4double z=GetVoxelZ()*_z_nb;
          G4double phi=_theta_nb*GetVoxeltheta();
          auto tube = geo.Tube("tube1","water",r0,r,z,0,phi,G4ThreeVector(0,0,0),G4ThreeVector(0,0,0),_world._logic)._logic;
          _phantom_detector= geo.Tube_Voxelize_Detector(r,GetVoxeltheta(),z,_rad_nb,_theta_nb,_z_nb,tube,"water");
          // _phantom_detector= geo.Tube_Shell_Detector(10*cm,10*cm,1*cm,90*deg,1*cm,geo.Tube("t1","water",0,10*cm,10*cm,0,360*deg,G4ThreeVector(),G4ThreeVector(),_world._logic)._logic);




return _world._physical;
}
void k1DC::ConstructSDandField()
{
  phantomSD* _water_phantom_SD = new phantomSD("k1/phantomSD","edep");
  G4SDManager::GetSDMpointer()->AddNewDetector(_water_phantom_SD);
  SetSensitiveDetector(_phantom_detector,_water_phantom_SD);

}