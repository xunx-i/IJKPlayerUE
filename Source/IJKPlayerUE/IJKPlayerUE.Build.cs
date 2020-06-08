// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class IJKPlayerUE : ModuleRules
{
	public IJKPlayerUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
        PublicIncludePaths.AddRange(
			new string[] {
                "Runtime/Launch/Public",
                Path.Combine(PluginPath, "Public")
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "IJKPlayerUE/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Json",
                "JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
        if (Target.Platform == UnrealTargetPlatform.Android)
        {

            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "IJKPlayerUE_APL.xml"));
        }
    }
}
