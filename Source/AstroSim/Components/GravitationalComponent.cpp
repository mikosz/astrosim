// Fill out your copyright notice in the Description page of Project Settings.

#include "GravitationalComponent.h"

#include "EngineUtils.h"
#include "GravitationalSystem.h"
#include "Math/UnitConversion.h"

// Sets default values for this component's properties
UGravitationalComponent::UGravitationalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked
	// every frame.  You can turn these features off to improve performance if you
	// don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

FMass UGravitationalComponent::GetSimulatedMass() const
{
	return Mass * GetScale(3);
}

double UGravitationalComponent::GetSimulatedRadius() const
{
	return RadiusM * GetScale();
}

void UGravitationalComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	auto* OwnerPrimitiveComp = Owner->GetComponentByClass<UPrimitiveComponent>();
	if (!IsValid(OwnerPrimitiveComp))
	{
		return;
	}

	auto BodyInstance = OwnerPrimitiveComp->GetBodyInstance();
	BodyInstance->SetMassOverride(GetSimulatedMass().GetValue<SafeMath::Units::FKilograms>());

	if (!IsValid(ParentGravitationalBody))
	{
		return;
	}

	const FVector ParentToThis_WS = Owner->GetActorLocation() - ParentGravitationalBody->GetActorLocation();
	const FVector ParentUp_WS = ParentGravitationalBody->GetTransform().GetUnitAxis(EAxis::Z);

	// #TODO_dontcommit: not necessarily correct, what with up being possibly aligned with to this - should assert it's not
	Velocity_CmPS_WS = FVector::CrossProduct(ParentUp_WS, ParentToThis_WS).GetSafeNormal()
					   * FUnitConversion::Convert(AverageOrbitalSpeed_KmPS, EUnit::Kilometers, EUnit::Centimeters);
}

void UGravitationalComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	constexpr auto GravitationalConstant = 6.674e-11;

	if (!IsValid(GravitationalSystem))
	{
		return;
	}

	auto* World = GetWorld();
	auto* Owner = GetOwner();

	if (!IsValid(World) || !IsValid(Owner))
	{
		return;
	}

	auto* OwnerPrimitiveComp = Owner->GetComponentByClass<UPrimitiveComponent>();
	const auto Location_WS = Owner->GetActorLocation();

	if (!IsValid(OwnerPrimitiveComp))
	{
		return;
	}

	DrawDebugDirectionalArrow(
		World,
		Location_WS,
		Location_WS + Velocity_CmPS_WS * GravitationalSystem->PlaybackSpeed * GetScale(),
		1.f,
		FColor::Green);
	// DrawDebugPoint(World, Location, 10.f, FColor::Green);

	const auto SimTime = DeltaTime * GravitationalSystem->PlaybackSpeed;
	auto DeltaVelocity_CmPS_WS = FVector::ZeroVector;

	for (auto* OtherActor : FActorRange{World})
	{
		if (!IsValid(OtherActor) || OtherActor == Owner)
		{
			continue;
		}

		auto* OtherGravitationalComp = OtherActor->GetComponentByClass<UGravitationalComponent>();
		if (!IsValid(OtherGravitationalComp))
		{
			continue;
		}

		const auto OtherLocation_WS = OtherActor->GetActorLocation();

		if (OtherLocation_WS.Equals(Location_WS))
		{
			continue;
		}

		auto ScaledDistance_Cm = 1.;
		auto AccelerationDir_WS = FVector{};
		(OtherLocation_WS - Location_WS).ToDirectionAndLength(AccelerationDir_WS, ScaledDistance_Cm);

		const auto UnscaledDistance_Cm = ScaledDistance_Cm / GetScale();
		const auto UnscaledDistance_M =
			FUnitConversion::Convert(UnscaledDistance_Cm, EUnit::Centimeters, EUnit::Meters);

		const auto Acceleration_MPerSSq =
			(GravitationalConstant * OtherGravitationalComp->Mass.GetValue<SafeMath::Units::FKilograms>())
			/ (UnscaledDistance_M * UnscaledDistance_M);
		const auto Acceleration_CmPerSSq = FUnitConversion::Convert(
			Acceleration_MPerSSq, EUnit::MetersPerSecondSquared, EUnit::CentimetersPerSecondSquared);

		const auto AccelerationToApply_CmPerSSq = AccelerationDir_WS * Acceleration_CmPerSSq;

		DrawDebugDirectionalArrow(
			World,
			Location_WS,
			Location_WS + AccelerationToApply_CmPerSSq * GravitationalSystem->PlaybackSpeed * GetScale(),
			1.f,
			FColor::Yellow);

		DeltaVelocity_CmPS_WS += AccelerationToApply_CmPerSSq * SimTime;
	}

	if (GravitationalSystem->IsPlaying())
	{
		Velocity_CmPS_WS += DeltaVelocity_CmPS_WS;
		const FVector Offset_Cm = Velocity_CmPS_WS * SimTime;
		Owner->SetActorLocation(Location_WS + Offset_Cm * GetScale());
	}
}

void UGravitationalComponent::ScaleAndPutInOrbit()
{
	if (!IsValid(GravitationalSystem))
	{
		return;
	}

	auto* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}

	// Location
	if (IsValid(ParentGravitationalBody))
	{
		auto* ParentGravitationalComp = ParentGravitationalBody->GetComponentByClass<UGravitationalComponent>();
		if (!IsValid(ParentGravitationalComp))
		{
			return;
		}

		const auto ParentLocation = ParentGravitationalBody->GetActorLocation();
		const auto Location = Owner->GetActorLocation();

		const auto Dir =
			Location.Equals(ParentLocation) ? FVector::RightVector : (Location - ParentLocation).GetUnsafeNormal();
		const auto ScaledLocation =
			ParentLocation
			+ Dir * FUnitConversion::Convert(OrbitSemiMajorAxis_Km, EUnit::Kilometers, EUnit::Centimeters)
				  * GravitationalSystem->GetScale();

		Owner->SetActorLocation(ScaledLocation);
	}

	// Scale
	{
		Owner->SetActorScale3D(FVector::One());

		const auto UnscaledExtent = Owner->GetComponentsBoundingBox().GetExtent().Length();

		if (FMath::IsNearlyZero(UnscaledExtent))
		{
			return;
		}

		const auto ScaledRadius =
			FUnitConversion::Convert(RadiusM, EUnit::Meters, EUnit::Centimeters) * GravitationalSystem->GetScale();
		const auto Scale = ScaledRadius / UnscaledExtent;

		Owner->SetActorScale3D(FVector{Scale});
	}
}

double UGravitationalComponent::GetScale(int32 Exp) const
{
	if (!IsValid(GravitationalSystem))
	{
		return 1.;
	}

	const double BaseScale = GravitationalSystem->GetScale();
	auto Result = 1.;

	for (; Exp > 0; --Exp)
	{
		Result *= BaseScale;
	}

	return Result;
}
