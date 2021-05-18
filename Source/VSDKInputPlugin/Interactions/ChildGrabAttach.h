// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GrabAttachment.h"
#include "InteractableGrab.h"
#include "ChildGrabAttach.generated.h"

/**
 * Basic implementation of the GrabAttachment class. This grabbing technique takes the object
 * and makes it a child of the grabbing object. When release, it returns it back to the original
 * parent.
 *
 * Written by: Arthur Wollocko (awollocko@cra.com), 2020
 * Updated by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UChildGrabAttach : public UGrabAttachment
{
	GENERATED_BODY()

public:	
	UChildGrabAttach();

	UPROPERTY(VisibleAnywhere)
		AActor* OriginalParent;

	UPROPERTY(VisibleAnywhere)
		bool bSimulatingPhysics;

	UPROPERTY(VisibleAnywhere)
		UPrimitiveComponent* PhysicsComponent;

	UPROPERTY()
		UInteractableGrab* GrabComponent;

	/** UGrabAttachment Override */
	virtual void TryGrab(AActor* GrabberActor, AActor* PreviousGrabber) override;

	virtual void TryUngrab(AActor* UngrabberActor) override;

	/** UInteractableProperty Override */
	virtual void BeginPlay_Implementation() override;
};
