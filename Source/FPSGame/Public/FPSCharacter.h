#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class AFPSProjectile;
class USoundBase;
class UAnimSequence;
class UPawnNoiseEmitterComponent;


UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* Mesh1PComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

public:
	AFPSCharacter();

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	UAnimSequence* FireAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bIsCarryingObjective;

protected:

	void Fire();

	////////////////////////////////////////////////
	// NEW: added server implementable function   //
	UFUNCTION(Server, Reliable, WithValidation)   //
	void ServerFire();                            //
	////////////////////////////////////////////////

	void MoveForward(float Val);

	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

};
