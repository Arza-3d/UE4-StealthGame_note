#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"

AFPSAIGuard::AFPSAIGuard()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}
