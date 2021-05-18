// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IMotionController.h"
#include "VirtuosoTrackingState.generated.h"

/**
*   Stores the current state of a
*	motion-controlled input device (e.g. controller, tracked hand).
*
*	Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
*/
UCLASS(BlueprintType)
class VIRTUOSOINPUT_API UVirtuosoTrackingState : public UObject
{
public:

	GENERATED_BODY()

	UVirtuosoTrackingState();
	~UVirtuosoTrackingState();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WorldToMetersScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETrackingStatus TrackingStatus;

};
