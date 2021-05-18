// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FilterInteractables.generated.h"

UENUM(BlueprintType)
enum EFilterType {
	TAG		UMETA(DisplayName = "Tag")
};

UENUM(BlueprintType)
enum EFilterLevel {
	OVERLAP		UMETA(DisplayName = "Overlap"),
	IGNORE		UMETA(DisplayName = "Ignore")
};

USTRUCT(BlueprintType)
struct FFilterInteractableData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		TEnumAsByte<EFilterLevel> FilterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		TEnumAsByte<EFilterType> FilterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		FName FilterValue;
};

/**
 * TODO
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(Blueprintable, ClassGroup = (VSDK), meta = (BlueprintSpawnableComponent))
class VSDKINPUTPLUGIN_API UFilterInteractables : public UActorComponent
{
	GENERATED_BODY()

private:
	UFUNCTION()
		bool IsValidFilter(AActor* UsingActor, FFilterInteractableData filter);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FFilterInteractableData> FilterForInteractableObjects;

	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		bool IsValidInteractable(AActor* UsingActor);
};
