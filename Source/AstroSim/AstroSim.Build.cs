// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AstroSim : ModuleRules
{
	public AstroSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
