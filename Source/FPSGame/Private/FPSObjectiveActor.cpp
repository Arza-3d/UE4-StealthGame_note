#include "FPSObjectiveActor.h"
//////////////////////////////////////////////1a
// NEW: added new component
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
//////////////////////////////////////////////1z

AFPSObjectiveActor::AFPSObjectiveActor()
{

	//////////////////////////////////////////////////////////////////////////////2a
	// NEW: added new component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);
	//////////////////////////////////////////////////////////////////////////////2z
}
