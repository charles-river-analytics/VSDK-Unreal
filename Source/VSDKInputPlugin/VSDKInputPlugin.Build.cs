// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
// Manipulated by Arthur Wollocko (awollocko@cra.com) - Charles River Analytics, 2020

using UnrealBuildTool;

public class VSDKInputPlugin : ModuleRules
{
	public VSDKInputPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "HeadMountedDisplay", "VirtuosoInput" });


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
