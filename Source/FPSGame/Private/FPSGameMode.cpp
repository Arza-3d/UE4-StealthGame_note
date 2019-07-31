#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
///////////////////////////////////////////1a
// NEW: it is used to GetAllActorsOfClass
#include "Kismet/GameplayStatics.h"
///////////////////////////////////////////1z

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////2a
		// NEW: move the camera to other actor if the class is defined in blueprint
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
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////2z

	}

	OnMissionCompleted(InstigatorPawn);

}
