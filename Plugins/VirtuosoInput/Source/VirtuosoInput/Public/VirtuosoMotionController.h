// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "IMotionController.h"
#include "VirtuosoHandState.h"
#include "VirtuosoMotionController.generated.h"

/* Forward declaration */
namespace VirtuosoInput
{
	class VirtuosoInputDevice;
}

/**
*	Provides motion tracking input to an actor, using the Virtuoso Input System.
*
*	Contributors: Dan Duggan (dduggan@cra.com) Updated: September 2020
*/
UCLASS(Blueprintable, ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VIRTUOSOINPUT_API UVirtuosoMotionController : public UPrimitiveComponent
{
	GENERATED_BODY()

public:

	UVirtuosoMotionController();

	UFUNCTION(BlueprintCallable)
		ETrackingStatus GetTrackingStatus();

	UFUNCTION(BlueprintCallable)
		VirtuosoHandId GetMotionSource();

	UFUNCTION(BlueprintCallable)
		void SetMotionSource(VirtuosoHandId HandId);

protected:

	ETrackingStatus TrackingStatus;

	UPROPERTY(BlueprintReadWrite)
		VirtuosoHandId MotionSource;

	float GetWorldToMetersScalar();

	TSharedPtr<class VirtuosoInput::VirtuosoInputDevice> VirtuosoInputDev;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
