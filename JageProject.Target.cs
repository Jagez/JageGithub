// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class JageProjectTarget : TargetRules
{
	public JageProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("JageProject");
		ExtraModuleNames.Add("JageNetwork");
		ExtraModuleNames.Add("JageLoadingScreen");
		ExtraModuleNames.Add("JageUserInterface");
		ExtraModuleNames.Add("JageToolUnit");
		ExtraModuleNames.Add("JageAI");
		ExtraModuleNames.Add("JageCharacter");
		ExtraModuleNames.Add("JageMaterial");
		ExtraModuleNames.Add("JageGameplay");
		ExtraModuleNames.Add("JageThread");
	}
}
