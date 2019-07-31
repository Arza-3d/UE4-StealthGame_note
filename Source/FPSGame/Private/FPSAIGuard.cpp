#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

AFPSAIGuard::AFPSAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);

	//////////////////////////////////////////////////////////////////////////////1a
	// NEW: bind function to OnHearNoise delegate
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	//////////////////////////////////////////////////////////////////////////////1z
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////2a
// NEW: function to bind
void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector & Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}
/////////////////////////////////////////////////////////////////////////////////////////////////2z
