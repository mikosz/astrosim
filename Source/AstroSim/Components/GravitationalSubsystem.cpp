#include "GravitationalSubsystem.h"

void UGravitationalSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGravitationalSubsystem::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TStatId UGravitationalSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UAutoDestroySubsystem, STATGROUP_Tickables);
}
