// Fill out your copyright notice in the Description page of Project Settings.

#include "GravitationalSubsystem.h"

#include "EngineUtils.h"
#include "GravitationalSystem.h"
#include "ImGuiModule.h"

#include <imgui.h>

void UGravitationalSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGravitationalSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShowUI();
}

TStatId UGravitationalSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UAutoDestroySubsystem, STATGROUP_Tickables);
}

void UGravitationalSubsystem::ShowUI() const
{
	if (!ImGui::Begin("Gravitational"))
	{
		return;
	}

	for (auto* System : TActorRange<AGravitationalSystem>{GetWorld()})
	{
		ImGui::Text(TCHAR_TO_ANSI(*System->GetActorLabel()));

		if (IsValid(System))
		{
			ImGui::InputDouble("Scale base", &System->ScaleBase);
			ImGui::InputDouble("Scale exponent", &System->ScaleExp);
			ImGui::InputDouble("Playback speed", &System->PlaybackSpeed);

			if (ImGui::Button("Play / Pause"))
			{
				System->State =
					(System->IsPlaying() ? EGravitationalSystemState::Paused : EGravitationalSystemState::Playing);
			}

			ImGui::SameLine();

			ImGui::BeginDisabled(System->State != EGravitationalSystemState::Paused);
			if (ImGui::Button("Step"))
			{
				System->State = EGravitationalSystemState::StepRequested;
			}
			ImGui::EndDisabled();
		}

		ImGui::Separator();
	}

	ImGui::End();
}
