// Fill out your copyright notice in the Description page of Project Settings.

#include "GravitationalSubsystemDeveloperToolkitTool.h"

#include "EngineUtils.h"
#include "GravitationalSystem.h"
#include "ImGuiDeveloperToolkit/ImGuiDeveloperToolkitWindow.h"
#include "ImGuiDeveloperToolkit/PropertyInspector.h"
#include "imgui.h"

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

		PropertyInspector::Inspect(TCHAR_TO_ANSI(*System->GetActorLabel()), *System);
		PropertyInspector::Inspect(
			TCHAR_TO_ANSI(*System->GetActorLabel()), const_cast<const AGravitationalSystem&>(*System));
	}
}

// #TODO_dontcommit
#if 0

// struct

USTRUCT(DisplayName = "Strukturka wewnętrzna")
struct ASTROSIM_API FInspectorTestInternalStruct
{
	GENERATED_BODY()

	UPROPERTY(DisplayName = "Intidżer 1")
	int32 Integer = 0;

	UPROPERTY(DisplayName = "Intidżer 2")
	int32 Integer2 = 0;
};

UCLASS(DisplayName = "Klaska")
class ASTROSIM_API UInspectorTestClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(DisplayName = "Intidżer")
	int32 Integer = 0;
};

USTRUCT(DisplayName = "Strukturka")
struct ASTROSIM_API FInspectorTestStruct
{
	GENERATED_BODY()

	UPROPERTY(DisplayName = "Intidżer")
	int32 Integer = 0;

	UPROPERTY(DisplayName = "Tablica")
	TArray<int32> Integers{3, 42, 666};

	UPROPERTY(DisplayName = "Strukturka")
	FInspectorTestInternalStruct InternalStruct;

	UPROPERTY(DisplayName = "Tablica strukturek")
	TArray<FInspectorTestInternalStruct> InternalStructs{{}, {}, {}};

	UPROPERTY(DisplayName = "Wskaźniczek na obiekt typu testowego")
	TObjectPtr<UInspectorTestClass> TestObjectActual = NewObject<UInspectorTestClass>();

	UPROPERTY(DisplayName = "Wskaźniczek na obiekt typu testowego ale UObject")
	TObjectPtr<UObject> TestObjectSuper = NewObject<UInspectorTestClass>();
};


// inspect
SetNextWindowPosAndSizeWithinMainViewport(ImVec2{.6f, .1f}, ImVec2{.3f, .3f}, ImGuiCond_FirstUseEver);

PropertyInspector::Inspect("S", S, this);

PropertyInspector::Inspect("S but const", const_cast<const FInspectorTestStruct&>(S), this);

#endif
