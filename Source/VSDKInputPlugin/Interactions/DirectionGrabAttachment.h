// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GrabAttachment.h"
#include "Tickable.h"
#include "DirectionGrabAttachment.generated.h"

/**
 * GrabAttachment for a secondary grabs that will make the object's forward direction point in 
 * the direction established between the two grabbers.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API UDirectionGrabAttachment : public UGrabAttachment, public FTickableGameObject
{
	GENERATED_BODY()
	
private:
	bool bReadyToTick = false;

public:
	UDirectionGrabAttachment();

	UPROPERTY()
		AActor* FirstGrabber;

	UPROPERTY()
		AActor* SecondGrabber;

	UPROPERTY()
		FVector InitialGrabOffset;

	/* UGrabAttachment Override */
	virtual void TryGrab(AActor* GrabberActor, AActor* PreviousGrabber) override;

	virtual void TryUngrab(AActor* UngrabberActor) override;

	/* FTickableGameObject Override */
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;
};
