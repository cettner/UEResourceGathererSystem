// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDropPoint.h"
#include "DrawDebugHelpers.h"
#include "Components/ShapeComponent.h"

#include "Interfaces/ResourceGatherer.h"


AResourceDropPoint::AResourceDropPoint() : Super()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AResourceDropPoint::OnOverlapBegin);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AResourceDropPoint::OnOverlapEnd);
}

void AResourceDropPoint::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (HasAuthority())
	{
		IResourceGatherer * gatherer = Cast<IResourceGatherer>(OtherActor);
		const UWorld * world = GetWorld();
	}

}

void AResourceDropPoint::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}


void AResourceDropPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AResourceDropPoint::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}
