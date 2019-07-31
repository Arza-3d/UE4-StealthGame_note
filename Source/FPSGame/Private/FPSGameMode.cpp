#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
}

///////////////////////////////////////////////////////////////////////////////////1a
// NEW: added bool as function param
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
///////////////////////////////////////////////////////////////////////////////////1z
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPointClass)
		{
			AActor* NewViewTarget;

			TArray<AActor*> ReturnedActors;

			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				NewViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(
				"SpectatingViewPoint class is nullptr. Please update GameMode class with valid subclass, Cannot change spectating view target"
			));
		}

	}

	///////////////////////////////////////////////////////2a
	// NEW: added bool as event param
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
	///////////////////////////////////////////////////////2z
}
