// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_Forest : ModuleRules
{
	public UE_Forest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "EnhancedInput",
         "UMG", "NavigationSystem", "AIModule", "GamePlayTasks" , "Niagara",
          "XRBase", "HeadMountedDisplay"
        });


        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd"
            });
        }


        PrivateDependencyModuleNames.AddRange(new string[] {  });


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PublicIncludePaths.Add("UE_Forest");
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
