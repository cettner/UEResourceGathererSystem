// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/ResourceGeneratorInterface.h"

// Add default functionality here for any IResourceGenerator functions that are not pure virtual.

TSubclassOf<UResource> IResourceGeneratorInterface::GetResourceClass() const
{
    return TSubclassOf<UResource>();
}
