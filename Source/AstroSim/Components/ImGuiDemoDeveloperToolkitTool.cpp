#include "ImGuiDemoDeveloperToolkitTool.h"

#include "imgui.h"

FAnsiString UImGuiDemoDeveloperToolkitTool::GetToolName() const
{
	return "ImGui Demo";
}

EImGuiDeveloperToolkitToolContext UImGuiDemoDeveloperToolkitTool::GetContext() const
{
	return EImGuiDeveloperToolkitToolContext::Editor | EImGuiDeveloperToolkitToolContext::Game;
}

void UImGuiDemoDeveloperToolkitTool::Tick(
	float DeltaTime, bool& bInOutShow, EImGuiDeveloperToolkitToolContext Context, UWorld* World)
{
	if (bInOutShow)
	{
		ImGui::ShowDemoWindow(&bInOutShow);
	}
}
