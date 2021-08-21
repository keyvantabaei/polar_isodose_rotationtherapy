


#include "k1AI.hh"
#include "k1PG.hh"
#include "k1EA.hh"
#include "k1RA.hh"
#include "HistoManager.hh"


k1AI::k1AI()
 : G4VUserActionInitialization()
{}



k1AI::~k1AI()
{}

void k1AI::BuildForMaster() const
{
HistoManager* histo=new HistoManager();
SetUserAction(new k1RA(histo));
}


void k1AI::Build() const
{
  HistoManager* histo=new HistoManager();
  k1RA* run_action=new k1RA(histo);
  SetUserAction(new k1EA(run_action,histo));
  SetUserAction(new k1RA(histo));
  SetUserAction(new k1PG);
}  

