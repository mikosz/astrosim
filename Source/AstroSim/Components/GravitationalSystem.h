// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GravitationalSystem.generated.h"

UENUM()
enum class EGravitationalSystemState
{
	Paused,
	Playing,
	StepRequested,
	Stepping,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTROSIM_API AGravitationalSystem : public AActor
{
	GENERATED_BODY()

public:
	using EState = EGravitationalSystemState;

	UPROPERTY(EditAnywhere)
	EGravitationalSystemState State = EState::Paused;

	UPROPERTY(EditAnywhere)
	double PlaybackSpeed = 1.;

	UPROPERTY(EditAnywhere)
	double ScaleBase = 10.;

	UPROPERTY(EditAnywhere)
	double ScaleExp = 1.;

	AGravitationalSystem();

	bool IsPlaying() const;

	double GetScale() const;

	virtual void BeginPlay() override;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
};
