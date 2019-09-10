#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSJumpPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSJumpPad : public AActor
{
	GENERATED_BODY()
	
public:	

	AFPSJumpPad();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USceneComponent* DefaultScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Launch", Meta = (ClampMin = "0"))
	float LaunchSpeed = 300.0f;

	// in degree
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Launch")
	float LaunchDegree = 30.0f;

private:

	UFUNCTION()
	void LaunchCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
