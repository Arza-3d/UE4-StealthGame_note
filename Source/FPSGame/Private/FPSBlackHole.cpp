#include "FPSBlackHole.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/GameFramework/Pawn.h"


AFPSBlackHole::AFPSBlackHole()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphere->SetupAttachment(MeshComp);
	InnerSphere->SetSphereRadius(50.0f);

	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphere->SetupAttachment(MeshComp);
	OuterSphere->SetSphereRadius(1200.0f);

	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::HandleInnerSphereBeginOverlap);
}

void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlapedComps;
	OuterSphere->GetOverlappingComponents(OverlapedComps);

	const float sphereRadius = OuterSphere->GetScaledSphereRadius();

	for (int i = 0; i < OverlapedComps.Num(); i++)
	{
		UPrimitiveComponent* primComp = OverlapedComps[i];

		if (primComp && primComp->IsSimulatingPhysics())
		{
			primComp->AddRadialForce(GetActorLocation(), sphereRadius, -3000.0f, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBlackHole::HandleInnerSphereBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
		OtherActor->Destroy();
}



