
#include "k1RA.hh"
#include "k1DC.hh"
#include "HistoManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>

G4Run* k1RA::GenerateRun()
{ 
  _run = new Run();
  return _run;
}
k1RA::k1RA(HistoManager* histo): G4UserRunAction(),_histo(histo)
{  
doses=new G4double[1000000];
}


k1RA::~k1RA()
{ }


void k1RA::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  _histo->Book();

  for(int i=0;i<1000000;i++)doses[i]=0;

    // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}


void k1RA::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;



Run* _run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
auto doseMatrix=_run->GetDose();

  // std::ofstream myfile;
  // myfile.open ("result.txt");
   const k1DC* _detConstruction= static_cast<const k1DC*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());



//isocenter
G4double isocenter_s=0;
G4double isocenter=1e12;
for(int i=0;i<96;i++)
{
  for(int j=0;j<100;j++)
  {
    G4int index = j*100 + (i*10000);
    isocenter_s+=doseMatrix[index];
  }
  if(isocenter_s<isocenter)
    isocenter=isocenter_s;
}

G4double dr=_detConstruction->GetVoxelRadius();
G4double dz=_detConstruction->GetVoxelZ();
G4double dphi=_detConstruction->GetVoxeltheta();

for(int j=0;j<_detConstruction->GetVoxelNB();j++)
{

  if(doseMatrix[j]!=0)
  {
          G4int iphi=(G4int)j/10000;
          G4int iz=(G4int)((j-iphi*10000)/100);
          G4int ir=(G4int)(j-((G4int)j/10000)*10000 - ((G4int)((j-iphi*10000)/100))*100 );

          // G4double theta=(M_PI*3.75*iphi)/180;
          // G4double R=((ir+1)*dr - ir*dr)/2+ir*dr;
          // G4double R  = ir*dr;
          // G4double ix = R*cos(theta);
          // G4double iy = R*sin(theta);

          // G4cout
          // <<" ---------->>  R :"<< R
          // <<" ---------->>  Phi :"<< theta
          // <<" ---------->>  Phi :"<< 3.75*iphi
          // <<" ---------->>  Z :"<<round(iz)
          // <<" ---------->>  X :"<<round(ix)
          // <<" ---------->>  Y :"<<round(iy)
          // // <<" ir :"<<ir
          // // <<" iphi :"<<iphi
          // <<G4endl;


          // myfile  <<" ---------->>  R :"    << R           <<G4endl;
          // myfile  <<" ---------->>  Phi :"  << theta       <<G4endl;
          // myfile  <<" ---------->>  Phi :"  << 3.75*iphi   <<G4endl;
          // myfile  <<" ---------->>  Z :"    <<round(iz)    <<G4endl;;
          // myfile  <<" ---------->>  X :"    <<round(ix)    <<G4endl;
          // myfile  <<" ---------->>  Y :"    <<round(iy)    <<G4endl;
          // myfile  <<" ---------->>  Dose :" <<doseMatrix[j]    <<G4endl;
          // myfile  <<"-------------------------------------------------------- "    <<G4endl;




          _histo->Fill_3D_Histogram_Polar(ir,iphi+1,iz,(doseMatrix[j]/isocenter)*100);
          // _histo->Fill_3D_Histogram_CART(ix,iy,iz,doseMatrix[j]);
          // _histo->Fill_3D_TTree_CART(round(ix),round(iy),iz,doseMatrix[j]);

  }
}
  // myfile.close();

_histo->Save();
G4cout<<"Matrix Dose Saved ./"<<G4endl;
}
