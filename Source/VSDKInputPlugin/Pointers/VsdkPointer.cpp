// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VsdkPointer.h"
#include <Kismet/GameplayStaticsTypes.h>
#include <NavigationSystem.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>

AVsdkPointer::AVsdkPointer()
{
	// Projectiles
	ParabolicProjectileRadius = 10.f;
	ParabolicProjectileSpeed = 800.f;
	ParabolicSimulatioMaxTime = 2.f;

	PointerSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PointerPath"));
	PointerSpline->SetupAttachment(GetRootComponent());
}

void AVsdkPointer::UpdateVisualizationPath(const TArray<FVector> &Path)
{
	PointerSpline->ClearSplinePoints(false);
	for (int32 i = 0; i < Path.Num(); ++i)
	{
		FVector LocalPosition = PointerSpline->GetComponentTransform().InverseTransformPosition(Path[i]);
		FSplinePoint SplinePoint(i, LocalPosition, ESplinePointType::Curve);
		PointerSpline->AddPoint(SplinePoint, false);
	}

	PointerSpline->UpdateSpline();
}

void AVsdkPointer::DrawPath(const TArray<FVector> &Path)
{
	UpdateVisualizationPath(Path);

	// Default everything to invis, to make sure if they're not being used they're not visible (e.g., when pointing at a wall instead of the ground)
	for (USplineMeshComponent* SplineMesh : PointerPathMeshPool)
	{
		SplineMesh->SetVisibility(false);
	}


	// Now do the logic around object pool and creating objects
	int32 SegmentNum = Path.Num() - 1;
	for (int32 i = 0; i < SegmentNum; ++i)
	{
		if (PointerPathMeshPool.Num() <= i)
		{
			USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
			SplineMesh->SetMobility(EComponentMobility::Movable);
			SplineMesh->AttachToComponent(PointerSpline, FAttachmentTransformRules::KeepRelativeTransform);
			SplineMesh->SetStaticMesh(PointerMesh);
			SplineMesh->SetMaterial(0, PointerMaterial);
			SplineMesh->RegisterComponent();
			PointerPathMeshPool.Add(SplineMesh);
		}

		// Get the dynamic mesh OUT OF THE POOL. If it doesn't exist, it will create one above ^^
		USplineMeshComponent* SplineMesh = PointerPathMeshPool[i];
		SplineMesh->SetVisibility(true);

		FVector StartPos, StartTan, EndPos, EndTan;
		PointerSpline->GetLocalLocationAndTangentAtSplinePoint(i, StartPos, StartTan);
		PointerSpline->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTan);

		SplineMesh->SetStartAndEnd(StartPos, StartTan, EndPos, EndTan, true);
	}
}

bool AVsdkPointer::FindEndLocationAndPath(TArray<FVector> &OutPath, FVector &OutLocation)
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector Look = GetOwner()->GetActorForwardVector();
	Look = Look.RotateAngleAxis(ForwardDownAngleAdjustment, GetOwner()->GetActorRightVector());
	// Rotate the look vector DOWN, so that we naturally are pointing slightly down. (Ergonomics)
	FVector End = Start + Look + GetOwner()->GetActorForwardVector() * MaxPointerDistance;

	FPredictProjectilePathParams Params(ParabolicProjectileRadius, Start, Look * ParabolicProjectileSpeed, ParabolicSimulatioMaxTime, ECollisionChannel::ECC_Visibility, GetOwner()); // Ignore this target actor
	Params.OverrideGravityZ = 0.f;
	Params.bTraceComplex = true;			// Enable complex collisions to account for potential user failure to set up simple collisions on environment. Consider revising if struggling with performance.
	FPredictProjectilePathResult Result;

	FNavLocation NavLocation;

	bool bHitNavMesh = false;
	if (PointerType == EPointerType::Line)
	{
		FHitResult Hit(ForceInit);
		FCollisionQueryParams CollisionParams;
		// Do a simple line trace, and add the points to the PATH to be visualized via spline
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams);
		OutPath.Add(Start);

		bHitNavMesh = UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(Hit.Location, NavLocation, PointerProjectionExtent);
		// Add end point to the path. IF hit, stop at hit point.
		FVector EndOfLine = (bHitNavMesh) ? NavLocation.Location : End;
		OutPath.Add(End);
	}
	else
	{
		// Do parabolic estimation based on parameters
		bool bDidHit = UGameplayStatics::PredictProjectilePath(this, Params, Result);
		for (FPredictProjectilePathPointData PointData : Result.PathData)
		{
			OutPath.Add(PointData.Location);
		}
		if (!bDidHit)
		{
			return false;
		}

		bHitNavMesh = UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(Result.HitResult.Location, NavLocation, PointerProjectionExtent);
	}

	OutLocation = NavLocation.Location;
	return bHitNavMesh;
}

void AVsdkPointer::AdjustVisibility(bool bIsVisible)
{
	Super::AdjustVisibility(bIsVisible);
	PointerSpline->SetVisibility(bIsVisible, true);
}
