#include "FPSObjectiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
/////////////////////////////////////////////////1a
// NEW: need this for emitting particle system
#include "Kismet/GameplayStatics.h"
/////////////////////////////////////////////////1z

AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);

	/////////////////////////////////////////////////////////////////////2a
	// NEW: edit collision
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	/////////////////////////////////////////////////////////////////////2z
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();
}
