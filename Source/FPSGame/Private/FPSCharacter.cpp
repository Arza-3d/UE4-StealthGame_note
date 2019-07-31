#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PawnNoiseEmitterComponent.h"


AFPSCharacter::AFPSCharacter()
{

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight);
	CameraComponent->bUsePawnControlRotation = true;

	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->RelativeRotation = FRotator(2.0f, -15.0f, 5.0f);
	Mesh1PComponent->RelativeLocation = FVector(0, 0, -160.0f);

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");

	NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComponent"));
}


void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}


void AFPSCharacter::Fire()
{

	ServerFire();

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation)
	{

		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// NEW: server function                                                                  //
void AFPSCharacter::ServerFire_Implementation()                                          //
{                                                                                        //
	if (ProjectileClass)                                                                 //
	{                                                                                    //
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");          //
		FRotator MuzzleRotation = GunMeshComponent->GetSocketRotation("Muzzle");         //
                                                                                         //
		FActorSpawnParameters ActorSpawnParams;                                          //
		ActorSpawnParams.SpawnCollisionHandlingOverride =                                //
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding; //
		ActorSpawnParams.Instigator = this;                                              //
                                                                                         //
		GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation,          //
			MuzzleRotation, ActorSpawnParams);                                           //
	}                                                                                    //
}                                                                                        //
                                                                                         //
bool AFPSCharacter::ServerFire_Validate()                                                //
{                                                                                        //
	return true;                                                                         //
}                                                                                        //
///////////////////////////////////////////////////////////////////////////////////////////

void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}
