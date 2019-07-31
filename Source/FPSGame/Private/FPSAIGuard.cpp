#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"

AFPSAIGuard::AFPSAIGuard()
{
  PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
  ///////////////////////////////1a
  // NEW: default state is idle
  GuardState = EAIState::Idle;
  ///////////////////////////////1z
}

void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
  ////////////////////////////////////2a
  // NEW: on seen alerted
	SetGuardState(EAIState::Alerted);
  ////////////////////////////////////2z

}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector & Location, float Volume)
{
  //////////////////////////////////////////3a
  // NEW: if already alerted don't do this
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
  //////////////////////////////////////////3z
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
  ///////////////////////////////////////4a
  // NEW: Change to suspicious
	SetGuardState(EAIState::Suspicious);
  ///////////////////////////////////////4z

}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}

/////////////////////////////////////////////////////5a
// NEW: change guard state function and EVENT!!!
void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}
	GuardState = NewState;

	OnStateChanged(NewState);
}
/////////////////////////////////////////////////////5z
