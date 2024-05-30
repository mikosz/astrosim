// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AstroSim : ModuleRules
{
	public AstroSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "PhysicsCore", "Chaos", "ImGui" });

		PrivateDefinitions.Add("IMPLOT_API=DLLIMPORT");
	}
}