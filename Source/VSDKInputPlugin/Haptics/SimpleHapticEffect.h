// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <VirtuosoInput\Public\VirtuosoHandState.h>
#include "SimpleHapticEffect.generated.h"

/*
	The SimpleHapticEffect can be used as an example for building other haptic effects,
	or simply used to set up a one-off haptic effect.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: November 2020
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API USimpleHapticEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	USimpleHapticEffect();

protected:
	virtual void BeginPlay() override;

	class AVirtuosoHapticsManager* FindHapticsManager();


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHapticFeedbackEffect_Base* HapticPayload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		VirtuosoHandId HapticLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AVirtuosoHapticsManager* HapticsManager;

	UFUNCTION(BlueprintCallable)
		virtual void PlayHaptics();
		
};
