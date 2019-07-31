#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:

	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

/////////////////////////////////////////////////////////////////////////1a
// NEW: Added beginplay and some overlapping delegate event
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	void PlayEffects();

public:
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
/////////////////////////////////////////////////////////////////////////1z
};
