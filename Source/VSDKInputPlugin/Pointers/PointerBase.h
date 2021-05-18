// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Chaos/Array.h>
#include "Math/Vector.h"
#include "PointerBase.generated.h"

/** 
* Provides the base class type for pointer implementation
* Initial included pointers will be Parabolic and Straight
* 
*/
UCLASS()
class VSDKINPUTPLUGIN_API APointerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointerBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Pointer")
		FVector PointerProjectionExtent;	// How far the pointer can go
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VSDK | Pointer")
		float ForwardDownAngleAdjustment;	// Allow ergonomics accounting for a downward rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Pointer")
		float MaxPointerDistance;

protected:
	UPROPERTY()
		USceneComponent* PointerRoot;

public:	
	virtual void UpdateVisualizationPath(const TArray<FVector> &Path);
	virtual void DrawPath(const TArray<FVector> &Path);
	virtual bool FindEndLocationAndPath(TArray<FVector> &OutPath, FVector &OutLocation);

	virtual void AdjustVisibility(bool bIsVisible);

};
