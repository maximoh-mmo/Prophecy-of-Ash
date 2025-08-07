//
// Copyright 2025 Max Heinze. All Rights Reserved.
//

using UnrealBuildTool;
using System.Collections.Generic;

public class ProphecyOfAshTarget : TargetRules
{
	public ProphecyOfAshTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ProphecyOfAsh" } );
	}
}
