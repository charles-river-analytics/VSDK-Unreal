// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "InteractionVolume.h"
#include "SnapInteraction.generated.h"

UCLASS(BlueprintType, Blueprintable)
class VSDKINPUTPLUGIN_API USnapInteraction : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	USnapInteraction();


public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		FVector SnapLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		FRotator SnapOrientation;

	/** Events */
	UFUNCTION(BlueprintImplementableEvent, Category = "VSDK | Snap Interaction")
		void OnSnap(AActor* Other);

	void OnSnap_Implementation(AActor* Other);

	UFUNCTION(BlueprintCallable, Category = "VSDK | Snap Interaction")
		virtual void TrySnapActor(AActor* Other);

};
