#include "FPSJumpPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"

AFPSJumpPad::AFPSJumpPad()
{
	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	RootComponent = DefaultScene;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 20.0f));
	BoxComp->SetupAttachment(DefaultScene);
	
	BoxComp->bHiddenInGame = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(DefaultScene);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSJumpPad::LaunchCharacter);
}

void AFPSJumpPad::LaunchCharacter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacter* theCharacter = Cast<ACharacter>(OtherActor);
	if (theCharacter)
	{

		FVector launchVelocity;
		{
			FVector forward = GetActorForwardVector();
			FVector right = GetActorRightVector();

			launchVelocity = UKismetMathLibrary::RotateAngleAxis(forward, LaunchDegree, right) * LaunchSpeed;
			launchVelocity = FVector(launchVelocity.X, launchVelocity.Y, UKismetMathLibrary::Abs(launchVelocity.Z));
		}

		theCharacter->LaunchCharacter(launchVelocity, true, true);		
	}

}



