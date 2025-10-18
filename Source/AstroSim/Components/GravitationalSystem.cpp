// Fill out your copyright notice in the Description page of Project Settings.

#include "GravitationalSystem.h"

AGravitationalSystem::AGravitationalSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AGravitationalSystem::IsPlaying() const
{
	return State == EState::Stepping || State == EState::Playing;
}

double AGravitationalSystem::GetScale() const
{
	return FMath::Pow(ScaleBase, ScaleExp);
}

void AGravitationalSystem::BeginPlay()
{
	Super::BeginPlay();
}

void AGravitationalSystem::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (State == EState::StepRequested)
	{
		State = EState::Stepping;
	}
	else if (State == EState::Stepping)
	{
		State = EState::Paused;
	}
}
