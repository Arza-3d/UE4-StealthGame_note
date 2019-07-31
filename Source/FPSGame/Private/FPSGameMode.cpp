// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = AFPSHUD::StaticClass();
}

/////////////////////////////////////////////////////////////1a
// NEW: complete mission to be called and start the event
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn) {
		InstigatorPawn->DisableInput(nullptr);
	}

	OnMissionCompleted(InstigatorPawn);
	/////////////////////////////////////////////////////////////1z
}
