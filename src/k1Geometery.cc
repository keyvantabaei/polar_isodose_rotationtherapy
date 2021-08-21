#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4PVParameterised.hh"
#include "G4PVParameterised.hh"
#include "Parametrisation.hh"
#include "G4SubtractionSolid.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
struct greaterSmaller { 
    G4VPhysicalVolume* _physical; 
    G4LogicalVolume* _logic;
    G4VSolid* _SOLID;
}; 
typedef struct greaterSmaller Struct; 
class Geometery 
{
public:
G4Material* create_material(G4String name)
{
    if(name=="water")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_WATER");
     return _world_mat;
    }
    if(name=="steel")
    {
    G4Element* eCr=new G4Element("cripton","Cr",36,86*g/mole);
    G4Element* eFe=new G4Element("iron","Fe",26,54*g/mole);
     G4Material* _steel = new G4Material("Steel",1*g/cm3,2);
     _steel->AddElement(eCr,17);
     _steel->AddElement(eFe,83);
     return _steel;
    }
    if(name=="tungsten")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_W");
     return _world_mat;
    }
    else if(name=="vaccum")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Galactic");
     return _world_mat;
    }
    else if(name=="pb")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_Pb");
     return _world_mat;
    }
        else if(name=="air")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_AIR");
     return _world_mat;
    }
            else if(name=="carbon")
    {
     G4NistManager* nist = G4NistManager::Instance();
     G4Material* _world_mat = nist->FindOrBuildMaterial("G4_C");
     return _world_mat;
    }
    else
    {
        return 0;
    }
}
Struct Box(G4String name,G4String mat_name,G4ThreeVector size,G4ThreeVector pos,G4LogicalVolume* mother_logic)
{
Struct s;
// world box
s._SOLID = new G4Box(name+"_SOLID",size.x()/2,size.y()/2,size.z()/2);
// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(0,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}
Struct Tube(G4String name,G4String mat_name,G4double r0,G4double r1,G4double h,G4double start_phi,G4double spin_phi,G4ThreeVector pos,G4ThreeVector rot,G4LogicalVolume* mother_logic)
{
Struct s;
// world box
s._SOLID = new G4Tubs(name+"_SOLID",r0,r1,h/2,start_phi,spin_phi);
// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name+"_LOGIC");
// world physical
G4RotationMatrix* myRotation = new G4RotationMatrix();
//aval hol x micharkhone axis haye mokhtasat ro bad hol axis Y
myRotation->rotateX(rot.x()); //az halat ghbli be andazeh rot.x() axis haye y va z ro becharkhon va be halat jadid bebar
myRotation->rotateY(rot.y()); //az halat ghbli be andazeh rot.y() axis haye x va z ro becharkhon va be halat jadid bebar
// myRotation->rotateZ(rot.z());
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(myRotation,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}
Struct Sphere(G4String name,G4String mat_name,G4double r0,G4double r1,G4double start_phi,G4double end_phi,G4double start_theta,G4double end_theta,G4ThreeVector pos,G4LogicalVolume* mother_logic)
{
Struct s;
// world box
s._SOLID = new G4Sphere(name,r0,r1,start_phi,end_phi,start_theta,end_theta);
// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name);
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name,0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(0,pos,s._logic,name,mother_logic,false,0,true); 
}
return s;
}
Struct Trapezoid(G4String name,G4String mat_name,G4double dx1,G4double dx2,G4double dy1,G4double dy2,G4double dz,G4ThreeVector pos,G4LogicalVolume* mother_logic)
{
Struct s;
// world box
s._SOLID = new G4Trd(name+"_SOLID",dx1/2,dx2/2,dy1/2,dy2/2,dz/2);

// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(0,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}
Struct GenericTrapezoid(G4String name,G4String mat_name,G4double pz,G4double py,G4double px,G4double pltx,G4ThreeVector pos,G4ThreeVector rot,G4LogicalVolume* mother_logic)
{
Struct s;
// world box
s._SOLID = new G4Trap(name+"_SOLID",pz,py,px,pltx);
G4RotationMatrix* myRotation = new G4RotationMatrix();
//aval hol x micharkhone axis haye mokhtasat ro bad hol axis Y
myRotation->rotateX(rot.x()); //az halat ghbli be andazeh rot.x() axis haye y va z ro becharkhon va be halat jadid bebar
myRotation->rotateY(rot.y()); //az halat ghbli be andazeh rot.y() axis haye x va z ro becharkhon va be halat jadid bebar
myRotation->rotateZ(rot.z());
// world logical
s._logic= new G4LogicalVolume(s._SOLID,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(myRotation,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(myRotation,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}



std::tuple<G4LogicalVolume*,G4ThreeVector> Replica_Z(G4LogicalVolume* _shape,G4ThreeVector size,G4double nz,G4String mat_name)
{
    G4double zcell_size=size.z()/nz;
    G4VSolid* repZ = new G4Box("repZ",size.x()/2,size.y()/2,zcell_size/2);
    G4LogicalVolume* voxellog = new G4LogicalVolume(repZ,create_material(mat_name),"repZ");
    new G4PVReplica("repZ",voxellog,_shape,kZAxis,nz,zcell_size);
    return std::make_tuple(voxellog,G4ThreeVector(size.x(),size.y(),zcell_size)) ;
}
std::tuple<G4LogicalVolume*,G4ThreeVector> Replica_Y(G4LogicalVolume* _shape,G4ThreeVector size,G4double ny,G4String mat_name)
{
    G4double ycell_size=size.y()/ny;
    G4VSolid* repY = new G4Box("repY",size.x()/2,ycell_size/2,size.z()/2);
    G4LogicalVolume* voxellog = new G4LogicalVolume(repY,create_material(mat_name),"repY");
    new G4PVReplica("repY",voxellog,_shape,kYAxis,ny,ycell_size);
    return std::make_tuple(voxellog,G4ThreeVector(size.x(),ycell_size,size.z())) ;

}
std::tuple<G4LogicalVolume*,G4ThreeVector> Replica_X(G4LogicalVolume* _shape,G4ThreeVector size,G4double nx,G4String mat_name)
{
    G4double xcell_size=size.x()/nx;
    G4VSolid* repX = new G4Box("repX",xcell_size/2,size.y()/2,size.z()/2);
    G4LogicalVolume* voxellog = new G4LogicalVolume(repX,create_material(mat_name),"repX");
    new G4PVReplica("repX",voxellog,_shape,kXAxis,nx,xcell_size);
    return std::make_tuple(voxellog,G4ThreeVector(xcell_size,size.y(),size.z())) ;

}

G4LogicalVolume* NestedParameterization(G4LogicalVolume* _shape,G4ThreeVector size,G4ThreeVector dividenumber,G4String mat_name)
{
    auto repY=Replica_Y(_shape,size,dividenumber.y(),mat_name);
    auto repX=Replica_X(std::get<0>(repY),std::get<1>(repY),dividenumber.x(),mat_name);
    
    G4ThreeVector senssize =G4ThreeVector(size.x()/dividenumber.x(),size.y()/dividenumber.y(),size.z()/dividenumber.z());
    auto water=create_material(mat_name);
    std::vector<G4Material*> mat(2,water);
    G4VSolid* paraZ = new G4Box("voxel",senssize.x()/2,senssize.y()/2,senssize.z()/2);
    G4LogicalVolume* voxellog = new G4LogicalVolume(paraZ,water,"voxel");
    // Parameterisation* voxelpara = new Parameterisation(senssize/2,(G4int)dividenumber.z(),mat);
    // new G4PVParameterised("voxel",voxellog,std::get<0>(repX),kUndefined,dividenumber.z(),voxelpara);
    return voxellog;
}


Struct HollowBox(G4String name,G4String mat_name,G4ThreeVector ourtsize,G4ThreeVector innersize,G4ThreeVector rel_pos,G4ThreeVector pos,G4LogicalVolume* mother_logic)
{
Struct s;
// outerBox
G4Box* outerBox = new G4Box(name+"_SOLID",ourtsize.x()/2,ourtsize.y()/2,ourtsize.z()/2);
// outerBox
G4Box* innerBox = new G4Box(name+"_SOLID",innersize.x()/2,innersize.y()/2,innersize.z()/2);
//subtrack
G4SubtractionSolid *hollowBox = new G4SubtractionSolid(name+"_HOLLOW",outerBox,innerBox,0,rel_pos);

// world logical
s._logic= new G4LogicalVolume(hollowBox,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(0,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}

Struct HollowCylander(G4String name,G4String mat_name,std::tuple<G4double,G4double,G4double,G4double,G4double> oc,std::tuple<G4double,G4double,G4double,G4double,G4double> ic,G4ThreeVector rel_pos,G4ThreeVector pos,G4ThreeVector rot,G4LogicalVolume* mother_logic)
{
    G4RotationMatrix* myRotation = new G4RotationMatrix();
//aval hol x micharkhone axis haye mokhtasat ro bad hol axis Y
// myRotation->rotateX(rot.x()); //az halat ghbli be andazeh rot.x() axis haye y va z ro becharkhon va be halat jadid bebar
// myRotation->rotateY(rot.y()); //az halat ghbli be andazeh rot.y() axis haye x va z ro becharkhon va be halat jadid bebar
// myRotation->rotateZ(rot.z());
Struct s;
// outerBox
G4Tubs* outerBox = new G4Tubs(name+"_SOLID",std::get<0>(oc),std::get<1>(oc),std::get<2>(oc)/2,std::get<3>(oc),std::get<4>(oc));
// outerBox
G4Tubs* innerBox = new G4Tubs(name+"_SOLID",std::get<0>(ic),std::get<1>(ic),std::get<2>(ic)/2,std::get<3>(ic),std::get<4>(ic));
//subtrack
G4SubtractionSolid *hollowBox = new G4SubtractionSolid(name+"_HOLLOW",outerBox,innerBox,0,rel_pos);

// world logical
s._logic= new G4LogicalVolume(hollowBox,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(myRotation,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}

Struct HeadHousing(G4String name,G4String mat_name,G4ThreeVector ourtsize,std::tuple<G4double,G4double,G4double,G4double,G4double> ic,G4ThreeVector rel_pos,G4ThreeVector pos,G4LogicalVolume* mother_logic)
{
Struct s;
// outerBox
G4Box* outerBox = new G4Box(name+"_SOLID",ourtsize.x()/2,ourtsize.y()/2,ourtsize.z()/2);
// outerBox
G4Tubs* innerBox = new G4Tubs(name+"_SOLID",std::get<0>(ic),std::get<1>(ic),std::get<2>(ic)/2,std::get<3>(ic),std::get<4>(ic));
//subtrack
G4SubtractionSolid *hollowBox = new G4SubtractionSolid(name+"_HOLLOW",outerBox,innerBox,0,rel_pos);

// world logical
s._logic= new G4LogicalVolume(hollowBox,create_material(mat_name),name+"_LOGIC");
// world physical
if(mother_logic==0)
{
s._physical =new G4PVPlacement(0,G4ThreeVector(),s._logic,name+"_PHYSI",0,false,0,true); 
}
else
{
 s._physical =new G4PVPlacement(0,pos,s._logic,name+"_PHYSI",mother_logic,false,0,true); 
}
return s;
}










G4LogicalVolume* Tube_Voxelize_Detector(G4double r,G4double phi ,G4double z,G4int rNo,G4int phiNo,G4int zNo,G4LogicalVolume* tube_logic,G4String mat_name)
{

     G4Material* _world_mat = create_material("water");
     std::vector<G4Material*> material(2,_world_mat);

    // phi rep number will be 2
    // phi = ((180 * phi)/M_PI)/phiNo;
    

    G4VSolid* repphi =new G4Tubs("repPhi",0,r,z/2,0,phi);
    G4LogicalVolume* voxellogphi = new G4LogicalVolume(repphi,_world_mat,"repPhi");
    new G4PVReplica("repPhi",voxellogphi,tube_logic,kPhi,phiNo,phi);



    // Z rep number will be 1
    G4double dz = z/zNo;
    G4VSolid* repZ =new G4Tubs("repZ",0,r,dz/2,0,phi);
    G4LogicalVolume* voxellogZ = new G4LogicalVolume(repZ,_world_mat,"repZ");
    new G4PVReplica("repZ",voxellogZ,voxellogphi,kZAxis,zNo,dz);


    // R rep number will be 0
    G4double dr = r/rNo;
    G4VSolid* repR =new G4Tubs("repR",0,dr,dz/2,0,phi);
    G4LogicalVolume* voxellogR = new G4LogicalVolume(repR,_world_mat,"repR");

    // G4cout
    // <<" ----------------------- >> Phoi :" <<phi
    // <<" ----------------------- >> r :"    <<r
    // <<" ----------------------- >> z :"    <<z
    // <<" ----------------------- >> rNo :"  <<rNo
    // <<" ----------------------- >> phiNo :"<<phiNo
    // <<" ----------------------- >> zNo :"  <<zNo
    // <<" ----------------------- >> dr :"   <<dr
    // <<" ----------------------- >> dz :"   <<dz
    // <<G4endl;

    Parametrisation* voxelpara = new Parametrisation(dr,phi,dz,material);
    new G4PVParameterised("repR",voxellogR,voxellogZ,kUndefined,rNo,voxelpara);

return voxellogR;
}


};