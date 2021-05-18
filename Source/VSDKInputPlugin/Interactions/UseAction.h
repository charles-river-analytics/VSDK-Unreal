// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableProperty.h"
#include "UseAction.generated.h"

/**
 * The base class to implement different use behaviors. Implement the TryUse function to set up the
 * use action and TryUnuse to stop the action. Not all uses will need to be stopped if they are 'one-off'.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(BlueprintType, Blueprintable)
class VSDKINPUTPLUGIN_API UUseAction : public UInteractableProperty
{
	GENERATED_BODY()

public:
	UUseAction();

	UPROPERTY()
		UInteractableUse* InteractableUse;

	UFUNCTION(BlueprintCallable, Category = VSDK)
		void SetInteractableUse(UInteractableUse* ActionUse);

	UFUNCTION(BlueprintCallable, Category = VSDK)
		UInteractableUse* GetInteractableUse();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = VSDK)
		void TryUse(AActor* UsingActor);
	virtual void TryUse_Implementation(AActor* UsingActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = VSDK)
		void TryUnuse(AActor* UnusingActor);
	virtual void TryUnuse_Implementation(AActor* UnusingActor);
};
