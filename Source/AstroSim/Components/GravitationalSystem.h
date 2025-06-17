// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GravitationalSystem.generated.h"

/// Gravitational system playback state
UENUM()
enum class EGravitationalSystemState
{
	Paused UMETA(ToolTip = "Gravitational system simulation is paused"),
	Playing UMETA(ToolTip = "Gravitational system simulation is playing"),
	StepRequested,
	Stepping,
};

// #TODO_dontcommit
UCLASS()
class ASTROSIM_API UExample : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Str = TEXT("Dupa");

	UPROPERTY(EditAnywhere)
	int32 I = 42;
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

	// #TODO_dontcommit
	UPROPERTY(EditAnywhere, Instanced)
	UExample* ExamplePtr = nullptr;
	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<const UExample> ConstExamplePtr = nullptr;

	AGravitationalSystem();

	bool IsPlaying() const;

	double GetScale() const;

	virtual void BeginPlay() override;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	// #TODO_dontcommit
	virtual void PreEditChange(FProperty* PropertyThatWillChange) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
