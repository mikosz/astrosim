// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

using UnrealBuildTool;

public class AstroSimEditorTarget : TargetRules
{
	public AstroSimEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("AstroSim");
	}
}