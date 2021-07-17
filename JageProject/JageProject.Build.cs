// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JageProject : ModuleRules
{
	public JageProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
			, "UMG"
			, "JageUserInterface"
			, "JageNetwork"
			, "JageLoadingScreen"
			, "JageToolUnit"
			, "JageAI"
			, "JageCharacter"
			, "JageMaterial"
			, "JageGameplay"
		});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"MoviePlayer"
			}
			);

	}
}
