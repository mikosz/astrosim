// Fill out your copyright notice in the Description page of Project Settings.

#include "GravitationalSubsystemDeveloperToolkitTool.h"

#include "EngineUtils.h"
#include "GravitationalSystem.h"
#include "ImGuiDeveloperToolkit/ImGuiDeveloperToolkitWindow.h"
#include "ImGuiDeveloperToolkit/PropertyInspector.h"
#include "imgui.h"
#include "ImGuiDeveloperToolkit/AutoWidget.h"

FAnsiString UGravitationalSubsystemDeveloperToolkitTool::GetToolName() const
{
	return "Gravitational Subsystem";
}

EImGuiDeveloperToolkitToolContext UGravitationalSubsystemDeveloperToolkitTool::GetContext() const
{
	return EImGuiDeveloperToolkitToolContext::Editor | EImGuiDeveloperToolkitToolContext::Game;
}

void UGravitationalSubsystemDeveloperToolkitTool::Tick(
	const float DeltaTime, bool& bInOutShow, const EImGuiDeveloperToolkitToolContext Context, UWorld* World)
{
	using namespace ImGuiDeveloperToolkit;

	if (!bInOutShow)
	{
		return;
	}

	ON_SCOPE_EXIT
	{
		ImGui::End();
	};

	if (!ImGui::Begin("Gravitational", &bInOutShow))
	{
		return;
	}

	if (!IsValid(World))
	{
		return;
	}

	for (auto* System : TActorRange<AGravitationalSystem>{World})
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

		// #TODO_dontcommit
		InspectorSetup.ObjectSetup.bShowCategories = true;
		InspectorSetup.ObjectSetup.bShowHierarchy = false;
		InspectorSetup.OnlyChildrenOf = AActor::StaticClass();
		
		PropertyInspector::Inspect(TCHAR_TO_ANSI(*System->GetActorLabel()), *System, InspectorSetup);
		PropertyInspector::Inspect(
			TCHAR_TO_ANSI(*System->GetActorLabel()), const_cast<const AGravitationalSystem&>(*System), InspectorSetup);
	}
}

