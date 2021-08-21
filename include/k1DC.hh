#ifndef k1DC_h
#define k1DC_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

const G4int _rad_nb = 100;
const G4int _theta_nb = 96;
const G4int _z_nb = 100;

const G4double _radius=1*CLHEP::mm;
const G4double _degree=3.75*CLHEP::deg;
const G4double _z=1*CLHEP::mm;


const G4ThreeVector phantomsize(10*CLHEP::cm,10*CLHEP::cm,10*CLHEP::cm);
const G4ThreeVector phantomsegments(100,100,100);

class k1DC  : public G4VUserDetectorConstruction
{
    public:
    k1DC();
    virtual ~k1DC();
virtual void ConstructSDandField();
virtual G4VPhysicalVolume* Construct();

G4LogicalVolume* GetPhantomVolume() const { return _phantom_detector; }

G4double GetVoxelRadius()   const{return _radius;}
G4double GetVoxeltheta()    const{return _degree;}
G4double GetVoxelZ()        const{return _z;}
// G4int    GetVoxelNB()       const{return _rad_nb*_theta_nb*_z_nb;}
G4int    GetVoxelNB()       const{return _z_nb*_rad_nb*_theta_nb;}

G4ThreeVector _phantom_size;
G4ThreeVector _cell_count;
private:
G4LogicalVolume* _phantom_detector;
};

#endif