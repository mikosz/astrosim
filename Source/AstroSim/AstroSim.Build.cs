// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

using UnrealBuildTool;

public class AstroSim : ModuleRules
{
	public AstroSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[]
			{ "SafeMath", "SafeMathEditor", "ImGuiDeveloperToolkitSubsystem", "ImGuiDeveloperToolkitWidgets" });

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "PhysicsCore", "Chaos", "ImGui"
		});
	}
}