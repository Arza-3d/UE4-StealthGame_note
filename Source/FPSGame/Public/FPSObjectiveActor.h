#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

//////////////////////////////1a
// NEW: added components
class UStaticMeshComponent;
class USphereComponent;
/////////////////////////////1z

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:

	AFPSObjectiveActor();

protected:

	////////////////////////////////////////////////////////2a
	// NEW: Added component here
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	////////////////////////////////////////////////////////2z

};
