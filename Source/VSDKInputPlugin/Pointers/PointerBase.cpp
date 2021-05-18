// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "PointerBase.h"
#include "Math/Vector.h"
#include <Components/SceneComponent.h>

APointerBase::APointerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointerProjectionExtent = FVector(100.f);
	ForwardDownAngleAdjustment = 15.f;
	MaxPointerDistance = 1000.f;

	PointerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PointerRoot"));
	SetRootComponent(PointerRoot);
}

void APointerBase::UpdateVisualizationPath(const TArray<FVector> &Path)
{
	// NO OP
}

void APointerBase::DrawPath(const TArray<FVector> &Path)
{
	// NO OP
}

bool APointerBase::FindEndLocationAndPath(TArray<FVector> &OutPath, FVector &OutLocation)
{
	return false;
}

void APointerBase::AdjustVisibility(bool bIsVisible)
{
	// NO OP
}

