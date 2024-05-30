// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GravitationalComponent.generated.h"

class AGravitationalSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTROSIM_API UGravitationalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGravitationalComponent();

	UPROPERTY(EditAnywhere)
	TObjectPtr<AGravitationalSystem> GravitationalSystem = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ParentGravitationalBody = nullptr;

	UPROPERTY(EditAnywhere)
	double MassKg = 1.;

	UPROPERTY(EditAnywhere)
	double RadiusM = 1.;

	UPROPERTY(EditAnywhere)
	double AverageOrbitalSpeed_KmPS = 0.;

	UPROPERTY(EditAnywhere)
	double OrbitSemiMajorAxis_Km = 0.;

	double GetSimulatedMass() const;

	double GetSimulatedRadius() const;

	virtual void BeginPlay() override;

	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(CallInEditor)
	void ScaleAndPutInOrbit();

private:
	double GetScale(int32 Exp = 1) const;

	UPROPERTY()
	FVector Velocity_CmPS_WS = FVector::Zero();
};
