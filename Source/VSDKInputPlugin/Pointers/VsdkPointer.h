// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PointerBase.h"
#include "VsdkPointer.generated.h"

UENUM(BlueprintType)
enum class EPointerType : uint8 {
	Parabolic UMETA(DisplayName = "Parabolic"),
	Line   UMETA(DisplayName = "Linear"),
	None   UMETA(DisplayName = "None")
};

/**
 * Extension of the Pointer base, implements the parabolic (arced) and linear pointer.
 * Allows for dynamic setting of the mesh and material for adjustable look and feel.
 *
 * Written by: Arthur Wollocko (awollocko@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API AVsdkPointer : public APointerBase
{
	GENERATED_BODY()

public:

	AVsdkPointer();

	/** Mesh and Material visuals */
	UPROPERTY()
		TArray<class USplineMeshComponent*> PointerPathMeshPool;
	UPROPERTY(EditDefaultsOnly, Category = "VSDK | Pointer")
		class UStaticMesh* PointerMesh;
	UPROPERTY(EditDefaultsOnly, Category = "VSDK | Pointer")
		class UMaterialInterface* PointerMaterial;
	UPROPERTY(EditAnywhere, Category = "VSDK | Pointer")
		class USplineComponent* PointerSpline;

	/** Decides if this pointer is parabolic or linear. */
	UPROPERTY(EditAnywhere, Category = "VSDK | Pointer")
		EPointerType PointerType = EPointerType::Parabolic;

	/** Parabolic visualization for Pointing -- Private to avoid confusion for users */
	UPROPERTY(VisibleAnywhere, Category = "VSDK | Pointer")
		float ParabolicProjectileRadius;		// For the parabolic curve, the individual projectile point radius along the path. 
	UPROPERTY(VisibleAnywhere, Category = "VSDK | Pointer")
		float ParabolicProjectileSpeed;		// How fast the projectiles come off the controllers for visualization and prediction
	UPROPERTY(VisibleAnywhere, Category = "VSDK | Pointer")
		float ParabolicSimulatioMaxTime;		// The max time taken for this projectile prediction simulation

public:
	virtual void UpdateVisualizationPath(const TArray<FVector> &Path) override;
	virtual void DrawPath(const TArray<FVector> &Path) override;
	virtual bool FindEndLocationAndPath(TArray<FVector> &OutPath, FVector &OutLocation) override;

	virtual void AdjustVisibility(bool bIsVisible) override;

};
