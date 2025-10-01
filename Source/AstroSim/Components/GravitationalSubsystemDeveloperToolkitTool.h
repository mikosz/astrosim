// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ImGuiDeveloperToolkit/ImGuiDeveloperToolkitTool.h"
#include "ImGuiDeveloperToolkit/PropertyInspector.h"

#include "GravitationalSubsystemDeveloperToolkitTool.generated.h"

UCLASS()
class ASTROSIM_API UGravitationalSubsystemDeveloperToolkitTool : public UImGuiDeveloperToolkitTool
{
	GENERATED_BODY()
public:
	virtual FAnsiString GetToolName() const override;
	virtual EImGuiDeveloperToolkitToolContext GetContext() const override;
	virtual void Tick(
		float DeltaTime, bool& bInOutShow, EImGuiDeveloperToolkitToolContext Context, UWorld* World) override;

private:
	ImGuiDeveloperToolkit::PropertyInspector::FInspectorSetup InspectorSetup;
};
