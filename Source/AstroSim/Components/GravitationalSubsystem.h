// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/WorldSubsystem.h"

#include "GravitationalSubsystem.generated.h"

UCLASS()
class ASTROSIM_API UGravitationalSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
};
