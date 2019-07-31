#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;
////////////////////////////1a
// NEW: added decal class
class UDecalComponent;
////////////////////////////1z

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()

public:

	AFPSExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	///////////////////////////////////////////////////////2a
	// NEW: added decal component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;
	///////////////////////////////////////////////////////2z

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
