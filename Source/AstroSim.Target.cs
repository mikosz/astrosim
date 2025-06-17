// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

using UnrealBuildTool;

public class AstroSimTarget : TargetRules
{
	public AstroSimTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("AstroSim");
	}
}