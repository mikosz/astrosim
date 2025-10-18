// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

using UnrealBuildTool;

public class AstroSimTarget : TargetRules
{
	public AstroSimTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("AstroSim");
	}
}