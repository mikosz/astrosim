// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

using UnrealBuildTool;

public class AstroSimEditorTarget : TargetRules
{
	public AstroSimEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("AstroSim");
	}
}