// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ResourceGathererSystem : ModuleRules
{
	public ResourceGathererSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "CoreUObject" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
