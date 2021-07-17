// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class JageProjectEditorTarget : TargetRules
{
	public JageProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.AddRange( new string[] { "JageProject"
			, "JageNetwork"
			, "JageLoadingScreen"
			, "JageUserInterface"
			, "JageToolUnit"
			, "JageAI"
			, "JageCharacter"
			, "JageMaterial"
			, "JageGameplay"
			, "JageThread"
		});
	}
}
