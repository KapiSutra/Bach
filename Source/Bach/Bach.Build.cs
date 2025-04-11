// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// ReSharper disable UseCollectionExpression

public class Bach : ModuleRules
{
    public Bach(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                // ... add public include paths required here ...
            }
        );


        PrivateIncludePaths.AddRange(
            new string[]
            {
                // ... add other private include paths required here ...
            }
        );


        PublicDependencyModuleNames.AddRange(
            new[]
            {
                "Core",
                // ... add other public dependencies that you statically link with here ...
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Morzat",
                "EnhancedInput",
                "AnimGraphRuntime",
                "GameplayTags",
                "StateTreeModule",
                "GameplayAbilities",
                "GameplayStateTreeModule",
                "AIModule"
                // ... add private dependencies that you statically link with here ...	
            }
        );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );
    }
}